/************************************
 * Matthew Franchi                  *
 * CPSC 2310 Spring 20              *
 * Lab Section: 001 (3:30 PM)       *
 * Username: mwfranc                *
 * Instructor: Dr. Yvon Feaster     *
*************************************/


#include "functions.h"


int_type get_int_type(unsigned x)
{
    // parallel arrays of the available type names and their corresponding
    // bit size
    char* type_names[] = {"uint8_t","uint16_t","uint32_t"};
    int bytes[] = {1,2,4};

    // counter for the number of bytes in x
    int x_bytes = 0;
    // initially, calculate the number of bits
    while(x > 0)
    {
        x/=2;
        x_bytes++;
    }
    // divide x_bytes by 8.0 to get a double representing the bit size
    // take the ceiling of this to round up and get the actual bit size
    x_bytes = ceil(x_bytes/8.0);

    // nested ternary operator to get the appropriate index for the parallel
    // arrays above
    uint8_t type_index = x_bytes == 1 ? 0 : x_bytes == 2 ? 1 : 2;

    // declare an instance of struct int_type
    int_type integer;

    // get the number of bytes, type name from parallel arrays
    integer.bytes = bytes[type_index];
    integer.type_name=type_names[type_index];

    // return the filled-in struct
    return integer;
}

unsigned * get_inputs()
{
    // args is initially of size long, to accomodate overflow errors
    // dynamically initialize args
    long int *args = (long *) malloc(2 * sizeof(long int));

    // assume size unsigned, as this is the maximum size the prog works with
    uint8_t bytes = 4;

    // array of quantity names
    char *arg_names[] = {"multiplicand", "multiplier"};

    // process the multiplicand and multiplier until in range
    do
    {
        printf("Enter a positive integer multiplicand: ");
        scanf("%ld", &args[0]);
    } while (!test_valid_range(&args[0], &arg_names[0], &bytes));

    do
    {
        printf("Enter a positive integer multiplier: ");
        scanf("%ld", &args[1]);
    } while (!test_valid_range(&args[1], &arg_names[1], &bytes));

    // determine the maximum of the multiplier and multiplicand
    unsigned max_idx = args[0] > args[1] ? 0 : 1;

    // get the matching integer data type
    int_type type = get_int_type(args[max_idx]);
    bytes = type.bytes;
    // inform the user of the assumed data type
    printf("\nData type of %s inferred from size of %s (%lu).\n", type.type_name,
           arg_names[max_idx], args[max_idx]);

    // create a new array to hold M, Q, and byte size
    unsigned *final_args = (unsigned *) malloc(3 * sizeof(unsigned));

    // index 0 is M, index 1 is Q, index 2 is bytes
    final_args[0] = args[0];
    final_args[1] = args[1];
    final_args[2] = bytes;

    // free the first args array, no longer needed
    free(args);

    return final_args;
}

char* to_binary(const unsigned *x, const uint8_t *bytes){

    uint8_t bits = *bytes*8;

    // MASK is dependent on the macro bits, equal to 2^bits/2
    unsigned MASK = pow(2,bits)/2;


    // b_string: dynamically allocated string to contain binary
    // representation; dependent on bits
    char* b_string = malloc(sizeof(char)*(bits+1));

    // For loop to iterate through each bit of x, using MASK
    for(int n = 0; n < bits; n++){
        // Check the result of x & MASK to give the value of each bit
        if((*x & MASK) == OFF){
            b_string[n] = '0';
        }
        else{
            b_string[n] = '1';
        }
        // bitwise shift MASK one bit, iterates to next bit
        MASK = MASK >> 1;
    }

    // insert null character at the end of the string to properly terminate
    b_string[bits] = '\0';

    return b_string;
}

bool test_valid_range(const long int *n, char* *quantity, const uint8_t *bytes)
{
    // get max_bound from data type ranges found in limits.h
    unsigned MAX_BOUNDS[3] = {UINT8_MAX,UINT16_MAX,UINT32_MAX};
    // round bytes*.75 -> 1 byte = uint8; 2 bytes = uint16; 4 bytes = uint32
    unsigned max_bound = MAX_BOUNDS[(int)round(*bytes*.75)];

    // CASE I : value is in range
    if(0 <= *n && *n <= max_bound)
    {
        return true;
    }
    // CASE II: value is out of range
    else
    {
        printf("%s is out of bounds. Please enter it again. \n",*quantity);
        return false;
    }

}

void print_initial_registers(const unsigned *M, const unsigned *C,
        const unsigned *ACC,const unsigned *Q, const uint8_t *bytes)
{
    // make strings of the binary values for M and Q
    char *M_binary = to_binary(M,bytes), *Q_binary = to_binary(Q,bytes);

    // formatted output according to spec sheet
    // step number is offset with two tabs
    printf("\nM = multiplicand = %u (User specified)\n"
           "Q = multiplier = %u (User specified)\n"
           "C = carry = 0\n"
           "ACC = accumulator = 0\n\n",*M,*Q);
    printf("STEP 0 \t\tInitialize the data"
           " M = %s (%u)"
           " C = %u"
           " ACC = %u"
           " Q = %s (%u)\n\n"
           ,M_binary,*M,*C,*ACC,Q_binary,*Q);

    // free the memory occupied by strings, as they are no longer needed
    free(M_binary); free(Q_binary);
}

void print_step(unsigned *M, unsigned *C, unsigned *ACC, unsigned*Q,
                const uint8_t *bytes)
{
    // static step_number, value is kept in between function runs
    static uint8_t step_number = 1;
    uint8_t bits = *bytes * 8;

    // strings of common messages
    // storing as string allows for padding within printf
    char add_message[] = "lsb = 1 add M to the ACC";
    char noadd_message[] = "lsb = 0 no add to the ACC";
    char shift_message[] = "Shift >> 1";
    char line_break[] = \
    "------------------------------------------------------------------------";

    char *M_binary, *ACC_binary, *Q_binary;

    // header
    printf("STEP %u\t\tC\t%*s\t%*s\n",step_number,bits,"ACC",bits,"Q");

    // dynamic strings for binary values
    ACC_binary = to_binary(ACC,bytes); Q_binary = to_binary(Q,bytes);

    // initial values
    // three tabs to account for step number

    printf("\t\t\t%u\t%s\t%s\n",*C,ACC_binary,Q_binary);

    // free occupied memory
    free(ACC_binary);
    free(Q_binary);

    // lsb line
    // CASE I : lsb = 1
    if((*Q%2) != 0)
    {
        M_binary = to_binary(M,bytes);

        printf("\t\t\t+\t%s\t%*s\n",M_binary,
                (unsigned)(strlen(add_message)+bits+1),add_message);
        free(M_binary);

        // if addition of ACC and M will cause overflow, then set the carry to 1
        if(*ACC + *M > pow(2,*bytes*8)-1)
        {
            *C = 1;
        }
        // accumulate
        *ACC += *M;
    }
    // CASE II: lsb = 0
    else
    {
        printf("\t\t\t+\t%0*d\t%*s\n",bits,0,
                (unsigned)(strlen(noadd_message)+bits+1),noadd_message);
    }

    // line break
    // the . in the printf truncates line_break to length bits*2+4 (4 for \t)
    printf("\t\t\t\t%.*s\n",bits*2+4,line_break);

    // after accumulation line
    ACC_binary = to_binary(ACC,bytes);
    Q_binary = to_binary(Q,bytes);

    printf("\t\t\t%u\t%s\t%s\n",*C,ACC_binary,Q_binary);

    free(ACC_binary);
    free(Q_binary);

    // shift message line
    printf("\t\t\t\t%*s\n",
            (unsigned)(bits*2+5+strlen(shift_message)),shift_message);

    // calculating shift
    // right-shift Q by 1
    *Q = *Q >> 1;
    // if lsb of ACC is 1, then make msb of Q 1
    *Q = *ACC%2 != 0 ? *Q + pow(2,bits-1) : *Q;

    // right shift ACC by 1
    *ACC = *ACC >> 1;

    // if carry is one, set it equal to 0
    if(*C == 1)
    {
        *C = 0;
    }

    // print final result
    ACC_binary = to_binary(ACC,bytes);
    Q_binary = to_binary(Q,bytes);

    printf("\t\t\t%u\t%s\t%s\n\n\n",*C,ACC_binary,Q_binary);

    free(ACC_binary);
    free(Q_binary);

    // increment step number
    step_number ++;

}

void check_result(unsigned *C, unsigned *ACC, unsigned *Q,const uint8_t *bytes)
{
    // calculate the result by left shifting ACC by number of bits
    // and adding Q to it
    // ACC_extended handles the uint32_bit case, so that ACC << 32
    // is not overflow behavior
    const unsigned long ACC_extended = *ACC;
    unsigned long result = (ACC_extended << *bytes*8) + *Q;
    const unsigned M = result / *Q;

    char *ACC_binary = to_binary(ACC,bytes), *Q_binary = to_binary(Q,bytes);
    char *M_binary = to_binary(&M,bytes);

    // formatted output
    printf("FINAL RESULT: \n Decimal: %lu \n Binary:  %s%s\n",
            result,ACC_binary,Q_binary);

    free(ACC_binary); free(Q_binary);

    // counter to keep track of power of 2
    long power_of_2 = 1;

    // expansion table, uses string padding to show each binary digit
    printf("EXPANSION: \n");
    printf("| Pos | 1/0 | x |     Power of 2     |       Result       |\n");
    for(int n = 1; n <= *bytes*2*8; n++)
    {
        printf("|%5u|%5lu| x |%-20lu|%20lu|\n",n,result%2,power_of_2,
                power_of_2*(result%2));
        result = result >> 1;
        power_of_2 *= 2;
    }
}