/* S2019.c
**
** Course: CMPS 250
** Author: P. M. J. 
** Last Modified: January 31, 2019
** Collaborated with: Worked alone.
**
** Java application that forms and prints initials from full names input in the
** form last, first m. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Strings.h"

#define LIMIT 30
#define MAX_LENGTH 48

#define NL '\n'
#define NC '\0'
#define COMMA ','
#define PERIOD '.'
#define BLANK ' '

void initialsOf(char *fullName, char *result);

int main(int argc, char *argv[]) {
   char *line, initials[7];
   int length;
/* Illustrative instructions to echo the run-time arguments
   int i;
   printf("argc is %d\n",argc);
   for(i=0;i<argc;i++) {
     printf("%d:\"%s\"",i,argv[i]);
     if((i+1)<argc) { printf(","); }
   }
   printf("\n");
*/
   if(argc > 1) {  //Check to make sure the run-time argument is present
     FILE *fptr;
     fptr = fopen(argv[1],"r");
     if(fptr != NULL) {  //Check to make sure the file has been opened
       do {
         line = nextLine(fptr,MAX_LENGTH);
         Strim(line);
         length = Slength(line);
         if(length > 0) {
           printf("\"%s\" yields ",line);
           initialsOf(line,initials);
           printf("\"%s\"\n",initials);
         }
         free(line);
       } while (length > 0);
       fclose(fptr);
     } else {
       printf("--->ERROR: unable to open file named \"%s\"\n",argv[1]);
     }
   } else {
     printf("--->ERROR: Required filename argument missing\n");
   }
}

void initialsOf(char *fullName, char *result) {
   char first = BLANK, middle = BLANK, last = BLANK;
   int length, index = 0, indexOfComma, indexOfPeriod;
   char *subString;
   length = Slength(fullName);
   if(length > 0) {
      last = fullName[0];
      indexOfPeriod = SindexOf(fullName,PERIOD);
      if(indexOfPeriod > 0) {
         middle = fullName[indexOfPeriod-1];
      }
      indexOfComma = SindexOf(fullName,COMMA);
      if(indexOfComma > 0) {
         subString = SsubStr(fullName,(indexOfComma+1),length);
         if(subString != NULL) {
           Strim(subString);
           if(Slength(subString) > 0) {
              result[0] = subString[0];  result[1] = PERIOD;  index = 2;
           }
           free(subString);
         }
      }
      if(middle != BLANK) {
        result[index] = middle;  result[index+1] = PERIOD; index = index + 2;
      }
      if(last != BLANK) {
        result[index] = last;  result[index+1] = PERIOD; index = index + 2;
      }
   }
   result[index] = NC;
}
