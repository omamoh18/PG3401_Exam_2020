#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _PERSON {
   char *name;
   int size;
   struct PERSON *pArray;
}PERSON;

void bubbleSort(PERSON * array, int n);
void swap (char **a, char **b);
int findElement(PERSON* person, int n);

int main (int argc, char *argV[]) {
   
   PERSON *array;
   int size = array->size;
   size = argc - 1;
   
   array = malloc(size* sizeof(*array));
   
   int i = 0;
   if (argc < 2) {
      printf("No command line arguments written!\n");
      return 1;
  }
   for (i = 0; i < size; i++) {
   
       array[i].name = argV[i + 1];
       size = strlen(argV[i + 1]);
       array[i].pArray = array;
  }
       bubbleSort(array, size);
       
   for (i = 0; i < size; i++) {

       printf("[%d] | %s | size %d\n", i, array[i].name, size);
     }
     return 0;
  }

//The sorting method
void bubbleSort (PERSON * array, int n) {
   int swapped = 1;
   while (swapped) {
         swapped = 0;
   for (int i = 1; i < n; i++) {
       if (strcmp(array[i-1].name, array[i].name) > 0) {
          swap (&array[i-1].name, &array[i].name);
          swapped = 1;
       }
     }
   }
}

// Swapping method
void swap (char **a, char **b) {
   char *pCurrent;
   pCurrent = *a;
   *a = *b;
   *b = pCurrent;
}

int findElement (PERSON * person, int n) {
      int i;
      PERSON * personArray = person->pArray; 
      for (i = 0; i < n; i++) {
          if (personArray[i].name == person->name) { 
             return i;
          }
    }
}

