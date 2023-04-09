#include <stdio.h>
#include <stdbool.h>

typedef enum {
    START_GAME,
    LOAD_GAME,
    OPTIONS,
    EXIT,
    MENU_OPTIONS_COUNT
} MenuOption;

void display_start_menu();
MenuOption get_user_choice();

int main() {
    bool exit_game = false;
    
    while (!exit_game) {
        display_start_menu();
        MenuOption choice = get_user_choice();
        
        switch (choice) {
            case START_GAME:
                printf("Starting new game...\n");
                // TODO: Implement game logic
                break;
            case LOAD_GAME:
                printf("Loading game...\n");
                // TODO: Implement load game logic
                break;
            case OPTIONS:
                printf("Showing options...\n");
                // TODO: Implement options logic
                break;
            case EXIT:
                printf("Exiting game...\n");
                exit_game = true;
                break;
            default:
                printf("Invalid option, please try again.\n");
        }
    }

    return 0;
}

void display_start_menu() {
    printf("\n=== 2D RPG GAME ===\n");
    printf("1. Start Game\n");
    printf("2. Load Game\n");
    printf("3. Options\n");
    printf("4. Exit\n");
    printf("Please choose an option: ");
}

MenuOption get_user_choice() {
    int choice;
    scanf("%d", &choice);

    return (MenuOption)(choice - 1);
}
