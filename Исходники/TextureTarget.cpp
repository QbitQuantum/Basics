//----------------------------------------------------------------------------//
void NullTextureTarget::declareRenderSize(const Sizef& sz)
{
	Rectf r;
	r.setSize(sz);
    r.setPosition(glm::vec2(0, 0));
    setArea(r);
}