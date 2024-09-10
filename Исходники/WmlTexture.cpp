//----------------------------------------------------------------------------
void Texture::Load (Stream& rkStream, Stream::Link* pkLink)
{
    Object::Load(rkStream,pkLink);

    // native data
    StreamReadEnum(rkStream,m_eCorrection);
    StreamReadEnum(rkStream,m_eApply);
    StreamRead(rkStream,m_kBlendColor);
    StreamReadEnum(rkStream,m_eWrap);
    StreamReadEnum(rkStream,m_eFilter);
    StreamReadEnum(rkStream,m_eMipmap);
    StreamRead(rkStream,m_fPriority);

    if ( rkStream.GetVersion() >= Version(1,3) )
    {
        StreamReadEnum(rkStream,m_eEnvmap);
        StreamRead(rkStream,m_kBorderColor);
        StreamReadEnum(rkStream,m_eCombineFuncRGB);
        StreamReadEnum(rkStream,m_eCombineFuncAlpha);
        StreamReadEnum(rkStream,m_eCombineSrc0RGB);
        StreamReadEnum(rkStream,m_eCombineSrc1RGB);
        StreamReadEnum(rkStream,m_eCombineSrc2RGB);
        StreamReadEnum(rkStream,m_eCombineSrc0Alpha);
        StreamReadEnum(rkStream,m_eCombineSrc1Alpha);
        StreamReadEnum(rkStream,m_eCombineSrc2Alpha);
        StreamReadEnum(rkStream,m_eCombineOp0RGB);
        StreamReadEnum(rkStream,m_eCombineOp1RGB);
        StreamReadEnum(rkStream,m_eCombineOp2RGB);
        StreamReadEnum(rkStream,m_eCombineOp0Alpha);
        StreamReadEnum(rkStream,m_eCombineOp1Alpha);
        StreamReadEnum(rkStream,m_eCombineOp2Alpha);
        StreamReadEnum(rkStream,m_eCombineScaleRGB);
        StreamReadEnum(rkStream,m_eCombineScaleAlpha);
    }

    // link data
    Image* pkImage;
    StreamRead(rkStream,pkImage);
    pkLink->Add(pkImage);
}