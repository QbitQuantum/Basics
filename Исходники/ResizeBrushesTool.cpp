 void ResizeBrushesTool::commitResize() {
     MapDocumentSPtr document = lock(m_document);
     if (m_totalDelta.null())
         document->cancelTransaction();
     else
         document->commitTransaction();
     m_dragFaces.clear();
 }