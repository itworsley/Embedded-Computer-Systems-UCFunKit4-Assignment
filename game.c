/* ENCE260 2018 Group assignment
 * Group 211
 * Joshua Smith - jsm160
 * Isaac Worsley -
 * */

/* Module declarations */
#include "system.h"
#include "ledmat.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font5x7_1.h"
#include "ir_uart.h"

/* Define polling rate in Hz.  */
#define LOOP_RATE 300
#define MESSAGE_RATE 10

//int rps(char pChoice, char oChoice)
//{
    //return 0;
//}

void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

int main (void)
{
    /* System init */
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

    char options[4];
    int i = 0;
    options[0] = 'R';
    options[1] = 'P';
    options[2] = 'S';
    options[3] = '\0';
    char character = options[i];


    while (1)
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();

        if (navswitch_push_event_p (NAVSWITCH_NORTH) && i < 2)
            character = options[++i];

        if (navswitch_push_event_p (NAVSWITCH_SOUTH) && i > 0)
            character = options[--i];
        display_character(character);
    }
    return 0;
}
