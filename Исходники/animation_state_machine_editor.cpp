void AnimationNodeStateMachineEditor::_state_machine_draw() {

	Ref<StyleBox> style = get_stylebox("frame", "GraphNode");
	Ref<StyleBox> style_selected = get_stylebox("selectedframe", "GraphNode");

	Ref<Font> font = get_font("title_font", "GraphNode");
	Color font_color = get_color("title_color", "GraphNode");
	Ref<Texture> play = get_icon("Play", "EditorIcons");
	Ref<Texture> auto_play = get_icon("AutoPlay", "EditorIcons");
	Ref<Texture> edit = get_icon("Edit", "EditorIcons");
	Color accent = get_color("accent_color", "Editor");
	Color linecolor = get_color("font_color", "Label");
	linecolor.a *= 0.3;
	Ref<StyleBox> playing_overlay = get_stylebox("position", "GraphNode");

	bool playing = state_machine->is_playing();
	StringName current = state_machine->get_current_node();
	StringName blend_from = state_machine->get_blend_from_node();
	Vector<StringName> travel_path = state_machine->get_travel_path();

	if (state_machine_draw->has_focus()) {
		state_machine_draw->draw_rect(Rect2(Point2(), state_machine_draw->get_size()), accent, false);
	}
	int sep = 3 * EDSCALE;

	List<StringName> nodes;
	state_machine->get_node_list(&nodes);

	node_rects.clear();
	Rect2 scroll_range(Point2(), state_machine_draw->get_size());

	//snap lines
	if (dragging_selected) {

		Vector2 from = (state_machine->get_node(selected_node)->get_position() * EDSCALE) + drag_ofs - state_machine->get_graph_offset() * EDSCALE;
		if (snap_x != StringName()) {
			Vector2 to = (state_machine->get_node(snap_x)->get_position() * EDSCALE) - state_machine->get_graph_offset() * EDSCALE;
			state_machine_draw->draw_line(from, to, linecolor, 2);
		}
		if (snap_y != StringName()) {
			Vector2 to = (state_machine->get_node(snap_y)->get_position() * EDSCALE) - state_machine->get_graph_offset() * EDSCALE;
			state_machine_draw->draw_line(from, to, linecolor, 2);
		}
	}

	//pre pass nodes so we know the rectangles
	for (List<StringName>::Element *E = nodes.front(); E; E = E->next()) {

		Ref<AnimationNode> anode = state_machine->get_node(E->get());
		String name = E->get();
		bool needs_editor = EditorNode::get_singleton()->item_has_editor(anode.ptr());
		Ref<StyleBox> sb = E->get() == selected_node ? style_selected : style;

		Size2 s = sb->get_minimum_size();
		int strsize = font->get_string_size(name).width;
		s.width += strsize;
		s.height += MAX(font->get_height(), play->get_height());
		s.width += sep + play->get_width();
		if (needs_editor) {
			s.width += sep + edit->get_width();
		}

		Vector2 offset;
		offset += anode->get_position() * EDSCALE;
		if (selected_node == E->get() && dragging_selected) {
			offset += drag_ofs;
		}
		offset -= s / 2;
		offset = offset.floor();

		//prepre rect

		NodeRect nr;
		nr.node = Rect2(offset, s);
		nr.node_name = E->get();

		scroll_range = scroll_range.merge(nr.node); //merge with range

		//now scroll it to draw
		nr.node.position -= state_machine->get_graph_offset() * EDSCALE;

		node_rects.push_back(nr);
	}

	transition_lines.clear();

	//draw conecting line for potential new transition
	if (connecting) {
		Vector2 from = (state_machine->get_node(connecting_from)->get_position() * EDSCALE) - state_machine->get_graph_offset() * EDSCALE;
		Vector2 to;
		if (connecting_to_node != StringName()) {
			to = (state_machine->get_node(connecting_to_node)->get_position() * EDSCALE) - state_machine->get_graph_offset() * EDSCALE;
		} else {
			to = connecting_to;
		}

		for (int i = 0; i < node_rects.size(); i++) {
			if (node_rects[i].node_name == connecting_from) {
				_clip_src_line_to_rect(from, to, node_rects[i].node);
			}
			if (node_rects[i].node_name == connecting_to_node) {
				_clip_dst_line_to_rect(from, to, node_rects[i].node);
			}
		}

		_connection_draw(from, to, AnimationNodeStateMachineTransition::SwitchMode(transition_mode->get_selected()), true, false, false, false);
	}

	Ref<Texture> tr_reference_icon = get_icon("TransitionImmediateBig", "EditorIcons");
	float tr_bidi_offset = int(tr_reference_icon->get_height() * 0.8);

	//draw transition lines
	for (int i = 0; i < state_machine->get_transition_count(); i++) {

		TransitionLine tl;
		tl.from_node = state_machine->get_transition_from(i);
		Vector2 ofs_from = (dragging_selected && tl.from_node == selected_node) ? drag_ofs : Vector2();
		tl.from = (state_machine->get_node(tl.from_node)->get_position() * EDSCALE) + ofs_from - state_machine->get_graph_offset() * EDSCALE;

		tl.to_node = state_machine->get_transition_to(i);
		Vector2 ofs_to = (dragging_selected && tl.to_node == selected_node) ? drag_ofs : Vector2();
		tl.to = (state_machine->get_node(tl.to_node)->get_position() * EDSCALE) + ofs_to - state_machine->get_graph_offset() * EDSCALE;

		Ref<AnimationNodeStateMachineTransition> tr = state_machine->get_transition(i);
		tl.disabled = tr->is_disabled();
		tl.auto_advance = tr->has_auto_advance();
		tl.mode = tr->get_switch_mode();
		tl.width = tr_bidi_offset;

		if (state_machine->has_transition(tl.to_node, tl.from_node)) { //offset if same exists
			Vector2 offset = -(tl.from - tl.to).normalized().tangent() * tr_bidi_offset;
			tl.from += offset;
			tl.to += offset;
		}

		for (int i = 0; i < node_rects.size(); i++) {
			if (node_rects[i].node_name == tl.from_node) {
				_clip_src_line_to_rect(tl.from, tl.to, node_rects[i].node);
			}
			if (node_rects[i].node_name == tl.to_node) {
				_clip_dst_line_to_rect(tl.from, tl.to, node_rects[i].node);
			}
		}

		bool selected = selected_transition_from == tl.from_node && selected_transition_to == tl.to_node;

		bool travel = false;

		if (blend_from == tl.from_node && current == tl.to_node) {
			travel = true;
		}

		if (travel_path.size()) {

			if (current == tl.from_node && travel_path[0] == tl.to_node) {
				travel = true;
			} else {
				for (int j = 0; j < travel_path.size() - 1; j++) {
					if (travel_path[j] == tl.from_node && travel_path[j + 1] == tl.to_node) {
						travel = true;
						break;
					}
				}
			}
		}
		_connection_draw(tl.from, tl.to, tl.mode, !tl.disabled, selected, travel, tl.auto_advance);

		transition_lines.push_back(tl);
	}

	//draw actual nodes
	for (int i = 0; i < node_rects.size(); i++) {

		String name = node_rects[i].node_name;
		Ref<AnimationNode> anode = state_machine->get_node(name);
		bool needs_editor = EditorNode::get_singleton()->item_has_editor(anode.ptr());
		Ref<StyleBox> sb = name == selected_node ? style_selected : style;
		int strsize = font->get_string_size(name).width;

		NodeRect &nr = node_rects.write[i];

		Vector2 offset = nr.node.position;
		int h = nr.node.size.height;

		//prepre rect

		//now scroll it to draw
		state_machine_draw->draw_style_box(sb, nr.node);

		if (playing && (blend_from == name || current == name || travel_path.find(name) != -1)) {
			state_machine_draw->draw_style_box(playing_overlay, nr.node);
		}

		bool onstart = state_machine->get_start_node() == name;
		if (onstart) {
			state_machine_draw->draw_string(font, offset + Vector2(0, -font->get_height() - 3 * EDSCALE + font->get_ascent()), TTR("Start"), font_color);
		}

		if (state_machine->get_end_node() == name) {

			int endofs = nr.node.size.x - font->get_string_size(TTR("End")).x;
			state_machine_draw->draw_string(font, offset + Vector2(endofs, -font->get_height() - 3 * EDSCALE + font->get_ascent()), TTR("End"), font_color);
		}

		offset.x += sb->get_offset().x;

		nr.play.position = offset + Vector2(0, (h - play->get_height()) / 2).floor();
		nr.play.size = play->get_size();

		Ref<Texture> play_tex = onstart ? auto_play : play;

		if (over_node == name && over_node_what == 0) {
			state_machine_draw->draw_texture(play_tex, nr.play.position, accent);
		} else {
			state_machine_draw->draw_texture(play_tex, nr.play.position);
		}
		offset.x += sep + play->get_width();

		nr.name.position = offset + Vector2(0, (h - font->get_height()) / 2).floor();
		nr.name.size = Vector2(strsize, font->get_height());

		state_machine_draw->draw_string(font, nr.name.position + Vector2(0, font->get_ascent()), name, font_color);
		offset.x += strsize + sep;

		if (needs_editor) {
			nr.edit.position = offset + Vector2(0, (h - edit->get_height()) / 2).floor();
			nr.edit.size = edit->get_size();

			if (over_node == name && over_node_what == 1) {
				state_machine_draw->draw_texture(edit, nr.edit.position, accent);
			} else {
				state_machine_draw->draw_texture(edit, nr.edit.position);
			}
			offset.x += sep + edit->get_width();
		}
	}

	scroll_range = scroll_range.grow(200 * EDSCALE);

	//adjust scrollbars
	updating = true;
	h_scroll->set_min(scroll_range.position.x);
	h_scroll->set_max(scroll_range.position.x + scroll_range.size.x);
	h_scroll->set_page(state_machine_draw->get_size().x);
	h_scroll->set_value(state_machine->get_graph_offset().x);

	v_scroll->set_min(scroll_range.position.y);
	v_scroll->set_max(scroll_range.position.y + scroll_range.size.y);
	v_scroll->set_page(state_machine_draw->get_size().y);
	v_scroll->set_value(state_machine->get_graph_offset().y);
	updating = false;

	state_machine_play_pos->update();
}