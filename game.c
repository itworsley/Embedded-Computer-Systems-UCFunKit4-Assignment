/** ENCE260 2018 Group assignment
    Group 211
    @file game.c
    @author Joshua Smith - jsm160
    @author Isaac Worsley - itw21
    @date 19 Oct 2018
    @brief Paper Scissors Rock is a simple two-player game programmed using the C language on a UCFunKit4.
*/


/* Module declarations. */
#include "system.h"
#include "ledmat.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pacer.h"
#include "timer.h"
#include "../fonts/font5x7_1.h"
#include "ir_uart.h"
#include "results.h"

/* Define polling rate in Hz. */
#define LOOP_RATE 300
#define MESSAGE_RATE 20


/* Displays the given text (character) on the LED matrix. */
void displayCharacter (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

/* Initialise the FunKit4 hardware and the tinygl module used to display text. */
void gameInit (void)
{
    /* Initialise FunKit. */
    system_init();
    ledmat_init();
    navswitch_init();
    pacer_init(LOOP_RATE);
    ir_uart_init();
    timer_init();

    /* Initialise tinygl module. */
    tinygl_init(LOOP_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_NORMAL);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_update ();
}

/* Main function of program. */
int main (void)
{
    gameInit();

    /* Initialise a list of possible game choices. */
    char options[4];
    int i = 0;
    options[0] = 'R';
    options[1] = 'P';
    options[2] = 'S';
    options[3] = '\0';

    /* Displayed if waiting for character. */
    char wait = '-';

    /* Initialise helper variables. */
    char character = options[i];
    char pChoice = '\0';
    char oChoice = '\0';
    char received = 0;
    char sent = 0;
    char ready = 0;
    char tempSym;
    char result;
    int text = 0;

    pacer_wait ();

    /* Begin infinite loop. */
    while (1)
    {
        /* Player has not chosen a symbol to transmit yet. */
        if(!ready) {
            navswitch_update ();
            tinygl_update ();
            if (navswitch_push_event_p (NAVSWITCH_NORTH) && i < 2) {
                character = options[++i];
            } if (navswitch_push_event_p (NAVSWITCH_SOUTH) && i > 0) {
                character = options[--i];
            } if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                pChoice = character;
                tinygl_clear();
                ready = 1;
            }
            displayCharacter(character);
        }

        /* Transmit symbol if player has chosen one. */
        else {
            ir_uart_putc(pChoice);
            sent = 1;
        }

        /* No symbol has been received. */
        if (!received) {
            if (ir_uart_read_ready_p()) {
                 //timer_wait(8000);
                tempSym = ir_uart_getc();
                /* Check if recieved symbol is valid */
                if(tempSym == 'R' || tempSym == 'P' || tempSym == 'S') {
                    oChoice = tempSym;
                    received = 1;
                }
            }
        }

        /* Symbol has been sent, but none received. Display a hyphen. */
        if (sent && !received) {
            displayCharacter(wait);
        }

        /* If sent symbol and received symbol. Process result of game. */
        if(sent && received) {
            /* Determine the outcome of the game. */
            result = getResult(pChoice, oChoice);

            if (result == 'W') {
                if (!text) {
                    tinygl_text("WINNER");
                    text = 1;
                }
            } else if (result == 'L') {
                if (!text) {
                    tinygl_text("LOSER");
                    text = 1;
                }
            } else if (result == 'D') {
                if (!text) {
                    tinygl_text("DRAW");
                    text = 1;
                }
            }

            navswitch_update();

            /* Reset the game. */
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                oChoice = 'X';
                pChoice = 'Y';
                text = 0;
                sent = 0;
                received = 0;
                ready = 0;
                i = 0;
                tinygl_clear();
                character = options[i];
                displayCharacter(character);
            }
        }

        tinygl_update();
    }
    return 0;
}
