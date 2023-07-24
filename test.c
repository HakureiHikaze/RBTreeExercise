#include "RBTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Vector.h"

int main(){
    RBTree* test = CreateRBTree();
    int arr[11] = {5,2,6,7,3,4,1,9,10,8,0};
    int n = 0;
    scanf("%d",&n);
    for(int i =0; i<n;i++){
        Insert(test,i);
    }
    RBTMidTraversal(test);
    printf("Depth of tree is %d\n", GetDepth(test));
    Release(test);
    return 0;
}
