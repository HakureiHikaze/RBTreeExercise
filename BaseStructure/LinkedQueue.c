#include "LinkedQueue.h"
QueueNode* createQueueNode_(){
    QueueNode* queueNode = (QueueNode*) calloc(1, sizeof(QueueNode));
    queueNode->next = 0;
    queueNode->prev = 0;
    queueNode->data = 0;
    return queueNode;
}
Queue* CreateQueue(){
    Queue* queue = (Queue*) calloc(1, sizeof (Queue));
    queue->size = 0;
    return queue;
}
void releaseNode_(QueueNode* queueNode){
    free(queueNode);
}
void releaseNodeRecursively_(QueueNode* queueNode){
    if(queueNode) {
        if (queueNode->next) {
            releaseNodeRecursively_(queueNode->next);
        }
        free(queueNode);
    }
}
void ReleaseQueue(Queue* queue){
    releaseNodeRecursively_(queue->first);
    free(queue);
}
void Enqueue(Queue* queue, void* ptrData){
    QueueNode* temp = queue->last;
    queue->last = createQueueNode_();
    queue->last->data = ptrData;
    if(temp) temp->prev = queue->last;
    queue->last->next = temp;
    queue->first = queue->first?queue->first: queue->last;
    queue->size++;
}

void* Dequeue(Queue* queue){
    QueueNode * node = queue->first;
    void* temp = node->data;
    queue->first = node->prev;
    if(queue->first) {
        queue->first->next = 0;
    }else{
        queue->last = 0;
    }
    releaseNode_(node);
    queue->size--;
    return temp;
}

size_t GetQueueSize(Queue* queue){
    if(queue){
        if(!queue->first){
            return 0;
        }
        else{
            return queue->size;
        }
    }
    return 0;
}