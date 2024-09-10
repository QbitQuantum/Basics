void AnimationTree::_process_graph(float p_delta) {

	_update_properties(); //if properties need updating, update them

	//check all tracks, see if they need modification

	root_motion_transform = Transform();

	if (!root.is_valid()) {
		ERR_PRINT("AnimationTree: root AnimationNode is not set, disabling playback.");
		set_active(false);
		cache_valid = false;
		return;
	}

	if (!has_node(animation_player)) {
		ERR_PRINT("AnimationTree: no valid AnimationPlayer path set, disabling playback");
		set_active(false);
		cache_valid = false;
		return;
	}

	AnimationPlayer *player = Object::cast_to<AnimationPlayer>(get_node(animation_player));

	ObjectID current_animation_player = 0;

	if (player) {
		current_animation_player = player->get_instance_id();
	}

	if (last_animation_player != current_animation_player) {

		if (last_animation_player) {
			Object *old_player = ObjectDB::get_instance(last_animation_player);
			if (old_player) {
				old_player->disconnect("caches_cleared", this, "_clear_caches");
			}
		}

		if (player) {
			player->connect("caches_cleared", this, "_clear_caches");
		}

		last_animation_player = current_animation_player;
	}

	if (!player) {
		ERR_PRINT("AnimationTree: path points to a node not an AnimationPlayer, disabling playback");
		set_active(false);
		cache_valid = false;
		return;
	}

	if (!cache_valid) {
		if (!_update_caches(player)) {
			return;
		}
	}

	{ //setup

		process_pass++;

		state.valid = true;
		state.invalid_reasons = "";
		state.animation_states.clear(); //will need to be re-created
		state.valid = true;
		state.player = player;
		state.last_pass = process_pass;
		state.tree = this;

		// root source blends

		root->blends.resize(state.track_count);
		float *src_blendsw = root->blends.ptrw();
		for (int i = 0; i < state.track_count; i++) {
			src_blendsw[i] = 1.0; //by default all go to 1 for the root input
		}
	}

	//process

	{

		if (started) {
			//if started, seek
			root->_pre_process(SceneStringNames::get_singleton()->parameters_base_path, NULL, &state, 0, true, Vector<StringName>());
			started = false;
		}

		root->_pre_process(SceneStringNames::get_singleton()->parameters_base_path, NULL, &state, p_delta, false, Vector<StringName>());
	}

	if (!state.valid) {
		return; //state is not valid. do nothing.
	}
	//apply value/transform/bezier blends to track caches and execute method/audio/animation tracks

	{

		bool can_call = is_inside_tree() && !Engine::get_singleton()->is_editor_hint();

		for (List<AnimationNode::AnimationState>::Element *E = state.animation_states.front(); E; E = E->next()) {

			const AnimationNode::AnimationState &as = E->get();

			Ref<Animation> a = as.animation;
			float time = as.time;
			float delta = as.delta;
			bool seeked = as.seeked;

			for (int i = 0; i < a->get_track_count(); i++) {

				NodePath path = a->track_get_path(i);

				ERR_CONTINUE(!track_cache.has(path));

				TrackCache *track = track_cache[path];
				if (track->type != a->track_get_type(i)) {
					continue; //may happen should not
				}

				track->root_motion = root_motion_track == path;

				ERR_CONTINUE(!state.track_map.has(path));
				int blend_idx = state.track_map[path];

				ERR_CONTINUE(blend_idx < 0 || blend_idx >= state.track_count);

				float blend = (*as.track_blends)[blend_idx];

				if (blend < CMP_EPSILON)
					continue; //nothing to blend

				switch (track->type) {

					case Animation::TYPE_TRANSFORM: {

						TrackCacheTransform *t = static_cast<TrackCacheTransform *>(track);

						if (track->root_motion) {

							if (t->process_pass != process_pass) {

								t->process_pass = process_pass;
								t->loc = Vector3();
								t->rot = Quat();
								t->rot_blend_accum = 0;
								t->scale = Vector3(1, 1, 1);
							}

							float prev_time = time - delta;
							if (prev_time < 0) {
								if (!a->has_loop()) {
									prev_time = 0;
								} else {
									prev_time = a->get_length() + prev_time;
								}
							}

							Vector3 loc[2];
							Quat rot[2];
							Vector3 scale[2];

							if (prev_time > time) {

								Error err = a->transform_track_interpolate(i, prev_time, &loc[0], &rot[0], &scale[0]);
								if (err != OK) {
									continue;
								}

								a->transform_track_interpolate(i, a->get_length(), &loc[1], &rot[1], &scale[1]);

								t->loc += (loc[1] - loc[0]) * blend;
								t->scale += (scale[1] - scale[0]) * blend;
								Quat q = Quat().slerp(rot[0].normalized().inverse() * rot[1].normalized(), blend).normalized();
								t->rot = (t->rot * q).normalized();

								prev_time = 0;
							}

							Error err = a->transform_track_interpolate(i, prev_time, &loc[0], &rot[0], &scale[0]);
							if (err != OK) {
								continue;
							}

							a->transform_track_interpolate(i, time, &loc[1], &rot[1], &scale[1]);

							t->loc += (loc[1] - loc[0]) * blend;
							t->scale += (scale[1] - scale[0]) * blend;
							Quat q = Quat().slerp(rot[0].normalized().inverse() * rot[1].normalized(), blend).normalized();
							t->rot = (t->rot * q).normalized();

							prev_time = 0;

						} else {
							Vector3 loc;
							Quat rot;
							Vector3 scale;

							Error err = a->transform_track_interpolate(i, time, &loc, &rot, &scale);
							//ERR_CONTINUE(err!=OK); //used for testing, should be removed

							if (t->process_pass != process_pass) {

								t->process_pass = process_pass;
								t->loc = loc;
								t->rot = rot;
								t->rot_blend_accum = 0;
								t->scale = scale;
							}

							if (err != OK)
								continue;

							t->loc = t->loc.linear_interpolate(loc, blend);
							if (t->rot_blend_accum == 0) {
								t->rot = rot;
								t->rot_blend_accum = blend;
							} else {
								float rot_total = t->rot_blend_accum + blend;
								t->rot = rot.slerp(t->rot, t->rot_blend_accum / rot_total).normalized();
								t->rot_blend_accum = rot_total;
							}
							t->scale = t->scale.linear_interpolate(scale, blend);
						}

					} break;
					case Animation::TYPE_VALUE: {

						TrackCacheValue *t = static_cast<TrackCacheValue *>(track);

						Animation::UpdateMode update_mode = a->value_track_get_update_mode(i);

						if (update_mode == Animation::UPDATE_CONTINUOUS || update_mode == Animation::UPDATE_CAPTURE) { //delta == 0 means seek

							Variant value = a->value_track_interpolate(i, time);

							if (value == Variant())
								continue;

							if (t->process_pass != process_pass) {
								t->value = value;
								t->process_pass = process_pass;
							}

							Variant::interpolate(t->value, value, blend, t->value);

						} else if (delta != 0) {

							List<int> indices;
							a->value_track_get_key_indices(i, time, delta, &indices);

							for (List<int>::Element *F = indices.front(); F; F = F->next()) {

								Variant value = a->track_get_key_value(i, F->get());
								t->object->set_indexed(t->subpath, value);
							}
						}

					} break;
					case Animation::TYPE_METHOD: {

						if (delta == 0) {
							continue;
						}
						TrackCacheMethod *t = static_cast<TrackCacheMethod *>(track);

						List<int> indices;

						a->method_track_get_key_indices(i, time, delta, &indices);

						for (List<int>::Element *F = indices.front(); F; F = F->next()) {

							StringName method = a->method_track_get_name(i, F->get());
							Vector<Variant> params = a->method_track_get_params(i, F->get());

							int s = params.size();

							ERR_CONTINUE(s > VARIANT_ARG_MAX);
							if (can_call) {
								t->object->call_deferred(
										method,
										s >= 1 ? params[0] : Variant(),
										s >= 2 ? params[1] : Variant(),
										s >= 3 ? params[2] : Variant(),
										s >= 4 ? params[3] : Variant(),
										s >= 5 ? params[4] : Variant());
							}
						}

					} break;
					case Animation::TYPE_BEZIER: {

						TrackCacheBezier *t = static_cast<TrackCacheBezier *>(track);

						float bezier = a->bezier_track_interpolate(i, time);

						if (t->process_pass != process_pass) {
							t->value = bezier;
							t->process_pass = process_pass;
						}

						t->value = Math::lerp(t->value, bezier, blend);

					} break;
					case Animation::TYPE_AUDIO: {

						TrackCacheAudio *t = static_cast<TrackCacheAudio *>(track);

						if (seeked) {
							//find whathever should be playing
							int idx = a->track_find_key(i, time);
							if (idx < 0)
								continue;

							Ref<AudioStream> stream = a->audio_track_get_key_stream(i, idx);
							if (!stream.is_valid()) {
								t->object->call("stop");
								t->playing = false;
								playing_caches.erase(t);
							} else {
								float start_ofs = a->audio_track_get_key_start_offset(i, idx);
								start_ofs += time - a->track_get_key_time(i, idx);
								float end_ofs = a->audio_track_get_key_end_offset(i, idx);
								float len = stream->get_length();

								if (start_ofs > len - end_ofs) {
									t->object->call("stop");
									t->playing = false;
									playing_caches.erase(t);
									continue;
								}

								t->object->call("set_stream", stream);
								t->object->call("play", start_ofs);

								t->playing = true;
								playing_caches.insert(t);
								if (len && end_ofs > 0) { //force a end at a time
									t->len = len - start_ofs - end_ofs;
								} else {
									t->len = 0;
								}

								t->start = time;
							}

						} else {
							//find stuff to play
							List<int> to_play;
							a->track_get_key_indices_in_range(i, time, delta, &to_play);
							if (to_play.size()) {
								int idx = to_play.back()->get();

								Ref<AudioStream> stream = a->audio_track_get_key_stream(i, idx);
								if (!stream.is_valid()) {
									t->object->call("stop");
									t->playing = false;
									playing_caches.erase(t);
								} else {
									float start_ofs = a->audio_track_get_key_start_offset(i, idx);
									float end_ofs = a->audio_track_get_key_end_offset(i, idx);
									float len = stream->get_length();

									t->object->call("set_stream", stream);
									t->object->call("play", start_ofs);

									t->playing = true;
									playing_caches.insert(t);
									if (len && end_ofs > 0) { //force a end at a time
										t->len = len - start_ofs - end_ofs;
									} else {
										t->len = 0;
									}

									t->start = time;
								}
							} else if (t->playing) {

								bool loop = a->has_loop();

								bool stop = false;

								if (!loop && time < t->start) {
									stop = true;
								} else if (t->len > 0) {
									float len = t->start > time ? (a->get_length() - t->start) + time : time - t->start;

									if (len > t->len) {
										stop = true;
									}
								}

								if (stop) {
									//time to stop
									t->object->call("stop");
									t->playing = false;
									playing_caches.erase(t);
								}
							}
						}

						float db = Math::linear2db(MAX(blend, 0.00001));
						if (t->object->has_method("set_unit_db")) {
							t->object->call("set_unit_db", db);
						} else {
							t->object->call("set_volume_db", db);
						}
					} break;
					case Animation::TYPE_ANIMATION: {

						TrackCacheAnimation *t = static_cast<TrackCacheAnimation *>(track);

						AnimationPlayer *player2 = Object::cast_to<AnimationPlayer>(t->object);

						if (!player2)
							continue;

						if (delta == 0 || seeked) {
							//seek
							int idx = a->track_find_key(i, time);
							if (idx < 0)
								continue;

							float pos = a->track_get_key_time(i, idx);

							StringName anim_name = a->animation_track_get_key_animation(i, idx);
							if (String(anim_name) == "[stop]" || !player2->has_animation(anim_name))
								continue;

							Ref<Animation> anim = player2->get_animation(anim_name);

							float at_anim_pos;

							if (anim->has_loop()) {
								at_anim_pos = Math::fposmod(time - pos, anim->get_length()); //seek to loop
							} else {
								at_anim_pos = MAX(anim->get_length(), time - pos); //seek to end
							}

							if (player2->is_playing() || seeked) {
								player2->play(anim_name);
								player2->seek(at_anim_pos);
								t->playing = true;
								playing_caches.insert(t);
							} else {
								player2->set_assigned_animation(anim_name);
								player2->seek(at_anim_pos, true);
							}
						} else {
							//find stuff to play
							List<int> to_play;
							a->track_get_key_indices_in_range(i, time, delta, &to_play);
							if (to_play.size()) {
								int idx = to_play.back()->get();

								StringName anim_name = a->animation_track_get_key_animation(i, idx);
								if (String(anim_name) == "[stop]" || !player2->has_animation(anim_name)) {

									if (playing_caches.has(t)) {
										playing_caches.erase(t);
										player2->stop();
										t->playing = false;
									}
								} else {
									player2->play(anim_name);
									t->playing = true;
									playing_caches.insert(t);
								}
							}
						}

					} break;
				}
			}
		}
	}

	{
		// finally, set the tracks
		const NodePath *K = NULL;
		while ((K = track_cache.next(K))) {
			TrackCache *track = track_cache[*K];
			if (track->process_pass != process_pass)
				continue; //not processed, ignore

			switch (track->type) {

				case Animation::TYPE_TRANSFORM: {

					TrackCacheTransform *t = static_cast<TrackCacheTransform *>(track);

					Transform xform;
					xform.origin = t->loc;

					xform.basis.set_quat_scale(t->rot, t->scale);

					if (t->root_motion) {

						root_motion_transform = xform;

						if (t->skeleton && t->bone_idx >= 0) {
							root_motion_transform = (t->skeleton->get_bone_rest(t->bone_idx) * root_motion_transform) * t->skeleton->get_bone_rest(t->bone_idx).affine_inverse();
						}
					} else if (t->skeleton && t->bone_idx >= 0) {

						t->skeleton->set_bone_pose(t->bone_idx, xform);

					} else {

						t->spatial->set_transform(xform);
					}

				} break;
				case Animation::TYPE_VALUE: {

					TrackCacheValue *t = static_cast<TrackCacheValue *>(track);

					t->object->set_indexed(t->subpath, t->value);

				} break;
				case Animation::TYPE_BEZIER: {

					TrackCacheBezier *t = static_cast<TrackCacheBezier *>(track);

					t->object->set_indexed(t->subpath, t->value);

				} break;
				default: {
				} //the rest don't matter
			}
		}
	}
}