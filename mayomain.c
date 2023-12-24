#include "mayoincl.h"
#include "mayoparsegen.h"

int main()
{   
    char readBuf[2048];
    Lang_Statement_t in[500];
    Lang_Statement_t *current;
    int counter = 0;
    int i;
    FILE *file_p = fopen("C:\\Users\\alkit\\OneDrive\\Documents\\progaming\\esolang\\mayonnaise.txt", "r+");
    // FILE *out_p = fopen("mayonnaise.c", "w+");
    while(fscanf(file_p, "%2047s", readBuf) != EOF)
    {
        current = &(in[counter]);
        current->statementLength += strlen(readBuf);
        strcat(current->statement, readBuf);

        if (strchr(readBuf, ';') == NULL) 
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

    parseStatements(&(in[0]), counter);

    fclose(file_p);
    // fclose(out_p);
    return 0;
}