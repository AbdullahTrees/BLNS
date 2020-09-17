#define max_num_size 230
//#define DEBUG

#include "BRIHODAKAR.H"     // Contains stdio and conio already...

int main(void)
{
    char yuugenumber1[max_num_size + 5] = {0};
    char yuugenumber2[max_num_size + 5] = {0};
    char answer[max_num_size + 5] = {0};

    printf("BRIHODAKAR LARGE NUMBER SYSTEM!\nPlease enter the first number: ");
    input_to_array(yuugenumber1, max_num_size);
    printf("\nAnd the second number, por favor: ");
    input_to_array(yuugenumber2, max_num_size);

    printf("\n\n\nOk... So.... \n 1) Add two numbers\n 2) Subtract #1 from #2\n 3) Subtract #2 from #1   : ");
    switch (getche())
    {
        case '1':       add_bri_num(yuugenumber1, yuugenumber2, yuugenumber2); printf("\n\n"); display_num(yuugenumber2); break;
        case '2':       subtract_bri_num(yuugenumber2, yuugenumber1, yuugenumber1); printf("\n\n"); display_num(yuugenumber1); break;
        case '3':       subtract_bri_num(yuugenumber1, yuugenumber2, yuugenumber2); printf("\n\n"); display_num(yuugenumber2); break;
    }

    return 0;
}
