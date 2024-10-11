#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#include "tokeniser.h"

long file_size = 0;
int char_size = 0;
unsigned char *buffer = NULL;
char *filename = "simple.html";

unsigned int current_char_input;
unsigned int next_char_input;

// Cursor for iterating through the buffer
unsigned char *cursor = NULL;
unsigned char *end = NULL;

unsigned int decode_utf8(const unsigned char *cursor, int *char_size)
{
    unsigned char byte = cursor[0];

    if (byte < 0x80)
    {
        *char_size = 1;
        return byte; // ASCII character
    }
    else if ((byte & 0xE0) == 0xC0)
    {
        *char_size = 2;
        return ((byte & 0x1F) << 6) | (cursor[1] & 0x3F);
    }
    else if ((byte & 0xF0) == 0xE0)
    {
        *char_size = 3;
        return ((byte & 0x0F) << 12) | ((cursor[1] & 0x3F) << 6) | (cursor[2] & 0x3F);
    }
    else if ((byte & 0xF8) == 0xF0)
    {
        *char_size = 4;
        return ((byte & 0x07) << 18) | ((cursor[1] & 0x3F) << 12) | ((cursor[2] & 0x3F) << 6) | (cursor[3] & 0x3F);
    }
    *char_size = -1; // Invalid UTF-8 sequence
    return 0;
}

int temp_buffer(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("File opening failed");
        return -1;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate buffer to read the file content
    buffer = (unsigned char *)malloc(size);
    if (!buffer)
    {
        perror("Memory allocation failed");
        fclose(file);
        return -1;
    }

    // Read file content into the buffer
    size_t read_bytes = fread(buffer, 1, size, file);
    if (read_bytes != size)
    {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return -1;
    }
    fclose(file);


    //Initialize cursor and end
    cursor = buffer;
    end = buffer + size;

    return 0;
}

unsigned int codepoint()
{
    while (cursor < end)
    {
        int char_size = 0;
        unsigned int codepoint = decode_utf8(cursor, &char_size);

        if (char_size == -1)
        {
            fprintf(stderr, "Invalid UTF-8 character detected.\n");
            cursor++;
            continue;
        }

        // Print the current codepoint (in hex) and its size
        printf("Codepoint: U+%04X (size: %d bytes)\n", codepoint, char_size);

        // Move cursor to the next character
        cursor += char_size;
        return codepoint;
    }
    return 0;
}

void cleanbuff()
{
    free(buffer);
}

unsigned int next_char()
{
    if (cursor < end)
    {
        return buffer[cursor - buffer];
    }
    return 0;
}


int main() {
    
    if (temp_buffer(filename) != 0)
    {
        return 1;
    }
    
    unsigned int current_char;
    while ((current_char_input = codepoint()) != 0) {
        if(next_char() == '!')
        {
            printf("%c \t", current_char_input);
        }
        printf("Codepoint: U+%04X\n", current_char_input);
        // run(current_char_input);
    }

    cleanbuff();
    return 0;
}