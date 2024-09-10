TreeNode *nextNode(TreeNode *given)
{
    if(given == NULL) {
        return NULL;
    }
    
    // just check if there is a right subtree under the given node
    // and go left to the bottom
    // because that is in order succession
    TreeNode *curr = given->getRight();
    if(curr != NULL) {
        
        while(curr->getLeft() != NULL) {
            curr = curr->getLeft();
        }
        
        return curr;
    }
    // else
    // go upwards until you switch to being on the left instead of right
    // or you cant go up anymore
    curr = given;
    TreeNode *p = curr->getParent();
    
    while(p != NULL && p->getLeft() != curr) {
        curr = p;
        p = p->getParent();
    }
    
    return curr;
}