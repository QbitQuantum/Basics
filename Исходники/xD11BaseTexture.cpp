 bool  xD11UnkwonTexture::_update(ID3D11Resource* pLockTexture , void* data  , int dateLen , int rowPitch , int depthPicth , int mipmapLevel , int arraySlice)
 {
     if(pLockTexture == NULL)
         return false;

     ID3D11DeviceContext* pDeviceContext = m_pD11RenderApi->d11DeviceContext();
     UINT lockResource = D3D10CalcSubresource((UINT)mipmapLevel , (UINT)arraySlice, (UINT)m_TexInfo.m_MipmapLevel);

     if(m_TexInfo.m_Usage == D3D11_USAGE_DEFAULT)
     {
         if(rowPitch == 0 ) rowPitch = dateLen;
         if(depthPicth == 0) depthPicth = dateLen;
         pDeviceContext->UpdateSubresource(pLockTexture ,lockResource , NULL , data ,rowPitch , depthPicth);         
     }
     else //只有非DEFAULT的纹理才是可以Map的。
     {
         char* pMapedData = NULL;
         int   Pitch = 0;
         int   SlicePith = 0;
         UINT  mapFlag = 0;


         if(pMapedData == NULL)
             return false;

         D3D11_MAPPED_SUBRESOURCE mappedTex;
         mappedTex.pData = NULL;
         mappedTex.RowPitch = 0;
         mappedTex.DepthPitch = 0;
         pDeviceContext->Map(pLockTexture , lockResource , D3D11_MAP_WRITE_DISCARD , mapFlag , &mappedTex );
         pMapedData = (char*)mappedTex.pData;
         Pitch     = mappedTex.RowPitch;
         SlicePith = mappedTex.DepthPitch;
         memcpy(pMapedData , data , dateLen);
         pDeviceContext->Unmap(pLockTexture , lockResource);
     }
     return true;
 }