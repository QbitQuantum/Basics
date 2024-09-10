void LineRenderer::RenderAll(RenderContext* rc)
{
    ID3D11DeviceContext* d3dContext = rc->Context();

    // update constant buffer

    Matrix viewProj = rc->Cam().View() * rc->Cam().Proj();
    viewProj.Transpose();
    UpdateConstantBuffer(d3dContext,m_perframeCB,&viewProj,sizeof(viewProj));
        	
    // set constant buffer to vertex shader    
    ID3D11Buffer* cbuffers[1] = {m_perframeCB};
    d3dContext->VSSetConstantBuffers(0,1,cbuffers);

    // set shaders
	d3dContext->VSSetShader(m_vsShader,NULL,0);
    d3dContext->GSSetShader( NULL, NULL, 0 );
	d3dContext->PSSetShader(m_psShader,NULL,0);

    // set vertex layout and primitive  topology    
    d3dContext->IASetInputLayout(m_vertexLayoutPC);
    d3dContext->IASetPrimitiveTopology( D3D_PRIMITIVE_TOPOLOGY_LINELIST );

    RenderStateCache* rscache = rc->GetRenderStateCache();
    // set state-blocks ( raster, depth, and blend states)     
    d3dContext->RSSetState(rscache->GetRasterState(FillMode::Wireframe,CullMode::BACK));    
    d3dContext->OMSetDepthStencilState(NULL,0);    
    d3dContext->OMSetBlendState( NULL, NULL, 0xFFFFFFFF );
    
    ID3D11Buffer* vbuffers[1] = {m_vbPC->GetBuffer()};
    uint32_t strides[1] = {m_vbPC->GetStride()};
    uint32_t offsets[1] = {0};
    d3dContext->IASetVertexBuffers( 0, 1, vbuffers, strides, offsets );
    

    uint32_t bufSize = m_vbPC->GetCount();
    uint32_t totalVertexCount = (uint32_t) m_vertsPC.size();
    uint32_t start = 0;
    uint32_t count =  (totalVertexCount < bufSize) ? totalVertexCount : bufSize;
     
    HRESULT hr;
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    
    while(start < totalVertexCount)
    {        
        hr = d3dContext->Map(m_vbPC->GetBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        if(FAILED(hr)) break;
        CopyMemory(mappedResource.pData, &m_vertsPC[start], m_vbPC->GetStride() * count);
        d3dContext->Unmap(m_vbPC->GetBuffer(), 0);            
        d3dContext->Draw(count,0);

        start += count;
        if( (start + count) > totalVertexCount)
            count = totalVertexCount - start;
    }
    m_vertsPC.clear();
}