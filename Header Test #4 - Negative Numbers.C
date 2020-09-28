#define max_num_size 230

#include "BRIHODAKAR.H"     // Contains stdio and conio already...

int main(void)
{
	char num1[max_num_size + 5] = {8, 1, 9, 2, 3, 4, 8, 9, 0, 1, 9, 7, 8, 2, 3, 4, 8, 9, 0, 1, 2, 3, 'S', 8, 9, 7, 1, 2, 3, 0, 9, 7, 8, 1, 2, 3, 7, 8, 9, 0, 1, 2, 3, 4, 7, 8, 8, 4, 7, 8, 2, 3, 4, 8, 9, 7, 8, 1, 8, 3, 7, 4, 1, 2, 3, 8, 4, 5, 2, 8, 9, 7, 3, 4, 6};
	char num2[max_num_size + 5] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 0, 2, 3, 0, 4, 4, 0, 2, 3, 1, 4, 0, 2, 3, 4, 0, 2, 3, 4, 0, 0, 0, 0, 2, 3, 0, 4, 2, 3, 0, 4, 0, 0, 0, 0, 'S', 1, 2, 3, 4, 7, 8, 8, 4};
	char num3[max_num_size + 5] = { 'A' };

	unsigned long long int eznumber;

	printf("Test of negative numbers and proper negative terminator behaviour! Press any key to continue...\n");
	getch();

	printf("\nCase 01: removegarbage function test \t Printing results: \n");
	display_num(num1);
	removegarbage(num1);
	printf("\n\n\n");
	display_num(num1);

	printf("\nCase 02: removegarbage in array_management test. \t Printing results: \n");
	display_num(num2);
	array_management(num2, 1);
	printf("\n\n\n");
	display_num(num2);

	printf("\nCase 03: bri_itoa for easy inputting of small numbers. \t Type in a number(scanf %%llu): \n");
	scanf("%llu", &eznumber);
	printf("%llu\n", eznumber);
	bri_itoa(eznumber, num3);
	printf("\n\n\n");
	display_num(num3);

	printf("\nCase 04: Addition of number previously obtained from bri_itoa to initial cases: \n");
	printf("\n\n\n");
	add_bri_num(num3, num1, num1);
	display_num(num1);
	printf("\n");
	add_bri_num(num3, num2, num2);
	display_num(num2);
	printf("\nNegative number handling not implemented yet... Even though the terminators imply a negative number, the absolute value of both will be added...\n");

	return 0;
}
