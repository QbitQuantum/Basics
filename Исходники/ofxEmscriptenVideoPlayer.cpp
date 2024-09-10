void ofxEmscriptenVideoPlayer::update(){
	gotFirstFrame = pixels.isAllocated();
	if(html5video_player_update(id,pixels.isAllocated() && usePixels,pixels.getPixels())){
		if(texture.texData.width!=html5video_player_width(id) || texture.texData.height!=html5video_player_height(id)){
			texture.texData.width = html5video_player_width(id);
			texture.texData.height = html5video_player_height(id);
			texture.texData.tex_w = texture.texData.width;
			texture.texData.tex_h = texture.texData.height;
			switch(getPixelFormat()){
			case OF_PIXELS_RGBA:
				pixels.allocate(texture.texData.width,texture.texData.height,4);
				break;
			case OF_PIXELS_RGB:
				pixels.allocate(texture.texData.width,texture.texData.height,3);
				break;
			case OF_PIXELS_MONO:
				pixels.allocate(texture.texData.width,texture.texData.height,1);
				break;
			default:
				ofLogError() << "unknown pixel format, can't allocating texture";
				break;
			}
		}
		if(texture.texData.textureID!=html5video_player_texture_id(id)){
			texture.texData.bFlipTexture = false;
			switch(getPixelFormat()){
			case OF_PIXELS_RGBA:
				texture.texData.glInternalFormat = GL_RGBA;
				break;
			case OF_PIXELS_RGB:
				texture.texData.glInternalFormat = GL_RGB;
				break;
			case OF_PIXELS_MONO:
				texture.texData.glInternalFormat = GL_LUMINANCE;
				break;
			default:
				ofLogError() << "unknown pixel format, can't allocating texture";
				break;
			}
			texture.texData.tex_u = 1;
			texture.texData.tex_t = 1;
			texture.texData.textureTarget = GL_TEXTURE_2D;
			texture.texData.bAllocated = true;
			texture.setUseExternalTextureID(html5video_player_texture_id(id));
		}
	}
}