Embedded Programming Assignment

Rock, Paper, Scissors

Authors:
Joshua Smith - jsm160@uclive.ac.nz
Isaac Worsley - itw21@uclive.ac.nz

Overview:
Paper Scissors Rock is a simple two-player game programmed using the C language on a UCFunKit4.

Building Program:
 1. Plug in your UCFunKit4 and insure it is mounted to the PC.
 2. Run the terminal in the folder where the game.c and other program files are located.
 3. This can be checked by typing ls into the terminal (ell-s) and pressing enter. Should display:
        game.c  Makefile  README.md  README.txt  results.c  results.h
 4. If you are in the correct directory, type into the terminal the command 'make' (no quotes).
 5. This will produce the necessary files to run the program.
 6. Then type 'make program' (no quotes). This will then run the game.
 
Steps:
 1. Align the two FunKits so the IR transmitters are aligned with the corresponding IR recievers.
 2. Players are able to use the FunKit nav switch to select their choice of Paper (P), Scissors (S) or Rock(R).
 3. They then press the up (North) or down (South) on the nav switch to select their choice.
 4. Then when they press the nav switch button, the LED matrix should display the outcome of the game.
 5. To start the game again, press the nav switch button.
