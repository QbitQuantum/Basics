 void UVRotateTool::doEndMouseDrag(const InputState& inputState) {
     MapDocumentSPtr document = lock(m_document);
     document->commitTransaction();
 }