//----------------------------------------------------------------------------
void LightNode::Load (Stream& rkStream, Stream::Link* pkLink)
{
    Node::Load(rkStream,pkLink);

    if ( rkStream.GetVersion() >= Version(1,8) )
    {
        StreamRead(rkStream,m_kLRotate);
        StreamRead(rkStream,m_kLTranslate);
    }
    else
    {
        m_kLRotate = Matrix3f::IDENTITY;
        m_kLTranslate = Vector3f::ZERO;
    }

    // link data
    Light* pkLight;
    StreamRead(rkStream,pkLight);
    pkLink->Add(pkLight);
}