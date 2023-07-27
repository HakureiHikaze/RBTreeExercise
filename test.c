#include "RBTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "MT19937.h"
#include "SinglyLinkedList.h"
#include "Utilities.h"

void MT19937Test(){
    unsigned long seed = time(NULL);
    MT19937 * mt = InitRandMT(seed);
    for(int i =0; i<10; i++){
        printf("Rand() = %u\n", ((unsigned)ExtractRandMT(mt))%10);
    }
}

void RBTreeTest(){
    NonRedundantRNG * rng = NonRedundantRNGInit((unsigned long )time(NULL),-16,32);
    RBTree * tree = CreateRBTree();
    for(int i = 0; i<32; i++){
        Insert(tree, NRRNGExtract(rng));
    }
    for(int i =-16; i<16; i++){
        size_t depth = 0;
        RBTNode * found = FindData(tree,i,&depth);
        printf("%d\n",found->data);
    }
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

void MTTest(){
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
void NonredundantTest(){
    NonRedundantRNG* rng = NonRedundantRNGInit((size_t)time(NULL),-128,256);
    for(int i = 0; i<256; i++){
        printf("%d\n", NRRNGExtract(rng));
    }
    NRRNGRelease(rng);
}

int main(){
    RBTreeTest();
    return 0;
}
