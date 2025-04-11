#include "QFIFO.h"
#include <stdlib.h>
#include <stdio.h>

FQueue* FQCreate()
{
  FQueue* q = (FQueue*)malloc( sizeof( FQueue ) ); // allocate memory for queue

  if( !q ) // if not sucessful return null
    return NULL;

  q->pHead = q->pTail = NULL; // set values for head and tail to null

  return q; // return pointer to queue
}

int FQEmpty( FQueue* q )
{
  return !q || !( q->pHead ); // check if q exists and if head is not Null
}

int FQEnqueue( FQueue* q, QINFO* p )
{
  if( !q || !p ) // in case q or p is not existing return with 0 (False)
    return 0;

  FQItem* newItem = (FQItem*)malloc( sizeof( FQItem ) ); // allocate memory for new queue element

  if( !newItem ) // check if allocation was sucessful if not return 0 (False)
    return 0;

  newItem->pInfo = p; // set p added by user as pInfo value
  newItem->pNext = NULL; // set next item of created element to NULL

  if( !( q->pHead ) ) // if head is null then head is newItem
    q->pHead = newItem;
  else                // else set tail next value to new item
    q->pTail->pNext = newItem;

  q->pTail = newItem; // set tail value to new item

  return 1; // return that enqueue was sucessful
}

QINFO* FQDequeue( FQueue* q )
{
  if( FQEmpty( q ) ) // check if queue is not empty
    return NULL;

  QINFO* val = q->pHead->pInfo; // get value in current head
  FQDel( q ); // delete head element

  return val; // return value we got
}

void FQClear( FQueue* q, void(__cdecl *freeMem )( const void* ) )
{
  if( !q ) // check if queue exists
  {
    printf( "Queue does not exist in FQClear\n" );
    return;
  }
  
  if( !freeMem )
  {
    printf( "Free memory function does not exits\n" );
    return;
  }

  while( !FQEmpty( q ) )        // repeat until queue is empty
    freeMem( FQDequeue( q ) );  // free memory from queue and delete queue elements
}

void FQRemove( FQueue** q, void(__cdecl *freeMem )( const void* ) )
{
  if( !q || !(*q) ) // check if queue adress exists and queue pointer exists
  {
    printf( "Queue does not exist in FQRemove\n" );
    return;
  }

  if( !freeMem )
  {
    printf( "Free memory function does not exits\n" );
    return;
  }

  FQClear( *q, *freeMem );  // clear queue elements
  free( *q );               // remove queue from memory

  *q = NULL; // set queue to null
}

void FQDel( FQueue* q )
{
  if( FQEmpty( q ) ) // if queue is empty or does not exists return
  {
    printf( "Queue is empty or does not exist in FQDel\n" );
    return;
  }

  FQItem* ptr = q->pHead; // get head pointer element
  q->pHead = ptr->pNext; // set head to the next element

  if( !(q->pHead) ) // in case current head is NULL set tail to NULL that we return to base values
    q->pTail = NULL;

  free( ptr ); // free item from memory
}

void FQPrint( FQueue* q, void(__cdecl *printInfo )( const void* ) )
{
  if( !q ) // check if queue exists
  {
    printf( "Queue is empty or does not exist in FQPrint\n" );
    return;
  }

  if( !printInfo )
  {
    printf( "print info function does not exits\n" );
    return;
  }

  FQItem* head = q->pHead; // get pointer of head element

  while( head ) // while head is not NULL
  {
    printInfo( head->pInfo ); // print info about what is currently in head
    head = head->pNext;       // change head to next element
  }
}