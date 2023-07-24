#include "RBTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Vector.h"

int main(){
    RBTree* test = CreateRBTree();
    int arr[11] = {5,2,6,7,3,4,1,9,10,8,0};
    for(int i =0; i<11;i++){
        Insert(test,arr[i]);
    }
    printf("Depth of tree is %d\n", GetDepth(test));
    RBTMidTraversal(test);
    Release(test);
    return 0;
}
