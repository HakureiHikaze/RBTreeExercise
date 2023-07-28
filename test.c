#include "RBTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
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
    NonRedundantRNG * rng = NonRedundantRNGInit((unsigned long )time(NULL),16,20);
    RBTree * tree = CreateRBTree();
    for(int i = 0; i<20; i++){
        Insert(tree, NRRNGExtract(rng));
    }
    for(int i =16; i<36; i++){
        size_t depth = 0;
        RBTNode * found = FindData(tree,(size_t)i,&depth);
        printf("%d\n",found->data);
    }
    Release(tree);
    NRRNGRelease(rng);
}
void RBTreeTest2(){
    NonRedundantRNG* rng = NonRedundantRNGInit((unsigned long)time(NULL), 16,16);
    RBTree* tree = CreateRBTree();
    int array[16];
    for(int i = 0; i< 16; i++){
        array[i] = NRRNGExtract(rng);
    }
    for(int i = 0; i<16;i++){
        Insert(tree,array[i]);
    }
    Release(tree);
    NRRNGRelease(rng);
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
    setlocale(LC_CTYPE,setlocale(LC_ALL,""));
    wchar_t test = L'┌';
    wprintf_s(L"%c",test);
    return 0;
}
