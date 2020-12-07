#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>

typedef struct _CCD { 
char digit[5]; 
int convert; 
struct _CCD* p; 
} CCD;

int Backendprocesspayment(int a, int64_t c, CCD* p, const char* n, int b);
// Function asked for in the exam
void validateDate (char* e);

int ProcessCreditcardPayment(int a, char* c, char* e, char* n) {

   /* C99 type, our compiler supports this... */
   int64_t llCreditcard = 0; 
   char *i = (char*)c; 
   int j = 0;

   CCD *pc, *cc = (CCD*)malloc(sizeof(CCD));

   if (!cc) exit(1); 
      else pc = cc;
      memset(cc, 0, sizeof(CCD));
     
   /* Create 4 linked structures that holds one 4 digit
   segment of cardnumber: */
   while (i[0]) {

         pc->digit[j++] = i++[0];

   if (strlen(pc->digit) == 4) {

      pc->p = (CCD*)malloc(sizeof(CCD));

   if (!pc->p) exit(1);

      else {
      memset(pc->p, 0, sizeof(CCD)); pc = pc->p; j=0;
      }
   }
}

   /* Check that card starts with 4242, if not card is from
   another bank so we fail: */
   if (strcmp(cc->digit, "4242") != 0) { 

      free(cc); return 6; }

   /* Calculate the cardnumber as a 64 bit integer: */
   for (j = 12, pc = cc; pc; pc = pc->p, j-=4) {

       pc->convert = atoi(pc->digit) ;

       llCreditcard += ((int64_t)pc->convert) * pow(10, j);
      }

   /* If next section is 123x it is a bonus card with cash-back, we
   send type (x) to backend below: Set j to the type of bonus card */
   if (strncmp(cc->p->digit, "123", 3) == 0) {

      // The bug occurs here 
      //j = cc->p->digit[cc->p->digit[3]/((cc->p->digit[3]-'0')%9)];
      
      /* My soloution for fixing the bug
       explanation can be found in the pdf */
      j = cc->p->digit[cc->p->digit[3]];
     
     }

   /* Call backend function: */
   Backendprocesspayment(a, llCreditcard, cc, n, j);
   
   // Function to check
   // if the cc date is valid
   validateDate (e);
   
   //The second and third fault did i found is here 
   //free(cc);
   
   /* My soloution for fixing the bug
   explanation can be found in the pdf */
   free(cc->p->p->p->p);
   free(cc->p->p);
   free(cc->p);
   free(cc);

   return 0;
}

int Backendprocesspayment (int a, int64_t c, CCD* p, const char* n, int b) {
   return 0;
}

void validateDate (char* e) { 

   char *orignal;
   char *token;
   int cardMonth;
   int cardYear;
   int month;
   int year;
   int test;

   // Making copy of input
   orignal = strdup(e);

   // Arithmetic time 
   time_t now;

   // current time
   time(&now);

   // Converts time_t value to calendar time
   struct tm *local = localtime(&now);
   
   // get month of year
   month = local->tm_mon + 1;
   
   // Modulo operator for 
   // getting year as 20
   year = local->tm_year % 100;

   // Getting card month 
   token = strtok(orignal, "/");
   cardMonth = atoi(token); 
   
   // Getting card year 
   token = strtok(NULL, "/");
   cardYear = atoi(token); // + 2000
   
   printf("Card month : %d\n", cardMonth);
   printf("Card year : %d\n", cardYear);

   // Check if card is upto date
   if (cardMonth >= month && cardYear >= year) { 
     
      printf("Date of this card is valid\n");
      printf("Today date : %02d/%d\n", month, year);
 } else {

      printf("Date of this card has expired!\n");
      printf("Todays date : %02d/%d\n", month, year);
   }
}

int main() {

   // This one is never used
   // only sent back to Backendprocesspayment
   // that does nothing
   int empty = 0;

   //Same as a 
   char *emptyTwo;

   // test for 9 as the 8th number
   int test = ProcessCreditcardPayment(empty, "4242123956456743", "12/20", emptyTwo);
   printf("ProcessCreditcardPaymentOne : %d\n", test);

   // Test to see if date fails
   int testThree = ProcessCreditcardPayment(empty, "4242123056455543", "10/20", emptyTwo);
   printf("ProcessCreditcardPaymentThree : %d\n", testThree);

   // Date has expired
   //validateDate("10/20");
   // Date is valid
   //validateDate("12/20");

   return 0;
}
