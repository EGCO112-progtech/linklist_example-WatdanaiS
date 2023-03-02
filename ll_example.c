
// Fig. 12.3: fig12_03.c
// Inserting and deleting nodes in a list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// self-referential structure                       
struct Node {                                      
   int id; // each listNode contains a student id number
   char name[30]; // name of student that display alongside the id
   struct Node *nextPtr; // pointer to next node
   struct Node *pPtr; // pointer to next node
}; // end structure listNode                        

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr; // synonym for ListNode*

// prototypes

void insert( LLPtr *sPtr, int value , char stdname[30]);
int deletes( LLPtr *sPtr, int value );
int isEmpty( LLPtr sPtr );
void printList( LLPtr currentPtr );
void instructions( void );
void reverseList( LLPtr currentPtr );

int main( void )
{ 
   LLPtr startPtr = NULL; // initially there are no nodes
   unsigned int choice; // user's choice
   int idnum; // id num entered by user
   char idname[30]; // name entered by user

   instructions(); // display the menu
   printf( "%s", "? " );
   scanf( "%u", &choice ); // %u is unsigned (not negative) int

   // loop while user does not choose 3
   while ( choice != 3 ) { 

      switch ( choice ) { 
         case 1:
            printf( "%s", "Enter a student ID number: " );
            scanf( "%d", &idnum);
            printf( "%s", "Enter a student name: " );
            scanf( "%s", idname );
            insert( &startPtr, idnum , idname); // insert id number in list
            printList( startPtr );
            reverseList( startPtr );
           printf("\n");
            break;
         case 2: // delete an element
            // if list is not empty
            if ( !isEmpty( startPtr ) ) { 
               printf( "%s", "Enter number to be deleted: " );
               scanf( "%d", &idnum );

               // if character is found, remove it
               if ( deletes( &startPtr, idnum ) ) { // remove that ID number
                  printf( "%d deleted.\n", idnum );
                  printList( startPtr );
                  reverseList( startPtr );
                 printf("\n");
               } // end if
               else {
                  printf( "%d not found.\n\n", idnum );
               } // end else
            } // end if
            else {
               puts( "List is empty.\n" );
            } // end else

            break;
         default:
            puts( "Invalid choice.\n" );
            instructions();
            break;
      } // end switch

      printf( "%s", "? " );
      scanf( "%u", &choice );
   } // end while
  /* Clear all nodes at the end of nodes*/
   puts( "End of run." );
} // end main

// display program instructions to user
void instructions( void )
{ 
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order
void insert( LLPtr *sPtr, int value , char stdname[30])
{ 
   LLPtr newPtr; // pointer to new node
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list

   newPtr =(LLPtr) malloc( sizeof( LLnode ) ); // create node

   if ( newPtr != NULL ) { // is space available
      newPtr->id = value; // place value in node
      newPtr->nextPtr = NULL; // node does not link to another node
      newPtr->pPtr = NULL;
      strcpy(newPtr->name,stdname);
    
       
      previousPtr = NULL;
      currentPtr = *sPtr;

      // loop to find the correct location in the list       
      while ( currentPtr != NULL && value > currentPtr->id ) {
         previousPtr = currentPtr; // walk to ...               
         currentPtr = currentPtr->nextPtr; // ... next node 
      } // end while                                         

      // insert new node at beginning of list
      if ( previousPtr == NULL ) { 
         newPtr->nextPtr = *sPtr;
         if(currentPtr != NULL)
           currentPtr->pPtr=newPtr;
         *sPtr = newPtr;
        
      } // end if
      else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
         if(currentPtr!=NULL) 
           currentPtr->pPtr=newPtr;
         newPtr->pPtr=previousPtr;
         newPtr->nextPtr = currentPtr;
         
      } // end else
   } // end if
   else {
      printf( "%d not inserted. No memory available.\n", value );
   } // end else
} // end function insert

// delete a list element
int deletes( LLPtr *sPtr, int value )
{ 
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list
   LLPtr tempPtr; // temporary node pointer

   // delete first node
   if ( value == ( *sPtr )->id ) { 
      tempPtr = *sPtr; // hold onto node being removed
      *sPtr = ( *sPtr )->nextPtr; // de-thread the node
     if(*sPtr)
       (*sPtr)->pPtr=NULL;
      free( tempPtr ); // free the de-threaded node ( free ก็คือ delete นั่นแหละ )
      return value;
   } // end if
   else { 
      previousPtr = *sPtr;
      currentPtr = ( *sPtr )->nextPtr;

      // loop to find the correct location in the list
      while ( currentPtr != NULL && currentPtr->id != value ) { 
         previousPtr = currentPtr; // walk to ...  
         currentPtr = currentPtr->nextPtr; // ... next node  
      } // end while

      // delete node at currentPtr
      if ( currentPtr != NULL ) { 
         tempPtr = currentPtr;
        currentPtr=currentPtr->nextPtr;
         previousPtr->nextPtr = currentPtr;
        if(currentPtr != NULL)
        currentPtr->pPtr=previousPtr;
         free( tempPtr );
         return value;
      } // end if
   } // end else

   return '\0';
} // end function delete

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{ 
   return sPtr == NULL;
} // end function isEmpty

// print the list
void printList( LLPtr currentPtr )
{ 
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else { 
      puts( "The list is:" );

      // while not the end of the list
      while ( currentPtr->nextPtr!= NULL ) {
         printf( "%d (%s) --> ", currentPtr->id , currentPtr->name);
         currentPtr = currentPtr->nextPtr;   
      } // end while

      printf( "%d (%s) --> NULL\n",currentPtr->id , currentPtr->name);
       

     
       
   } // end else
} // end function printList

void reverseList( LLPtr currentPtr )
{ 
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "Reversed list is empty.\n" );
   } // end if
   else { 
      puts( "The reverse list is:" );
     while ( currentPtr->nextPtr!= NULL ) {
         currentPtr = currentPtr->nextPtr;
       }

      // while not the end of the list
      while ( currentPtr->pPtr!= NULL ) {
         printf( "%d (%s) --> ", currentPtr->id, currentPtr->name );
         currentPtr = currentPtr->pPtr;   
      } // end while

      printf( "%d (%s) --> NULL\n",currentPtr->id , currentPtr->name);
       

     
       
   } // end else
} // end function reverseList