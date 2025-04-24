#include <stdio.h>
void first_way(int count, int *ages, char *names[]);

void first_way(int count, int *ages, char *names[]){
// first way using indexing
   int i = 0;
   for(i = 0; i < count; i++) {
        printf("%s has %d years alive.\n",
                  names[i], ages[i]);
        printf("address of names[i]:%p,address of ages[i]:%p.\n",&(names[i]), &(ages[i]));
   }
   printf("---\n");
}

int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    printf("%ld\n",sizeof(int));
    int i = 0;

    // first way using indexing
    first_way(count,ages,names);
    //second way using indexing
    for(i = 0; i < count; i++) {
	printf("%s has %d years alive.\n",
		*(names+i),*(ages+i));
	printf("address of names+i:%p,address of ages+i:%p.\n", names+i, ages+i);
    }

    printf("---\n");

    return 0;
}
