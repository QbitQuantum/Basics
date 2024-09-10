bool RuleFeatureSet::invalidateStyleForClassChange(Element* element, Vector<AtomicString>& invalidationClasses, bool foundInvalidationSet)
{
    int oldSize = invalidationClasses.size();
    if (element->needsStyleInvalidation()) {
        if (InvalidationList* invalidationList = m_pendingInvalidationMap.get(element)) {
            foundInvalidationSet = true;
            for (InvalidationList::const_iterator it = invalidationList->begin(); it != invalidationList->end(); ++it) {
                if ((*it)->wholeSubtreeInvalid()) {
                    element->setNeedsStyleRecalc(SubtreeStyleChange);
                    invalidationClasses.remove(oldSize, invalidationClasses.size() - oldSize);
                    element->clearChildNeedsStyleInvalidation();
                    return true;
                }
                (*it)->getClasses(invalidationClasses);
            }
        }
    }

    bool thisElementNeedsStyleRecalc = false;

    if (element->hasClass()) {
        const SpaceSplitString& classNames = element->classNames();
        for (Vector<AtomicString>::const_iterator it = invalidationClasses.begin(); it != invalidationClasses.end(); ++it) {
            if (classNames.contains(*it)) {
                thisElementNeedsStyleRecalc = true;
                break;
            }
        }
    }

    // foundInvalidationSet will be true if we are in a subtree of a node with a DescendantInvalidationSet on it.
    // We need to check all nodes in the subtree of such a node.
    if (foundInvalidationSet || element->childNeedsStyleInvalidation()) {
        bool someChildrenNeedStyleRecalc = invalidateStyleForClassChangeOnChildren(element, invalidationClasses, foundInvalidationSet);
        // We only need to possibly recalc style if this node is in the subtree of a node with a DescendantInvalidationSet on it.
        if (foundInvalidationSet)
            thisElementNeedsStyleRecalc = thisElementNeedsStyleRecalc || someChildrenNeedStyleRecalc;
    }

    if (thisElementNeedsStyleRecalc)
        element->setNeedsStyleRecalc(LocalStyleChange);

    invalidationClasses.remove(oldSize, invalidationClasses.size() - oldSize);
    element->clearChildNeedsStyleInvalidation();
    return thisElementNeedsStyleRecalc;
}