void Particles2DEditorPlugin::_generate_emission_mask() {

	Ref<ParticlesMaterial> pm = particles->get_process_material();
	if (!pm.is_valid()) {
		EditorNode::get_singleton()->show_warning(TTR("Can only set point into a ParticlesMaterial process material"));
		return;
	}

	Ref<Image> img;
	img.instance();
	Error err = ImageLoader::load_image(source_emission_file, img);
	ERR_EXPLAIN(TTR("Error loading image:") + " " + source_emission_file);
	ERR_FAIL_COND(err != OK);

	if (img->is_compressed()) {
		img->decompress();
	}
	img->convert(Image::FORMAT_RGBA8);
	ERR_FAIL_COND(img->get_format() != Image::FORMAT_RGBA8);
	Size2i s = Size2(img->get_width(), img->get_height());
	ERR_FAIL_COND(s.width == 0 || s.height == 0);

	Vector<Point2> valid_positions;
	Vector<Point2> valid_normals;
	Vector<uint8_t> valid_colors;

	valid_positions.resize(s.width * s.height);

	EmissionMode emode = (EmissionMode)emission_mask_mode->get_selected();

	if (emode == EMISSION_MODE_BORDER_DIRECTED) {
		valid_normals.resize(s.width * s.height);
	}

	bool capture_colors = emission_colors->is_pressed();

	if (capture_colors) {
		valid_colors.resize(s.width * s.height * 4);
	}

	int vpc = 0;

	{
		PoolVector<uint8_t> data = img->get_data();
		PoolVector<uint8_t>::Read r = data.read();

		for (int i = 0; i < s.width; i++) {
			for (int j = 0; j < s.height; j++) {

				uint8_t a = r[(j * s.width + i) * 4 + 3];

				if (a > 128) {

					if (emode == EMISSION_MODE_SOLID) {

						if (capture_colors) {
							valid_colors[vpc * 4 + 0] = r[(j * s.width + i) * 4 + 0];
							valid_colors[vpc * 4 + 1] = r[(j * s.width + i) * 4 + 1];
							valid_colors[vpc * 4 + 2] = r[(j * s.width + i) * 4 + 2];
							valid_colors[vpc * 4 + 3] = r[(j * s.width + i) * 4 + 3];
						}
						valid_positions[vpc++] = Point2(i, j);

					} else {

						bool on_border = false;
						for (int x = i - 1; x <= i + 1; x++) {
							for (int y = j - 1; y <= j + 1; y++) {

								if (x < 0 || y < 0 || x >= s.width || y >= s.height || r[(y * s.width + x) * 4 + 3] <= 128) {
									on_border = true;
									break;
								}
							}

							if (on_border)
								break;
						}

						if (on_border) {
							valid_positions[vpc] = Point2(i, j);

							if (emode == EMISSION_MODE_BORDER_DIRECTED) {
								Vector2 normal;
								for (int x = i - 2; x <= i + 2; x++) {
									for (int y = j - 2; y <= j + 2; y++) {

										if (x == i && y == j)
											continue;

										if (x < 0 || y < 0 || x >= s.width || y >= s.height || r[(y * s.width + x) * 4 + 3] <= 128) {
											normal += Vector2(x - i, y - j).normalized();
										}
									}
								}

								normal.normalize();
								valid_normals[vpc] = normal;
							}

							if (capture_colors) {
								valid_colors[vpc * 4 + 0] = r[(j * s.width + i) * 4 + 0];
								valid_colors[vpc * 4 + 1] = r[(j * s.width + i) * 4 + 1];
								valid_colors[vpc * 4 + 2] = r[(j * s.width + i) * 4 + 2];
								valid_colors[vpc * 4 + 3] = r[(j * s.width + i) * 4 + 3];
							}

							vpc++;
						}
					}
				}
			}
		}
	}

	valid_positions.resize(vpc);
	if (valid_normals.size()) {
		valid_normals.resize(vpc);
	}

	ERR_EXPLAIN(TTR("No pixels with transparency > 128 in image.."));
	ERR_FAIL_COND(valid_positions.size() == 0);

	PoolVector<uint8_t> texdata;

	int w = 2048;
	int h = (vpc / 2048) + 1;

	texdata.resize(w * h * 2 * sizeof(float));

	{
		PoolVector<uint8_t>::Write tw = texdata.write();
		float *twf = (float *)tw.ptr();
		for (int i = 0; i < vpc; i++) {

			twf[i * 2 + 0] = valid_positions[i].x;
			twf[i * 2 + 1] = valid_positions[i].y;
		}
	}

	img.instance();
	img->create(w, h, false, Image::FORMAT_RGF, texdata);

	Ref<ImageTexture> imgt;
	imgt.instance();
	imgt->create_from_image(img, 0);

	pm->set_emission_point_texture(imgt);
	pm->set_emission_point_count(vpc);

	if (capture_colors) {

		PoolVector<uint8_t> colordata;
		colordata.resize(w * h * 4); //use RG texture

		{
			PoolVector<uint8_t>::Write tw = colordata.write();
			for (int i = 0; i < vpc * 4; i++) {

				tw[i] = valid_colors[i];
			}
		}

		img.instance();
		img->create(w, h, false, Image::FORMAT_RGBA8, colordata);

		imgt.instance();
		imgt->create_from_image(img, 0);
		pm->set_emission_color_texture(imgt);
	}

	if (valid_normals.size()) {
		pm->set_emission_shape(ParticlesMaterial::EMISSION_SHAPE_DIRECTED_POINTS);

		PoolVector<uint8_t> normdata;
		normdata.resize(w * h * 2 * sizeof(float)); //use RG texture

		{
			PoolVector<uint8_t>::Write tw = normdata.write();
			float *twf = (float *)tw.ptr();
			for (int i = 0; i < vpc; i++) {
				twf[i * 2 + 0] = valid_normals[i].x;
				twf[i * 2 + 1] = valid_normals[i].y;
			}
		}

		img.instance();
		img->create(w, h, false, Image::FORMAT_RGF, normdata);

		imgt.instance();
		imgt->create_from_image(img, 0);
		pm->set_emission_normal_texture(imgt);

	} else {
		pm->set_emission_shape(ParticlesMaterial::EMISSION_SHAPE_POINTS);
	}
}