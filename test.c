#include "RBTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include "MT19937.h"
#include "SinglyLinkedList.h"
#include "Utilities.h"
#include "Vector.h"
#include "LinkedQueue.h"
#include "StringProducer.h"

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

void LengthTest(){
    wchar_t* str = L"测试文本测试文本测试文本测试文本测试文本测试文本";
    wprintf_s(L"Length of \"%s\" is: %u\n", str, StrLen(str));
    long i = -8192;
    long j = 16384;
    long k = -2000000000;
    printf_s("Length of %ld is: %u\n",i, DigitLen(i));
    printf_s("Length of %ld is: %u\n",j, DigitLen(j));
    printf_s("Length of %ld is: %u\n",k, DigitLen(k));
}
void QueueTest(){
    Queue* queue = CreateQueue();
    for(void* i = 0; (size_t)i<0x100; i++){
        Enqueue(queue,i);
    }
    for(size_t i = 0; i< 0x100; i++){
        printf("%ld\n", Dequeue(queue));
    }
    ReleaseQueue(queue);
}

void VectorTest(){
    Vector * vector = VectorCreate();
    for(size_t i = 0; i<0xffffffff; i++){
        VectorAppend(vector,(void*)i);
    }
    VectorRelease(vector);
}
void ToLayerTest(){
    unsigned max = 0;
    //7, 4, 9, 8, 3, 6, 1, 5, 2,
    while (1){
        scanf_s("%lu",&max);
        NonRedundantRNG * rng = NonRedundantRNGInit((unsigned long )time(NULL), 1, max);
        int* l = (int*)calloc(max, sizeof(int));
        int l1[] ={7, 4, 9, 8, 3, 6, 1, 5, 2};
        printf_s("Generating random numbers.\n");
        for(unsigned i = 0; i < max; i++){
            l[i] = NRRNGExtract(rng);
            //printf_s("%lu, ",l[i]);
        }
        NRRNGRelease(rng);
        printf_s("Random numbers generated.\n");
        RBTree * tree = CreateRBTree();
        for(unsigned i = 0; i < max; i++){
            Insert(tree, l[i]);
        }
        free(l);
        Vector** vectors = ToLayer(tree);
        for(size_t i = 1; i< (size_t)vectors[0]; i++){
            for(size_t j = 0;j<vectors[i]->size; j++){
                Vector * v = vectors[i];
                RBTNode* node = (RBTNode*)v->data[j];
                //printf_s("\t%lu,%d", node? node->data:0, node?node->color : 0);
            }
            //printf_s(";\n");
        }
        for(size_t i = 1; i< (size_t)vectors[0]; i++){
            VectorRelease(vectors[i]);
        }
        free(vectors);
        Release(tree);
        fflush(0);
        printf_s("********new********\n");
    }
}

void SPTest1(){
    StringProducer* test = SPNewWStr(L"testtesttesttest");
    SPAppendWStr(test,L"append1append2append3append4append5");
    SPInsertWChar(test,0,L'i');
    SPInsertWStr(test,2,L"oo");
    wprintf_s(SPGetWStringPtr(test));
    wprintf_s(L"%c", SPDeleteAt(test,0));
    wprintf_s(L"\n");
    SPRelease(test);
}

int main(){
    setlocale(LC_CTYPE,setlocale(LC_ALL,""));
    SPTest1();
    return 0;
}
