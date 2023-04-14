#include "types.h"
#include "user.h"

#define N 956
//Number of elements in the local array. Set to not exceed the maximum stack size of 4KB 
//Increasing it (such as N=10000) causes a trap for page fault.

//int arrGlobal[10000]; 

// user program which uses pgtPrint system call
int main(int argc, char *argv[])
{
  int arrLocal[N];
  for(int i=0; i<N; i++) {arrLocal[i] = 1;}

  pgtPrint();

  // Note: compiler optimizations get rid of the local array if it not needed
  // So we will calculate and print a dummy sum at the end
  int sum = 0;       
  for(int i=0; i<N; i++){sum += arrLocal[i];}
  printf(1, "Dummy sum of local array = %d\n", sum);

  exit();
}
