void RenderView::setSelection(RenderObject *s, int sp, RenderObject *e, int ep)
{
    // Make sure both our start and end objects are defined. 
    // Check www.msnbc.com and try clicking around to find the case where this happened.
    if ((s && !e) || (e && !s))
        return;

    // Just return if the selection hasn't changed.
    if (m_selectionStart == s && m_selectionStartPos == sp &&
        m_selectionEnd == e && m_selectionEndPos == ep)
        return;

    // Record the old selected objects.  These will be used later
    // when we compare against the new selected objects.
    int oldStartPos = m_selectionStartPos;
    int oldEndPos = m_selectionEndPos;

    // Objects each have a single selection rect to examine.
    typedef HashMap<RenderObject*, SelectionInfo*> SelectedObjectMap;
    SelectedObjectMap oldSelectedObjects;
    SelectedObjectMap newSelectedObjects;

    // Blocks contain selected objects and fill gaps between them, either on the left, right, or in between lines and blocks.
    // In order to get the repaint rect right, we have to examine left, middle, and right rects individually, since otherwise
    // the union of those rects might remain the same even when changes have occurred.
    typedef HashMap<RenderBlock*, BlockSelectionInfo*> SelectedBlockMap;
    SelectedBlockMap oldSelectedBlocks;
    SelectedBlockMap newSelectedBlocks;

    RenderObject* os = m_selectionStart;
    RenderObject* stop = rendererAfterPosition(m_selectionEnd, m_selectionEndPos);
    while (os && os != stop) {
        if ((os->canBeSelectionLeaf() || os == m_selectionStart || os == m_selectionEnd) && os->selectionState() != SelectionNone) {
            // Blocks are responsible for painting line gaps and margin gaps.  They must be examined as well.
            oldSelectedObjects.set(os, new SelectionInfo(os));
            RenderBlock* cb = os->containingBlock();
            while (cb && !cb->isRenderView()) {
                BlockSelectionInfo* blockInfo = oldSelectedBlocks.get(cb);
                if (blockInfo)
                    break;
                oldSelectedBlocks.set(cb, new BlockSelectionInfo(cb));
                cb = cb->containingBlock();
            }
        }
        
        os = os->nextInPreOrder();
    }

    // Now clear the selection.
    SelectedObjectMap::iterator oldObjectsEnd = oldSelectedObjects.end();
    for (SelectedObjectMap::iterator i = oldSelectedObjects.begin(); i != oldObjectsEnd; ++i)
        i->first->setSelectionState(SelectionNone);

    // set selection start and end
    m_selectionStart = s;
    m_selectionStartPos = sp;
    m_selectionEnd = e;
    m_selectionEndPos = ep;

    // Update the selection status of all objects between m_selectionStart and m_selectionEnd
    if (s && s == e)
        s->setSelectionState(SelectionBoth);
    else {
        if (s)
            s->setSelectionState(SelectionStart);
        if (e)
            e->setSelectionState(SelectionEnd);
    }

    RenderObject* o = s;
    stop = rendererAfterPosition(e, ep);
    
    while (o && o != stop) {
        if (o != s && o != e && o->canBeSelectionLeaf())
            o->setSelectionState(SelectionInside);
        o = o->nextInPreOrder();
    }

    // Now that the selection state has been updated for the new objects, walk them again and
    // put them in the new objects list.
    o = s;
    while (o && o != stop) {
        
        if ((o->canBeSelectionLeaf() || o == s || o == e) && o->selectionState() != SelectionNone) {
            newSelectedObjects.set(o, new SelectionInfo(o));
            RenderBlock* cb = o->containingBlock();
            while (cb && !cb->isRenderView()) {
                BlockSelectionInfo* blockInfo = newSelectedBlocks.get(cb);
                if (blockInfo)
                    break;
                newSelectedBlocks.set(cb, new BlockSelectionInfo(cb));
                cb = cb->containingBlock();
            }
        }

        o = o->nextInPreOrder();
    }

    if (!m_frameView)
        return;

    // Have any of the old selected objects changed compared to the new selection?
    for (SelectedObjectMap::iterator i = oldSelectedObjects.begin(); i != oldObjectsEnd; ++i) {
        RenderObject* obj = i->first;
        SelectionInfo* newInfo = newSelectedObjects.get(obj);
        SelectionInfo* oldInfo = i->second;
        if (!newInfo || oldInfo->rect() != newInfo->rect() || oldInfo->state() != newInfo->state() ||
            (m_selectionStart == obj && oldStartPos != m_selectionStartPos) ||
            (m_selectionEnd == obj && oldEndPos != m_selectionEndPos)) {
            m_frameView->updateContents(oldInfo->rect());
            if (newInfo) {
                m_frameView->updateContents(newInfo->rect());
                newSelectedObjects.remove(obj);
                delete newInfo;
            }
        }
        delete oldInfo;
    }
    
    // Any new objects that remain were not found in the old objects dict, and so they need to be updated.
    SelectedObjectMap::iterator newObjectsEnd = newSelectedObjects.end();
    for (SelectedObjectMap::iterator i = newSelectedObjects.begin(); i != newObjectsEnd; ++i) {
        SelectionInfo* newInfo = i->second;
        m_frameView->updateContents(newInfo->rect());
        delete newInfo;
    }

    // Have any of the old blocks changed?
    SelectedBlockMap::iterator oldBlocksEnd = oldSelectedBlocks.end();
    for (SelectedBlockMap::iterator i = oldSelectedBlocks.begin(); i != oldBlocksEnd; ++i) {
        RenderBlock* block = i->first;
        BlockSelectionInfo* newInfo = newSelectedBlocks.get(block);
        BlockSelectionInfo* oldInfo = i->second;
        if (!newInfo || oldInfo->rects() != newInfo->rects() || oldInfo->state() != newInfo->state()) {
            m_frameView->updateContents(oldInfo->rects());
            if (newInfo) {
                m_frameView->updateContents(newInfo->rects());
                newSelectedBlocks.remove(block);
                delete newInfo;
            }
        }
        delete oldInfo;
    }
    
    // Any new blocks that remain were not found in the old blocks dict, and so they need to be updated.
    SelectedBlockMap::iterator newBlocksEnd = newSelectedBlocks.end();
    for (SelectedBlockMap::iterator i = newSelectedBlocks.begin(); i != newBlocksEnd; ++i) {
        BlockSelectionInfo* newInfo = i->second;
        m_frameView->updateContents(newInfo->rects());
        delete newInfo;
    }
}