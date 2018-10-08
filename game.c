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

/* Define polling rate in Hz.  */
#define LOOP_RATE 300

//int rps(char pChoice, char oChoice)
//{
	//return 0;
//}

int main (void)
{
	/* System init */
    system_init();
	ledmat_init();
	navswitch_init();
	tinygl_init(LOOP_RATE);
	pacer_init(LOOP_RATE);
	
	tinygl_font_set(&font5x7_1);
	tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
	tinygl_text_dir_set (TINYGL_TEXT_DIR_NORMAL);

	tinygl_text("RPS");
	
    while (1)
    {
	navswitch_update();
	tinygl_update();
	pacer_wait();
    }
    return 0;
}
