#ifndef STRINGS_H
#define STRINGS_H

#include <stddef.h>

const char* Strings_get_next_token(const char* text, const char delim);
const char* Strings_get_next_line(const char* text);

#endif  // STRINGS_H