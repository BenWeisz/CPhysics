#include "util/io.h"

const char* IO_read(const char* path) 
{
    FILE* fp = fopen(path, "rb");
    if (fp == NULL)
    {
        Log_error("Failed to open file: %s\n", path);
        return NULL;
    }   

    if (fseek(fp, 0, SEEK_END) == -1)
    {
        Log_error("Failed to seek to end of file: %s\n", path);
        fclose(fp);
        return NULL;
    }

    i64 file_size = ftell(fp);
    if (file_size == -1)
    {
        Log_error("Failed to read the file length of the file: %s\n", path);
        fclose(fp);
        return NULL;
    }

    if (fseek(fp, 0, SEEK_SET) == -1)
    {
        Log_error("Failed to seek to start of file: %s\n", path);
        fclose(fp);
        return NULL;
    }

    char* data = (char*)malloc(file_size + 1);
    if (data == NULL)
    {
        Log_error("Failed to allocate space for file contents\n");
        fclose(fp);
        return NULL;
    }
    data[file_size] = '\0';

    i64 bytes_read = fread(data, sizeof(char), file_size, fp);
    if (bytes_read != file_size)
    {
        Log_error("Failed to read all the bytes of the file: %s\n", path);
        fclose(fp);
        free(data);
        return NULL;
    }

    fclose(fp);
    return data;
}