/** ENCE260 2018 Group assignment
    Group 211
    @file results.h
    @author Joshua Smith - jsm160
    @author Isaac Worsley - itw21
    @date 19 Oct 2018
    @brief Module for Paper Scissors rock, which caculates the result of the game.
  */
  
#ifndef RESULTS_H
#define RESULTS_H

#include "system.h"

/* Initialise all possible characters to be displayed on the LED matrix,
 * determines result of the game. */
char getResult(char pChoice, char oChoice);

#endif
