#include "util/strings.h"

const char* Strings_get_next_token(const char* text, const char delim)
{
    const char* curr_char = text;
    const char* next_token = NULL;
    while (*curr_char != '\0')
    {
        if (*curr_char == delim)
        {
            next_token = curr_char + 1;
            break;
        }
        curr_char++;
    }

    if (*next_token == '\0')
        return NULL;
    return next_token;
}

const char* Strings_get_next_line(const char* text)
{
    return Strings_get_next_token(text, '\n');
}