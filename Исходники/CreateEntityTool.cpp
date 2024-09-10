 void CreateEntityTool::commitEntity() {
     assert(m_entity != NULL);
     MapDocumentSPtr document = lock(m_document);
     document->commitTransaction();
     m_entity = NULL;
 }