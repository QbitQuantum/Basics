    void SubModel::fillContainer(const AABSPTree<Triangle>::Node& pNode, int &pTreeNodePos, int &pTrianglePos, Vector3& pLo, Vector3& pHi)
    {
        TreeNode treeNode = TreeNode(pNode.valueArray.size(), pTrianglePos);
        treeNode.setSplitAxis(pNode.splitAxis);
        treeNode.setSplitLocation(pNode.splitLocation);

        int currentTreeNodePos = pTreeNodePos++;

        Vector3 lo = Vector3(inf(),inf(),inf());
        Vector3 hi = Vector3(-inf(),-inf(),-inf());

        for(int i=0;i<pNode.valueArray.size(); i++)
        {
            G3D::_AABSPTree::Handle<Triangle>* h= pNode.valueArray[i];
            Triangle t = h->value;
            TriangleBox triangleBox = TriangleBox(t.vertex(0),t.vertex(1), t.vertex(2));
            lo = lo.min(triangleBox.getBounds().getLo().getVector3());
            hi = hi.max(triangleBox.getBounds().getHi().getVector3());

            getTriangles()[pTrianglePos++] = triangleBox;
        }

        if(pNode.child[0] != 0)
        {
            treeNode.setChildPos(0, pTreeNodePos);
            fillContainer(*pNode.child[0], pTreeNodePos, pTrianglePos, lo, hi);
        }
        if(pNode.child[1] != 0)
        {
            treeNode.setChildPos(1, pTreeNodePos);
            fillContainer(*pNode.child[1], pTreeNodePos, pTrianglePos, lo, hi);
        }

        treeNode.setBounds(lo,hi);

        // get absolute bounds
        pLo = pLo.min(lo);
        pHi = pHi.max(hi);

        getTreeNodes()[currentTreeNodePos] = treeNode;
    }