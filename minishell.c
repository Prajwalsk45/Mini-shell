#include "minishell.h"


char prompt[50]="MINISHELL$";
int main()
{
    system("clear");
    char input_string[50];
    scan_input(prompt,input_string);
}