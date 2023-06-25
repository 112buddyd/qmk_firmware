#pragma once

#ifdef OLED_ENABLE
    #include "luna.c"

    static void print_status_narrow(void) {
        oled_set_cursor(0, 0);

        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write("@BASE", false);
                break;
            case 1:
                oled_write("@GAME", false);
                break;
            case 2:
                oled_write("@CTRL", false);
                break;
            case 3:
                oled_write("@FUNC",false);
                break;
            default:
                oled_write("WTF", false);
        }

        oled_set_cursor(0,3);
        oled_write("WPM", false);
        oled_set_cursor(0,4);
        oled_write(get_u8_str(get_current_wpm(), '0'), false);

        // oled_set_cursor(0,6);


        render_luna(0,13);
    }

#endif
