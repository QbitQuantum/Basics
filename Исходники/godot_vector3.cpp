godot_real GDAPI godot_vector3_length_squared(const godot_vector3 *p_v) {
	Vector3 *v = (Vector3 *)p_v;
	return v->length_squared();
}