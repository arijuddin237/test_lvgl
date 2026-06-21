#include "lvgl.h"

void create_racing_dashboard(lv_obj_t *parent) {
    // 1. Set background screen menjadi hitam
    lv_obj_set_style_bg_color(parent, lv_color_hex(0x000000), 0);
    lv_obj_set_style_bg_opa(parent, LV_OPA_COVER, 0);

    // ==========================================
    // SEKSI KIRI: RPM GAUGE (ARC)
    // ==========================================
    
    // Kontainer luar untuk lingkaran biru tipis background (opsional, disimulasikan lewat arc)
    lv_obj_t *rpm_arc = lv_arc_create(parent);
    lv_obj_set_size(rpm_arc, 240, 240);
    lv_obj_align(rpm_arc, LV_ALIGN_LEFT_MID, 20, 0);
    lv_arc_set_rotation(rpm_arc, 135);
    lv_arc_set_bg_angles(rpm_arc, 0, 270);
    lv_arc_set_value(rpm_arc, 70); // Nilai contoh (setara ~4862 RPM)
    
    // Styling Arc (Sesuai gambar: background hitam/putih, value biru)
    lv_obj_set_style_arc_color(rpm_arc, lv_color_hex(0x0000FF), LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(rpm_arc, 25, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(rpm_arc, lv_color_hex(0x111111), LV_PART_MAIN);
    lv_obj_set_style_arc_width(rpm_arc, 5, LV_PART_MAIN);
    lv_obj_remove_style(rpm_arc, NULL, LV_PART_KNOB); // Hilangkan bulatan ujung

    // Teks Label "RPM"
    lv_obj_t *lbl_rpm_title = lv_label_create(rpm_arc);
    lv_label_set_text(lbl_rpm_title, "RPM");
    lv_obj_set_style_text_color(lbl_rpm_title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(lbl_rpm_title, &lv_font_montserrat_18, 0);
    lv_obj_align(lbl_rpm_title, LV_ALIGN_CENTER, 0, -20);

    // Angka RPM "4862"
    lv_obj_t *lbl_rpm_val = lv_label_create(rpm_arc);
    lv_label_set_text(lbl_rpm_val, "4862");
    lv_obj_set_style_text_color(lbl_rpm_val, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(lbl_rpm_val, &lv_font_montserrat_40, 0); // Gunakan font besar
    lv_obj_align(lbl_rpm_val, LV_ALIGN_CENTER, 0, 15);


    // ==========================================
    // SEKSI KANAN: UTAMA (SPEEDOMETER & MAP)
    // ==========================================

    // Container Speedometer (062 km/h)
    lv_obj_t *speed_cont = lv_obj_create(parent);
    lv_obj_set_size(speed_cont, 180, 80);
    lv_obj_align(speed_cont, LV_ALIGN_TOP_RIGHT, -120, 20);
    lv_obj_set_style_bg_color(speed_cont, lv_color_hex(0x000000), 0);
    lv_obj_set_style_border_color(speed_cont, lv_color_hex(0x888888), 0);
    lv_obj_set_style_border_width(speed_cont, 2, 0);
    lv_obj_set_style_radius(speed_cont, 10, 0);
    lv_obj_clear_flag(speed_cont, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *lbl_speed = lv_label_create(speed_cont);
    lv_label_set_text(lbl_speed, "062");
    lv_obj_set_style_text_color(lbl_speed, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(lbl_speed, &lv_font_montserrat_48, 0);
    lv_obj_align(lbl_speed, LV_ALIGN_LEFT_MID, 10, 0);

    lv_obj_t *lbl_gps = lv_label_create(speed_cont);
    lv_label_set_text(lbl_gps, "GPS\nkm/h");
    lv_obj_set_style_text_color(lbl_gps, lv_color_hex(0x00FF00), 0); // Hijau untuk tulisan GPS
    lv_obj_set_style_text_font(lbl_gps, &lv_font_montserrat_14, 0);
    lv_obj_align(lbl_gps, LV_ALIGN_RIGHT_MID, -10, 0);

    // Container Map (Samping Speedometer)
    lv_obj_t *map_cont = lv_obj_create(parent);
    lv_obj_set_size(map_cont, 80, 80);
    lv_obj_align(map_cont, LV_ALIGN_TOP_RIGHT, -20, 20);
    lv_obj_set_style_bg_color(map_cont, lv_color_hex(0xCCCCCC), 0); // Abu-abu terang
    lv_obj_set_style_radius(map_cont, 10, 0);
    lv_obj_clear_flag(map_cont, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *lbl_map_title = lv_label_create(map_cont);
    lv_label_set_text(lbl_map_title, "Map");
    lv_obj_set_style_text_color(lbl_map_title, lv_color_hex(0x777777), 0);
    lv_obj_align(lbl_map_title, LV_ALIGN_TOP_MID, 0, -5);

    lv_obj_t *lbl_map_val = lv_label_create(map_cont);
    lv_label_set_text(lbl_map_val, "2");
    lv_obj_set_style_text_color(lbl_map_val, lv_color_hex(0x000000), 0);
    lv_obj_set_style_text_font(lbl_map_val, &lv_font_montserrat_38, 0);
    lv_obj_align(lbl_map_val, LV_ALIGN_BOTTOM_MID, 0, 5);


    // ==========================================
    // SEKSI BAWAH: INDIKATOR DATA (EOT, TPS, BAT)
    // ==========================================
    
    // Karena indikator 'Gear' dihapus, kolom kanan bawah ini kita geser 
    // agar tampilannya seimbang atau diletakkan sejajar di bawah speedometer.
    int16_t x_offset = -20; 
    int16_t y_start = 115;
    int16_t row_gap = 42;

    // --- BARIS 1: EOT (Menggantikan WAF) ---
    lv_obj_t *eot_cont = lv_obj_create(parent);
    lv_obj_set_size(eot_cont, 240, 34);
    lv_obj_align(eot_cont, LV_ALIGN_TOP_RIGHT, x_offset, y_start);
    lv_obj_set_style_bg_color(eot_cont, lv_color_hex(0x000000), 0);
    lv_obj_set_style_border_color(eot_cont, lv_color_hex(0x666666), 0);
    lv_obj_set_style_border_width(eot_cont, 1, 0);
    lv_obj_set_style_radius(eot_cont, 8, 0);
    lv_obj_clear_flag(eot_cont, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *lbl_eot_title = lv_label_create(eot_cont);
    lv_label_set_text(lbl_eot_title, "EOT");
    lv_obj_set_style_text_color(lbl_eot_title, lv_color_hex(0xAAAAAA), 0);
    lv_obj_align(lbl_eot_title, LV_ALIGN_LEFT_MID, 10, 0);

    lv_obj_t *lbl_eot_val = lv_label_create(eot_cont);
    lv_label_set_text(lbl_eot_val, "75   %");
    lv_obj_set_style_text_color(lbl_eot_val, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(lbl_eot_val, LV_ALIGN_RIGHT_MID, -10, 0);

    // --- BARIS 2: TPS ---
    lv_obj_t *tps_cont = lv_obj_create(parent);
    lv_obj_set_size(tps_cont, 240, 34);
    lv_obj_align(tps_cont, LV_ALIGN_TOP_RIGHT, x_offset, y_start + row_gap);
    lv_obj_set_style_bg_color(tps_cont, lv_color_hex(0x000000), 0);
    lv_obj_set_style_border_color(tps_cont, lv_color_hex(0x666666), 0);
    lv_obj_set_style_border_width(tps_cont, 1, 0);
    lv_obj_set_style_radius(tps_cont, 8, 0);
    lv_obj_clear_flag(tps_cont, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *lbl_tps_title = lv_label_create(tps_cont);
    lv_label_set_text(lbl_tps_title, "TPS");
    lv_obj_set_style_text_color(lbl_tps_title, lv_color_hex(0xAAAAAA), 0);
    lv_obj_align(lbl_tps_title, LV_ALIGN_LEFT_MID, 10, 0);

    lv_obj_t *lbl_tps_val = lv_label_create(tps_cont);
    lv_label_set_text(lbl_tps_val, "15  degree");
    lv_obj_set_style_text_color(lbl_tps_val, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(lbl_tps_val, LV_ALIGN_RIGHT_MID, -10, 0);

    // --- BARIS 3: BAT ---
    lv_obj_t *bat_cont = lv_obj_create(parent);
    lv_obj_set_size(bat_cont, 240, 34);
    lv_obj_align(bat_cont, LV_ALIGN_TOP_RIGHT, x_offset, y_start + (row_gap * 2));
    lv_obj_set_style_bg_color(bat_cont, lv_color_hex(0x000000), 0);
    lv_obj_set_style_border_color(bat_cont, lv_color_hex(0x666666), 0);
    lv_obj_set_style_border_width(bat_cont, 1, 0);
    lv_obj_set_style_radius(bat_cont, 8, 0);
    lv_obj_clear_flag(bat_cont, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *lbl_bat_title = lv_label_create(bat_cont);
    lv_label_set_text(lbl_bat_title, "BAT");
    lv_obj_set_style_text_color(lbl_bat_title, lv_color_hex(0xAAAAAA), 0);
    lv_obj_align(lbl_bat_title, LV_ALIGN_LEFT_MID, 10, 0);

    lv_obj_t *lbl_bat_val = lv_label_create(bat_cont);
    lv_label_set_text(lbl_bat_val, "12.8   %");
    lv_obj_set_style_text_color(lbl_bat_val, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(lbl_bat_val, LV_ALIGN_RIGHT_MID, -10, 0);
}
