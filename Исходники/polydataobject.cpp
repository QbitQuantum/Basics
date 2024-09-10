void PolyDataObject::ObjectAddedToScene()
{
    connect( GetManager(), SIGNAL(ReferenceObjectChanged()), this, SLOT(OnReferenceChanged()) );
    connect( GetManager(), SIGNAL(ReferenceTransformChanged()), this, SLOT(OnReferenceChanged()) );
    connect( GetManager(), SIGNAL(CursorPositionChanged()), this, SLOT(OnCursorPositionChanged()) );
    connect( GetManager(), SIGNAL(StartCursorInteraction()), this, SLOT(OnStartCursorInteraction()) );
    connect( GetManager(), SIGNAL(EndCursorInteraction()), this, SLOT(OnEndCursorInteraction()) );
    m_referenceToPolyTransform->Identity();
    m_referenceToPolyTransform->Concatenate( GetWorldTransform() );
    m_referenceToPolyTransform->Concatenate( GetManager()->GetInverseReferenceTransform() );
    UpdateCuttingPlane();
    UpdateClippingPlanes();
}