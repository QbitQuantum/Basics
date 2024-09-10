void TreeTools<T>::showRotationPointers_Tree(AVLTree<T> tree, TreeNode<T>* tr, bool rotLeft, bool showUsingShow)
{
    if(!tr) return;
    if(showUsingShow)
    {
        int showAllLeftRight=0;
        TreeNode<T>* par = tr->getParent();
        if(par)
        {
            if(tr == par->getParent()) //it's left child
                showAllLeftRight = 1;
            else
                showAllLeftRight = 2;
        }
        //showTree(tree, (par ? par : tr), 4, 2, showAllLeftRight);
        //showTree(tree, tr, tree.getElemShower(), 3, 2);
        tree.showTree(DataShowMode::Value, PointerShowMode::AllPointers);
        return;
    }
}