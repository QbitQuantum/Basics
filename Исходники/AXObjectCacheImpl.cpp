void AXObjectCacheImpl::updateAriaOwns(const AXObject* owner, const Vector<String>& idVector, HeapVector<Member<AXObject>>& ownedChildren)
{
    //
    // Update the map from the AXID of this element to the ids of the owned children,
    // and the reverse map from ids to possible AXID owners.
    //

    HashSet<String> currentIds = m_ariaOwnerToIdsMapping.get(owner->axObjectID());
    HashSet<String> newIds;
    bool idsChanged = false;
    for (const String& id : idVector) {
        newIds.add(id);
        if (!currentIds.contains(id)) {
            idsChanged = true;
            HashSet<AXID>* owners = m_idToAriaOwnersMapping.get(id);
            if (!owners) {
                owners = new HashSet<AXID>();
                m_idToAriaOwnersMapping.set(id, adoptPtr(owners));
            }
            owners->add(owner->axObjectID());
        }
    }
    for (const String& id : currentIds) {
        if (!newIds.contains(id)) {
            idsChanged = true;
            HashSet<AXID>* owners = m_idToAriaOwnersMapping.get(id);
            if (owners) {
                owners->remove(owner->axObjectID());
                if (owners->isEmpty())
                    m_idToAriaOwnersMapping.remove(id);
            }
        }
    }
    if (idsChanged)
        m_ariaOwnerToIdsMapping.set(owner->axObjectID(), newIds);

    //
    // Now figure out the ids that actually correspond to children that exist and
    // that we can legally own (not cyclical, not already owned, etc.) and update
    // the maps and |ownedChildren| based on that.
    //

    // Figure out the children that are owned by this object and are in the tree.
    TreeScope& scope = owner->node()->treeScope();
    Vector<AXID> newChildAXIDs;
    for (const String& idName : idVector) {
        Element* element = scope.getElementById(AtomicString(idName));
        if (!element)
            continue;

        AXObject* child = getOrCreate(element);
        if (!child)
            continue;

        // If this child is already aria-owned by a different owner, continue.
        // It's an author error if this happens and we don't worry about which of the
        // two owners wins ownership of the child, as long as only one of them does.
        if (isAriaOwned(child) && getAriaOwnedParent(child) != owner)
            continue;

        // You can't own yourself!
        if (child == owner)
            continue;

        // Walk up the parents of the owner object, make sure that this child doesn't appear
        // there, as that would create a cycle.
        bool foundCycle = false;
        for (AXObject* parent = owner->parentObject(); parent && !foundCycle; parent = parent->parentObject()) {
            if (parent == child)
                foundCycle = true;
        }
        if (foundCycle)
            continue;

        newChildAXIDs.append(child->axObjectID());
        ownedChildren.append(child);
    }

    // Compare this to the current list of owned children, and exit early if there are no changes.
    Vector<AXID> currentChildAXIDs = m_ariaOwnerToChildrenMapping.get(owner->axObjectID());
    bool same = true;
    if (currentChildAXIDs.size() != newChildAXIDs.size()) {
        same = false;
    } else {
        for (size_t i = 0; i < currentChildAXIDs.size() && same; ++i) {
            if (currentChildAXIDs[i] != newChildAXIDs[i])
                same = false;
        }
    }
    if (same)
        return;

    // The list of owned children has changed. Even if they were just reordered, to be safe
    // and handle all cases we remove all of the current owned children and add the new list
    // of owned children.
    for (size_t i = 0; i < currentChildAXIDs.size(); ++i) {
        // Find the AXObject for the child that this owner no longer owns.
        AXID removedChildID = currentChildAXIDs[i];
        AXObject* removedChild = objectFromAXID(removedChildID);

        // It's possible that this child has already been owned by some other owner,
        // in which case we don't need to do anything.
        if (removedChild && getAriaOwnedParent(removedChild) != owner)
            continue;

        // Remove it from the child -> owner mapping so it's not owned by this owner anymore.
        m_ariaOwnedChildToOwnerMapping.remove(removedChildID);

        if (removedChild) {
            // If the child still exists, find its "real" parent, and reparent it back to
            // its real parent in the tree by detaching it from its current parent and
            // calling childrenChanged on its real parent.
            removedChild->detachFromParent();
            AXID realParentID = m_ariaOwnedChildToRealParentMapping.get(removedChildID);
            AXObject* realParent = objectFromAXID(realParentID);
            childrenChanged(realParent);
        }

        // Remove the child -> original parent mapping too since this object has now been
        // reparented back to its original parent.
        m_ariaOwnedChildToRealParentMapping.remove(removedChildID);
    }

    for (size_t i = 0; i < newChildAXIDs.size(); ++i) {
        // Find the AXObject for the child that will now be a child of this owner.
        AXID addedChildID = newChildAXIDs[i];
        AXObject* addedChild = objectFromAXID(addedChildID);

        // Add this child to the mapping from child to owner.
        m_ariaOwnedChildToOwnerMapping.set(addedChildID, owner->axObjectID());

        // Add its parent object to a mapping from child to real parent. If later this owner
        // doesn't own this child anymore, we need to return it to its original parent.
        AXObject* originalParent = addedChild->parentObject();
        m_ariaOwnedChildToRealParentMapping.set(addedChildID, originalParent->axObjectID());

        // Now detach the object from its original parent and call childrenChanged on the
        // original parent so that it can recompute its list of children.
        addedChild->detachFromParent();
        childrenChanged(originalParent);
    }

    // Finally, update the mapping from the owner to the list of child IDs.
    m_ariaOwnerToChildrenMapping.set(owner->axObjectID(), newChildAXIDs);
}