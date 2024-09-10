Node* FibonacciHeap::deleteMin()
{
        Node *temp = minRoot_->children_->getLeftMostSibling();
        Node *nextTemp = NULL;

        // Adding children_ to root list
        while(temp != NULL)
        {
                nextTemp = temp->rightSibling_; // Save next Sibling
                temp->remove();
                minRoot_->addSibling(temp);
                temp = nextTemp;
        }

        // Select the left-most sibling of minRoot_
        temp = minRoot_->getLeftMostSibling();

        // Remove minRoot_ and set it to any sibling, if there exists one
        if(temp == minRoot_)
        {
                if(minRoot_->rightSibling_)
                        temp = minRoot_->rightSibling_;
                else
                {
                        // Heap is obviously empty
                        Node* out = minRoot_;
                        minRoot_->remove();
                        minRoot_ = NULL;
                        return out;
                }
        }
        Node* out = minRoot_;

        minRoot_->remove();

        minRoot_ = temp;

        // Initialize list of roots
        for(int i=0; i<100; i++)
                rootListByRank_[i] = NULL;

        while(temp)
        {
                // Check if weight_ of current vertex is smaller than the weight_ of minRoot_
                if(temp->weight_ < minRoot_->weight_)
                {
                        minRoot_ = temp;
                }

                nextTemp = temp->rightSibling_;
                link(temp);
                temp = nextTemp;

        }
        return out;
}