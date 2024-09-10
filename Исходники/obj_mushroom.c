static void obj_mushroom_construct(GameObject* self, Vector2 pos, void* user_data) {
	SprHandle spr_handle = (SprHandle)user_data;

	ObjMushroom* mushroom = (ObjMushroom*)self;

	Vector2 size = sprsheet_get_size_h(spr_handle);
	float width = size.x;
	float height = size.y;

	mushroom->oh = height;
	mushroom->h = height;
	mushroom->dh = 0.0f;

	float adjust = 20.0f;

	// Take 10 pixel slice at the top as a collider geometry
	RectF collider = {
		pos.x  + adjust, 		pos.y - height,
		pos.x  + width - adjust, pos.y - height + 10.0f
	};

	// Physics
	PhysicsComponent* physics = self->physics;
	physics->cd_obj = coldet_new_aabb(objects_cdworld, &collider, OBJ_MUSHROOM_TYPE, NULL);
	physics->inv_mass = 0.0f;
	physics->hit_callback = obj_mushroom_collide;

	// Render
	RenderComponent* render = self->render;
	render->world_dest = rectf(
			pos.x, pos.y - height,
			pos.x + width, pos.y
	);
	render->layer = foreground_layer;
	render->anim_frame = MAX_UINT16;
	render->spr = spr_handle;
	render->update_pos = obj_mushroom_update_pos;
	render->became_invisible = obj_mushroom_became_invisible;
}