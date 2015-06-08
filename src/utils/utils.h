/* Multiple inclusion is permited and safe.
   It allows .h to define a MODNAME and undef it at the end */

#include <cstdio>

#ifdef DPRINTF
# undef DPRINTF
#endif

#ifdef EPRINTF
# undef EPRINTF
#endif

#ifndef MODNAME
# define MODNAME "undef"
#endif

#ifdef DEBUG_TRACE
# define DPRINTF(fmt, ...) fprintf(stderr, MODNAME ": " fmt, ##__VA_ARGS__)
#else
# define DPRINTF(fmt, ...) do {} while(0)
#endif

#define EPRINTF(fmt, ...) fprintf(stderr, "[error] " MODNAME ": " fmt, ##__VA_ARGS__)

