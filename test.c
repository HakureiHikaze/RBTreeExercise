#include "RBTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "MT19937.h"
#include "SinglyLinkedList.h"

void MT19937Test(){
    unsigned long seed = time(NULL);
    MT19937 * mt = InitRandMT(seed);
    for(int i =0; i<10; i++){
        printf("Rand() = %u\n", ((unsigned)ExtractRandMT(mt))%10);
    }
}

void RBTreeTest(){
    const int CAPACITY = 16;
    RBTree* test = CreateRBTree();
    for(int i =1; i <= CAPACITY; i++){
        Insert(test,i);
    }
    unsigned seed = (unsigned)time(NULL);
    for(int j = 0; j<100; j++){
        seed = (seed<<5)*5+seed;
        srand(seed);
        size_t data = ((rand()<<2)) % CAPACITY + 1;
        size_t depth = 0;
        printf("Finding %zu\n",data);
        RBTNode* result = FindData(test,data, &depth);
        printf("Found %zu at 0x%p in the depth of %zu.\n", data, result, depth);
    }
    size_t depth = 0;
    printf("Finding %d\n", CAPACITY);
    RBTNode* result = FindData(test, CAPACITY, &depth);
    printf("Found %d at 0x%p in the depth of %zu.\n", CAPACITY, result, depth);
    //printf("Depth of tree is %d\n", GetDepth(test));
    Release(test);
    printf("Size of long long: %zu", sizeof (long long));
}

void SinglyLinkedListTest(){
    SLList* list = SLListInit();
    for(int i = 0; i<16; i++){
        SLListAppend(list,i);
    }
    SLListInsert(list,6,120);
    printf("Deleted %zu, data is %ld", 14, SLListDelete(list,14));
    SLListRelease(list);
}

void NonredundantTest(){
    SLList * list = SLListInit();
    unsigned long seed = time(NULL);
    MT19937 * mt = InitRandMT(seed);
    for(long i = 0; i< 2500; i++){
        SLListAppend(list,i);
    }
    while(list->length){
        printf("%ld\n", SLListDelete(list, ExtractRandMT(mt)%list->length));
    }
}

int main(){
    NonredundantTest();
    return 0;
}
