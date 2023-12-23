#include "mayocomp2.h"
typedef struct Statement_t
{
    int statementNumber;
    char statement[2047];
    int statementLength;
} Statement_t;

int main(char *name)
{
    if (!name) return -1;
    
    char read_buf[2048];
    Statement_t in[500];
    Statement_t *current;
    int counter = 0;
    int i;
    FILE *file_p = fopen("mayonnaise.mayo", "r+");
    FILE *out_p = fopen("mayonnaise.c", "w+");

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

    fclose(file_p);
    fclose(out_p);
    return 0;
}