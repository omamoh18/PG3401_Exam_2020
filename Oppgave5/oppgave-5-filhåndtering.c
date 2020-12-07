#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef char byte;

const byte *base64Table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int base64Decode(const byte *input, byte *output);
int findIndex(const byte value);

int main () {

   FILE *pFileOne; 
   FILE *pFileTwo;
   byte encoded[1024];
   byte decoded[1024];
   
   // Opening the file for reading
   if ((pFileOne = fopen("encoded-base64.txt", "r")) == NULL) {
      printf("The file cannot be opened %s\n", "encoded-base64.txt");
      return 1; // Just to state which file is not opening
   } else {
      printf("File is open for reading\n");
   }
   // Opening the we are writing to
   if ((pFileTwo = fopen("decoded-base64.txt", "w" )) == NULL) {
      printf("The file cannot be opened %s\n", "decoded-base64.txt");
      return 2; // Just to state which file is not opening
   }       printf("File is open for writing\n");
   
   
   /* Reading content from the file
   pFileOne = fopen("encoded-base64.txt", "r");*/
   while (fgets ( encoded, 1024, pFileOne ) != NULL) {
         
         // Checking if i read 
         //the data from fileone
         printf("Data is read : %s" , encoded); 
         
         base64Decode(encoded, decoded);
          
         // Write the dataToBeWritten into the file 
         if ( strlen (  decoded  ) > 0 ) {
            
           // Is data decoded?
           printf("I hope it is decoded...%s\n", decoded); 
             
            // writing in the file using fputs() 
            fputs(decoded, pFileTwo) ;    
            fputs("\n", pFileTwo) ; 
        } 

   }
   
   printf ("The content is copied to decoded-base64 %s", decoded);
   
   // Closing the files
   fclose (pFileOne);
   fclose (pFileTwo);
   
   return 0;
}

int base64Decode(const byte *input, byte *output) {
    
   const size_t len = strlen(input);
   const byte *this = input;
   const byte *end = input + len;
   int buffer;
 
   if (len % 4 != 0) {
   return 1;
  }
    
 
   while (this != end) {
         const byte byteOne = *this++;
         const byte byteTwo = *this++;
         
         // This can be the 1st padding byte
         const byte byteThree = *this++;
         // This can be first or second
         const byte byteFour= *this++;
 
         const int indexOne = findIndex(byteOne);
         
         const int indexTwo = findIndex(byteTwo);

        // The first byte is giving
        // us 6 bits
        buffer = indexOne << 2;
        // We laso get 2 bits from
        //the first byte
        buffer |= indexTwo >> 4;
        // This is to output
        // the first byte
        *output++ = buffer;
 
        if (byteFour != '=') {
            
           const int indexThree = findIndex(byteThree);
 
            //The second byte is giving
            //us 4 bits 
            buffer = (indexTwo & 0xF) << 4;
            // The second byte is giving
            // us 4 bits
            buffer += indexThree >> 2;
            // This is to output
            // the second byte
            *output++ = buffer;
 
            if (byteFour != '=') {
                
                const int indexFour = findIndex(byteFour);
                
                // We are getting 2 bits 
                // from the third byte
                buffer = (indexThree & 0x3) << 6;
                // We get 6 bits from
                // the third byte
                buffer |= indexFour;
                // This is to output
                // the third byte
                *output++ = buffer;
            }
        }
    }
 
    // To mark the end 
    // of the string
    *output = '\0';
    
    return 0;
}

int findIndex(const byte value) {
   
   /*This is for locating the position
   of every encoded characther in the 
   table.*/
   if (value >= 'A' && 'Z' >= value) {
   return value - 'A';
   
   } else if (value >= 'a' && 'z' >= value) {
   return value - 'a' + 26;
   
   } else if ('0' <= value && value <= '9') {
   return value - '0' + 52;
   
   } else if (value == '+' ) {
   return 62;

   } else if (value == '/') {
   return 63;
   
   }
   
   return -1;
}
