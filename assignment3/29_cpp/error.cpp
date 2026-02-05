/* error.c */

#include "global.h"

void error(const char* message)  /* generates all error messages  */
{
    fflush(stdout);
    fprintf(stderr, "[Error on line %d: %s]\n", lineno, message);
    exit(EXIT_FAILURE);  /*  unsuccessful termination  */
}
