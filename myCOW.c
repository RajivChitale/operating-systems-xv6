#include "types.h"
#include "stat.h"
#include "user.h"

#define N 3000		//global array size - change to see effect. Try 3000, 5000, 10000
int glob[3*N];
int pid;

/*
init 2*N entries
fork
parent sets N to 3*N entries
child accesses first few entries
*/


int main(){
	glob[0]=2;	//initialize with any integer value

    pgtPrint();
    printf(1, "\n");

	printf (1, "Allocating data\n");
	//printf (1, "global addr from user space: %x\n", glob);
	for (int i=1;i<2*N;i++){
		glob[i]=glob[i-1];
    }	

    pgtPrint();
    printf(1, "\n");

    pid=fork();

    //parent
    if(pid>0){
        printf (1, "Forked\n\n");
        pgtPrint();
        for (int i=N;i<3*N;i++){
            glob[i]=glob[i-1];
            if (i%2000 ==0){ 
                printf(1, "\n");
                pgtPrint();
            }
        }
        printf (1, "\nPrinting final page table:\n");
        pgtPrint();
        printf(1, "Value: %d\n", glob[N-1]);
        for(int i =0; i<4; i++){
            wait();
        }
    }
    //child
    else{
        for(int i=1;i<N;i++){
            glob[i]=glob[i-1];
        }
    }
	
   exit();
}

