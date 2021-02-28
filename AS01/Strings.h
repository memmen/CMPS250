//File Strings.h,  Strings Operations
//     ---------
//CMPS 250 - Spring 2017, P.M.J.

/* Functional subprogram that returns the length of the given string.
*/
int Slength(char string[]);

/* Subprogram  that copys the characters in one array of charactters to be
   the values of another array of characters.
*/
void Scopy(char source[], char destin[]);

/* Functional subprogram  that returns an integer indicating the result of 
   the comparision of one string to another.
*/
int ScompareTo(char one[], char two[]);

/* Subprogram that modifies the representation of the given string by "removing"
   all leading blank characters from the beginning of the string.
*/
void StrimLeading(char *string);

/* Subprogram that modifies the representation of the given string by "removing"
   all trailing blank characters from the end of the string.
*/
void StrimTrailing(char *string);

/* Subprogram that modifies the representation of the given string by "removing"
   all leading and trailing blank characters from the string.
*/
void Strim(char *string);

/* Subprogram that returns the index of the first occurrence of given character 
   in the substring of given string starting at the given index, or -1 if the 
   character is not found.
*/
int SnextIndexOf(char *string, char c, int startIndex);

/* Subprogram that returns the index of the first occurrence of given character 
   in the given string or -1 if the character is not found.
*/
int SindexOf(char *string, char c);

/* Subprogram that allocates and returns an array of characters containing 
   the representation of a copy of the substring indicated by the given 
   string and starting and stopping indexes.
*/
char *SsubStr(char *string, int startIndex, int stopIndex);

/* Subprogram that reads an entire "line" of input (up to, and including the end of
   line character), allocates and returns the array representation of that string.
   Note that the array does not include the end of line character though.
*/
char *nextLine(FILE *file, int maxLength);
