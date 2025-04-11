#ifndef QFIFO_H
#define QFIFO_H

#include "global.h" // added by user it defines what info will be stored in array

typedef struct tagFQItem // one queue element
{ 
  QINFO* pInfo;     // info got from global.h
  tagFQItem* pNext; // pointer to the next element in array
} FQItem;

typedef struct // Queue type
{
  FQItem* pHead;  // pointer to the first queue item
  FQItem* pTail;  // pointer to the last queue item
} FQueue;

FQueue* FQCreate();                                                     // creating queue pointer (initialization)
int     FQEmpty( FQueue* q );                                           // checks if queue is empty or if it does not exist
int     FQEnqueue( FQueue* q, QINFO* p );                               // insert new item into queue and return if its sucessful
QINFO*  FQDequeue( FQueue* q );                                         // take first element from queue
void    FQClear( FQueue* q, void(__cdecl *freeMem )( const void* ) );   // clears whole queue and frees memory
void    FQRemove( FQueue** q, void(__cdecl *freeMem )( const void* ) ); // clears queue and then removes queue
void    FQDel( FQueue* q );                                             // removes one queue element and frees memory for it
void    FQPrint( FQueue* q, void(__cdecl *printInfo )( const void* ) ); // prints whole queue without changing head or tail
#endif