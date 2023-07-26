#include <stdlib.h>
#include"SinglyNode.h"
void SNodeRelease(SNode* node){
    if(!node)free(node);
}