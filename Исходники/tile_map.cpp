void TileMap::_update_dirty_quadrants() {

	if (!pending_update)
		return;
	if (!is_inside_tree())
		return;
	if (!tile_set.is_valid())
		return;

	VisualServer *vs = VisualServer::get_singleton();
	Physics2DServer *ps = Physics2DServer::get_singleton();
	Vector2 tofs = get_cell_draw_offset();
	Vector2 tcenter = cell_size/2;
	Matrix32 nav_rel;
	if (navigation)
		nav_rel = get_relative_transform_to_parent(navigation);

	Vector2 qofs;

	SceneTree *st=SceneTree::get_singleton();
	Color debug_collision_color;

	bool debug_shapes = st && st->is_debugging_collisions_hint();
	if (debug_shapes) {
		debug_collision_color=st->get_debug_collisions_color();
	}

	while (dirty_quadrant_list.first()) {

		Quadrant &q = *dirty_quadrant_list.first()->self();

		for (List<RID>::Element *E=q.canvas_items.front();E;E=E->next()) {

			vs->free(E->get());
		}

		q.canvas_items.clear();

		ps->body_clear_shapes(q.body);
		int shape_idx=0;

		if (navigation) {
			for(Map<PosKey,Quadrant::NavPoly>::Element *E=q.navpoly_ids.front();E;E=E->next()) {

				navigation->navpoly_remove(E->get().id);
			}
			q.navpoly_ids.clear();
		}

		for(Map<PosKey,Quadrant::Occluder>::Element *E=q.occluder_instances.front();E;E=E->next()) {
			VS::get_singleton()->free(E->get().id);
		}
		q.occluder_instances.clear();
		Ref<CanvasItemMaterial> prev_material;
		RID prev_canvas_item;
		RID prev_debug_canvas_item;

		for(int i=0;i<q.cells.size();i++) {

			Map<PosKey,Cell>::Element *E=tile_map.find( q.cells[i] );
			Cell &c=E->get();
			//moment of truth
			if (!tile_set->has_tile(c.id))
				continue;
			Ref<Texture> tex = tile_set->tile_get_texture(c.id);
			Vector2 tile_ofs = tile_set->tile_get_texture_offset(c.id);

			Vector2 wofs = _map_to_world(E->key().x, E->key().y);
			Vector2 offset = wofs - q.pos + tofs;

			if (!tex.is_valid())
				continue;

			Ref<CanvasItemMaterial> mat = tile_set->tile_get_material(c.id);

			RID canvas_item;
			RID debug_canvas_item;

			if (prev_canvas_item==RID() || prev_material!=mat) {

				canvas_item=vs->canvas_item_create();
				if (mat.is_valid())
					vs->canvas_item_set_material(canvas_item,mat->get_rid());
				vs->canvas_item_set_parent( canvas_item, get_canvas_item() );
				Matrix32 xform;
				xform.set_origin( q.pos );
				vs->canvas_item_set_transform( canvas_item, xform );
				vs->canvas_item_set_light_mask(canvas_item,get_light_mask());
				vs->canvas_item_set_blend_mode(canvas_item,VS::MaterialBlendMode(get_blend_mode()));

				q.canvas_items.push_back(canvas_item);

				if (debug_shapes) {

					debug_canvas_item=vs->canvas_item_create();
					vs->canvas_item_set_parent( debug_canvas_item, canvas_item );
					vs->canvas_item_set_z_as_relative_to_parent(debug_canvas_item,false);
					vs->canvas_item_set_z(debug_canvas_item,VS::CANVAS_ITEM_Z_MAX-1);
					q.canvas_items.push_back(debug_canvas_item);
					prev_debug_canvas_item=debug_canvas_item;
				}

				prev_canvas_item=canvas_item;
				prev_material=mat;

			} else {
				canvas_item=prev_canvas_item;
				if (debug_shapes) {
					debug_canvas_item=prev_debug_canvas_item;
				}
			}



			Rect2 r = tile_set->tile_get_region(c.id);
			Size2 s = tex->get_size();

			if (r==Rect2())
				s = tex->get_size();
			else {
				s = r.size;
				r.pos.x+=fp_adjust;
				r.pos.y+=fp_adjust;
				r.size.x-=fp_adjust*2.0;
				r.size.y-=fp_adjust*2.0;
			}

			Rect2 rect;
			rect.pos=offset.floor();
			rect.size=s;

			if (rect.size.y > rect.size.x) {
				if ((c.flip_h && (c.flip_v || c.transpose)) || (c.flip_v && !c.transpose))
					tile_ofs.y += rect.size.y - rect.size.x;
			} else if (rect.size.y < rect.size.x) {
				if ((c.flip_v && (c.flip_h || c.transpose)) || (c.flip_h && !c.transpose))
					tile_ofs.x += rect.size.x - rect.size.y;
			}

		/*	rect.size.x+=fp_adjust;
			rect.size.y+=fp_adjust;*/

			if (c.transpose)
				SWAP(tile_ofs.x, tile_ofs.y);

			if (c.flip_h) {
				rect.size.x=-rect.size.x;
				tile_ofs.x=-tile_ofs.x;
			}
			if (c.flip_v) {
				rect.size.y=-rect.size.y;
				tile_ofs.y=-tile_ofs.y;
			}

			Vector2 center_ofs;

			if (tile_origin==TILE_ORIGIN_TOP_LEFT) {
				rect.pos+=tile_ofs;
				
			} else if (tile_origin==TILE_ORIGIN_BOTTOM_LEFT) {
								
				rect.pos+=tile_ofs;
				
				if(c.transpose)
				{
					if(c.flip_h)
						rect.pos.x-=cell_size.x;
					else
						rect.pos.x+=cell_size.x;
				} else {
					if(c.flip_v)
						rect.pos.y-=cell_size.y;
					else
						rect.pos.y+=cell_size.y;
				}
				
			} else if (tile_origin==TILE_ORIGIN_CENTER) {
				rect.pos+=tcenter;

				Vector2 center = (s/2) - tile_ofs;
				center_ofs=tcenter-(s/2);

				if (c.flip_h)
					rect.pos.x-=s.x-center.x;
				else
					rect.pos.x-=center.x;

				if (c.flip_v)
					rect.pos.y-=s.y-center.y;
				else
					rect.pos.y-=center.y;
			}


			if (r==Rect2()) {
				tex->draw_rect(canvas_item,rect,false,Color(1,1,1),c.transpose);
			} else {
				tex->draw_rect_region(canvas_item,rect,r,Color(1,1,1),c.transpose);
			}

			Vector< Ref<Shape2D> > shapes = tile_set->tile_get_shapes(c.id);


			for(int i=0;i<shapes.size();i++) {

				Ref<Shape2D> shape = shapes[i];
				if (shape.is_valid()) {

					Vector2 shape_ofs = tile_set->tile_get_shape_offset(c.id);
					Matrix32 xform;
					xform.set_origin(offset.floor());

					_fix_cell_transform(xform,c,shape_ofs+center_ofs,s);

					if (debug_canvas_item) {
						vs->canvas_item_add_set_transform(debug_canvas_item,xform);
						shape->draw(debug_canvas_item,debug_collision_color);

					}
					ps->body_add_shape(q.body,shape->get_rid(),xform);
					ps->body_set_shape_metadata(q.body,shape_idx++,Vector2(E->key().x,E->key().y));

				}
			}

			if (debug_canvas_item) {
				vs->canvas_item_add_set_transform(debug_canvas_item,Matrix32());
			}

			if (navigation) {
				Ref<NavigationPolygon> navpoly = tile_set->tile_get_navigation_polygon(c.id);
				if (navpoly.is_valid()) {
					Vector2 npoly_ofs = tile_set->tile_get_navigation_polygon_offset(c.id);
					Matrix32 xform;
					xform.set_origin(offset.floor()+q.pos);
					_fix_cell_transform(xform,c,npoly_ofs+center_ofs,s);


					int pid = navigation->navpoly_create(navpoly,nav_rel * xform);

					Quadrant::NavPoly np;
					np.id=pid;
					np.xform=xform;
					q.navpoly_ids[E->key()]=np;
				}
			}


			Ref<OccluderPolygon2D> occluder=tile_set->tile_get_light_occluder(c.id);
			if (occluder.is_valid()) {

				Vector2 occluder_ofs = tile_set->tile_get_occluder_offset(c.id);
				Matrix32 xform;
				xform.set_origin(offset.floor()+q.pos);
				_fix_cell_transform(xform,c,occluder_ofs+center_ofs,s);

				RID orid = VS::get_singleton()->canvas_light_occluder_create();
				VS::get_singleton()->canvas_light_occluder_set_transform(orid,get_global_transform() * xform);
				VS::get_singleton()->canvas_light_occluder_set_polygon(orid,occluder->get_rid());
				VS::get_singleton()->canvas_light_occluder_attach_to_canvas(orid,get_canvas());
				VS::get_singleton()->canvas_light_occluder_set_light_mask(orid,occluder_light_mask);
				Quadrant::Occluder oc;
				oc.xform=xform;
				oc.id=orid;
				q.occluder_instances[E->key()]=oc;
			}
		}

		dirty_quadrant_list.remove( dirty_quadrant_list.first() );
		quadrant_order_dirty=true;
	}



	pending_update=false;

	if (quadrant_order_dirty) {

		for (Map<PosKey,Quadrant>::Element *E=quadrant_map.front();E;E=E->next()) {

			Quadrant &q=E->get();
			for (List<RID>::Element *E=q.canvas_items.front();E;E=E->next()) {

				VS::get_singleton()->canvas_item_raise(E->get());
			}
		}

		quadrant_order_dirty=false;
	}

	for(int i=0;i<get_child_count();i++) {

		CanvasItem *c=get_child(i)->cast_to<CanvasItem>();

		if (c)
			VS::get_singleton()->canvas_item_raise(c->get_canvas_item());
	}

	_recompute_rect_cache();

}