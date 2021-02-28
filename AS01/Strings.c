//File Strings.c,  Strings Operations
//     ---------
//CMPS 250 - Spring 2019, P.M.J.

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

/* Functional subprogram that returns the length of the given string.
*/
int Slength(char string[])
{
   return (int)strlen(string);
}

/* Subprogram  that copys the characters in one array of charactters to be
   the values of another array of characters.
*/
void Scopy(char source[], char destin[])
{
   strcpy(destin, source);
}

/* Functional subprogram  that returns an integer indicating the result of 
   the comparision of one string to another.
*/
int ScompareTo(char one[], char two[])
{
   int result = 0;
   int index = 0;
   int oneChar, twoChar;
   while ((one[index] == two[index]) && (one[index] != '\0'))
   {
      index = index + 1;
   }
   result = one[index] - two[index];
   return result;
}

/* Subprogram that modifies the representation of the given string by "removing"
   all leading blank characters from the beginning of the string.
*/
void StrimLeading(char *string)
{
   int index = 0;
   int prior;
   // Determine the number of leading blanks
   while (string[index] == ' ')
   {
      index = index + 1;
   }
   if (index > 0)
   {
      prior = 0;
      //Shift each following character earlier in the array
      while (string[index] != '\0')
      {
         string[prior] = string[index];
         prior = prior + 1;
         index = index + 1;
      }
      string[prior] = '\0';
   }
}

/* Subprogram that modifies the representation of the given string by "removing"
   all trailing blank characters from the end of the string.
*/
void StrimTrailing(char *string)
{
   int index = Slength(string);
   //Replace each trailing blnak by the null character
   while ((index > 0) && (string[index - 1] == ' '))
   {
      index = index - 1;
      string[index] = '\0';
   }
}

/* Subprogram that modifies the representation of the given string by "removing"
   all leading and trailing blank characters from the string.
*/
void Strim(char *string)
{
   StrimTrailing(string);
   StrimLeading(string);
}

/* Subprogram that returns the index of the first occurrence of given character 
   in the substring of given string starting at the given index, or -1 if the 
   character is not found.
*/
int SnextIndexOf(char *string, char c, int startIndex)
{
   int result = -1;
   if (startIndex < Slength(string))
   {
      result = startIndex;
      while ((string[result] != '\0') && (string[result] != c))
      {
         result = result + 1;
      }
      if (string[result] == '\0')
      {
         result = -1;
      }
   }
   return result;
}

/* Subprogram that returns the index of the first occurrence of given character 
   in the given string or -1 if the character is not found.
*/
int SindexOf(char *string, char c)
{
   int result = 0;
   while ((string[result] != '\0') && (string[result] != c))
   {
      result = result + 1;
   }
   if (string[result] == '\0')
   {
      result = -1;
   }
   return result;
}

/* Subprogram that allocates and returns an array of characters containing 
   the representation of a copy of the substring indicated by the given 
   string and starting and stopping indexes.
*/
char *SsubStr(char *string, int startIndex, int stopIndex)
{
   char *result = NULL;
   int length, index;
   if ((startIndex < stopIndex) && (stopIndex <= Slength(string)))
   {
      length = (stopIndex - startIndex);
      result = malloc(sizeof(char) * (length + 1));
      for (index = 0; startIndex < stopIndex; startIndex++)
      {
         result[index] = string[startIndex];
         index++;
      }
      result[index] = '\0';
   }
   return result;
}

/* Subprogram that reads an entire "line" of input (up to, and including the end of
   line character), allocates and returns the array representation of that string.
   Note that the array does not include the end of line character though.
*/
char *nextLine(FILE *file, int maxLength)
{
   char *result;
   char *string = malloc(sizeof(char) * (maxLength + 1));
   int length;
   int index = 0;
   do
   {

      string[index] = (char)getc(file);
      if (string[index] == EOF)
      {
         string[index] = '\n';
      }
      index = index + 1;
   } while ((index < maxLength) && (string[index - 1] != '\n'));

   string[index - 1] = '\0';
   result = malloc(sizeof(char) * (index + 1));
   strcpy(result, string);
   free(string);
   return result;
}
