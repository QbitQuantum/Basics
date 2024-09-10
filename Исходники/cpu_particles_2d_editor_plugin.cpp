void CPUParticles2DEditorPlugin::_generate_emission_mask() {

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
							valid_colors.write[vpc * 4 + 0] = r[(j * s.width + i) * 4 + 0];
							valid_colors.write[vpc * 4 + 1] = r[(j * s.width + i) * 4 + 1];
							valid_colors.write[vpc * 4 + 2] = r[(j * s.width + i) * 4 + 2];
							valid_colors.write[vpc * 4 + 3] = r[(j * s.width + i) * 4 + 3];
						}
						valid_positions.write[vpc++] = Point2(i, j);

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
							valid_positions.write[vpc] = Point2(i, j);

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
								valid_normals.write[vpc] = normal;
							}

							if (capture_colors) {
								valid_colors.write[vpc * 4 + 0] = r[(j * s.width + i) * 4 + 0];
								valid_colors.write[vpc * 4 + 1] = r[(j * s.width + i) * 4 + 1];
								valid_colors.write[vpc * 4 + 2] = r[(j * s.width + i) * 4 + 2];
								valid_colors.write[vpc * 4 + 3] = r[(j * s.width + i) * 4 + 3];
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

	ERR_EXPLAIN(TTR("No pixels with transparency > 128 in image..."));
	ERR_FAIL_COND(valid_positions.size() == 0);

	if (capture_colors) {
		PoolColorArray pca;
		pca.resize(vpc);
		PoolColorArray::Write pcaw = pca.write();
		for (int i = 0; i < vpc; i += 1) {
			Color color;
			color.r = valid_colors[i * 4 + 0] / 255.0f;
			color.g = valid_colors[i * 4 + 1] / 255.0f;
			color.b = valid_colors[i * 4 + 2] / 255.0f;
			color.a = valid_colors[i * 4 + 3] / 255.0f;
			pcaw[i] = color;
		}
		particles->set_emission_colors(pca);
	}

	if (valid_normals.size()) {
		particles->set_emission_shape(CPUParticles2D::EMISSION_SHAPE_DIRECTED_POINTS);
		PoolVector2Array norms;
		norms.resize(valid_normals.size());
		PoolVector2Array::Write normsw = norms.write();
		for (int i = 0; i < valid_normals.size(); i += 1) {
			normsw[i] = valid_normals[i];
		}
		particles->set_emission_normals(norms);
	} else {
		particles->set_emission_shape(CPUParticles2D::EMISSION_SHAPE_POINTS);
	}

	{
		PoolVector2Array points;
		points.resize(valid_positions.size());
		PoolVector2Array::Write pointsw = points.write();
		for (int i = 0; i < valid_positions.size(); i += 1) {
			pointsw[i] = valid_positions[i];
		}
		particles->set_emission_points(points);
	}
}