#include <stdio.h>
#include <tBuf.h>
#include <unistd.h>


int main ()
{
  printf("Hallo Welt\n");

  int nb = 5;
  tBuf b1 = tBuf(2, nb, 3);

  printf("Update Time: %02d\n", b1.getUpdTime());
  
  for (int i = 0; i < 12; i++) {
    printf("\nIt: %02d\n", i);
    b1.pushEle( (float) i );
    printf("Num: %4.1f\n", b1.popEle(0));
    printf("Current buffer index: %02d\n", b1.getIndex());
    sleep(1);
  };
      
  printf("\nList Elements:\n");
  for ( int i = 0; i < nb; i++ ) {
    printf("Count: %3d, Val: %4.1f\n", b1.numEle(i),b1.popEle(i));
  }


}
