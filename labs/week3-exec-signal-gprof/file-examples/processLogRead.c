#include <stdio.h>
#include <stdlib.h>

int main()
{
   char *name[50];
   FILE *fptr;
   fptr = fopen("log.txt","r");

   if (fptr == NULL){
       printf("Error! opening file");
       exit(1);
   }

   fscanf(fptr,"%s",&name);

   printf("\n\nValue of name = %s\n\n",name);
   fclose(fptr); 
  
   return 0;
}
