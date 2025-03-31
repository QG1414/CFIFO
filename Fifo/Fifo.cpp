#include <stdio.h>
#include <stdlib.h>
#include "QFIFO.h"

int main()
{
  FQueue* q = FQCreate();

  if( !q )
  {
    printf( "MEMORY allocation error\n" );
    return 1;
  }

  FQEnqueue(q, 3);
  FQEnqueue(q, 5);
  FQEnqueue(q, 7);


  FQRemove(&q);
  printf("1 = %d\n", FQDequeue(q));


  printf("2 = %d\n", FQDequeue(q));
  
  //tu sprawdzamy czy q jest nullem
  return 0;
}