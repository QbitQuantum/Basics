//-----------------------------------------------------------------------------
void D3D11HardwarePixelBuffer::_unmapstagingbuffer(bool copyback)
{
    _unmap(mStagingBuffer);

    if(copyback)
    {
        if(mLockBox.getHeight() == mParentTexture->getHeight() && mLockBox.getWidth() == mParentTexture->getWidth())
            mDevice.GetImmediateContext()->CopyResource(mParentTexture->getTextureResource(), mStagingBuffer);
        else
        {
            D3D11_BOX dstBoxDx11 = OgreImageBoxToDx11Box(mLockBox);
            dstBoxDx11.front = 0;
            dstBoxDx11.back = mLockBox.getDepth();

            unsigned int subresource = D3D11CalcSubresource(mSubresourceIndex, mLockBox.front, mParentTexture->getNumMipmaps()+1);
            mDevice.GetImmediateContext()->CopySubresourceRegion(mParentTexture->getTextureResource(), subresource, mLockBox.left, mLockBox.top, mSubresourceIndex, mStagingBuffer, subresource, &dstBoxDx11);
        }
    }
}