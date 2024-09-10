void PostOrder(BTree *tree)
{
    if(tree==NULL)
        return;
    if(tree->lchild!=NULL)
        PostOrder(tree->lchild);
    if(tree->rchild!=NULL)
        PostOrder(tree->rchild);
    Operator(tree->data);
}