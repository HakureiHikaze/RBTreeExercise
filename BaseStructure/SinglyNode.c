#include <stdlib.h>
#include"SinglyNode.h"
void SNodeRelease(SNode* node){
    free(node);
}