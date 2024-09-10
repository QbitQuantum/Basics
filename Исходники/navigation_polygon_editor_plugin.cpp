bool NavigationPolygonEditor::forward_gui_input(const Ref<InputEvent> &p_event) {

	if (!node)
		return false;

	if (node->get_navigation_polygon().is_null()) {

		Ref<InputEventMouseButton> mb = p_event;

		if (mb.is_valid() && mb->get_button_index() == 1 && mb->is_pressed()) {
			create_nav->set_text("No NavigationPolygon resource on this node.\nCreate and assign one?");
			create_nav->popup_centered_minsize();
		}
		return (mb.is_valid() && mb->get_button_index() == 1);
	}

	Ref<InputEventMouseButton> mb = p_event;

	if (mb.is_valid()) {

		Transform2D xform = canvas_item_editor->get_canvas_transform() * node->get_global_transform();

		Vector2 gpoint = mb->get_position();
		Vector2 cpoint = canvas_item_editor->get_canvas_transform().affine_inverse().xform(gpoint);
		cpoint = canvas_item_editor->snap_point(cpoint);
		cpoint = node->get_global_transform().affine_inverse().xform(cpoint);

		//first check if a point is to be added (segment split)
		real_t grab_threshold = EDITOR_DEF("editors/poly_editor/point_grab_radius", 8);

		switch (mode) {

			case MODE_CREATE: {

				if (mb->get_button_index() == BUTTON_LEFT && mb->is_pressed()) {

					if (!wip_active) {

						wip.clear();
						wip.push_back(cpoint);
						wip_active = true;
						edited_point_pos = cpoint;
						edited_outline = -1;
						canvas_item_editor->get_viewport_control()->update();
						edited_point = 1;
						return true;
					} else {

						if (wip.size() > 1 && xform.xform(wip[0]).distance_to(gpoint) < grab_threshold) {
							//wip closed
							_wip_close();

							return true;
						} else {

							wip.push_back(cpoint);
							edited_point = wip.size();
							canvas_item_editor->get_viewport_control()->update();
							return true;

							//add wip point
						}
					}
				} else if (mb->get_button_index() == BUTTON_RIGHT && mb->is_pressed() && wip_active) {
					_wip_close();
				}

			} break;

			case MODE_EDIT: {

				if (mb->get_button_index() == BUTTON_LEFT) {
					if (mb->is_pressed()) {

						if (mb->get_control()) {

							//search edges
							int closest_outline = -1;
							int closest_idx = -1;
							Vector2 closest_pos;
							real_t closest_dist = 1e10;

							for (int j = 0; j < node->get_navigation_polygon()->get_outline_count(); j++) {

								PoolVector<Vector2> points = node->get_navigation_polygon()->get_outline(j);

								int pc = points.size();
								PoolVector<Vector2>::Read poly = points.read();

								for (int i = 0; i < pc; i++) {

									Vector2 points[2] = { xform.xform(poly[i]),
										xform.xform(poly[(i + 1) % pc]) };

									Vector2 cp = Geometry::get_closest_point_to_segment_2d(gpoint, points);
									if (cp.distance_squared_to(points[0]) < CMP_EPSILON2 || cp.distance_squared_to(points[1]) < CMP_EPSILON2)
										continue; //not valid to reuse point

									real_t d = cp.distance_to(gpoint);
									if (d < closest_dist && d < grab_threshold) {
										closest_dist = d;
										closest_outline = j;
										closest_pos = cp;
										closest_idx = i;
									}
								}
							}

							if (closest_idx >= 0) {

								pre_move_edit = node->get_navigation_polygon()->get_outline(closest_outline);
								PoolVector<Point2> poly = pre_move_edit;
								poly.insert(closest_idx + 1, xform.affine_inverse().xform(closest_pos));
								edited_point = closest_idx + 1;
								edited_outline = closest_outline;
								edited_point_pos = xform.affine_inverse().xform(closest_pos);
								node->get_navigation_polygon()->set_outline(closest_outline, poly);
								canvas_item_editor->get_viewport_control()->update();
								return true;
							}
						} else {

							//look for points to move
							int closest_outline = -1;
							int closest_idx = -1;
							Vector2 closest_pos;
							real_t closest_dist = 1e10;

							for (int j = 0; j < node->get_navigation_polygon()->get_outline_count(); j++) {

								PoolVector<Vector2> points = node->get_navigation_polygon()->get_outline(j);

								int pc = points.size();
								PoolVector<Vector2>::Read poly = points.read();

								for (int i = 0; i < pc; i++) {

									Vector2 cp = xform.xform(poly[i]);

									real_t d = cp.distance_to(gpoint);
									if (d < closest_dist && d < grab_threshold) {
										closest_dist = d;
										closest_pos = cp;
										closest_outline = j;
										closest_idx = i;
									}
								}
							}

							if (closest_idx >= 0) {

								pre_move_edit = node->get_navigation_polygon()->get_outline(closest_outline);
								edited_point = closest_idx;
								edited_outline = closest_outline;
								edited_point_pos = xform.affine_inverse().xform(closest_pos);
								canvas_item_editor->get_viewport_control()->update();
								return true;
							}
						}
					} else {

						if (edited_point != -1) {

							//apply

							PoolVector<Vector2> poly = node->get_navigation_polygon()->get_outline(edited_outline);
							ERR_FAIL_INDEX_V(edited_point, poly.size(), false);
							poly.set(edited_point, edited_point_pos);
							undo_redo->create_action(TTR("Edit Poly"));
							undo_redo->add_do_method(node->get_navigation_polygon().ptr(), "set_outline", edited_outline, poly);
							undo_redo->add_undo_method(node->get_navigation_polygon().ptr(), "set_outline", edited_outline, pre_move_edit);
							undo_redo->add_do_method(node->get_navigation_polygon().ptr(), "make_polygons_from_outlines");
							undo_redo->add_undo_method(node->get_navigation_polygon().ptr(), "make_polygons_from_outlines");
							undo_redo->add_do_method(canvas_item_editor->get_viewport_control(), "update");
							undo_redo->add_undo_method(canvas_item_editor->get_viewport_control(), "update");
							undo_redo->commit_action();

							edited_point = -1;
							return true;
						}
					}
				} else if (mb->get_button_index() == BUTTON_RIGHT && mb->is_pressed() && edited_point == -1) {

					int closest_outline = -1;
					int closest_idx = -1;
					Vector2 closest_pos;
					real_t closest_dist = 1e10;

					for (int j = 0; j < node->get_navigation_polygon()->get_outline_count(); j++) {

						PoolVector<Vector2> points = node->get_navigation_polygon()->get_outline(j);

						int pc = points.size();
						PoolVector<Vector2>::Read poly = points.read();

						for (int i = 0; i < pc; i++) {

							Vector2 cp = xform.xform(poly[i]);

							real_t d = cp.distance_to(gpoint);
							if (d < closest_dist && d < grab_threshold) {
								closest_dist = d;
								closest_pos = cp;
								closest_outline = j;
								closest_idx = i;
							}
						}
					}

					if (closest_idx >= 0) {

						PoolVector<Vector2> poly = node->get_navigation_polygon()->get_outline(closest_outline);

						if (poly.size() > 3) {
							undo_redo->create_action(TTR("Edit Poly (Remove Point)"));
							undo_redo->add_undo_method(node->get_navigation_polygon().ptr(), "set_outline", closest_outline, poly);
							poly.remove(closest_idx);
							undo_redo->add_do_method(node->get_navigation_polygon().ptr(), "set_outline", closest_outline, poly);
							undo_redo->add_do_method(node->get_navigation_polygon().ptr(), "make_polygons_from_outlines");
							undo_redo->add_undo_method(node->get_navigation_polygon().ptr(), "make_polygons_from_outlines");
							undo_redo->add_do_method(canvas_item_editor->get_viewport_control(), "update");
							undo_redo->add_undo_method(canvas_item_editor->get_viewport_control(), "update");
							undo_redo->commit_action();
						} else {

							undo_redo->create_action(TTR("Remove Poly And Point"));
							undo_redo->add_undo_method(node->get_navigation_polygon().ptr(), "add_outline_at_index", poly, closest_outline);
							poly.remove(closest_idx);
							undo_redo->add_do_method(node->get_navigation_polygon().ptr(), "remove_outline", closest_outline);
							undo_redo->add_do_method(node->get_navigation_polygon().ptr(), "make_polygons_from_outlines");
							undo_redo->add_undo_method(node->get_navigation_polygon().ptr(), "make_polygons_from_outlines");
							undo_redo->add_do_method(canvas_item_editor->get_viewport_control(), "update");
							undo_redo->add_undo_method(canvas_item_editor->get_viewport_control(), "update");
							undo_redo->commit_action();
						}
						return true;
					}
				}

			} break;
		}
	}

	Ref<InputEventMouseMotion> mm = p_event;

	if (mm.is_valid()) {

		if (edited_point != -1 && (wip_active || mm->get_button_mask() & BUTTON_MASK_LEFT)) {

			Vector2 gpoint = mm->get_position();
			Vector2 cpoint = canvas_item_editor->get_canvas_transform().affine_inverse().xform(gpoint);
			cpoint = canvas_item_editor->snap_point(cpoint);
			edited_point_pos = node->get_global_transform().affine_inverse().xform(cpoint);

			canvas_item_editor->get_viewport_control()->update();
		}
	}

	return false;
}