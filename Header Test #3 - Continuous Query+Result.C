#define max_num_size 80
//#define DEBUG

#include "BRIHODAKAR.H"     // Contains stdio and conio already...

int main(void)
{
    char yuugenumber1[max_num_size + 5] = {0};
    char yuugenumber2[max_num_size + 5] = {0};
    char total[max_num_size + 5] = {0};

    char ch;

    printf("BRIHODAKAR LARGE NUMBER SYSTEM!\nContinuous User Addition/Subtraction\n\n\n");

    printf("Enter a number: ");
    input_to_array(yuugenumber1, max_num_size);

    printf("Enter another number: ");
    input_to_array(yuugenumber2, max_num_size);

    printf("Add/Subtract(second from first) these two numbers? (+/-) ");
    ch = getche();
    if (ch != '+' && ch != '-')
    {
        printf("\nI don't understand what you're saying... Try again...\n");
    }
    if (ch == '+')
    {
        add_bri_num(yuugenumber1, yuugenumber2, total);
        printf("\n");
        display_num(total);
    }
    if (ch == '-')
    {
        subtract_bri_num(yuugenumber1, yuugenumber2, total);
        printf("\n");
        display_num(total);
    }

    while (ch != 'q' && ch != 'Q')
    {
        printf("\nEnter another number: ");
        input_to_array(yuugenumber1, max_num_size);


        printf("Add/Subtract this number to/from the total? (+/-) ");
        ch = getche();
        if (ch != '+' && ch != '-')
        {
            printf("\nI don't understand what you're saying... Try again...\n");
            continue;
        }
        if (ch == '+')
        {
            add_bri_num(yuugenumber1, total, total);
            #ifdef DEBUG
            printf("\n Total:");
            display_array(total);
            printf("\n yuugenumber1:");
            display_array(yuugenumber1);
            printf("\n yuugenumber2:");
            display_array(yuugenumber2);
            #else
            printf("\n");
            display_num(total);
            #endif
        }
        if (ch == '-')
        {
            subtract_bri_num(total, yuugenumber1, total);
            #ifdef DEBUG
            printf("\n Total:");
            display_array(total);
            printf("\n yuugenumber1:");
            display_array(yuugenumber1);
            printf("\n yuugenumber2:");
            display_array(yuugenumber2);
            #else
            printf("\n");
            display_num(total);
            #endif // DEBUG
        }
        printf("\nExit now? (Q/any other key) ");
        ch = getche();
    }

    return 0;
}
