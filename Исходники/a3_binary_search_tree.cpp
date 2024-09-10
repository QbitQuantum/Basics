bool BinarySearchTree::remove(BinarySearchTree::DataType val)
{
	if (!exists(val))
		return false;
	
	if (size_ == 1)
	{
		root_ = NULL;
		size_--;
		return true; 
	}
	
	Node* index = root_;
	Node* parent = root_;
	
	while (index->val != val) 
	{
		parent = index; 
		if (val < index->val)
		{
			index = index->left;
		}
		else
		{
			index = index->right;
		}
	}
	
	bool left = false;
	if (parent->val > index->val)
		left = true;
	
	if (index->right == NULL && index->left == NULL)
	{
		if (left)
			parent->left = NULL;
		else 
			parent->right = NULL;
		delete index; 
	}
	
	else if (index->right == NULL && index->left != NULL)
	{
		if (left)
			parent->left = index->left; 	
		else 
			parent->right = index->left;
		//delete index; 
	}
	
	else if (index->right != NULL && index->left == NULL)
	{
		if (left)
			parent->left = index->right; 	
		else 
			parent->right = index->right;
		//delete index; 
	}
	
	else 
	{
		BinarySearchTree* preTree = new BinarySearchTree(); 
		BinarySearchTree* susTree = new BinarySearchTree(); 
		preTree->root_ = index->left;
		preTree->size_ = preTree->depth()+1;
		susTree->root_ = index->right;
		susTree->size_ = susTree->depth()+1;
		
		int pred = preTree->max();
		int succ = susTree->min();
		
		if ((val-pred) < (succ-val))
		{
			index->val = pred; 
			preTree->remove(pred);
		}
		else
		{
			index->val = succ;
			susTree->remove(succ);	
		}		
	}
	size_--;
	updateNodeBalance(root_); 
	return true; 
}