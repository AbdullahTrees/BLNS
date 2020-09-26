/**
	Brihodakar(Gigantic) Large Number System: Implementation for 100-digit numbers. (designed to be easily extendable)
	Made by AbdullahTrees, 2020

**/

#pragma warning(disable : 4996)  // This library is compatible with MS-DOS/Turbo C++ and hence needs to use old POSIX functions.

#ifndef _BRIHODAKAR_    // Declaration of BLNS ONLY IF it wasn't defined before.

    #define _BRIHODAKAR_     // This marks the beginning of the Brihodakar Large Number System Header/Library. Use this name to test presence of the BLNS in a sample source code.

// Standard Library prerequisites
#include <stdio.h>
#include <conio.h>

// Special constant definitions
#ifndef max_num_size
    #define max_num_size 100
#endif // max_num_size safety check



// LOWER LEVEL FUNCTIONS: Use these directly only when necessary
void display_num(const char brihodakar[]);											    //  BLNS: Displays the relevant Brihodakar number stored in array
void display_array(const char brihodakar[]);                                            //  BLNS: Displays the entire Brihodakar array in human-readable format
void input_to_array(char brihodakar[], int numsize);									//  BLNS: Regulated input segment (numsize allows for custom input size)
void array_management(char brihodakar[], int option);									//  BLNS: Multi-purpose array management function
																						/*          Option 1: Input/Unorganized data -> Standard Brihodakar array
																									Option 2: Standard Brihodakar array -> Big-endian converted Brihodakar array for operations
																						*/
void copy_array(char destination[], const char source[]);									//  BLNS: Copies the source array into the destination array
void add_array(const char conv_array1[], const char conv_array2[], char answer[]);          //  BLNS: Adds two big-endian converted Brihodakar arrays, brihodakar1 and brihodakar2
void subtract_array(const char conv_array1[], const char conv_array2[], char answer[]);     //  BLNS: Subtracts two big-endian converted Brihodakar arrays, conv_array1 MINUS conv_array2. ORDER MATTERS
void reset_array(char brihodakar[]);                                                        //  BLNS: Empties the entire Brihodakar array by writing zeroes... Equivalent to newly initializing a Brihodakar array

// HIGHER LEVEL FUNCTIONS: Consisting of use of multiple other functions. Much easier to use.
void add_bri_num(char brihodakar1[], char brihodakar2[], char answer[]);
void subtract_bri_num(char brihodakar1[], char brihodakar2[], char answer[]);




void display_num(const char brihodakar[])
{
	// DEPRECATED LOW-PERF Printer
	/*int m;
	for (m=0; brihodakar[m] != 'A'; m++)
	{
	printf("%d", brihodakar[m]);
	}
	//printf("%c", brihodakar[m]); // uncomment to display terminating character.
	return;
	*/

	int m;
	char tempstore[max_num_size + 5] = "";
	copy_array(tempstore, brihodakar);

	array_management(tempstore, 1); // So we see just the number and not all the zeroes from the Big-Endian conversion...

	for (m = 0; tempstore[m] != 'A' && tempstore[m] != 'S'; m++)
		tempstore[m] = tempstore[m] + '0';

    if (tempstore[m] == 'S')
        printf("-");

	#ifndef DEBUG		/* Write `#define DEBUG` to see the terminating character A*/
		tempstore[m] = '\0';
    #else
        tempstore[m+1] = '\0';
    #endif

	printf(tempstore);
	return;
}


void display_array(const char brihodakar[])
{
	int m;
	char tempstore[max_num_size + 5] = "";
	copy_array(tempstore, brihodakar);

	#ifdef DEBUG
        #define da_condition (m < max_num_size)         // condition when debug active
	#else
        #define da_condition (tempstore[m] != 'A' && tempstore[m] != 'S')      // condition when debug inactive
    #endif
	for (m = 0; da_condition; m++) // Simply, the for loop's condition changes depending on DEBUG state.
	{
		tempstore[m] = tempstore[m] + '0';
	}
    #undef da_condition

    if (tempstore[m] == 'S')
        printf("(NEGATIVE)");

	#ifndef DEBUG		/* Write `#define DEBUG` to see the terminating character A*/
		tempstore[m] = '\0';
    #else
        tempstore[m+1] = '\0';
    #endif

	printf(tempstore);
	return;
}


void input_to_array(char brihodakar[], int numsize)
{
	char in;
	int i;

	reset_array(brihodakar);

	input:
	for (i = 0; i<numsize; i++)
	{
		in = getch();

		if (in >= '0' && in <= '9')
		{
			brihodakar[i] = in - '0';
			if (i == numsize - 1)
				brihodakar[i + 1] = 'A';
			printf("%c", in);
		}
		else
		{
			if (in == '\r')
			{
				brihodakar[i] = 'A'; // Terminating character, use this to test
				printf("\n");
				break;
			}
			if (in == '.')
			{
				printf("\nSorry, Brihodakar is for integers only... Please try again\nPlease enter the number: ");
				goto input;
			}
			if (in == '\b')
			{
				if (i == 0)
				{
					i--;
					continue;
				}
				else
					i = i - 2;
				printf("\b \b");
				continue;
			}

			printf("   Illegitimate input, please enter numbers only, try again\nPlease enter the number: ");
			// gotophobes... Explain how you can restart the whole input sequence without goto...
			// Oh yeah, and it has to be intuitive and simple. The goto here isn't blowing up the program, so pls stop whining
			goto input;
		}
	}

	array_management(brihodakar, 1);
	return;
}

void array_management(char brihodakar[], int option)
{
	int i;

	switch (option)
	{
        case 1: //  SHIFT LEFT FULLY: Input --> Standard Brihodakar array
        {
            if (!(brihodakar[0] == 0 && (brihodakar[1] == 'A' || brihodakar[1] == 'S')))            // remove all leading zeroes before number
            {                                   /// final, should be perfect,... (no it isn't lol, add a termination check pls)
                while (brihodakar[0] == 0)     // Move every element one space forward IF there is a zero in front of it
                {
                    int k;
                    for (k = 0; k<max_num_size; k++)
                        brihodakar[k] = brihodakar[k + 1];
                }

            // This operation can cause a large string of zeroes in brihodakar[] to turn into a null array. So, just in case
                if (brihodakar[0] == 'A' || brihodakar[0] == 'S') // Turns a null array into an array of 0.
                {
                    reset_array(brihodakar);
                    brihodakar[1] = 'A';
                }
            }
        }
        break;
        case 2: // SHIFT RIGHT FULLY: Standard Brihodakar array --> Big-Endian Brihodakar array for operations
        {
            // TERMINATION CHECK
            {
                int is_terminated = 0, i, j;
                for (i=0, j = max_num_size; i < (max_num_size+5)/2 && j > 0; i++, j--)
                {
                    if (brihodakar[i] == 'A' || brihodakar[j] == 'A' || brihodakar[i] == 'S' || brihodakar[j] == 'S')
                    {
                        is_terminated = 1;
                        break;
                    }
                }

                if (is_terminated == 0)
                {
                    #ifdef DEBUG
                    printf("\n--DEBUG: Array was unterminated!! Resetting to zero array...\n");
                    #endif
                    reset_array(brihodakar);
                    brihodakar[1] = 'A';
                }
            }

            while (brihodakar[max_num_size] != 'A' && brihodakar[max_num_size] != 'S')
            {
                int k;
                for (k = max_num_size; k > 0; k--)
                {
                    brihodakar[k] = brihodakar[k - 1];
                    if (k == 1)
                        brihodakar[0] = 0;
                }
            }
        }
        break;
	}
	return;
}


void copy_array(char destination[], const char source[]) // FINAL
{
	int i = 0;
	while (i < max_num_size + 5)    /// final, should be safe now that `while` is no longer infinite
	{
		destination[i] = source[i];
		if (destination[i] == 'A' || destination[i] == 'S')
			return;
		i++;
	}
	printf("\n--ERROR: Source array is unterminated!!!\n");
	return;
}

void add_array(const char conv_array1[], const char conv_array2[], char answer[])
{
	int i;

	// Test big-endianess of arrays
	#define conv_array1_notterminated (conv_array1[max_num_size] != 'A' && conv_array1[max_num_size] != 'S')
	#define conv_array2_notterminated (conv_array2[max_num_size] != 'A' && conv_array2[max_num_size] != 'S')
	#define answer_notterminated (answer[max_num_size] != 'A' && answer[max_num_size] != 'S')

	if (conv_array1_notterminated || conv_array2_notterminated || answer_notterminated)  // Testing whether arrays are Big-Endian or not... WE WANT THIS TO BE 0!!
	{
		printf("\n--DEBUG: Addition failed: Improper array configuration. Please initialize/set arrays properly and try again\n");
	}
	else
	{
		char temp_array1[max_num_size + 5] = "";
		copy_array(temp_array1, conv_array1); // this allows us to add carries to conv_array1, since the original value of conv_array1 is now preserved.

		for (i = max_num_size - 1; i >= 0; i--)
		{
			int digitholder;

			digitholder = temp_array1[i] + conv_array2[i]; // conv_array1 IS temp_array1!!!!

			if (digitholder > 9) //  Carrying branch
			{
				digitholder = digitholder - 10;
				answer[i] = digitholder;   // The answer array that holds the computation, it must be initialized to Big-Endian 0 array first.
				if (i > 0)
					temp_array1[i - 1] = temp_array1[i - 1] + 1;
				else
					printf("\nWARNING!!!! OVERFLOW!!! THE ANSWER MAY BE WRONG\n");
			}
			else
				answer[i] = digitholder;
		}
	}
	#undef conv_array1_notterminated
	#undef conv_array2_notterminated
	#undef answer_notterminated

	return;
}


void subtract_array(const char conv_array1[], const char conv_array2[], char answer[])
{
	int i;

	// Test big-endianess of arrays
	#define conv_array1_notterminated (conv_array1[max_num_size] != 'A' && conv_array1[max_num_size] != 'S')
	#define conv_array2_notterminated (conv_array2[max_num_size] != 'A' && conv_array2[max_num_size] != 'S')
	#define answer_notterminated (answer[max_num_size] != 'A' && answer[max_num_size] != 'S')

	if (conv_array1_notterminated || conv_array2_notterminated || answer_notterminated)  // Testing whether arrays are Big-Endian or not... WE WANT THIS TO BE 0!!
	{
		printf("\n--DEBUG: Subtraction failed: Improper array configuration. Please initialize/set arrays properly and try again\n");
	}
	else
	{
		char temp_array1[max_num_size + 5] = "";
		copy_array(temp_array1, conv_array1); // this allows us to subtract carries to conv_array1, since the original value of conv_array1 is now preserved.

		for (i = max_num_size - 1; i >= 0; i--)
		{
			signed int digitholder;

			digitholder = temp_array1[i] - conv_array2[i]; // conv_array1 IS temp_array1!!!!

			if (digitholder < 0) //  Carrying branch
			{
				digitholder = digitholder + 10;
				answer[i] = digitholder;   // The answer array that holds the computation, it must be initialized to Big-Endian 0 array first.
				if (i > 0)
					temp_array1[i - 1] = temp_array1[i - 1] - 1;
				else
					printf("\nWARNING!!!! OVERFLOW!!! THE ANSWER MAY BE WRONG\n");
			}
			else
				answer[i] = digitholder;
		}
	}
	#undef conv_array1_notterminated
	#undef conv_array2_notterminated
	#undef answer_notterminated

	return;
}


void reset_array(char brihodakar[])
{
    int i;
    for(i=0; i < max_num_size+5; i++)
        brihodakar[i] = 0;

    return;
}



/*
    HIGHER LEVEL FUNCTIONS
*/



void add_bri_num(char brihodakar1[], char brihodakar2[], char answer[])
{
    array_management(brihodakar1, 2);
    array_management(brihodakar2, 2);
    array_management(answer, 2);

    add_array(brihodakar1, brihodakar2, answer);

    return;
}

void subtract_bri_num(char brihodakar1[], char brihodakar2[], char answer[])
{
    array_management(brihodakar1, 2);
    array_management(brihodakar2, 2);
    array_management(answer, 2);

    subtract_array(brihodakar1, brihodakar2, answer);

    return;
}


#endif         // BLNS Ends
