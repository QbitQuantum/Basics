static void sortBlock(unsigned from, unsigned to, Vector<Vector<Node*> >& parentMatrix, bool mayContainAttributeNodes)
{
    ASSERT(from + 1 < to); // Should not call this function with less that two nodes to sort.
    unsigned minDepth = UINT_MAX;
    for (unsigned i = from; i < to; ++i) {
        unsigned depth = parentMatrix[i].size() - 1;
        if (minDepth > depth)
            minDepth = depth;
    }

    // Find the common ancestor.
    unsigned commonAncestorDepth = minDepth;
    Node* commonAncestor;
    while (true) {
        commonAncestor = parentWithDepth(commonAncestorDepth, parentMatrix[from]);
        if (commonAncestorDepth == 0)
            break;

        bool allEqual = true;
        for (unsigned i = from + 1; i < to; ++i) {
            if (commonAncestor != parentWithDepth(commonAncestorDepth, parentMatrix[i])) {
                allEqual = false;
                break;
            }
        }
        if (allEqual)
            break;

        --commonAncestorDepth;
    }

    if (commonAncestorDepth == minDepth) {
        // One of the nodes is the common ancestor => it is the first in document order.
        // Find it and move it to the beginning.
        for (unsigned i = from; i < to; ++i)
            if (commonAncestor == parentMatrix[i][0]) {
                parentMatrix[i].swap(parentMatrix[from]);
                if (from + 2 < to)
                    sortBlock(from + 1, to, parentMatrix, mayContainAttributeNodes);
                return;
            }
    }

    if (mayContainAttributeNodes && commonAncestor->isElementNode()) {
        // The attribute nodes and namespace nodes of an element occur before the children of the element.
        // The namespace nodes are defined to occur before the attribute nodes.
        // The relative order of namespace nodes is implementation-dependent.
        // The relative order of attribute nodes is implementation-dependent.
        unsigned sortedEnd = from;
        // FIXME: namespace nodes are not implemented.
        for (unsigned i = sortedEnd; i < to; ++i) {
            Node* n = parentMatrix[i][0];
            if (n->isAttributeNode() && static_cast<Attr*>(n)->ownerElement() == commonAncestor)
                parentMatrix[i].swap(parentMatrix[sortedEnd++]);
        }
        if (sortedEnd != from) {
            if (to - sortedEnd > 1)
                sortBlock(sortedEnd, to, parentMatrix, mayContainAttributeNodes);
            return;
        }
    }

    // Children nodes of the common ancestor induce a subdivision of our node-set.
    // Sort it according to this subdivision, and recursively sort each group.
    HashSet<Node*> parentNodes;
    for (unsigned i = from; i < to; ++i)
        parentNodes.add(parentWithDepth(commonAncestorDepth + 1, parentMatrix[i]));

    unsigned previousGroupEnd = from;
    unsigned groupEnd = from;
    for (Node* n = commonAncestor->firstChild(); n; n = n->nextSibling()) {
        // If parentNodes contains the node, perform a linear search to move its children in the node-set to the beginning.
        if (parentNodes.contains(n)) {
            for (unsigned i = groupEnd; i < to; ++i)
                if (parentWithDepth(commonAncestorDepth + 1, parentMatrix[i]) == n)
                    parentMatrix[i].swap(parentMatrix[groupEnd++]);

            if (groupEnd - previousGroupEnd > 1)
                sortBlock(previousGroupEnd, groupEnd, parentMatrix, mayContainAttributeNodes);

            ASSERT(previousGroupEnd != groupEnd);
            previousGroupEnd = groupEnd;
#ifndef NDEBUG
            parentNodes.remove(n);
#endif
        }
    }

    ASSERT(parentNodes.isEmpty());
}