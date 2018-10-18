/** ENCE260 2018 Group assignment
    Group 211
    @file results.c
    @author Joshua Smith - jsm160
    @author Isaac Worsley - itw21
    @date 19 Oct 2018
    @brief Module for Paper Scissors rock, which caculates the result of the game.
*/

 
#include "results.h"

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

    while (1) {
        /* If a draw occurs. */
        if (pChoice == oChoice) {
            return draw;
        }

        /* If player chooses rock. */
        else if (pChoice == rock) {
            /* Rock beats scissors. */
            if (oChoice == scissor) {
                return win;
            }
            /* Paper beats rock. */
            else if (oChoice == paper) {
                return lose;
            }
        }

        /* If player chooses paper. */
        else if (pChoice == paper) {
            /* Paper beats rock. */
            if (oChoice == rock) {
                return win;
            }
            /* Scissors beats paper. */
            else if (oChoice == scissor) {
                return lose;
            }
        }

        /* If player chooses scissors. */
        else if (pChoice == scissor) {
            /* Scissors beats paper. */
            if (oChoice == paper) {
                return win;
            }
            /* Rock beats scissors. */
            else if (oChoice == rock) {
                return lose;
            }
        }
    }
}
