#define max_num_size 230
//#define DEBUG

#include "BRIHODAKAR.H"     // Contains stdio and conio already...
#include <windows.h>

int main(void)
{
    DWORD dwStartTime, dwEndTime;
    char yuugenumber1[max_num_size + 5] = {5, 5, 5, 5, 5, 'A'};
    char yuugenumber2[max_num_size + 5] = {0};
    char answer[max_num_size + 5] = {0};

    unsigned long long int iterations, i;

    // create 1
    yuugenumber2[0] = 1, yuugenumber2[1] = 'A';

    printf("BRIHODAKAR LARGE NUMBER SYSTEM!\n\n\nRepeated Addition for Benchmarking...\nPlease enter the number: ");
    //input_to_array(yuugenumber1, max_num_size);

    printf("\nHow many times does this have to be incremented by 1?: ");
    //iterations = 999999;
    scanf("%llu", &iterations);


    printf("\n\n\nOk... So....   \n1) Add this number to itself %llu times(multiplication)\n2) Add 1 to this number %llu times (incrementation)\n3) Subtract 1 from this number %llu times (decrementation - POSSIBLE UNDERFLOW)", iterations, iterations, iterations);

    switch ('1') //getche())
    {
    case '1':
        dwStartTime = GetTickCount();
        for(i=0; i<iterations; i++)
        {
            add_bri_num(yuugenumber1, answer, answer);
        }
        dwEndTime = GetTickCount() - dwStartTime;
        printf("\nCalculation took %g seconds\n", ((double)dwEndTime/1000.0));
        break;
    case '2':
        dwStartTime = GetTickCount();
        add_bri_num(yuugenumber1, answer, answer);
        for(i=0; i<iterations; i++)
        {
            add_bri_num(answer, yuugenumber2, answer);
        }
        dwEndTime = GetTickCount() - dwStartTime;
        printf("\nCalculation took %g seconds\n", ((double)dwEndTime/1000.0));
        break;
    case '3':
        dwStartTime = GetTickCount();
        subtract_bri_num(yuugenumber1, yuugenumber2, answer);
        for(i=0; i<iterations; i++)
        {
            subtract_bri_num(answer, yuugenumber2, answer);
        }
        dwEndTime = GetTickCount() - dwStartTime;
        printf("\nCalculation took %g seconds\n", ((double)dwEndTime/1000.0));
        break;
    }

    display_num(answer);
    return 0;
}
