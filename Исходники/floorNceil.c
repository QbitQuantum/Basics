struct BT  *Floor(struct BT *root, int key, struct BT **prev)
{
	
	if(root)
	{
		if(!Floor(root->l, key, prev))
			return 0;
		
		if(root->data==key)
				return root;
	 if(root->data>key )
				return (*prev);
		
			*prev = root;
		return Floor(root->r, key, prev);
		
		
	}else
	return NULL;
}