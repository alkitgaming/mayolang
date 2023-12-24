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
  int counter = 0;
  int openIndex = -1, endIndex = -1;
  char word[2047];

  char *nameStartIndex = 0x0, *nameSemicolonIndex = 0x0;
  int nameCounter = 0;
  while(statements[counter].statement != NULL)
  {
    sscanf(statements[counter].statement, "%s", word);
    if(!strcmp(word, "close-jar"))
    {
      endIndex = counter;
      if (openIndex != -1) break;
    }
    else if (!strcmp(word, "open-jar"))
    {
      openIndex = counter;
    }
    counter++;
  }

  C_Func_t *structure = malloc(sizeof(C_Func_t));
  if (endIndex == -1) reportCompileError(statements[0], "No jar-close found.");
  else if (openIndex == -1) reportCompileError(statements[0], "No jar-open found.");

  nameStartIndex = &(statements[0].statement[0]) + strlen("new-jar ");
  nameSemicolonIndex = strchr(statements[0].statement, ';');

  structure->nameLength = nameSemicolonIndex - nameStartIndex;
  strncpy(structure->name, nameStartIndex, structure->nameLength);
}
