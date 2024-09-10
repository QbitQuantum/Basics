void TreeScopeAdopter::moveTreeToNewScope(Node& root) const
{
    ASSERT(needsScopeChange());

#if !ENABLE(OILPAN)
    oldScope().guardRef();
#endif

    // If an element is moved from a document and then eventually back again the collection cache for
    // that element may contain stale data as changes made to it will have updated the DOMTreeVersion
    // of the document it was moved to. By increasing the DOMTreeVersion of the donating document here
    // we ensure that the collection cache will be invalidated as needed when the element is moved back.
    Document& oldDocument = oldScope().document();
    Document& newDocument = newScope().document();
    bool willMoveToNewDocument = oldDocument != newDocument;
    AXObjectCache* axObjectCache = oldDocument.existingAXObjectCache();
    if (willMoveToNewDocument)
        oldDocument.incDOMTreeVersion();

    for (Node& node : NodeTraversal::inclusiveDescendantsOf(root)) {
        updateTreeScope(node);

        if (willMoveToNewDocument) {
            if (axObjectCache)
                axObjectCache->remove(&node);
            moveNodeToNewDocument(node, oldDocument, newDocument);
        } else if (node.hasRareData()) {
            NodeRareData* rareData = node.rareData();
            if (rareData->nodeLists())
                rareData->nodeLists()->adoptTreeScope();
        }

        if (!node.isElementNode())
            continue;

        if (node.hasSyntheticAttrChildNodes()) {
            WillBeHeapVector<RefPtrWillBeMember<Attr>>& attrs = *toElement(node).attrNodeList();
            for (unsigned i = 0; i < attrs.size(); ++i)
                moveTreeToNewScope(*attrs[i]);
        }

        for (ShadowRoot* shadow = node.youngestShadowRoot(); shadow; shadow = shadow->olderShadowRoot()) {
            shadow->setParentTreeScope(newScope());
            if (willMoveToNewDocument)
                moveTreeToNewDocument(*shadow, oldDocument, newDocument);
        }
    }

#if !ENABLE(OILPAN)
    oldScope().guardDeref();
#endif
}