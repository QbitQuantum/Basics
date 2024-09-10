static void obj_trampoline_construct(GameObject* self, Vector2 pos, void* user_data) {
	SprHandle spr_handle = (SprHandle)user_data;

	ObjTrampoline* trampoline = (ObjTrampoline*)self;

	Vector2 size = sprsheet_get_size_h(spr_handle);
	float width = size.x;
	float height = size.y;

	trampoline->oh = height;
	trampoline->h = height;
	trampoline->dh = 0.0f;
	trampoline->db = 0.0f;

	RectF collider = {
		pos.x - 50.0f, 			pos.y,
		pos.x  + width + 50.0f, pos.y - height
	};

	// Physics
	PhysicsComponent* physics = self->physics;
	physics->cd_obj = coldet_new_aabb(objects_cdworld, &collider, OBJ_TRAMPOLINE_TYPE, NULL);
	physics->inv_mass = 0.0f;
	physics->hit_callback = obj_trampoline_collide;

	// Render
	RenderComponent* render = self->render;
	render->world_dest = rectf(
			pos.x, pos.y - height,
			pos.x + width, pos.y
	);
	render->layer = foreground_layer;
	render->anim_frame = MAX_UINT16;
	render->spr = spr_handle;
	render->update_pos = obj_trampoline_update_pos;
	render->became_invisible = obj_trampoline_became_invisible;

	// for rising up animation
	physics->cd_obj->pos.y += height/2.0f + 15.0f;
	render->world_dest.bottom += height/2.0f + 15.0f;
}