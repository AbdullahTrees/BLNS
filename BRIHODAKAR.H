/**
	Brihodakar(Gigantic) Large Number System: Implementation for 100-digit numbers. (designed to be easily extendable)
	Made by AbdullahTrees, 2020

**/
#include <stdio.h>
#include <conio.h>

#define _BRIHODAKAR_

#ifndef max_num_size

    #define max_num_size 100

#endif // max_num_size safety check


#ifdef _BRIHODAKAR_

<<<<<<< HEAD
void display_num(char brihodakar[]);										            //  BLNS: Displays the relevant Brihodakar number stored in array
=======
void display_num(const char brihodakar[]);												//  BLNS: Displays the relevant Brihodakar number stored in array
>>>>>>> parent of a29746f... Bug-fixing, #include improvement
void display_array(const char brihodakar[]);                                            //  BLNS: Displays the entire Brihodakar array in human-readable format
void input_to_array(char brihodakar[], int numsize);									//  BLNS: Regulated input segment (numsize allows for custom input size)
void array_management(char brihodakar[], int option);									//  BLNS: Multi-purpose array management function
																						/*          Option 1: Input/Unorganized data -> Standard Brihodakar array
																									Option 2: Standard Brihodakar array -> Big-endian converted Brihodakar array for operations
																						*/
void copy_array(char destination[], const char source[]);									//  BLNS: Copies the source array into the destination array
void add_array(const char conv_array1[], const char conv_array2[], char answer[]);          //  BLNS: Adds two big-endian converted Brihodakar arrays, brihodakar1 and brihodakar2
void subtract_array(const char conv_array1[], const char conv_array2[], char answer[]);     //  BLNS: Subtracts two big-endian converted Brihodakar arrays, conv_array1 MINUS conv_array2. ORDER MATTERS





void display_num(const char brihodakar[])
{
	// DEPRECATED LOW-PERF Printer
	int m;
	for (m=0; brihodakar[m] != 'A'; m++)
	{
	printf("%d", brihodakar[m]);
	}
	//printf("%c", brihodakar[m]); // uncomment to display terminating character.
	return;


	/*int m;
	char tempstore[max_num_size + 5] = "";
	copy_array(tempstore, brihodakar);

	for (m = 0; tempstore[m] != 'A'; m++)
	{
		tempstore[m] = tempstore[m] + '0';
<<<<<<< HEAD

	#ifndef DEBUG		/* Write `#define DEBUG` to see the terminating character A*/
	/*	tempstore[m] = '\0';
=======
	}
	#ifndef DEBUG		/* Write `#define DEBUG` see the terminating character A*/
		tempstore[m] = '\0';
>>>>>>> parent of a29746f... Bug-fixing, #include improvement
    #endif

    array_management(tempstore, 1); // So we see just the number and not all the zeroes from the Big-Endian conversion...

	printf(tempstore);
	return;*/
}


void display_array(const char brihodakar[])
{
	int m;
	char tempstore[max_num_size + 5] = "";
	copy_array(tempstore, brihodakar);

	for (m = 0; tempstore[m] != 'A'; m++)
	{
		tempstore[m] = tempstore[m] + '0';
	}
	#ifndef DEBUG		/* Write `#define DEBUG` see the terminating character A*/
		tempstore[m] = '\0';
    #endif

	printf(tempstore);
	return;
}


void input_to_array(char brihodakar[], int numsize)
{
	char in;
	int i;

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
	switch (option)
	{
		case 1: //  SHIFT LEFT FULLY: Input --> Standard Brihodakar array
		{
		    { // Termination check
                int is_terminated = 0, i, j;
                for (i = 0, j = max_num_size; i < (max_num_size + 5)/2 && j > 0; i++, j--)
                {
                    if (brihodakar[i] == 'A' || brihodakar[j] == 'A')
                    {
                        is_terminated = 1;
                        break;
                    }
                }
                if (is_terminated == 0)
                {
                    printf("\n--DEBUG: Array was unterminated!! Resetting to null array...\n");
                    brihodakar[0] = 0; brihodakar[1] = 'A';
                }
		    }

			if (!(brihodakar[0] == 0 && brihodakar[1] == 'A'))            // remove all leading zeroes before number
			{                                   /// final, should be perfect,...
				while (brihodakar[0] == 0)     // Move every element one space forward IF there is a zero in front of it
				{
					int k;
					for (k = 0; k<max_num_size; k++)
						brihodakar[k] = brihodakar[k + 1];
				}          // This operation can cause a large string of zeroes in brihodakar[] to turn into a null array. So, just in case

				if (brihodakar[0] == 'A') // Turns a null array into an array of 0.
                    {brihodakar[0] = 0; brihodakar[1] = 'A';}
			}
		}   break;

		case 2: //  SHIFT RIGHT FULLY: Standard Brihodakar array --> Big-Endian Brihodakar array for operations
		{
			// WARNING: DO NOT EXECUTE THIS OPERATION ON AN UNORDERED ARRAY (perform array_management(array, 1); first)
			while (brihodakar[max_num_size] != 'A')   /// final, should have no problems
			{
				int k;
				for (k = max_num_size; k > 0; k--)
				{
					brihodakar[k] = brihodakar[k - 1];
					if (k == 1)
						brihodakar[0] = 0;
				}
			}
		}   break;
	}
	return;
}


void copy_array(char destination[], const char source[]) // FINAL
{
	int i = 0;
	while (i < max_num_size + 5)    /// final, should be safe now that `while` is no longer infinite
	{
		destination[i] = source[i];
		if (destination[i] == 'A')
			return;
		i++;
	}
	printf("\n--DEBUG: Source array is unterminated!!!\n");
	return;
}

void add_array(char conv_array1[], char conv_array2[], char answer[]) // Tip, apply const to
{
	int i;

	// Test big-endianess of arrays
	if (conv_array1[max_num_size] != 'A' || conv_array2[max_num_size] != 'A' || answer[max_num_size] != 'A')
	{
		//printf("\n--DEBUG: Addition failed: Improper array configuration. Please initialize/set arrays properly and try again\n");
		array_management(conv_array1, 2);
		array_management(conv_array2, 2);
		array_management(answer, 2);
	}

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

	return;
}


void subtract_array(const char conv_array1[], const char conv_array2[], char answer[])
{
	int i;

	// Test big-endianess of arrays
	if (conv_array1[max_num_size] != 'A' || conv_array2[max_num_size] != 'A' || answer[max_num_size] != 'A')
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
	return;
}

#endif
