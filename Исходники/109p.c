int Floor(struct BST *root,int input)
    {
        if(!root)
            return -1;
            
            if(root->data==input)
                return root->data;
                
             if(root->data>input)
                return Floor(root->l,input);
                
             int f=Floor(root->r,input);
             return f>=input?f:root->data;      
    
    
    
    }   