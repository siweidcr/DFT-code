#include <stdio.h>
#include <ctype.h>
#include <string.h>

// forward declarations
void print_letters(int length, char arg[]);
void print_arguments(int argc, char *argv[]);


void print_arguments(int argc, char *argv[])
{
    int i = 0;
    int length = 0;

    for(i = 0; i < argc; i++) {
	length = strlen(argv[i]);
	printf("No.%d:\n",i+1);
        print_letters(length,argv[i]);
    }
}
void print_letters(int length, char arg[])
{
    int i = 0;

    for(i = 0; i< length; i++) {
        char ch = arg[i];

        if(isalpha(ch) || isblank(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }

    printf("\n");
}

int main(int argc, char *argv[])
{
//    printf("%d\n",argc);
    print_arguments(argc, argv);
    return 0;
}
