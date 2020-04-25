/************************************
 * Matthew Franchi                  *
 * CPSC 2310 Spring 20              *
 * Lab Section: 001 (3:30 PM)       *
 * Username: mwfranc                *
 * Instructor: Dr. Yvon Feaster     *
*************************************/
// GUARDS
#ifndef A2_FUNCTIONS_H
#define A2_FUNCTIONS_H

// INCLUSIONS
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// represents OFF binary digit (0)
#define OFF     0


// int_type struct definition
/* Parameters: bytes - uint8_t holding the number of bytes
 *             type_name - char array of the data type name
 */
typedef struct int_type_struct
{
    uint8_t bytes;
    char* type_name;
}int_type;


// get_inputs function declaration //
/* Parameters: none
 * Return: pointer to integer array of size 2
 *         index 0 : multiplicand
 *         index 1 : multiplier
 * This function gets an unsigned multiplicand and multiplier from user input,
 * assumes a data type from the largest of the two integers, and then
 * checks the range of both integers using said data type and test_valid_range
 */
unsigned * get_inputs();


// get_int_type function declaration
/* Parameters: x - unsigned integer that you want to find the byte size of
 * Return: a instance of struct int_type, representing the smallest data
 *              type that will hold both numbers;
 *              int_type is either uint8_t, uint16_t or uint32_t
 * This function takes an unsigned integer and determines the smallest
 * numeric data type that will hold said integer
 */
int_type get_int_type(unsigned x);


// test_valid_range function declaration//
/* Parameters: n - pointer to a constant long-size integer
 *                      we check the validity of n
 *             quantity - name of the quantity n represents
 *             bytes - pointer to constant 1-byte integer
 *                          bytes determines the upper bound of validity
 * This function takes in a long int n, and determines if it is within
 * the range 0 and 2^(8*bytes)-1.
 */
bool test_valid_range(const long int *n, char* *quantity, const uint8_t *bytes);


// to_binary function declaration //
/* Parameters: x - pointer to an unsigned integer
 *             bytes - number of bytes to print
 * Return: c-string (char array) of binary representation
 * This function takes an unsigned integer and prints it in
 * binary format.
 */
char* to_binary(const unsigned * x, const uint8_t *bytes);


// print_initial_registers function declaration //
/* Parameters: M - unsigned integer representing multiplicand
 *             C - unsigned integer representing carry
 *             ACC- unsigned integer representing accumulator
 *             Q - unsigned integer representing multiplier
 *             bytes - unsigned number of bytes to print out
 *  Return: void
 *  This function takes in all four elements involved in the multiplication
 *  and prints out a formatted output with their name and corresponding
 *  value
 */
void print_initial_registers(const unsigned *M, const unsigned *C,
            const unsigned *ACC,const unsigned *Q,const uint8_t *bytes);


// print_step function declaration //
/* Parameters: M - unsigned integer representing multiplicand
 *             C - unsigned integer representing carry
 *             ACC- unsigned integer representing accumulator
 *             Q - unsigned integer representing multiplier
 *             bytes - unsigned number of bytes to print out
 * Return: void
 * This function prints each step of the multiplication process
 * following format specified in the spec sheet. Arguments are
 * passed by reference so that they are directly modified, rather
 * than having copies
 */
void print_step(unsigned *M, unsigned *C, unsigned *ACC, unsigned*Q,
                const uint8_t *bytes);

// check_result function declaration //
/* Parameters: C - unsigned integer representing carry
 *             ACC- unsigned integer representing accumulator
 *             Q - unsigned integer representing multiplier
 *             bytes - unsigned number of bytes to print out
 * Return: void
 * This function prints a summary report of the multiplication,
 * checking to see that the binary multiplication actually
 * proceeded correctly.
 */
void check_result(unsigned *C, unsigned *ACC, unsigned *Q,
                    const uint8_t *bytes);

#endif //A2_FUNCTIONS_H

