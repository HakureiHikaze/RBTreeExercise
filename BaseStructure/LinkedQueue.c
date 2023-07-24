#include "LinkedQueue.h"
QueueNode* createQueueNode_(){
    QueueNode* queueNode = (QueueNode*) calloc(1, sizeof(queueNode));
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
    if(queueNode->next){
        releaseNodeRecursively_(queueNode->next);
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
    queue->first = queue->first?queue->first: queue->last;
    queue->size++;

}
void* Dequeue(Queue*){

}
size_t GetQueueSize(Queue*){

}