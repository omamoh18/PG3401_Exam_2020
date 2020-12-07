#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct _NODE {
   struct _NODE* next;
   struct _NODE* prev;
   char* name;
   int age;
   char* district;
} NODE;

typedef struct _LINKED_LIST {
   NODE* head;
   NODE* tail;
} LINKED_LIST;

void addNode(LINKED_LIST* list, char* name, int age, char* district);
NODE* createNode(char* name, int age, char* district);
NODE* findNode(LINKED_LIST* list, int index);
void deleteNodesWithName(LINKED_LIST* list, char* name);
int getSizeOfList(LINKED_LIST* list);
void deleteNodesWithAge(LINKED_LIST* list, int age);
//void validateInput (LINKED_LIST *list, int age, char *operator);

int main () {
   LINKED_LIST list = { NULL, NULL };
   char name[100];
   char input[100];
   int age;
   char district[100];
   int choice;
   char indexInput[100];
   int index;
   char deletionName[100];
   int sizeOfList;
   char *check;

   // Adding som dummy nodes
   //addNode(&list, "Borat", 25, "Nursultan");
   //addNode(&list, "Trump", 20, "Tehran");

   // add a couple of same names, and lets see if we can delete them all.
   addNode(&list, "Goku", 30, "Oslo");
   addNode(&list, "Goku", 30, "Florida");
   addNode(&list, "Goku", 30, "Kami House");
   //addNode(&list, "Bengt", 18, "LA");//1

   while (choice != '0') {
         printf ("Main menu\n");
         printf ("1.Add node\n");
         printf ("2.Display list\n");
         printf ("3.Check size of list\n");
         printf ("4.Delete node with same name\n");
         printf ("5.Delete node with same age\n");
         printf ("0. Exit\n");
         printf ("please, enter your choice:\n");

         choice = getchar();
         getchar();

   switch (choice) {
   case '1':
         printf("Enter your name: ");
         fgets(name, 100, stdin);
         name[strlen(name) -1] = '\0';
         
         printf("Enter your age: ");
         fgets(input, 100, stdin);
         age = atoi(input);
         
         printf("Enter your district: ");
         fgets(district, 100, stdin);
         district[strlen(district) -1] = '\0';
         
         addNode(&list, name, age, district);
         break;
   case '2':
         printf("Enter index: ");
         fgets(indexInput, 100, stdin);
         
         indexInput[strlen(indexInput) -1] = '\0';
         index = atoi(indexInput);
         
         findNode(&list, index);
         break;
   case '3':
         sizeOfList = getSizeOfList(&list);
         printf("Size of list before deletion is: %i\n", sizeOfList);
         sizeOfList = getSizeOfList(&list);
         break;
   case '4':
         sizeOfList = getSizeOfList(&list);
         
         printf("Enter name: ");
         fgets(name, 100, stdin);
         name[strlen(name) -1] = '\0';
         
         printf("Deleting nodes now...\n");
         deleteNodesWithName(&list, name);
         printf("Deletion done...\n");
         
         sizeOfList = getSizeOfList(&list);
         printf("Size of list after deletion is: %i\n", sizeOfList);
         break;
   case '5':
         sizeOfList = getSizeOfList(&list);
         
         printf("Enter age: ");
         fgets(input, 100, stdin);
         age = atoi(input);
         
         printf("Deleting nodes now...\n");
         //validateInput(&list, age, check);
         printf("Deletion done...\n");
         
         sizeOfList = getSizeOfList(&list);
         printf("Size of list after deletion is: %i\n", sizeOfList);
         break;
   case '0':
         exit(0);
         break;
      }
         printf("\n");
   }
         return 0;
}

void addNode(LINKED_LIST* list, char* name, int age, char* district) {
   // Creating the node first
   NODE* newNode = createNode(name, age, district);

   if (list->head == NULL) {
      // Initialing the list.
      list->head = newNode;
      list->tail = newNode;
}
   else {
      // Adding node to end of list
      NODE* oldTail = list->tail;
      oldTail->next = newNode;
      newNode->prev = oldTail;
      list->tail = newNode;
      newNode->next = NULL;
   }
}

NODE* findNode(LINKED_LIST* list, int index) {
   NODE* currentNode = list->head;
   if (index == 1) {
      printf("name: %s\n", (currentNode->name));
      printf("age: %d\n", (currentNode->age));
      printf("district: %s\n", (currentNode->district));
      return currentNode;
}
   int count = 1;
   while (currentNode != NULL && count != index) {
      currentNode = currentNode->next;
      count++;
      printf("name: %s\n", (currentNode->name));
      printf("age: %d\n", (currentNode->age));
      printf("district: %s\n", (currentNode->district));
}
      // Returns currentNode or null, if index is larger than size of list.
      return currentNode;
}

void deleteNodesWithName(LINKED_LIST* list, char* name) {
   NODE* currentNode = list->head;

   while (currentNode != NULL) {
   
   if (strcmp(currentNode->name, name) == 0) {
      
      // deletion process 
      NODE* nodeToBeDeleted = currentNode;
      NODE * prevNode = currentNode->prev;
      NODE * nextNode = currentNode->next;
   
   if (currentNode->prev == NULL && currentNode->next == NULL) { 
      
      free(nodeToBeDeleted->district);
      free(nodeToBeDeleted->name);
      free(nodeToBeDeleted);
      
      list->head = NULL;
      list->tail = NULL;
      currentNode = NULL;
      return;
   
   } else if (currentNode->prev == NULL && currentNode->next != NULL) {
      
      list->head = currentNode->next;
      
      list->head->prev = NULL;
      
      free(nodeToBeDeleted->district);
      free(nodeToBeDeleted->name);
      free(nodeToBeDeleted);
   
   } else if (currentNode->next == NULL) {
     
     list->tail = currentNode->prev;
     
     list->tail->next = NULL;
     
     free(nodeToBeDeleted->district);
     free(nodeToBeDeleted->name);
     free(nodeToBeDeleted);
   
   } else {
     
     currentNode->next->prev = currentNode->prev;
     currentNode->prev->next = currentNode->next;
     
     free(nodeToBeDeleted->district);
     free(nodeToBeDeleted->name);
     free(nodeToBeDeleted);
}
    currentNode = nextNode;
   }
 }
}

void deleteNodesWithAge(LINKED_LIST* list, int age) {
   NODE* currentNode = list->head;

   while (currentNode != NULL) {
   
   if (currentNode->age, age) {
   
      // deletion process 
      NODE* nodeToBeDeleted = currentNode;
      NODE * prevNode = currentNode->prev;
      NODE * nextNode = currentNode->next;
   
   if (currentNode->prev == NULL && currentNode->next == NULL) { 
   
      free(nodeToBeDeleted->district);
      free(nodeToBeDeleted->name);
      free(nodeToBeDeleted);
   
      list->head = NULL;
      list->tail = NULL;
      currentNode = NULL;
   
      return;
   
   } else if (currentNode->prev == NULL && currentNode->next != NULL) {
   
      list->head = currentNode->next;
   
      list->head->prev = NULL;
   
      free(nodeToBeDeleted->district);
      free(nodeToBeDeleted->name);
      free(nodeToBeDeleted);
   
   } else if (currentNode->next == NULL) {
   
     list->tail = currentNode->prev;
   
     list->tail->next = NULL;
   
     free(nodeToBeDeleted->district);
     free(nodeToBeDeleted->name);
     free(nodeToBeDeleted);
   
   } else {
   
     currentNode->next->prev = currentNode->prev;
     currentNode->prev->next = currentNode->next;
   
     free(nodeToBeDeleted->district);
     free(nodeToBeDeleted->name);
     free(nodeToBeDeleted);
   }
    currentNode = nextNode;
  }
 }
}

NODE* createNode(char* name, int age, char* district) {
   
   // We declare enough size for the struct pointer, and each pointer within.
   NODE* newNode = malloc(sizeof(NODE));
   newNode->next = NULL;
   newNode->prev = NULL;
   
   newNode->name = malloc(sizeof(char) * (strlen(name) + 1));
   
   strcpy(newNode->name, name);
   newNode->district = malloc(sizeof(char) * (strlen(district) + 1));
   
   strcpy(newNode->district, district);
   
   newNode->age = age;
   
   return newNode;
}

// This is a helper function to help debugging the list.
int getSizeOfList(LINKED_LIST* list) {

   int count = 0;

   NODE* currentNode = list->head;

   while (currentNode != NULL) {

         currentNode = currentNode->next;
         count++;
}
   return count;
}

void validateInput (LINKED_LIST *list, int age, char *operator) {
   NODE* currentNode = list->head;
   int result;
   if (strcmp(operator, "<") == 0) { 
      if (currentNode->age < age) {
         deleteNodesWithAge(list, age);
         }
   } else if(strcmp(operator, ">") == 0) {
            if (currentNode->age > age) {
               deleteNodesWithAge(list, age);
         }
   } else if (strcmp(operator, "==") == 0) { 
            if (currentNode->age == age) {
               deleteNodesWithAge(list, age);
      }
  } else {
    printf("NOT WORKING");
 }

}
