/* ENCE260 2018 Group assignment
 * Group 211
 * Joshua Smith - jsm160
 * Isaac Worsley - itw21
 * 16/10/18
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


/* Initialise all possible characters to be displayed on the LED matrix,
 * determines result of the game. */
char getResult(char pChoice, char oChoice)
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

    /* Initialise tinygl module. */
    tinygl_init(LOOP_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
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
            }
            if (navswitch_push_event_p (NAVSWITCH_SOUTH) && i > 0) {
                character = options[--i];
            }
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                pChoice = character;
                tinygl_clear();
                ready = 1;
            }
            displayCharacter(character);
        }

        /* Transmit symbol if player has chosen one. */
        else {
            ir_uart_putc_nocheck(pChoice);
            sent = 1;
        }

        /* No symbol has been recieved. */
        if (!received) {
            if (ir_uart_read_ready_p()) {
                tempSym = ir_uart_getc();
                /* Check if recieved symbol is valid */
                if(tempSym == 'R' || tempSym == 'P' || tempSym == 'S')
                {
                    oChoice = tempSym;
                    received = 1;
                }
                else {
                    displayCharacter(wait);
                }
            }
        }

        /* Symbol has been sent, but none recieved. Display a hyphen. */
        if (sent && !received) {
            displayCharacter(wait);
        }

        /* If sent symbol and recieved symbol. */
        if(sent && received) {
            /* Determine the outcome of the game. */
            character = getResult(pChoice, oChoice);
            displayCharacter (character);

            /* Set reduntant options, so IR doesn't continue transmitting valid text. */
            pChoice = 'X';
            oChoice = 'X';
            //ir_uart_putc(pChoice);

            navswitch_update();

            /* Reset the game. */
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
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
