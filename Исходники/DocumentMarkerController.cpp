void DocumentMarkerController::removeMarkers(Node* node, unsigned startOffset, int length, DocumentMarker::MarkerTypes markerTypes, RemovePartiallyOverlappingMarkerOrNot shouldRemovePartiallyOverlappingMarker)
{
    if (length <= 0)
        return;

    if (!possiblyHasMarkers(markerTypes))
        return;
    ASSERT(!(m_markers.isEmpty()));

    MarkerList* list = m_markers.get(node);
    if (!list)
        return;

    bool docDirty = false;
    unsigned endOffset = startOffset + length;
    for (size_t i = 0; i < list->size();) {
        DocumentMarker marker = list->at(i);

        // markers are returned in order, so stop if we are now past the specified range
        if (marker.startOffset() >= endOffset)
            break;

        // skip marker that is wrong type or before target
        if (marker.endOffset() <= startOffset || !markerTypes.contains(marker.type())) {
            i++;
            continue;
        }

        // at this point we know that marker and target intersect in some way
        docDirty = true;

        // pitch the old marker
        list->remove(i);

        if (shouldRemovePartiallyOverlappingMarker)
            // Stop here. Don't add resulting slices back.
            continue;

        // add either of the resulting slices that are left after removing target
        if (startOffset > marker.startOffset()) {
            DocumentMarker newLeft = marker;
            newLeft.setEndOffset(startOffset);
            list->insert(i, RenderedDocumentMarker(newLeft));
            // i now points to the newly-inserted node, but we want to skip that one
            i++;
        }
        if (marker.endOffset() > endOffset) {
            DocumentMarker newRight = marker;
            newRight.setStartOffset(endOffset);
            list->insert(i, RenderedDocumentMarker(newRight));
            // i now points to the newly-inserted node, but we want to skip that one
            i++;
        }
    }

    if (list->isEmpty()) {
        m_markers.remove(node);
        if (m_markers.isEmpty())
            m_possiblyExistingMarkerTypes = 0;
    }

    // repaint the affected node
    if (docDirty && node->renderer())
        node->renderer()->repaint();
}