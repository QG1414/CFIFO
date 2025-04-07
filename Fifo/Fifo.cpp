#include <stdio.h>
#include <stdlib.h>
#include "QFIFO.h"

void freeInfo( const void* );
QINFO* allocInfo( int a, int b, int c );
void printInfo( const void* pInfo );

#define QINFO_TAB_SIZE 2
#define DEBUG_PRINT

int main()
{
  FQueue* q = FQCreate();

  if( !q )
  {
    printf( "MEMORY allocation error\n" );
    return 1;
  }

  //Dodac do kolejki 4 elementy (wydrukowac kolejke)
  for( int i=1; i<=4; i++ )
  {
    QINFO* p = allocInfo( i, i+1, i+2 );
    FQEnqueue( q, p );
  }

#ifdef DEBUG_PRINT
  printf("Invoke FQPrint\n");
#endif
  FQPrint( q, printInfo );
  


#ifdef DEBUG_PRINT
  printf("\n\nDequeue element\n");
#endif
  for( int i=0; i<3; i++ )
  {
    QINFO* QInfo = FQDequeue( q );
    printInfo( QInfo );
    freeInfo( QInfo );
  }

#ifdef DEBUG_PRINT
  printf("\n\nInvoke FQPrint\n");
#endif
  FQPrint( q, printInfo );

  


  for( int i=0; i<2; i++ )
  {
    QINFO* p = allocInfo( i+10, i+10, i+20 );
    FQEnqueue( q, p );
  }

#ifdef DEBUG_PRINT
  printf("\n\nInvoke FQPrint\n");
#endif
  FQPrint( q, printInfo );




  FQClear( q, freeInfo );

  


  for( int i=0; i<3; i++ )
  {
    QINFO* p = allocInfo( i+100, i+100, i+200 );
    FQEnqueue( q, p );
  }

#ifdef DEBUG_PRINT
  printf("\n\nInvoke FQPrint\n");
#endif
  FQPrint( q, printInfo );


  //Usunac jeden element (wypisac go) (wydrukowac kolejke)
#ifdef DEBUG_PRINT
  printf("\n\nDequeue element\n");
#endif
  QINFO* QInfo = FQDequeue( q );
  printInfo( QInfo );
  freeInfo( QInfo );

#ifdef DEBUG_PRINT
  printf("\n\nInvoke FQPrint\n");
#endif
  FQPrint( q, printInfo );

  //usunac cala kolejke
  FQRemove( &q, freeInfo );


  return 0;
}

void freeInfo( const void* pInfo )
{
  if( !pInfo )
    return;

  QINFO* p = (QINFO*)pInfo;

  free( p->pTab );
  free( p );
}

QINFO* allocInfo( int a, int b, int c )
{
  QINFO* pInf = (QINFO*)malloc( sizeof( QINFO ) );

  if( !pInf )
    return NULL;

  pInf->pTab = (int*)malloc( QINFO_TAB_SIZE * sizeof( int ) );

  if( !( pInf->pTab ) )
  {
    free( pInf );
    return NULL;
  }

  pInf->key = a;
  pInf->pTab[0] = b;
  pInf->pTab[1] = c;

  return pInf;
}

void printInfo( const void* pInfo )
{
  printf( "key = %d pTab[0] = %d pTab[1] = %d\n",
          ((QINFO*)pInfo)->key,
          ((QINFO*)pInfo)->pTab[0],
          ((QINFO*)pInfo)->pTab[1] );
}