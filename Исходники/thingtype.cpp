const TexturePtr& ThingType::getTexture(int animationPhase)
{
    TexturePtr& animationPhaseTexture = m_textures[animationPhase];
    if(!animationPhaseTexture) {
        bool useCustomImage = false;
        if(animationPhase == 0 && !m_customImage.empty())
            useCustomImage = true;

        // we don't need layers in common items, they will be pre-drawn
        int textureLayers = 1;
        int numLayers = m_layers;
        if(m_category == ThingCategoryCreature && numLayers >= 2) {
             // 5 layers: outfit base, red mask, green mask, blue mask, yellow mask
            textureLayers = 5;
            numLayers = 5;
        }

        int indexSize = textureLayers * m_numPatternX * m_numPatternY * m_numPatternZ;
        Size textureSize = getBestTextureDimension(m_size.width(), m_size.height(), indexSize);
        ImagePtr fullImage;

        if(useCustomImage)
            fullImage = Image::load(m_customImage);
        else
            fullImage = ImagePtr(new Image(textureSize * Otc::TILE_PIXELS));

        m_texturesFramesRects[animationPhase].resize(indexSize);
        m_texturesFramesOriginRects[animationPhase].resize(indexSize);
        m_texturesFramesOffsets[animationPhase].resize(indexSize);

        for(int z = 0; z < m_numPatternZ; ++z) {
            for(int y = 0; y < m_numPatternY; ++y) {
                for(int x = 0; x < m_numPatternX; ++x) {
                    for(int l = 0; l < numLayers; ++l) {
                        bool spriteMask = (m_category == ThingCategoryCreature && l > 0);
                        int frameIndex = getTextureIndex(l % textureLayers, x, y, z);
                        Point framePos = Point(frameIndex % (textureSize.width() / m_size.width()) * m_size.width(),
                                               frameIndex / (textureSize.width() / m_size.width()) * m_size.height()) * Otc::TILE_PIXELS;

                        if(!useCustomImage) {
                            for(int h = 0; h < m_size.height(); ++h) {
                                for(int w = 0; w < m_size.width(); ++w) {
                                    uint spriteIndex = getSpriteIndex(w, h, spriteMask ? 1 : l, x, y, z, animationPhase);
                                    ImagePtr spriteImage = g_sprites.getSpriteImage(m_spritesIndex[spriteIndex]);
                                    if(spriteImage) {
                                        if(spriteMask) {
                                            static Color maskColors[] = { Color::red, Color::green, Color::blue, Color::yellow };
                                            spriteImage->overwriteMask(maskColors[l - 1]);
                                        }
                                        Point spritePos = Point(m_size.width()  - w - 1,
                                                                m_size.height() - h - 1) * Otc::TILE_PIXELS;

                                        fullImage->blit(framePos + spritePos, spriteImage);
                                    }
                                }
                            }
                        }

                        Rect drawRect(framePos + Point(m_size.width(), m_size.height()) * Otc::TILE_PIXELS - Point(1,1), framePos);
                        for(int x = framePos.x; x < framePos.x + m_size.width() * Otc::TILE_PIXELS; ++x) {
                            for(int y = framePos.y; y < framePos.y + m_size.height() * Otc::TILE_PIXELS; ++y) {
                                uint8 *p = fullImage->getPixel(x,y);
                                if(p[3] != 0x00) {
                                    drawRect.setTop   (std::min<int>(y, (int)drawRect.top()));
                                    drawRect.setLeft  (std::min<int>(x, (int)drawRect.left()));
                                    drawRect.setBottom(std::max<int>(y, (int)drawRect.bottom()));
                                    drawRect.setRight (std::max<int>(x, (int)drawRect.right()));
                                }
                            }
                        }

                        m_texturesFramesRects[animationPhase][frameIndex] = drawRect;
                        m_texturesFramesOriginRects[animationPhase][frameIndex] = Rect(framePos, Size(m_size.width(), m_size.height()) * Otc::TILE_PIXELS);
                        m_texturesFramesOffsets[animationPhase][frameIndex] = drawRect.topLeft() - framePos;
                    }
                }
            }
        }
        animationPhaseTexture = TexturePtr(new Texture(fullImage, true));
        animationPhaseTexture->setSmooth(true);
    }
    return animationPhaseTexture;
}