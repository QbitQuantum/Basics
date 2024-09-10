void GDAPI godot_pool_real_array_invert(godot_pool_real_array *p_self) {
	PoolVector<godot_real> *self = (PoolVector<godot_real> *)p_self;
	self->invert();
}