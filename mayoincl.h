#ifndef MAYOINCL_H

#define MAYOINCL_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

#define C_Value_int 1000;
#define C_Value_double 1001;
#define C_Value_char 1002;
#define C_Value_struct 1003;
#define C_Value_void 1004;

typedef struct Lang_Statement_t
{
  int statementNumber;
  char statement[2047];
  int statementLength;
} Lang_Statement_t;

typedef struct C_Variable_t
{
  int type;
  char* name;
  int nameLength;
} C_Variable_t;

typedef struct C_Func_t
{
  C_Variable_t *params;
  int paramCount;
  C_Variable_t retval;
  char* name;
  int nameLength;
  Lang_Statement_t *actions;
  int actionsLength;
} C_Func_t;

typedef struct C_Struct_t
{
  C_Variable_t *fields;
  int fieldsLength;
  char *name;
  int nameLength;
} C_Struct_t;
#endif