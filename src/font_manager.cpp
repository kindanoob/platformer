

#include "config.h"
#include "font_manager.h"


Font_manager::Font_manager() {
    add_resource(Font_name::arial_font, fonts_path + "arial.ttf");
    add_resource(Font_name::ubuntu_font, fonts_path + "ubuntu.ttf");
    add_resource(Font_name::cyrillic_font, fonts_path + "CyrillicOld.ttf");
}
