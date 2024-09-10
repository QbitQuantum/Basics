 RgbMap* getRgbMap() override {
   if (!m_rgbMap) {
     Sprite::RgbMapFor forLayer =
       ((m_layer->isBackground() ||
         m_sprite->pixelFormat() == IMAGE_RGB) ?
        Sprite::RgbMapFor::OpaqueLayer:
        Sprite::RgbMapFor::TransparentLayer);
     m_rgbMap = m_sprite->rgbMap(m_frame, forLayer);
   }
   return m_rgbMap;
 }