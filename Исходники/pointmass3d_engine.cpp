 void CPointMass3DEngine::RemoveEntity(CEntity& c_entity) {
    c_entity.Accept(m_cRemoveVisitor);
 }