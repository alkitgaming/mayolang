#include "mayoincl.h"
#include "mayoparsegen.h"
#include "mayocomperr.h"

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

C_Func_t *parseNewFunction(Lang_Statement_t *statements)
{
  int counter = 0, i, actionsIndex = 0;
  int containsIndex = -1, ingredientsIndex = -1;
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
    else if(!strcmp(word, "contains")) containsIndex = counter;
    else if(!strcmp(word, "ingredients")) ingredientsIndex = counter;
    counter++;
  }

  C_Func_t *structure = malloc(sizeof(C_Func_t));
  
  if (endIndex == -1) reportCompileError(&statements[0], "No jar-close found.");
  else if (openIndex == -1) reportCompileError(&statements[0], "No jar-open found.");

  nameStartIndex = &(statements[0].statement[0]) + strlen("new-jar ");
  nameSemicolonIndex = strchr(statements[0].statement, ';');

  structure->nameLength = nameSemicolonIndex - nameStartIndex;
  structure->name = malloc(sizeof(char) * structure->nameLength);
  strncpy(structure->name, nameStartIndex, structure->nameLength);

  structure->actionsLength = endIndex - openIndex - 1;
  structure->actions = malloc(structure->actionsLength * sizeof(Lang_Statement_t));
  for (i = openIndex + 1; i < endIndex; i++)
  { 
    (structure->actions[actionsIndex]) = statements[i];
  }
  return structure;
}

C_Variable_t *parseNewVariable(char *text)
{
  C_Variable_t *structure;
  char *word;
  while (sscanf(text, "%s", word))
  {
    if (!strcmp(word, getMayoTypeKeyword(C_Value_char))) structure->type = C_Value_char;
    else if (!strcmp(word, getMayoTypeKeyword(C_Value_int))) structure->type = C_Value_int;
    else if (!strcmp(word, getMayoTypeKeyword(C_Value_double))) structure->type = C_Value_double;
    else if (!strcmp(word, getMayoTypeKeyword(C_Value_void))) structure->type = C_Value_void;
    else if (!strcmp(word, getMayoTypeKeyword(C_Value_struct))) structure->type = C_Value_struct;
    else continue;
    break;
  }
  sscanf(text, "%s", word);
  structure->nameLength = strlen(word);
  if (strchr(word, ';')) structure->nameLength--;
  structure->name = malloc(sizeof(char) * structure->nameLength);
  strncpy(structure->name, word, structure->nameLength);
  return structure;
}

char *getMayoTypeKeyword(int cType)
{
  switch(cType)
  {
    case C_Value_char:
      return "label";
    case C_Value_double:
      return "hellmans";
    case C_Value_int:
      return "miraclewhip";
    case C_Value_void:
      return "empty";
    case C_Value_struct:
      return "mixture";
  }
}