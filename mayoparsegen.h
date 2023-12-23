#ifndef MAYOPARSEGEN_H
#define MAYOPARSEGEN_H
#include "mayoincl.h"

/**
 * This directly parses mayolang statements into compilable
 * structures to be compiled in other parse/compile files
*/
void parseStatements(Lang_Statement_t *statements, int statementsLength);
#endif