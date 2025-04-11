#include <stdio.h>
#include <stdlib.h>
#include "QFIFO.h"

void freeInfo( const void* );            // method to free QINFO from memory
QINFO* allocInfo( int key, int arr1, int arr2 ); // method to allocate QINFO in memory
void printInfo( const void* pInfo );     // method to print info into console

#define QINFO_TAB_SIZE 2  // QINFO size of dynamic array, now it holds 2 items
#define DEBUG_PRINT       // If more specific printing should be enabled

int main()
{
  // Create Queue
  FQueue* q = FQCreate();



  // If creation was not sucessful return with error message
  if( !q )
  {
    printf( "MEMORY allocation error for queue\n" );
    return 1;
  }



  // Add 4 elements to queue and print whole queue
#ifdef DEBUG_PRINT
  printf( "Enqueue elements\n" );
#endif

  for( int i=1; i<=4; i++ )
  {
    QINFO* p = allocInfo( i, i+1, i+2 );

    if( !p )
    {
      printf( "MEMORY allocation error for QINFO\n" );
      return 2;
    }

    if( !FQEnqueue( q, p ) )
    {
      printf( "Error while inserting value into queue\n" );
      return 3;
    }
  }

#ifdef DEBUG_PRINT
  printf( "\nInvoke FQPrint\n" );
#endif
  FQPrint( q, printInfo );
  


  // Dequeue 3 elements with printing from queue and then print whole queue
#ifdef DEBUG_PRINT
  printf( "\n\nDequeue element\n" );
#endif

  for( int i=0; i<3; i++ )
  {
    QINFO* QInfo = FQDequeue( q );
    printInfo( QInfo );
    freeInfo( QInfo );
  }

#ifdef DEBUG_PRINT
  printf( "\nInvoke FQPrint\n" );
#endif
  FQPrint( q, printInfo );

  

  // Enqueue 2 elements and then print whole queue
#ifdef DEBUG_PRINT
  printf( "\n\nEnqueue elements\n" );
#endif

  for( int i=0; i<2; i++ )
  {
    QINFO* p = allocInfo( i+10, i+10, i+20 );

    if( !p )
    {
      printf( "MEMORY allocation error for QINFO\n" );
      return 4;
    }

    if( !FQEnqueue( q, p ) )
    {
      printf( "Error while inserting value into queue\n" );
      return 5;
    }
  }

#ifdef DEBUG_PRINT
  printf( "\nInvoke FQPrint\n" );
#endif
  FQPrint( q, printInfo );



  // Clear whole queue
#ifdef DEBUG_PRINT
  printf( "\n\nClear Queue\n" );
#endif
  FQClear( q, freeInfo );

  

  // Enqueue 3 elements and then print whole queue
#ifdef DEBUG_PRINT
  printf( "\n\nEnqueue elements\n" );
#endif

  for( int i=0; i<3; i++ )
  {
    QINFO* p = allocInfo( i+100, i+100, i+200 );

    if( !p )
    {
      printf( "MEMORY allocation error for QINFO\n" );
      return 6;
    }

    if( !FQEnqueue( q, p ) )
    {
      printf( "Error while inserting value into queue\n" );
      return 7;
    }
  }

#ifdef DEBUG_PRINT
  printf( "\nInvoke FQPrint\n" );
#endif
  FQPrint( q, printInfo );



  // Dequeue 1 element with printing and then print whole queue
#ifdef DEBUG_PRINT
  printf( "\n\nDequeue element\n" );
#endif

  QINFO* QInfo = FQDequeue( q );
  printInfo( QInfo );
  freeInfo( QInfo );

#ifdef DEBUG_PRINT
  printf( "\nInvoke FQPrint\n" );
#endif
  FQPrint( q, printInfo );



  // Remove whole queue
#ifdef DEBUG_PRINT
  printf( "\n\nRemove Queue\n" );
#endif
  FQRemove( &q, freeInfo );



  return 0;
}

void freeInfo( const void* pInfo )
{
  if( !pInfo )
    return;

  QINFO* p = (QINFO*)pInfo;

  free( p->pTab ); // we need to first free array in QINFO
  free( p );       // we free QINFO from memory after array is cleared
}

QINFO* allocInfo( int key, int arr1, int arr2 )
{
  QINFO* pInf = (QINFO*)malloc( sizeof( QINFO ) ); // allocate memory for QINFO

  if( !pInf ) // if not sucessful return NULL
    return NULL;

  pInf->pTab = (int*)malloc( QINFO_TAB_SIZE * sizeof( int ) ); // allocate memory for array in QINFO

  if( !( pInf->pTab ) ) // if array creation not sucessful then return
  {
    free( pInf ); // before returning free memory alocated for QINFO
    return NULL;
  }

  pInf->key = key;      // assign key value
  pInf->pTab[0] = arr1;  // assign first array value
  pInf->pTab[1] = arr2;  // assign second array value

  return pInf; // return created pointer
}

void printInfo( const void* pInfo )
{
  // custom print for our data in QINFO, it changes depending on what we set in global.h
  printf( "key = %d pTab[0] = %d pTab[1] = %d\n",
          ((QINFO*)pInfo)->key,
          ((QINFO*)pInfo)->pTab[0],
          ((QINFO*)pInfo)->pTab[1] );
}