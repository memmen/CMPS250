/* AS01.c
**
** Course: CMPS 250
** Author: Brian Sean Memmen. 
** Last Modified: January 31, 2019
** Collaborated with: Bradley Hnatow.
**
** C application that forms and prints initials from full names input in the
** form last, first m. */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "Strings.h"

#define SPACING 10
#define MAX_LENGTH 100

void parse_file(char *file_name);
void print_formated_line(char *line_value);

int main(int argc, char *argv[])
{
    if (argc > 1)
    {

        parse_file(argv[1]);
    }
    else
    {
        printf("ERROR: No filename argument was given\n");
    }
    return 0;
}

/*
 * Function:  parse_file 
 * --------------------
 * Reads each line in of the given filename and reformates it into “perfectly” 
 * aligned columns and printing it out
 *
 *  file_name: name of file
 *
 *  returns: void
 */
void parse_file(char *file_name)
{
    FILE *file_pointer;
    // Open the file to read
    file_pointer = fopen(file_name, "r");

    // Checks to see if the file was not opened.
    if (file_pointer == NULL)
    {
        printf("ERROR: Unable to open file \"%s\"\n", file_name);
        return;
    }

    char *line;
    bool hasData = 1;
    do
    {
        line = nextLine(file_pointer, MAX_LENGTH);
        print_formated_line(line);
        hasData = strlen(line) != 0;

        //free(line);
    } while (hasData == 1);

    fclose(file_pointer);
}
void print_formated_line(char *line_value)
{
    
}
