/** 
 * @brief copy constructor
 * @details creates a copy of the passed in TBST
 * 
 * @param other TBST tree to copy
 */
TBST::TBST(const TBST& other) {
    root = NULL;
    nodeCount = 0;
    if(other.root != NULL) {
        // handle root separately
        assert(root == NULL); // make sure that tree is empty
        // then add the root
        NodeData* rootData = other.root->getData();
        insert(rootData->getToken(), rootData->getCount());

        // recursively copy the left and right subtrees
        recursiveCopy(other.root->getLeft());
        recursiveCopy(other.root->getRight());
    }
    else {
        root = NULL;
    }
}