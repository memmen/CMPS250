/* AS01.c
**
** Course: CMPS 250
** Author: Brian Sean Memmen. 
** Last Modified: Feb 28, 2021
** Collaborated with: Bradley Hnatow.
**
** C application that expects the name of an Assembly Language source program as its 
** single Run-Time Argument, then proceeds to read each line in that file, reformatting it into “perfectly” 
** aligned columns and printing it out.
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Strings.h"

#define SPACING 20
#define MAX_LENGTH 100

void parseFile(char *fileName);
void printFormatedLine(char *lineValue);
char *findComment(char *lineValue);
char *findLabel(char *lineValue);
char *findColonComment(char *lineValue);
char *findDoubleSlashComment(char *lineValue);
char *findOperator(char *lineValue);
char *findOperands(char *lineValue);
char *removeTabs(char *lineValue);
void printLine(char *comment, char *label, char *operator, char * operands);
void format(char *value);
void emptySpacing();

/*
 * Function:  main 
 * --------------------
 * Entry point to program
 *
 *  argc: number of arguments passed in
 *  argv: array of arguments values
 *
 *  returns: int
 */
int main(int argc, char *argv[])
{
    if (argc > 1) // Name of file is passes in
        parseFile(argv[1]);
    else
        printf("ERROR: No filename argument was given\n");
    return 0;
}

/*
 * Function:  parseFile 
 * --------------------
 * Reads each line in of the given filename and reformates it into “perfectly” 
 * aligned columns and printing it out
 *
 *  fileName: name of file
 *
 *  returns: void
 */
void parseFile(char *fileName)
{
    // Pointerr file
    FILE *filePointer;
    // Open the file to read
    filePointer = fopen(fileName, "r");

    if (filePointer == NULL) // File not opened
    {
        printf("ERROR: Unable to open file \"%s\"\n", fileName);
        return;
    }

    char *line; // Holds the value of the current line in file
    do
    {
        line = nextLine(filePointer, MAX_LENGTH); // Value of current line
        line = removeTabs(line);                  // Replace the tabs with spaces
        // Copy the line to a different char* for
        // it can be manipulated by other functions without
        // modifying the check to see if the linbe

        char *copyLine = (char *)malloc(MAX_LENGTH);
        Scopy(line, copyLine);

        // Print the line from the file in a formated format
        printFormatedLine(copyLine);
    } while (strlen(line) != 0);

    fclose(filePointer); //Destroy the pointer to the file
}

/*
 * Function:  removeTabs 
 * --------------------
 * Removes all tabs(\t) from the line and replace them 
 * with spaces.
 *
 *  lineValue: current lines value
 *
 *  returns: char*
 */
char *removeTabs(char *lineValue)
{

    for (int index = 0; index < Slength(lineValue); index++)
        if (lineValue[index] == '\t')
            lineValue[index] = ' ';
    return lineValue;
}

/*
 * Function:  printFormatedLine 
 * --------------------
 * Given the value of a line, parses the line into
 * a formated column layout.
 *
 *  lineValue: current lines value
 *
 *  returns: void
 */
void printFormatedLine(char *lineValue)
{

    // Trims out any extra spaces in the string
    Strim(lineValue);

    // Prase out values
    char *comment = findComment(lineValue);
    char *label = findLabel(lineValue);
    char *operator= findOperator(lineValue);
    char *operands = findOperands(lineValue);

    // Print values
    printLine(comment, label, operator, operands);
}

/*
 * Function:  printLine 
 * --------------------
 * Prints out the column formated line
 *
 *  comment: value of the comment section of the line
 *  label: value of the label section of the line
 *  operator: value of the operator section of the line
 *  operands: value of the comment section of the line
 * 
 *
 *  returns: void
 */
void printLine(char *comment, char *label, char *operator, char * operands)
{

    // Line only contains a comment
    if (label == NULL && operator== NULL && operands == NULL && comment != NULL)
    {
        printf("%s", comment);
        printf("\n");
        return;
    }

    // Print label or empty spaces in its spot
    if (label != NULL)
        format(label);
    else
        emptySpacing();

    // Print operator or empty spaces in its spot
    if (operator!= NULL)
        format(operator);
    else
        emptySpacing();

    // Print operands or empty spaces in its spot
    if (operands != NULL)
        format(operands);
    else
        emptySpacing();

    // At least one other value that is not null then comment
    if ((label != NULL || operator!= NULL || operands != NULL || comment != NULL) && comment != NULL)
        format(comment);
    printf("\n");
}

/*
 * Function:  format 
 * --------------------
 * Prints string with spacing set by the value of SPACING
 *
 *  value: value of string to be printed out
 * 
 *  returns: void
 */
void format(char *value)
{
    int spacesNeeded = SPACING - Slength(value);
    printf("%s", value);
    for (int spaceIndex = 0; spaceIndex < spacesNeeded; spaceIndex++)
        printf(" ");
}

/*
 * Function:  emptySpacing 
 * --------------------
 * Prints the number of spaces set by the value of SPACING
 *
 * 
 *  returns: void
 */
void emptySpacing()
{
    for (int spaceIndex = 0; spaceIndex < SPACING; spaceIndex++)
        printf(" ");
}

/*
 * Function:  findComment 
 * --------------------
 * Finds the comment in a given string.
 * 
 * lineValue: Value of the current line
 *
 * returns: char*
 */
char *findComment(char *lineValue)
{

    // My program is going to check for only
    // 2 types of comments ; and //. The program
    // will start with // then check for ;
    char *colonComment = findColonComment(lineValue);
    if (colonComment != NULL)
        return colonComment;

    char *slashComment = findDoubleSlashComment(lineValue);
    if (slashComment != NULL)
        return slashComment;

    return NULL;
}

/*
 * Function:  findDoubleSlashComment 
 * --------------------
 * Finds the comment in a given string. Only looking for comments
 * that are started by //
 * 
 * lineValue: Value of the current line
 *
 * returns: char*
 */
char *findDoubleSlashComment(char *lineValue)
{
    int index = SindexOf(lineValue, '/');
    // If index is -1 a comment does not exist
    if (index == -1 || lineValue[index + 1] != '/')
        return NULL;

    // Get the substring of the comment
    char *comment = SsubStr(lineValue, index, Slength(lineValue));
    if (index > 0)
    {
        char *line = SsubStr(lineValue, 0, index);
        Scopy(line, lineValue);
        Strim(line);
    }
    else
    {
        Scopy("", lineValue);
    }

    return comment;
}

/*
 * Function:  findColonComment 
 * --------------------
 * Finds the comment in a given string. Only looking for comments
 * that are started by ;
 * 
 * lineValue: Value of the current line
 *
 * returns: char*
 */
char *findColonComment(char *lineValue)
{
    int index = SindexOf(lineValue, ';');
    // If index is -1 a comment does not exist
    if (index == -1)
        return NULL;

    // Get the substring of the comment
    char *comment = SsubStr(lineValue, index, Slength(lineValue));
    char *line = "";
    Scopy(line, lineValue);
    return comment;
}
/*
 * Function:  findLabel 
 * --------------------
 *  Finds the label in the string
 *
 *  lineValue: value of the line
 *
 *  returns: value of the label
 */
char *findLabel(char *lineValue)
{
    // Finds the index of the first : which means it is a label
    int index = SindexOf(lineValue, ':');

    // If index is -1 a label does not exist
    if (index == -1)
        return NULL;

    // Get the substring of the label
    char *label = SsubStr(lineValue, 0, index + 1);
    Strim(label); // Remove any extra padding
    if ((index + 1) == Slength(lineValue))
    {
        Scopy("", lineValue);
    }
    else
    {
        char *line = SsubStr(lineValue, index + 1, Slength(lineValue));
        Strim(line);
        Scopy(line, lineValue);
    }
    return label;
}
/*
 * Function:  findOperator 
 * --------------------
 * Parse the operator out of the string
 *
 * lineValue: value of the line
 *
 * returns: value of the operator
 */
char *findOperator(char *lineValue)
{
    if (Slength(lineValue) == 0)
        return NULL;

    Strim(lineValue);
    int index = SindexOf(lineValue, ' ');

    if (index == -1)
    {
        char *operator= SsubStr(lineValue, 0, Slength(lineValue));
        Scopy("", lineValue);
        return operator;
    }
    else
    {
        char *operator= SsubStr(lineValue, 0, index);
        char *line = SsubStr(lineValue, index, Slength(lineValue));
        Scopy(line, lineValue);
        Strim(line);
        return operator;
    }
}
/*
 * Function:  findOperands 
 * --------------------
 * Parse the operator out of the string
 *
 * lineValue: value of the line
 *
 * returns: value of the operator
 */
char *findOperands(char *lineValue)
{
    if (Slength(lineValue) == 0)
        return NULL;
    Strim(lineValue);
    return lineValue;
}