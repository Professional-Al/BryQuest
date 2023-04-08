#include <nes.h>
#include <joypad.h>
#include <graphics.h>
#include <sound.h>

#define TITLE_SCREEN 0
#define OPTIONS_MENU 1
#define GAME_START 2

void draw_title_screen();
void draw_options_menu();
void handle_input();
void update_options();

uint8_t game_state = TITLE_SCREEN;
uint8_t cursor_position = 0;
uint8_t sound_volume = 1;

int main() {
    set_graphics_mode(PPU_GRAPHICS_MODE);
    set_sound_mode(SOUND_MODE);

    while (1) {
        switch (game_state) {
            case TITLE_SCREEN:
                draw_title_screen();
                break;
            case OPTIONS_MENU:
                draw_options_menu();
                break;
            case GAME_START:
                // Start the game here
                break;
        }
        handle_input();
    }

    return 0;
}

void draw_title_screen() {
    clear_screen();
    draw_string("My NES Game", 10, 6);
    draw_string("Start", 12, 12);
    draw_string("Options", 12, 14);
    draw_char('>', 10, 12 + cursor_position * 2);
}

void draw_options_menu() {
    clear_screen();
    draw_string("Options Menu", 8, 6);
    draw_string("Volume:", 10, 10);
    draw_char('0' + sound_volume, 18, 10);
    draw_string("Back", 12, 14);
    draw_char('>', 10, 10 + cursor_position * 2);
}

void handle_input() {
    uint8_t input = joypad_get_input();

    if (input & JOYPAD_START) {
        if (game_state == TITLE_SCREEN) {
            if (cursor_position == 0) {
                game_state = GAME_START;
            } else {
                game_state = OPTIONS_MENU;
                cursor_position = 0;
            }
        }
    }

    if (input & JOYPAD_UP) {
        if (cursor_position > 0) {
            cursor_position--;
        }
    }

    if (input & JOYPAD_DOWN) {
        if (game_state == TITLE_SCREEN && cursor_position < 1) {
            cursor_position++;
        } else if (game_state == OPTIONS_MENU && cursor_position < 1) {
            cursor_position++;
        }
    }

    if (input & JOYPAD_A) {
        if (game_state == OPTIONS_MENU) {
            update_options();
        }
    }

    if (input & JOYPAD_B) {
        if (game_state == OPTIONS_MENU) {
            game_state = TITLE_SCREEN;
            cursor_position = 1;
        }
    }
}

void update_options() {
    if (cursor_position == 0) {
        sound_volume = (sound_volume + 1) % 10;
        set_volume(sound_volume);
    } else {
        game_state = TITLE_SCREEN;
        cursor_position = 1;
    }
}
