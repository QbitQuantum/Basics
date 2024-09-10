void
bp_camera_set_look_at (camera_t *camera, vector_t look_at)
{
	float dir_length, up_length, right_length;
	vector_t dir;     /* direction vector not normalized */

	dir_length   = MAG (camera->direction);
	up_length    = MAG (camera->up);
	right_length = MAG (camera->right);

	SUB   (dir, look_at, camera->location);

	CROSS   (camera->right, dir, camera->sky);
	VRESIZE (camera->right, right_length);

	CROSS   (camera->up, camera->right, dir);
	VRESIZE (camera->up, up_length);

	VSET_SIZE (camera->direction, dir, dir_length);
}