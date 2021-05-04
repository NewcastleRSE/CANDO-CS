Notes and instructions for running the CANDO Box code in a linux (or other, I
guess!) test environment.

This has been tested for the current trial version on ubuntu linux 18.04.4 LTS
using the gnu gcc compiler.

To compile, cd into the directory containing the files in the command prompt and type:

gcc mainlinux.c -o mainlinux -lm


Differences:

The core scripts have been kept the same as much as possible, with references to
microcontroller libraries and prerequisit scripts all commented out.

The main.c script has been removed and replaced with mainlinux.c, because the
original main script was all interrupts all the time, and I think we need to
find a bit of a workaround to get this running on PC. The aim will be to
establish a similar workflow in mainlinux.c, but it will monitor a file for new
data (triggering an interrupt when new data is found) rather than listening to
an external input from a hardware pin. 

The arm_math.h library was causing issues, being made for arm processors I
suppose, so I have switched it out for <math.h> the standard C maths library.
Due to this, the cos and exp functions were throwing an error in init_kernel()
within the Phase_Shift_Algorithm.c script, because the math.h functions expect a
double type and were being given a float. This has been fixed by changing the
initial declaration of the variables which are established with exp and cos to
type double.

I also had to change the initial declaration of the algorithm phaseShift and GUI
GUIparams to being at the beginning of the Phase_Shift_Algorithm.c script,
rather than in the header file. I believe this is because the compile order for
gcc meant that they were being declared before the Algorithm.h header script had
been read in, causing an undeclared type error.


