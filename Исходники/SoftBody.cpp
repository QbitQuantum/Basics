Void SoftBody::_SetupPose( Bool bIsVolume, Bool bIsFrame )
{
    const Node * pNode;
    UInt iNodeIndex;

    // Update links
    EnumLinks();
    Link * pLink = EnumNextLink();
    while( pLink != NULL ) {
        pLink->UpdateConstants();
        pLink = EnumNextLink();
    }

    // Compute total mass
    Scalar fTotalMass = _ComputeMass();
    Scalar fMassK = fTotalMass * 1000.0f * (Scalar)( GetNodeCount() );

    EnumNodes();
    pNode = EnumNextNode();
    while( pNode != NULL ) {
        if ( pNode->InvMass == 0.0f )
            fTotalMass += fMassK;
        pNode = EnumNextNode();
    }
    Scalar fInvTotalMass = MathFn->Invert( fTotalMass );

    // Flags
    m_hPose.bIsVolume = bIsVolume;
    m_hPose.bIsFrame = bIsFrame;

    // Weights
    m_hPose.arrWeights.Clear();

    EnumNodes();
    pNode = EnumNextNode();
    while( pNode != NULL ) {
        if ( pNode->InvMass > 0.0f )
            m_hPose.arrWeights.Push( pNode->Mass * fInvTotalMass );
        else
            m_hPose.arrWeights.Push( fMassK * fInvTotalMass );
        pNode = EnumNextNode();
    }

    // COM
    m_hPose.vCenterOfMass = _ComputeCenterOfMass();

    // Deltas
    m_hPose.arrDeltas.Clear();

    EnumNodes();
    pNode = EnumNextNode();
    while( pNode != NULL ) {
        m_hPose.arrDeltas.Push( pNode->Position - m_hPose.vCenterOfMass );
        pNode = EnumNextNode();
    }

    // Volume
    m_hPose.fVolume = ( (bIsVolume) ? _ComputeVolume() : 0.0f );

    // BaseScaling
    Matrix3 matBaseScaling;
    matBaseScaling.MakeNull();

    Vector3 vTmpRow;

    EnumNodes();
    pNode = EnumNextNode();
    while( pNode != NULL ) {
        iNodeIndex = pNode->GetIndex();
        const Vector3 & vDelta = m_hPose.arrDeltas[iNodeIndex];
        const Vector3 & vWeightedDelta = ( vDelta * m_hPose.arrWeights[iNodeIndex] );
        matBaseScaling.GetRow( vTmpRow, 0 );
        matBaseScaling.SetRow( 0, vTmpRow + (vDelta * vWeightedDelta.X) );
        matBaseScaling.GetRow( vTmpRow, 1 );
        matBaseScaling.SetRow( 1, vTmpRow + (vDelta * vWeightedDelta.Y) );
        matBaseScaling.GetRow( vTmpRow, 2 );
        matBaseScaling.SetRow( 2, vTmpRow + (vDelta * vWeightedDelta.Z) );
        pNode = EnumNextNode();
    }
    matBaseScaling.Invert( m_hPose.matBaseScaling );

    // Rotation & Scaling
    m_hPose.matRotation.MakeIdentity();
    m_hPose.matScaling.MakeIdentity();
}