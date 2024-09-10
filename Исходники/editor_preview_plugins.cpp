Ref<Texture> EditorTexturePreviewPlugin::generate(const RES& p_from) {

	Image img;
	Ref<AtlasTexture> atex = p_from;
	if (atex.is_valid()) {
		Ref<ImageTexture> tex = atex->get_atlas();
		if (!tex.is_valid()) {
			return Ref<Texture>();
		}
		Image atlas = tex->get_data();
		img = atlas.get_rect(atex->get_region());
	}
	else {
		Ref<ImageTexture> tex = p_from;
		img = tex->get_data();
	}

	if (img.empty())
		return Ref<Texture>();

	img.clear_mipmaps();

	int thumbnail_size = EditorSettings::get_singleton()->get("filesystem/file_dialog/thumbnail_size");
	thumbnail_size*=EDSCALE;
	if (img.is_compressed()) {
		if (img.decompress()!=OK)
			return Ref<Texture>();
    } else if (img.get_format()!=Image::FORMAT_RGB8 && img.get_format()!=Image::FORMAT_RGBA8) {
		img.convert(Image::FORMAT_RGBA8);
	}

	int width,height;
	if (img.get_width() > thumbnail_size && img.get_width() >= img.get_height()) {

		width=thumbnail_size;
		height = img.get_height() * thumbnail_size / img.get_width();
	} else if (img.get_height() > thumbnail_size &&  img.get_height() >= img.get_width()) {

		height=thumbnail_size;
		width = img.get_width() * thumbnail_size / img.get_height();
	}  else {

		width=img.get_width();
		height=img.get_height();
	}

	img.resize(width,height);

	Ref<ImageTexture> ptex = Ref<ImageTexture>( memnew( ImageTexture ));

	ptex->create_from_image(img,0);
	return ptex;

}