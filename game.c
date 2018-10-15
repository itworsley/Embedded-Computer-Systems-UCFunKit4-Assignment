/* ENCE260 2018 Group assignment
 * Group 211
 * Joshua Smith - jsm160
 * Isaac Worsley - itw21
 * */

/* Module declarations. */
#include "system.h"
#include "ledmat.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font5x7_1.h"
#include "ir_uart.h"
#include <stdbool.h>

/* Define polling rate in Hz. */
#define LOOP_RATE 300
#define MESSAGE_RATE 10

static bool isGameOver = 0;

/** Initialise all possible characters to be displayed on the LED matrix
 *  as a result of making a decision about the result of the game */
char rps(char pChoice, char oChoice)
{
    char win = 'W';
    char lose = 'L';
    char draw = 'D';
    char rock = 'R';
    char paper = 'P';
    char scissor = 'S';

    while (1)
    {
        /* If a draw occurs. */
        if (pChoice == oChoice)
        {
            return draw;
        }

        /* If player chooses rock. */
        else if (pChoice == rock) {

            /* Rock beats scissors. */
            if (oChoice == scissor)
            {
                return win;
            }

            /* Paper beats rock. */
            else if (oChoice == paper)
            {
                return lose;
            }
        }

        /* If player chooses paper. */
        else if (pChoice == paper) {

            /* Paper beats rock. */
            if (oChoice == rock)
            {
                return win;
            }

            /* Scissors beats paper. */
            else if (oChoice == scissor)
            {
                return lose;
            }
        }

        /* If player chooses scissors. */
        else if (pChoice == scissor)
        {
            /* Scissors beats paper. */
            if (oChoice == paper)
            {
                return win;
            }

            /* Rock beats scissors. */
            else if (oChoice == rock)
            {
                return lose;
            }
        }
    }
}
/** Displays the text on the LED matrix. */
void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

/** Initialise the FunKit4 hardware and the tinygl module to display text. */
void game_init (void)
{
    system_init();
    ledmat_init();
    navswitch_init();
    tinygl_init(LOOP_RATE);
    pacer_init(LOOP_RATE);
    ir_uart_init();

    tinygl_font_set(&font5x7_1);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_NORMAL);
    tinygl_text_speed_set(MESSAGE_RATE);
}

int main (void)
{
    game_init();
    pacer_wait ();
    tinygl_update ();
    char options[4];
    int i = 0;
    options[0] = 'R';
    options[1] = 'P';
    options[2] = 'S';
    options[3] = '\0';
    char wait = '-';
    char character = options[i];
    char pChoice = '\0';
    //char oChoice = '\0';
    char oChoice;
    char recieved = 0;
    char sent = 0;
    char ready = 0;

    pacer_wait ();

    display_character(character);

    while (1)
    {

        navswitch_update ();
        tinygl_update ();
        if(!ready) {
            if (navswitch_push_event_p (NAVSWITCH_NORTH) && i < 2) {
                character = options[++i];
            }
            if (navswitch_push_event_p (NAVSWITCH_SOUTH) && i > 0) {
                character = options[--i];
            }
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                pChoice = character;
                tinygl_clear();
                ready = 1;
            }
            display_character(character);
        }

        else {
            ir_uart_putc(pChoice);
            sent = 1;
        }

        if (!recieved) {
            if (ir_uart_read_ready_p()) {
                oChoice = ir_uart_getc();
                recieved = 1;
            }
        }

        if (sent && !recieved) {
            display_character(wait);
        }

        if(sent && recieved) {
            character = rps(pChoice, oChoice);
            display_character (character);

            /* Reset the game */
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                sent = 0;
                recieved = 0;
                ready = 0;
                display_character('R');
            }
        }

        tinygl_update();
    }
    return 0;
}
