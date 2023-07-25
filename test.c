#include "RBTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Vector.h"

int main(){
#define CAPACITY 8192
    RBTree* test = CreateRBTree();
    for(int i =1; i<=CAPACITY;i++){
        Insert(test,i);
    }
    unsigned seed = (unsigned)time(NULL);
    for(int j = 0; j<100; j++){
        seed = (seed<<5)*5+seed;
        srand(seed);
        size_t data = ((rand()<<2))%CAPACITY+1;
        size_t depth = 0;
        printf("Finding %zu\n",data);
        RBTNode* result = FindData(test,data, &depth);
        printf("Found %zu at 0x%p in the depth of %zu.\n", data, result, depth);
    }
    size_t depth = 0;
    printf("Finding %zu\n",CAPACITY);
    RBTNode* result = FindData(test,CAPACITY, &depth);
    printf("Found %zu at 0x%p in the depth of %zu.\n", CAPACITY, result, depth);
    //printf("Depth of tree is %d\n", GetDepth(test));
    Release(test);
    return 0;
}