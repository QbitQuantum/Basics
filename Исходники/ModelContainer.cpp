    void ModelContainer::fillContainer(const AABSPTree<SubModel *>::Node& pNode, int &pSubModelPos, int &pTreeNodePos, int &pTrianglePos, Vector3& pLo, Vector3& pHi, Vector3& pFinalLo, Vector3& pFinalHi)
    {
        // TreeNode for the SubModel
        TreeNode treeNode = TreeNode(pNode.valueArray.size(), pSubModelPos);
        treeNode.setSplitAxis(pNode.splitAxis);
        treeNode.setSplitLocation(pNode.splitLocation);
        int currentTreeNodePos = pTreeNodePos++;

        Vector3 lo = Vector3(inf(),inf(),inf());
        Vector3 hi = Vector3(-inf(),-inf(),-inf());

        for (int i=0; i<pNode.valueArray.size(); i++)
        {
            G3D::_AABSPTree::Handle<SubModel*>* h= pNode.valueArray[i];
            SubModel *m = h->value;

            memcpy(&getTreeNodes()[pTreeNodePos], &m->getTreeNode(0), sizeof(TreeNode) * m->getNNodes());
            memcpy(&getTriangles()[pTrianglePos], &m->getTriangle(0), sizeof(TriangleBox) * m->getNTriangles());

            SubModel newModel = SubModel(m->getNTriangles(), getTriangles(), pTrianglePos, m->getNNodes(), getTreeNodes(), pTreeNodePos);
            newModel.setReletiveBounds(m->getReletiveBounds().getLo(), m->getReletiveBounds().getHi());
            newModel.setBasePosition(m->getBasePosition());
            iSubModel[pSubModelPos++] = newModel;

            pTreeNodePos += m->getNNodes();
            pTrianglePos += m->getNTriangles();

            AABox box = m->getAABoxBounds();
            lo = lo.min(box.low());
            hi = hi.max(box.high());
            pFinalLo = pFinalLo.min(lo);
            pFinalHi = pFinalHi.max(hi);
        }
        /*
        if(pNode.valueArray.size() == 0) {
        int xxx = 0; // just for the breakpoint
        }
        */
        // get absolute bounds

        if(pNode.child[0] != 0)
        {
            treeNode.setChildPos(0, pTreeNodePos);
            fillContainer(*pNode.child[0], pSubModelPos, pTreeNodePos, pTrianglePos, lo, hi,pFinalLo,pFinalHi);
        }
        if(pNode.child[1] != 0)
        {
            treeNode.setChildPos(1, pTreeNodePos);
            fillContainer(*pNode.child[1], pSubModelPos, pTreeNodePos, pTrianglePos, lo, hi,pFinalLo,pFinalHi);
        }

        pLo = pLo.min(lo);
        pHi = pHi.max(hi);

        treeNode.setBounds(lo,hi);

        setTreeNode(treeNode, currentTreeNodePos);

    }