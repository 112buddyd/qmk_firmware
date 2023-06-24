#pragma once

#ifdef OLED_ENABLE
    #include "luna.c"

    static void print_status_narrow(void) {
        oled_set_cursor(0, 1);

        /* Print current layer */
        oled_write("Layer", false);

        oled_set_cursor(0, 2);

        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write("Base ", false);
                break;
            case 1:
                oled_write("Game", false);
                break;
            case 2:
                oled_write("Ctrl ", false);
                break;
            case 3:
                oled_write("Numpd", false);
                break;
            default:
                oled_write("Undef", false);
        }

        oled_set_cursor(0,4);
        oled_write("WPM", false);
        oled_set_cursor(0,5);
        oled_write(get_u8_str(get_current_wpm(), '0'), false);

        render_luna(0,13);
    }

#endif
