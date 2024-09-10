TBool TDebugFunctionality::GetStopModeFunctionality(TDes8& aDFBlock)
{
    TUint32 size = GetStopModeFunctionalityBufSize();
    if (aDFBlock.MaxLength() < size)
    {
        // Insufficient space to contain the debug functionality block
        return EFalse;
    }

    TUint8* ptr = (TUint8*)&size;
    aDFBlock.SetLength(0);
    aDFBlock.Append(ptr, 4);
    TVersion version = TVersion(KStopModeMajorVersionNumber, KStopModeMinorVersionNumber, KStopModePatchVersionNumber);
    ptr = (TUint8*)&version;
    aDFBlock.Append(ptr, sizeof(TVersion));

    AppendBlock((const TSubBlock&)StopModeFunctionalityCore,aDFBlock);
    AppendBlock((const TSubBlock&)StopModeFunctionalityFunctions,aDFBlock);
    AppendBlock((const TSubBlock&)StopModeFunctionalityList,aDFBlock);

    const TTagHeader& header = StopModeFunctionalityBuffers->iHeader;
    aDFBlock.Append((TUint8*)&header, sizeof(TTagHeader));

    for(TInt i=0; i<EBuffersLast; i++)
    {
        TTag tag;
        TheDBufferManager.GetBufferDetails((TBufferType)i, tag);
        aDFBlock.Append((TUint8*)&tag, sizeof(TTag));
    }

    if(aDFBlock.Length() != size - 4)
    {
        return EFalse;
    }

    TUint32* ptr32 = (TUint32*)aDFBlock.Ptr();
    TUint32 checksum = 0;
    for(TInt i=0; i<aDFBlock.Length(); i+=4)
    {
        checksum^=*ptr32;
        ptr32++;
    }

    ptr = (TUint8*)&checksum;
    aDFBlock.Append(ptr, 4);

    return ETrue;
}