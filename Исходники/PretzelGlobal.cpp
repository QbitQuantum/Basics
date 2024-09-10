 ci::gl::TextureRef PretzelGlobal::getTextureFromSkin( ci::Rectf rect ){
     Surface srf( rect.getWidth(), rect.getHeight(), true);
     srf.copyFrom( mSkinSurf, Area(rect.x1, rect.y1, rect.x2, rect.y2), vec2(-rect.x1, -rect.y1) );
     return ci::gl::Texture::create( srf );
 }