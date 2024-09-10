void QTextureViewer::paint(QPainter *painter, QPaintEvent *event)
{
    VOGL_NOTE_UNUSED(event);
    if (m_pKtxTexture == NULL)
    {
        return;
    }

    if (!m_mipmappedTexture.is_valid() || !m_mipmappedTexture.get_num_levels())
    {
        return;
    }

    painter->save();

    const uint border = 25;
    const uint minDimension = 10;
    uint texWidth = m_pKtxTexture->get_width();
    uint texHeight = m_pKtxTexture->get_height();

    uint drawWidth = vogl::math::maximum<uint>(minDimension, texWidth);
    uint drawHeight = vogl::math::maximum<uint>(minDimension, texHeight);

    // offset by 1 so that there is room to draw a border around the biggest mip level
    painter->translate(1, 1);

    // apply zoom factor using scaling
    painter->scale(m_zoomFactor, m_zoomFactor);

    painter->setPen(m_outlinePen);

    uint numMips = m_pKtxTexture->get_num_mips();
    uint maxMip = vogl::math::minimum(numMips, m_maxMipLevel);
    maxMip = vogl::math::minimum(maxMip, m_mipmappedTexture.get_num_levels() - 1);

    uint mipWidth = 0;
    uint mipHeight = 0;

    drawWidth = drawWidth >> m_baseMipLevel;
    drawHeight = drawHeight >> m_baseMipLevel;

    if (m_pKtxTexture->get_num_faces() == 6)
    {
        // adjust draw dimensions
        drawWidth *= 4;
        drawHeight *= 3;
    }

    uint minimumWidth = 0;
    uint minimumHeight = drawHeight + border;

    for (uint mip = m_baseMipLevel; mip <= maxMip; mip++)
    {
        if (m_pixmaps.contains(mip) == false && m_mipmappedTexture.is_valid())
        {
            QWidget* pParent = (QWidget*)this->parent();
            QCursor origCursor = pParent->cursor();
            pParent->setCursor(Qt::WaitCursor);

            vogl::color_quad_u8* pTmpPixels = NULL;
            if (m_mipmappedTexture.is_cubemap())
            {
                vogl::mip_level* mipLevel = m_mipmappedTexture.get_level(m_arrayIndex, 0, mip);
                vogl::image_u8* image = mipLevel->get_image();

                mipWidth = image->get_width();
                mipHeight = image->get_height();

                unsigned char tmp = 0;
                unsigned int pixelsSize = image->get_total_pixels();

                // store face dimensions
                uint faceWidth = mipWidth;
                uint faceHeight = mipHeight;

                uint cubeCrossStride = faceWidth*4;

                // adjust mip dimensions
                mipWidth *= 4;
                mipHeight *= 3;

                pTmpPixels = new vogl::color_quad_u8[pixelsSize * 12];
                memset(pTmpPixels, 0, pixelsSize * 12 * sizeof(vogl::color_quad_u8));

                // order is +X, -X, +Y, -Y, +Z, -Z
                uint faceRowOffset[6] = {faceHeight, faceHeight, 0, 2*faceHeight, faceHeight, faceHeight};
                uint faceColOffset[6] = {0, 2*faceWidth, faceWidth, faceWidth, 3*faceWidth, faceWidth};

                for (uint face = 0; face < m_mipmappedTexture.get_num_faces(); face++)
                {
                    vogl::mip_level* mipLevel2 = m_mipmappedTexture.get_level(m_arrayIndex, face, mip);
                    vogl::image_u8* image2 = mipLevel2->get_image();
                    vogl::color_quad_u8* pPixels = image2->get_pixels();

                    // calculate write location to start of face
                    vogl::color_quad_u8* writeLoc = pTmpPixels + cubeCrossStride*faceRowOffset[face] + faceColOffset[face];

                    for (uint h = 0; h < faceHeight; h++)
                    {
                        // copy row of face into cross
                        memcpy(writeLoc + h*cubeCrossStride, pPixels + h*faceWidth, faceWidth*sizeof(vogl::color_quad_u8));

                        // adjust color of each pixel
                        for (uint w = 0; w < faceWidth; w++)
                        {
                            vogl::color_quad_u8* pPixel = writeLoc + h*cubeCrossStride + w;
                            adjustChannels(m_channelSelection, pPixel->r, pPixel->g, pPixel->b, pPixel->a);
                            tmp = pPixel->r;
                            pPixel->r = pPixel->b;
                            pPixel->b = tmp;
                        }
                    }
                }
            }
            else
            {
                vogl::mip_level* mipLevel = m_mipmappedTexture.get_level(m_arrayIndex, m_sliceIndex, mip);
                vogl::image_u8* image = mipLevel->get_image();
                vogl::color_quad_u8* pPixels = image->get_pixels();

                mipWidth = image->get_width();
                mipHeight = image->get_height();

                unsigned char tmp = 0;
                unsigned int pixelsSize = image->get_total_pixels();

                pTmpPixels = new vogl::color_quad_u8[pixelsSize];
                memcpy(pTmpPixels, pPixels, pixelsSize*sizeof(vogl::color_quad_u8));
                for (uint i = 0; i < pixelsSize; i++)
                {
                    adjustChannels(m_channelSelection, pTmpPixels[i].r, pTmpPixels[i].g, pTmpPixels[i].b, pTmpPixels[i].a);
                    tmp = pTmpPixels[i].r;
                    pTmpPixels[i].r = pTmpPixels[i].b;
                    pTmpPixels[i].b = tmp;
                }
            }

            m_pixmaps.insert(mip, QPixmap::fromImage(QImage((unsigned char*)pTmpPixels, mipWidth, mipHeight, QImage::Format_ARGB32_Premultiplied)));
            m_pixmapData.insert(mip, pTmpPixels);
            pParent->setCursor(origCursor);
        }

        // make sure the rect is 1 pixel around the texture
        painter->drawRect(-1, -1, drawWidth+1, drawHeight+1);

        if (m_pixmaps.contains(mip))
        {
            uint left = 0;
            uint top = 0;
            if (m_bInvert)
            {
                // invert
                painter->scale(1,-1);
                top = -drawHeight;
            }

            painter->drawPixmap(left, top, drawWidth, drawHeight, m_pixmaps[mip]);

            if (m_bInvert)
            {
                // restore inversion
                painter->scale(1,-1);
            }
        }
        painter->translate(drawWidth + border, drawHeight / 2);

        minimumWidth += drawWidth + border;

        drawWidth /= 2;
        drawHeight /= 2;
    }

    this->setMinimumSize(minimumWidth * m_zoomFactor, minimumHeight * m_zoomFactor);

    painter->restore();
}