#include "mayoincl.h"
#include "mayoparsegen.h"

int main(char *name)
{
    if (!name) return -1;
    
    char read_buf[2048];
    Lang_Statement_t in[500];
    Lang_Statement_t *current;
    int counter = 0;
    int i;
    FILE *file_p = fopen("mayonnaise.txt", "r+");
    FILE *out_p = fopen("mayonnaise.c", "w+");
    if (!file_p) printf("why");

    while(fscanf(file_p, "%2047s", read_buf) != EOF)
    {
        current = &(in[counter]);
        current->statementLength += strlen(read_buf);
        strcat(current->statement, read_buf);

        if (strchr(read_buf, ';') == NULL) 
        {
            current->statementLength += 1;
            strcat(current->statement, " ");
            continue;
        }
        current->statementNumber = counter + 1;
        counter++;
    }

    for(i = 0; i < 10; i++)
    {
        printf("%d %d %s\n\n", in[i].statementNumber, in[i].statementLength, in[i].statement);
    }

    fclose(file_p);
    fclose(out_p);
    return 0;
}