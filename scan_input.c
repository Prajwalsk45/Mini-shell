#include "minishell.h"

char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
						"set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
						"exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", NULL};


char command[50];
char* external[50];

void execute_internal_commands(char *input_string)
{
    if((strcmp("cd",command))==0)
    {
        chdir(&input_string[3]);
    }
    else if((strcmp("pwd",command))==0)
    {
        char str[100];
        getcwd(str,100);
        printf("%s\n",str);
    }
    else if((strcmp("echo",command))==0)
    {

    }
    else if((strcmp("exit",command))==0)
    {
        exit(1);
    }

}
void scan_input(char *prompt, char *input_string)
{
    while(1)
    {
        printf("%s ",prompt);
        scanf(" %[^\n]",input_string);

        if((strncmp(input_string,"PS1=",4))== 0)
        {
            if(input_string[4]==' ')
            {
                printf("PS1 : command not found\n");
            }
            else
            {
                strcpy(prompt,input_string+4);
            }
        }
        else
        {
            char *cmd=get_command(input_string);

            //bulit in command
            int ret=check_command_type(cmd);

            if(ret == BUILTIN)
            {
                execute_internal_commands(input_string);
            }
        }
    }
}

// void extract_external_commands(char **external_commands)
// {
//     /*
//     s1 :open file externl_command.txt and read
//     s2 : store cmd
//     s3 allocate dynamically as 2d array;
//     */

    
    
// }

void extract_external_commands(char **external_commands)
{
    FILE *fp = fopen("externl_commands.txt","r");

    if(fp == NULL)
    {
        perror("fopen");
        return;
    }

    int i = 0;
    char temp[50];

    while(fscanf(fp,"%s",temp) != EOF)
    {
        external_commands[i] = malloc(strlen(temp) + 1);
        strcpy(external_commands[i], temp);
        i++;
    }

    external_commands[i] = NULL;

    fclose(fp);
}

int check_command_type(char *cmd)
{

    //built-in cmd
    for(int i=0;builtins[i]!=NULL;i++)
    {
        if((strcmp(builtins[i],cmd))==0)
        {
            //printf("bulit in command %s\n",cmd);
            return BUILTIN;
        }
    }

    //external cmd
    extract_external_commands(external);
    for(int i=0;external[i]!=NULL;i++)
    {
        if((strcmp(external[i],cmd))==0)
        {
            //printf("external command %s\n",cmd);
            return EXTERNAL;
        }
    }

    return NO_COMMAND;
}
char *get_command(char *input_string)
{
    
    int i=0;
    for(i=0;input_string[i]!=' ';i++)
    {
        command[i]=input_string[i];
    }
    command[i]='\0';

    return command;
}