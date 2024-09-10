void AnimatedSprite3D::_draw() {

	RID immediate = get_immediate();
	VS::get_singleton()->immediate_clear(immediate);

	if (frames.is_null()) {
		return;
	}

	if (frame < 0) {
		return;
	}

	if (!frames->has_animation(animation)) {
		return;
	}

	Ref<Texture> texture = frames->get_frame(animation, frame);
	if (!texture.is_valid())
		return; //no texuture no life
	Vector2 tsize = texture->get_size();
	if (tsize.x == 0 || tsize.y == 0)
		return;

	Size2i s = tsize;
	Rect2 src_rect;

	src_rect.size = s;

	Point2 ofs = get_offset();
	if (is_centered())
		ofs -= s / 2;

	Rect2 dst_rect(ofs, s);

	Rect2 final_rect;
	Rect2 final_src_rect;
	if (!texture->get_rect_region(dst_rect, src_rect, final_rect, final_src_rect))
		return;

	if (final_rect.size.x == 0 || final_rect.size.y == 0)
		return;

	Color color = _get_color_accum();
	color.a *= get_opacity();

	float pixel_size = get_pixel_size();

	Vector2 vertices[4] = {

		(final_rect.position + Vector2(0, final_rect.size.y)) * pixel_size,
		(final_rect.position + final_rect.size) * pixel_size,
		(final_rect.position + Vector2(final_rect.size.x, 0)) * pixel_size,
		final_rect.position * pixel_size,

	};

	Vector2 src_tsize = tsize;

	// Properly setup UVs for impostor textures (AtlasTexture).
	Ref<AtlasTexture> atlas_tex = texture;
	if (atlas_tex != NULL) {
		src_tsize[0] = atlas_tex->get_atlas()->get_width();
		src_tsize[1] = atlas_tex->get_atlas()->get_height();
	}

	Vector2 uvs[4] = {
		final_src_rect.position / src_tsize,
		(final_src_rect.position + Vector2(final_src_rect.size.x, 0)) / src_tsize,
		(final_src_rect.position + final_src_rect.size) / src_tsize,
		(final_src_rect.position + Vector2(0, final_src_rect.size.y)) / src_tsize,
	};

	if (is_flipped_h()) {
		SWAP(uvs[0], uvs[1]);
		SWAP(uvs[2], uvs[3]);
	}
	if (is_flipped_v()) {

		SWAP(uvs[0], uvs[3]);
		SWAP(uvs[1], uvs[2]);
	}

	Vector3 normal;
	int axis = get_axis();
	normal[axis] = 1.0;

	Plane tangent;
	if (axis == Vector3::AXIS_X) {
		tangent = Plane(0, 0, -1, -1);
	} else {
		tangent = Plane(1, 0, 0, -1);
	}

	RID mat = SpatialMaterial::get_material_rid_for_2d(get_draw_flag(FLAG_SHADED), get_draw_flag(FLAG_TRANSPARENT), get_draw_flag(FLAG_DOUBLE_SIDED), get_alpha_cut_mode() == ALPHA_CUT_DISCARD, get_alpha_cut_mode() == ALPHA_CUT_OPAQUE_PREPASS);

	VS::get_singleton()->immediate_set_material(immediate, mat);

	VS::get_singleton()->immediate_begin(immediate, VS::PRIMITIVE_TRIANGLE_FAN, texture->get_rid());

	int x_axis = ((axis + 1) % 3);
	int y_axis = ((axis + 2) % 3);

	if (axis != Vector3::AXIS_Z) {
		SWAP(x_axis, y_axis);

		for (int i = 0; i < 4; i++) {
			//uvs[i] = Vector2(1.0,1.0)-uvs[i];
			//SWAP(vertices[i].x,vertices[i].y);
			if (axis == Vector3::AXIS_Y) {
				vertices[i].y = -vertices[i].y;
			} else if (axis == Vector3::AXIS_X) {
				vertices[i].x = -vertices[i].x;
			}
		}
	}

	AABB aabb;

	for (int i = 0; i < 4; i++) {
		VS::get_singleton()->immediate_normal(immediate, normal);
		VS::get_singleton()->immediate_tangent(immediate, tangent);
		VS::get_singleton()->immediate_color(immediate, color);
		VS::get_singleton()->immediate_uv(immediate, uvs[i]);

		Vector3 vtx;
		vtx[x_axis] = vertices[i][0];
		vtx[y_axis] = vertices[i][1];
		VS::get_singleton()->immediate_vertex(immediate, vtx);
		if (i == 0) {
			aabb.position = vtx;
			aabb.size = Vector3();
		} else {
			aabb.expand_to(vtx);
		}
	}
	set_aabb(aabb);
	VS::get_singleton()->immediate_end(immediate);
}