Error EditorSceneImporterFBXConv::_parse_animations(State& state) {

	AnimationPlayer *ap = memnew( AnimationPlayer );

	state.scene->add_child(ap);
	ap->set_owner(state.scene);

	for(int i=0;i<state.animations.size();i++) {

		Dictionary anim = state.animations[i];
		ERR_CONTINUE(!anim.has("id"));
		Ref<Animation> an = memnew( Animation );
		an->set_name(_id(anim["id"]));


		if (anim.has("bones")) {

			Array bone_tracks = anim["bones"];
			for(int j=0;j<bone_tracks.size();j++) {
				Dictionary bone_track=bone_tracks[j];
				String bone = bone_track["boneId"];
				if (!bone_track.has("keyframes"))
					continue;
				if (!state.bones.has(bone))
					continue;

				Skeleton *sk = state.bones[bone].skeleton;

				if (!sk)
					continue;
				int bone_idx=sk->find_bone(bone);
				if (bone_idx==-1)
					continue;



				String path = state.scene->get_path_to(sk);
				path+=":"+bone;
				an->add_track(Animation::TYPE_TRANSFORM);
				int tidx = an->get_track_count()-1;
				an->track_set_path(tidx,path);


				Dictionary parent_xform_dict;
				Dictionary xform_dict;

				if (state.bones.has(bone)) {
					xform_dict=state.bones[bone].node;
				}


				Array parent_keyframes;
				if (sk->get_bone_parent(bone_idx)!=-1) {
					String parent_name = sk->get_bone_name(sk->get_bone_parent(bone_idx));
					if (state.bones.has(parent_name)) {
						parent_xform_dict=state.bones[parent_name].node;
					}

					print_line("parent for "+bone+"? "+parent_name+" XFD: "+String(Variant(parent_xform_dict)));
					for(int k=0;k<bone_tracks.size();k++) {
						Dictionary d = bone_tracks[k];
						if (d["boneId"]==parent_name) {
							parent_keyframes=d["keyframes"];
							print_line("found keyframes");
							break;
						}
					}


				}

				print_line("BONE XFD "+String(Variant(xform_dict)));

				Array keyframes=bone_track["keyframes"];

				for(int k=0;k<keyframes.size();k++) {

					Dictionary key=keyframes[k];
					Transform xform=_get_transform_mixed(key,xform_dict);
					float time = key["keytime"];
					time=time/1000.0;
#if 0
					if (parent_keyframes.size()) {
						//localize
						print_line(itos(k)+" localizate for: "+bone);

						float prev_kt=-1;
						float kt;
						int idx=0;

						for(int l=0;l<parent_keyframes.size();l++) {

							Dictionary d=parent_keyframes[l];
							kt=d["keytime"];
							kt=kt/1000.0;
							if (kt>time)
								break;
							prev_kt=kt;
							idx++;

						}

						Transform t;
						if (idx==0) {
							t=_get_transform_mixed(parent_keyframes[0],parent_xform_dict);
						} else if (idx==parent_keyframes.size()){
							t=_get_transform_mixed(parent_keyframes[idx-1],parent_xform_dict);
						} else {
							t=_get_transform_mixed(parent_keyframes[idx-1],parent_xform_dict);
							float d = (time-prev_kt)/(kt-prev_kt);
							if (d>0) {
								Transform t2=_get_transform_mixed(parent_keyframes[idx],parent_xform_dict);
								t=t.interpolate_with(t2,d);
							} else {
								print_line("exact: "+rtos(kt));
							}
						}

						xform = t.affine_inverse() * xform; //localize
					} else if (!parent_xform_dict.empty()) {
						Transform t = _get_transform(parent_xform_dict);
						xform = t.affine_inverse() * xform; //localize
					}
#endif

					xform = sk->get_bone_rest(bone_idx).affine_inverse() * xform;


					Quat q = xform.basis;
					q.normalize();
					Vector3 s = xform.basis.get_scale();
					Vector3 l = xform.origin;



					an->transform_track_insert_key(tidx,time,l,q,s);

				}

			}


		}


		ap->add_animation(_id(anim["id"]),an);

	}

	return OK;
}