/**
	Brihodakar(Gigantic) Large Number System: Implementation for 100-digit numbers. (designed to be easily extendable)
	Made by AbdullahTrees, 2020

**/

#include <stdio.h>
#include <conio.h>

/*
	Brihodakar Large Number System(BLNS): Information

	Basically, it is a string(terminated with 'A') of numbers, so there is no size limit to the number that it can hold except for the size of the array.
	= I intended the following things when making it:   1) Not complicated (it can become big of course, but shouldn't use things that I do not currently understand, such as typedefs and pointer arithmetic
														2) Easily extendable. For only a proof of concept I am currently limiting the size of the array to hold 100-digit numbers, but there's no reason why these principles can't work for larger digit numbers. Hence I expect BLNS to be easily extendable so that just by changing the constant I can work with 10-digit or 10000-digit numbers.
														3) Bug-free. This isn't really a complicated program, so I need to make sure BLNS works properly for ALL numbers. Since addition, subtraction, etc. all these operations are being implemented by the programmer(me!), there is no guarantee that the correct answer is returned by the algorithm that I've invented. For now trial and error seems to show that my algorithm works, but there may be 1 or 2 wierd edge cases. Idk how to guarantee that my algorithm that I've programmed works for all numbers, but I want to get to that point.

	= Why are you making this?
	Good question. First of all, I'm a new programmer and have no idea about the real-world, so there's that. I need a challenge that's easy and not impossible
	Also, try adding 301974818932465466578913243242342347328941234 to 1823749701842756793485627934851. Too big for unsigned long long int? Long double doesn't hold the entire answer? Yeah, I thought so...

	= Soo.... How does the BLNS work?
	Very simple. This is how a standard Brihodakar array should look like in memory:
			brihodakar[10] = [1 2 3 4 5 65 0 0 0 0]  (decimal/int view) (human-interpretable input/output format)
			brihodakar[10] = [A(nul)(nul)(nul)(nul)]  (char view)
			brihodakar[10] = [01 02 03 04 05 41 00 00 00 00]   (expected memory dump of relevant bits)

		Expected data:  Integers 0 through 9 = digits
						'A' = Terminating character
						'S' = Terminating character implying negative character?? (not implemented yet, I need a way to define negative numbers tho).

		Unexpected data: ANYTHING ELSE!

	= Oh, since I'm not some savant, I decided to implement addition and subtraction in the way humans normally add numbers. This means...
		1) When numbers are different sizes, addition is going to be utter chaos. We need to convert arrays to Big-Endian (basically significant digits at the very end, while still retaining the same order)
		2) Per digit addition (this means implementing carrying, overflow, etc. manually, so...

		This is what a Big-Endian array should look like:
				brihodakar1[15] = [0 0 0 0 0 0 0 0 1 2 3 4 5 6 A]
				brihodakar2[15] = [0 0 0 0 0 0 0 0 1 2 3 4 5 6 A]
		lets add those 2...
				brihodakar3[15] = [0 0 0 0 0 0 0 0 2 4 6 9 1 2 A]

		If we try displaying that right now with our display_num() function, there's gonna be a lot of useless zeroes in the front, hence array_management() can convert Big-Endian Brihodakar arrays to Standard, and vice versa.

	= A getche() loop cycles and takes in character inputs from the keyboard and stores numbers into the Brihodakar array PER DIGIT. The 'char' data type is only really being used for smaller memory footprint,
		Instead of storing the characters 0 through 9, we instead store the numbers 0 through 9, directly into the array, for easier calculation(imagine having to subtract - '0' all the time, eww).
		Displaying the array is also very simple. printf("%d", brihodakar[number]) works as C does not distinguish between chars and ints, and allows one to be treated like the other.

	= The following things work and I'm pretty sure should be bug-free... Please still check them and comment, of course.
		display_num(); copy_array(); input_to_array();   // feel free to still check them out of course, humans can never guarantee anything
	  The following things CURRENTLY DON'T WORK AND I HAVE NO IDEA WHY...
		add_array(); // this works when max_num_size = 100, but breaks and falls into an infinite loop when it's 105. Displays garbage in the arrays. Somehow it's getting corrupted

	= Any other questions, be sure to let me know in Discord!
*/

#define max_num_size 100  // DEFINES THE WORKING AREA OF THE BRIHODAKAR ARRAY: change this for dynamically large arrays, make sure to change declarations on BrihodakarX[] accordingly, always make Brihodakar array size slightly larger than this value

void display_num(const char brihodakar[]);												//  BLNS: Displays the Brihodakar array in human-readable format
void input_to_array(char brihodakar[], int numsize);									//  BLNS: Regulated input segment (numsize allows for custom input size)
void array_management(char brihodakar[], int option);									//  BLNS: Multi-purpose array management function
																						/*          Option 1: Input/Unorganized data -> Standard Brihodakar array
																									Option 2: Standard Brihodakar array -> Big-endian converted Brihodakar array for operations
																						*/
void add_array(const char conv_array1[], const char conv_array2[], char answer[]);          //  BLNS: Adds two big-endian converted Brihodakar arrays, brihodakar1 and brihodakar2
void subtract_array(const char conv_array1[], const char conv_array2[], char answer[]);     //  BLNS: Subtracts two big-endian converted Brihodakar arrays, conv_array1 MINUS conv_array2. ORDER MATTERS
void copy_array(char destination[], const char source[]);                       //  BLNS: Copies the source array into the destination array


int main(void)
{
	char brihodakar1[max_num_size+5] = "";          // The stars of the show: these arrays hold ordered data representing numbers,
	char brihodakar2[max_num_size+5] = "";          // according to the Brihodakar Large Number System specifications, which is
	char brihodakarans[max_num_size+5] = "";        // actually quite simple.

													/* General form for declaring an abstract Brihodakar array
															char <name>[max_num_size+5] = "";    */

	printf("Testing the implementation of the Brihodakar Large Number System(BLNS). ");

	// BLNS: regulated input segment
	printf("\nPlease enter the first number: \n");
	input_to_array(brihodakar1, max_num_size);
	printf("\nPlease enter the second number: \n");
	input_to_array(brihodakar2, max_num_size);

	printf("\n\n\nDEBUG: Displaying array\n");
	display_num(brihodakar1); // DEBUG
	printf("\n");
	display_num(brihodakar2); // DEBUG

	array_management(brihodakar1, 1);
	array_management(brihodakar2, 1);
		// brihodakarans is a non-input array and hence it has no terminating character. This must be added
		brihodakarans[0] = 'A';
		array_management(brihodakarans, 1);

	printf("\n\n\nDEBUG: Displaying array after basic management\n");
	display_num(brihodakar1);
	printf("\n");
	display_num(brihodakar2);

	// Conversion to Big-Endian for addition
	array_management(brihodakar1, 2);
	array_management(brihodakar2, 2);
	array_management(brihodakarans, 2);

	printf("\n\n\nDEBUG: Displaying array after big-endian conversion\n");
	display_num(brihodakar1);
	printf("\n");
	display_num(brihodakar2);
	printf("\n");
	display_num(brihodakarans);


	// Addition query (DEBUG)
	printf("\n\n\nAdding the two arrays\n");
	add_array(brihodakar1, brihodakar2, brihodakarans);
	printf("DEBUG: Displaying array after addition\n");
	display_num(brihodakarans);
	array_management(brihodakarans, 1);
	printf("\n\n\nAdding the two arrays, result: \n");
	display_num(brihodakarans);

	// Subtraction query (DEBUG)
	printf("\n\n\nSubtracting the second array from the first array\n");
	subtract_array(brihodakar1, brihodakar2, brihodakarans);
	printf("DEBUG: Displaying array after subtraction\n");
	display_num(brihodakarans);
	array_management(brihodakarans, 1);
	printf("\n\n\nSubtracting the two arrays, result: \n");
	display_num(brihodakarans);


	return 0;
}

void display_num(const char brihodakar[])
{
	/*int m;
	for (m=0; brihodakar[m] != 'A'; m++)
	{
		printf("%d", brihodakar[m]);
	}
	//printf("%c", brihodakar[m]); // uncomment to display terminating character.
	return;
	LOW-PERF Printer*/

	int m;
	char tempstore[max_num_size+5] = "";
	copy_array(tempstore, brihodakar);

	for (m=0; tempstore[m] != 'A'; m++)
	{
		tempstore[m] = tempstore[m] + '0';
	}
	if (1/* Set this to 0 to see the terminating character A*/)
		tempstore[m] = '\0';

	printf(tempstore);
	return;
}

void input_to_array(char brihodakar[], int numsize)
{
	char in;
	int i;

	input:
		for (i=0; i<numsize; i++)
		{
			in = getch();

			if (in >= '0' && in <= '9')
			{
				brihodakar[i] = in - '0';
				if (i == numsize - 1)
					brihodakar[i+1] = 'A';
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
	return;
}

void array_management(char brihodakar[], int option)
{
	int i;

	switch (option)
	{
	case 1: //  Input --> Standard Brihodakar array
		{
			if (!(brihodakar[0] == 0 && brihodakar[1] == 'A'))            // remove all leading zeroes before number
			{                                   /// final, should be perfect,...
				while (brihodakar[0] == 0)     // Move every element one space forward IF there is a zero in front of it
				{
					int k;
					for (k = 0; k<max_num_size; k++)
						brihodakar[k] = brihodakar[k+1];
				}          // This operation can cause a large string of zeroes in brihodakar[] to turn into a null array. So, just in case

				if (brihodakar[0] == 'A') // Turns a null array into an array of 0.
				{
					brihodakar[0] = 0; brihodakar[1] = 'A';
				}
			}
		}
		break;
	case 2: // Standard Brihodakar array --> Big-Endian Brihodakar array for operations
		{
			// WARMING: DO NOT EXECUTE THIS OPERATION ON AN UNORDERED ARRAY (perform array_management(array, 1); first)
			while (brihodakar[max_num_size] != 'A')   /// final, should have no problems
			{
				int k;
				for (k = max_num_size; k > 0; k--)
				{
					brihodakar[k] = brihodakar[k-1];
					if (k == 1)
						brihodakar[0] = 0;
				}
			}
		}
		break;
	}
	return;
}

void add_array(const char conv_array1[], const char conv_array2[], char answer[])
{
	int i;

	// Test big-endianess of arrays
	if (conv_array1[max_num_size] != 'A' || conv_array2[max_num_size] != 'A' || answer[max_num_size] != 'A')
	{
		printf("\n--DEBUG: Addition failed: Improper array configuration. Please initialize/set arrays properly and try again\n");
	}
	else
	{
		char temp_array1[max_num_size+5] = "";
		copy_array(temp_array1, conv_array1); // this allows us to add carries to conv_array1, since the original value of conv_array1 is now preserved.

		for (i=max_num_size-1; i>=0; i--)
		{
			int digitholder;

			digitholder = temp_array1[i] + conv_array2[i]; // conv_array1 IS temp_array1!!!!

			if (digitholder > 9) //  Carrying branch
			{
				digitholder = digitholder - 10;
				answer[i] = digitholder;   // Brihodakar3 is the answer array that holds the computation, it must be initialized to Big-Endian 0 array first.
				if (i > 0)
					temp_array1[i-1] = temp_array1[i-1] + 1;
				else
					printf("\nWARNING!!!! OVERFLOW!!! THE ANSWER MAY BE WRONG\n");
			}
			else
			{
				answer[i] = digitholder;
			}
		}
	}
	return;
}

void copy_array(char destination[], const char source[]) // FINAL
{
	int i=0;
	while (i < max_num_size + 5)    /// final, should be safe now that while is no longer infinite
	{
		destination[i] = source[i];
		if (destination[i] == 'A')
			return;
		i++;
	}
	printf("\n--DEBUG: Source array is unterminated!!!\n");
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
		char temp_array1[max_num_size+5] = "";
		copy_array(temp_array1, conv_array1); // this allows us to add carries to conv_array1, since the original value of conv_array1 is now preserved.

		for (i=max_num_size-1; i>=0; i--)
		{
			signed int digitholder;

			digitholder = temp_array1[i] - conv_array2[i]; // conv_array1 IS temp_array1!!!!

			if (digitholder < 0) //  Carrying branch
			{
				digitholder = digitholder + 10;
				answer[i] = digitholder;   // Brihodakar3 is the answer array that holds the computation, it must be initialized to Big-Endian 0 array first.
				if (i > 0)
					temp_array1[i-1] = temp_array1[i-1] - 1;
				else
					printf("\nWARNING!!!! OVERFLOW!!! THE ANSWER MAY BE WRONG\n");
			}
			else
			{
				answer[i] = digitholder;
			}
		}
	}
	return;
}
