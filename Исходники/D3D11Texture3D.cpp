bool Texture3D::SetData(unsigned level, int x, int y, int z, int width, int height, int depth, const void* data)
{
    PROFILE(SetTextureData);

    if (!object_)
    {
        LOGERROR("No texture created, can not set data");
        return false;
    }

    if (!data)
    {
        LOGERROR("Null source for setting data");
        return false;
    }

    if (level >= levels_)
    {
        LOGERROR("Illegal mip level for setting data");
        return false;
    }

    int levelWidth = GetLevelWidth(level);
    int levelHeight = GetLevelHeight(level);
    int levelDepth = GetLevelDepth(level);
    if (x < 0 || x + width > levelWidth || y < 0 || y + height > levelHeight || z < 0 || z + depth > levelDepth || width <= 0 ||
        height <= 0 || depth <= 0)
    {
        LOGERROR("Illegal dimensions for setting data");
        return false;
    }

    // If compressed, align the update region on a block
    if (IsCompressed())
    {
        x &= ~3;
        y &= ~3;
        width += 3;
        width &= 0xfffffffc;
        height += 3;
        height &= 0xfffffffc;
    }

    unsigned char* src = (unsigned char*)data;
    unsigned rowSize = GetRowDataSize(width);
    unsigned rowStart = GetRowDataSize(x);
    unsigned subResource = D3D11CalcSubresource(level, 0, levels_);

    if (usage_ == TEXTURE_DYNAMIC)
    {
        if (IsCompressed())
        {
            height = (height + 3) >> 2;
            y >>= 2;
        }

        D3D11_MAPPED_SUBRESOURCE mappedData;
        mappedData.pData = 0;

        graphics_->GetImpl()->GetDeviceContext()->Map((ID3D11Resource*)object_, subResource, D3D11_MAP_WRITE_DISCARD, 0,
            &mappedData);
        if (mappedData.pData)
        {
            for (int page = 0; page < depth; ++page)
            {
                for (int row = 0; row < height; ++row)
                {
                    memcpy((unsigned char*)mappedData.pData + (page + z) * mappedData.DepthPitch + (row + y) * mappedData.RowPitch +
                           rowStart, src + row * rowSize, rowSize);
                }
            }

            graphics_->GetImpl()->GetDeviceContext()->Unmap((ID3D11Resource*)object_, subResource);
        }
        else
        {
            LOGERROR("Failed to map texture for update");
            return false;
        }
    }
    else
    {
        if (IsCompressed())