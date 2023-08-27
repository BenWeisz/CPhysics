#include "util/log.h"

void Log_error(const char* format_str, ...)
{
    char* tag = "\033[1;41mERROR:\033[0m ";

    char message_whole[MAX_MESSAGE_LENGTH];
    strncpy(message_whole, tag, MAX_MESSAGE_LENGTH - 1);
    
    const u32 tag_length = strlen(tag);
    const u32 message_length = strlen(format_str);

    char* message_text = message_whole + tag_length;
    strncpy(message_text, format_str, MAX_MESSAGE_LENGTH - 1 - tag_length);

    message_whole[tag_length + message_length] = '\0';

    va_list args;
    va_start(args, format_str);
    vfprintf(stdout, message_whole, args);
    va_end(args);
}

void Log_warn(const char* format_str, ...)
{
    char* tag = "\033[1;43mWARNING:\033[0m ";

    char message_whole[MAX_MESSAGE_LENGTH];
    strncpy(message_whole, tag, MAX_MESSAGE_LENGTH - 1);
    
    const u32 tag_length = strlen(tag);
    const u32 message_length = strlen(format_str);

    char* message_text = message_whole + tag_length;
    strncpy(message_text, format_str, MAX_MESSAGE_LENGTH - 1 - tag_length);

    message_whole[tag_length + message_length] = '\0';

    va_list args;
    va_start(args, format_str);
    vfprintf(stdout, message_whole, args);
    va_end(args);
}

void Log_success(const char* format_str, ...)
{
    char* tag = "\033[1;42mSUCCESS:\033[0m ";

    char message_whole[MAX_MESSAGE_LENGTH];
    strncpy(message_whole, tag, MAX_MESSAGE_LENGTH - 1);
    
    const u32 tag_length = strlen(tag);
    const u32 message_length = strlen(format_str);

    char* message_text = message_whole + tag_length;
    strncpy(message_text, format_str, MAX_MESSAGE_LENGTH - 1 - tag_length);

    message_whole[tag_length + message_length] = '\0';

    va_list args;
    va_start(args, format_str);
    vfprintf(stdout, message_whole, args);
    va_end(args);
}