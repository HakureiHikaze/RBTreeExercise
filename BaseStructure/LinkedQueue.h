#pragma once
#include <stdlib.h>
typedef struct stQueueNode{
    struct stQueueNode* next, * prev;
    void* data;
}QueueNode;
typedef struct stQueue{
    QueueNode* first,* last;
    size_t size;
}Queue;
extern Queue* CreateQueue();
extern void ReleaseQueue(Queue*);
extern void Enqueue(Queue*, void*);
extern void* Dequeue(Queue*);
extern size_t GetQueueSize(Queue*);
