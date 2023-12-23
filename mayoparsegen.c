#include "mayoincl.h"
#include "mayoparsegen.h"

void parseStatements(Lang_Statement_t *statements, int statementsLength)
{
  int curStmt;
  char word[2047];
  for(curStmt = 0; curStmt < statementsLength; curStmt++)
  {
    sscanf(statements[curStmt].statement, "%s", word);
    if (!strcmp(word, "new-jar"))
    {
      parseNewFunction(&(statements[curStmt]));
    }
  }
}

C_Func_t parseNewFunction(Lang_Statement_t *statements)
{
  int counter;
  int openIndex, endIndex;
  char word[2047];

  int nameStartIndex, nameSemicolonIndex, nameCounter = 0;
  while(statements[counter].statement != NULL)
  {
    sscanf(statements[counter].statement, "%s", word);
    if(strcmp(word, "close-jar"))
    {
      endIndex = counter;
      if (openIndex != NULL) break;
    }
    else if (strcmp(word, "open-jar"))
    {
      openIndex = counter;
    }
  }

  C_Func_t structure;
  if (endIndex == NULL) reportCompileError(statements[0], "No jar-close found.");
  else if (openIndex == NULL) reportCompileError(statements[0], "No jar-open found.");
  nameStartIndex = statements[0].statement + strlen("new-jar ");
  nameSemicolonIndex = strchr(statements[0].statement, ';');

  char *name = malloc(sizeof(char) * nameSemicolonIndex-nameStartIndex);  
  structure.nameLength = nameSemicolonIndex - nameStartIndex;
  strncpy(structure.name, name, structure.nameLength);
}
