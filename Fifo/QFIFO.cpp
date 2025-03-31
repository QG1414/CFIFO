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

int FQEnqueue( FQueue* q, int x )
{
  if( !q )
    return 0;

  FQItem* newItem = (FQItem*)malloc( sizeof( FQItem ) );

  if( !newItem )
    return 0;

  newItem->key = x;
  newItem->pNext = NULL;

  if( !( q->pHead ) )
    q->pHead = newItem;
  else
    q->pTail->pNext = newItem;

  q->pTail = newItem;

  return 1;
}

int FQDequeue( FQueue* q )
{
  if( FQEmpty( q ) )
    return INT_MIN;

  int val = q->pHead->key;
  FQDel( q );

  return val;
}

void FQClear( FQueue* q )
{
  if( !q )
  {
    printf("Queue does not exist in FQClear\n");
    return;
  }

  while( !FQEmpty( q ) )
    FQDel( q );
}

void FQRemove( FQueue** q )
{
  if( !q )
  {
    printf("Queue does not exist in FQRemove\n");
    return;
  }

  FQClear( *q );
  free( *q );

  *q = NULL;
}

void FQDel( FQueue* q )
{
  if( FQEmpty( q ) )
  {
    printf("Queue is empty or does not exist in FQDel\n");
    //kolejka nie istnieje lub jest pusta
    return;
  }

  FQItem* ptr = q->pHead;
  q->pHead = ptr->pNext;
  free( ptr );
}