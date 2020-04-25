/************************************
 * Matthew Franchi                  *
 * CPSC 2310 Spring 20              *
 * Lab Section: 001 (3:30 PM)       *
 * Username: mwfranc                *
 * Instructor: Dr. Yvon Feaster     *
*************************************/


#include "functions.h"

int main()
{
    // initial values
    unsigned C = 0, ACC = 0, Q = 0, M = 0;
    uint8_t bytes = 0;
    // get multiplicand and multiplier, as well as inferred data size
    unsigned * arguments = get_inputs();


    // initialize M and Q from the arguments array
    M = arguments[0];
    Q = arguments[1];
    bytes = arguments[2];

    free(arguments);
    // Step 0 : Print initial registers
    print_initial_registers(&M,&C,&ACC,&Q,&bytes);

    // Steps with multiplication; runs bits times
    for(int n = 1; n <= bytes*8; n ++)
    {
        print_step(&M,&C,&ACC,&Q,&bytes);
    }

    // check result
    check_result(&C,&ACC,&Q,&bytes);
}
