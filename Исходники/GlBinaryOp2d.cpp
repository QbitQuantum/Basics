status_t _GlBinaryOp2d::Process(	const GlPlanes* src, GlPlanes& dest,
									GlProcessStatus* status)
{
	if (dest.size < 1) return B_OK;

	GlAlgo2d*		lh = Algo2dAt(_LH_INDEX);
	GlAlgo2d*		rh = Algo2dAt(_RH_INDEX);

	if (lh && rh) {
		GlPlanes*	c = dest.Clone();
		if (c && c->size == dest.size) {
			lh->Process(src, dest, status);
			rh->Process(src, *c, status);
			if (mOp == GL_ADD_BINARY_SRF_KEY) Add(dest, *c);
			else if (mOp == GL_SUB_BINARY_SRF_KEY) Sub(dest, *c);
			else if (mOp == GL_MULT_BINARY_SRF_KEY) Mult(dest, *c);
			else if (mOp == GL_DIV_BINARY_SRF_KEY) Div(dest, *c);
			else if (mOp == GL_MIN_BINARY_SRF_KEY) Min(dest, *c);
			else if (mOp == GL_MAX_BINARY_SRF_KEY) Max(dest, *c);
			else ArpASSERT(false);
		}
		delete c;
	} else if (lh) {
		lh->Process(src, dest, status);
	} else if (rh) {
		rh->Process(src, dest, status);
	}
	return B_OK;
}