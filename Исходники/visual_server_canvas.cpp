void VisualServerCanvas::_render_canvas_item(Item *p_canvas_item, const Transform2D &p_transform, const Rect2 &p_clip_rect, const Color &p_modulate, int p_z, RasterizerCanvas::Item **z_list, RasterizerCanvas::Item **z_last_list, Item *p_canvas_clip, Item *p_material_owner) {

	Item *ci = p_canvas_item;

	if (!ci->visible)
		return;

	Rect2 rect = ci->get_rect();
	Transform2D xform = p_transform * ci->xform;
	Rect2 global_rect = xform.xform(rect);
	global_rect.pos += p_clip_rect.pos;

	if (ci->use_parent_material && p_material_owner)
		ci->material_owner = p_material_owner;
	else {
		p_material_owner = ci;
		ci->material_owner = NULL;
	}

	Color modulate(ci->modulate.r * p_modulate.r, ci->modulate.g * p_modulate.g, ci->modulate.b * p_modulate.b, ci->modulate.a * p_modulate.a);

	if (modulate.a < 0.007)
		return;

	int child_item_count = ci->child_items.size();
	Item **child_items = (Item **)alloca(child_item_count * sizeof(Item *));
	copymem(child_items, ci->child_items.ptr(), child_item_count * sizeof(Item *));

	if (ci->clip) {
		if (p_canvas_clip != NULL) {
			ci->final_clip_rect = p_canvas_clip->final_clip_rect.clip(global_rect);
		} else {
			ci->final_clip_rect = global_rect;
		}
		ci->final_clip_owner = ci;

	} else {
		ci->final_clip_owner = p_canvas_clip;
	}

	if (ci->sort_y) {

		SortArray<Item *, ItemPtrSort> sorter;
		sorter.sort(child_items, child_item_count);
	}

	if (ci->z_relative)
		p_z = CLAMP(p_z + ci->z, VS::CANVAS_ITEM_Z_MIN, VS::CANVAS_ITEM_Z_MAX);
	else
		p_z = ci->z;

	for (int i = 0; i < child_item_count; i++) {

		if (!child_items[i]->behind)
			continue;
		_render_canvas_item(child_items[i], xform, p_clip_rect, modulate, p_z, z_list, z_last_list, (Item *)ci->final_clip_owner, p_material_owner);
	}

	if (ci->copy_back_buffer) {

		ci->copy_back_buffer->screen_rect = xform.xform(ci->copy_back_buffer->rect).clip(p_clip_rect);
	}

	if ((!ci->commands.empty() && p_clip_rect.intersects(global_rect)) || ci->vp_render || ci->copy_back_buffer) {
		//something to draw?
		ci->final_transform = xform;
		ci->final_modulate = Color(modulate.r * ci->self_modulate.r, modulate.g * ci->self_modulate.g, modulate.b * ci->self_modulate.b, modulate.a * ci->self_modulate.a);
		ci->global_rect_cache = global_rect;
		ci->global_rect_cache.pos -= p_clip_rect.pos;
		ci->light_masked = false;

		int zidx = p_z - VS::CANVAS_ITEM_Z_MIN;

		if (z_last_list[zidx]) {
			z_last_list[zidx]->next = ci;
			z_last_list[zidx] = ci;

		} else {
			z_list[zidx] = ci;
			z_last_list[zidx] = ci;
		}

		ci->next = NULL;
	}

	for (int i = 0; i < child_item_count; i++) {

		if (child_items[i]->behind)
			continue;
		_render_canvas_item(child_items[i], xform, p_clip_rect, modulate, p_z, z_list, z_last_list, (Item *)ci->final_clip_owner, p_material_owner);
	}
}