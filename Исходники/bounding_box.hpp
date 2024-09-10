bool BoundingBox<VEC>::contains(const BoundingBox<VEC>& bb)
{
	assert(m_initialized || !"Bounding box not initialized");
	return this->contains(bb.min()) && this->contains(bb.max());
}