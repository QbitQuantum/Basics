//----------------------------------------------------------------------------
void ParticleController::Load (Stream& rkStream,
    Stream::Link* pkLink)
{
    Controller::Load(rkStream,pkLink);

    // NOTE.  ParticleController was derived from PointController.  The
    // PointController::Save wrote various quantities to disk that are now
    // managed by ParticleController.  These quantities are written to disk
    // in the same order, so no special handling must occur here based on the
    // stream version number.
    // native data
    StreamRead(rkStream,m_fSystemLinearSpeed);
    StreamRead(rkStream,m_fSystemAngularSpeed);
    StreamRead(rkStream,m_kSystemLinearAxis);
    StreamRead(rkStream,m_kSystemAngularAxis);

    int iVertexQuantity;
    StreamRead(rkStream,iVertexQuantity);
    Reallocate(iVertexQuantity);
    StreamRead(rkStream,m_afPointLinearSpeed,iVertexQuantity);
    StreamRead(rkStream,m_afPointAngularSpeed,iVertexQuantity);
    StreamRead(rkStream,m_akPointLinearAxis,iVertexQuantity);
    StreamRead(rkStream,m_akPointAngularAxis,iVertexQuantity);
    StreamRead(rkStream,m_fSystemSizeChange);

    if ( rkStream.GetVersion() < Version(1,4) )
    {
        // The vertex quantity had been written to disk twice, once by
        // PointController and once by ParticleController.  Read it and
        // discard since it was loaded above.
        int iDiscard;
        StreamRead(rkStream,iDiscard);
    }

    StreamRead(rkStream,m_afPointSizeChange,iVertexQuantity);
}