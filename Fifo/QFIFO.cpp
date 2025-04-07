#include "QFIFO.h"
#include <stdlib.h>
#include <stdio.h>

FQueue* FQCreate()
{
  FQueue* q = (FQueue*)malloc( sizeof( FQueue ) );

  if( !q )
    return NULL;

  q->pHead = q->pTail = NULL;

  return q;
}

int FQEmpty( FQueue* q )
{
  return !q || !( q->pHead );
}

int FQEnqueue( FQueue* q, QINFO* p )
{
  if( !q )
    return 0;

  FQItem* newItem = (FQItem*)malloc( sizeof( FQItem ) );

  if( !newItem )
    return 0;

  newItem->pInfo = p;
  newItem->pNext = NULL;

  if( !( q->pHead ) )
    q->pHead = newItem;
  else
    q->pTail->pNext = newItem;

  q->pTail = newItem;

  return 1;
}

QINFO* FQDequeue( FQueue* q )
{
  if( FQEmpty( q ) )
    return NULL;

  QINFO* val = q->pHead->pInfo;
  FQDel( q );

  return val;
}

void FQClear( FQueue* q, void( __cdecl *freeMem )( const void* ) )
{
  if( !q )
  {
    printf("Queue does not exist in FQClear\n");
    return;
  }

  while( !FQEmpty( q ) )
    freeMem( FQDequeue( q ) );
}

void FQRemove( FQueue** q, void( __cdecl *freeMem )( const void* ) )
{
  if( !q || !(*q) )
  {
    printf("Queue does not exist in FQRemove\n");
    return;
  }

  FQClear( *q, *freeMem );
  free( *q );

  *q = NULL;
}

void FQDel( FQueue* q )
{
  if( FQEmpty( q ) )
  {
    printf("Queue is empty or does not exist in FQDel\n");
    return;
  }

  FQItem* ptr = q->pHead;
  q->pHead = ptr->pNext;

  if( !(q->pHead) )
    q->pTail = NULL;

  free( ptr );

}

void FQPrint( FQueue* q, void( __cdecl *printInfo )( const void* ) )
{
  if( !q )
  {
    printf("Queue is empty or does not exist in FQPrint\n");
    return;
  }

  FQItem* head = q->pHead;

  while( head )
  {
    printInfo( head->pInfo );
    head = head->pNext;
  }
}