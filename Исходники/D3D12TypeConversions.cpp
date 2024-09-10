void TextureViewDesc_to_D3D12_RTV_DESC(const TextureViewDesc& RTVDesc, D3D12_RENDER_TARGET_VIEW_DESC &D3D12RTVDesc, Uint32 SampleCount)
{
    TextureViewDesc_to_D3D_RTV_DESC(RTVDesc, D3D12RTVDesc, SampleCount);
    switch (RTVDesc.TextureDim)
    {
        case RESOURCE_DIM_TEX_1D:
        break;

        case RESOURCE_DIM_TEX_1D_ARRAY:
        break;

        case RESOURCE_DIM_TEX_2D:
            if( SampleCount > 1 )
            {
            }
            else
            {
                D3D12RTVDesc.Texture2D.PlaneSlice = 0;
            }
        break;

        case RESOURCE_DIM_TEX_2D_ARRAY:
            if( SampleCount > 1 )
            {
            }
            else
            {
                D3D12RTVDesc.Texture2DArray.PlaneSlice = 0;
            }
        break;

        case RESOURCE_DIM_TEX_3D:
        break;

        default:
            UNEXPECTED( "Unexpected view type" );
    }
}