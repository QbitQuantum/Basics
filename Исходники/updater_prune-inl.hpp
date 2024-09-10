 /*! \brief do prunning of a tree */
 inline void DoPrune(RegTree &tree) {
   int npruned = 0;
   // initialize auxiliary statistics
   for (int nid = 0; nid < tree.param.num_nodes; ++nid) {
     tree.stat(nid).leaf_child_cnt = 0;
   }
   for (int nid = 0; nid < tree.param.num_nodes; ++nid) {
     if (tree[nid].is_leaf()) {
       npruned = this->TryPruneLeaf(tree, nid, tree.GetDepth(nid), npruned);
     }
   }
   if (silent == 0) {
     printf("tree prunning end, %d roots, %d extra nodes, %d pruned nodes ,max_depth=%d\n",
            tree.param.num_roots, tree.num_extra_nodes(), npruned, tree.MaxDepth());
   }
 }