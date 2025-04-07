#ifndef QFIFO_H
#define QFIFO_H

#include "global.h" // dostarczany przez uzytkownika tej kolejki

typedef struct tagFQItem
{ 
  QINFO* pInfo;
  tagFQItem* pNext;
} FQItem;   //FIFO Queue Item

typedef struct
{
  FQItem* pHead;  // ptr to the first queue item
  FQItem* pTail;  // ptr to the last queue item
} FQueue;  /// typ kolejkowy

FQueue* FQCreate();                    // queue initiating  (NULL - fail)
int     FQEmpty( FQueue* q );          // if FIFO empty returned 1 else 0 te¿ zwraca 1 gdy q jest nullem
int     FQEnqueue( FQueue* q, QINFO* p ); // insert new item at the end sprawdzanie czy kolejka jest pusta
QINFO*  FQDequeue( FQueue* q );        // take out the first item
void    FQClear( FQueue* q, void( __cdecl *freeMem )( const void* ) );          // clears the queue czyszczenie kolejki do puki jest nie pusta
void    FQRemove( FQueue** q, void( __cdecl *freeMem )( const void* ) );         // clears the queue  (=QFClear()) and removes sprawdza czy istniej, nastepnie czysci i zwalnia pamiêæ
void    FQDel( FQueue* q );            // removes only first item usuniecie elementu
void    FQPrint( FQueue* q, void( __cdecl *printInfo )( const void* ) );
#endif