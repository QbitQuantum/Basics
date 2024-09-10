//----------------------------------------------------------------------------
void GelatinBlob::DoPhysical ()
{
    m_pkModule->Update(GetTimeInSeconds());

    // Update sphere surface.  The particle system and sphere maintain their
    // own copy of the vertices, so this update is necessary.
    Vector3f* akVertex = m_spkSphere->Vertices();
    int i;
    for (i = 0; i < 12; i++)
        akVertex[i] = m_pkModule->Position(i);

    m_spkSphere->UpdateModelBound();

    // update the segments representing the springs
    int iNumSprings = m_pkModule->GetNumSprings();
    for (i = 0; i < iNumSprings; i++)
    {
        int iV0, iV1;
        float fConstant, fLength;
        m_pkModule->GetSpring(i,iV0,iV1,fConstant,fLength);

        Polyline* pkPoly = WmlStaticCast(Polyline,m_spkSegments->GetChild(i));
        Vector3f* akVertex = pkPoly->Vertices();
        akVertex[0] = m_pkModule->Position(iV0);
        akVertex[1] = m_pkModule->Position(iV1);
    }
}