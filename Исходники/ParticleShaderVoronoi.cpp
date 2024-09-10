void ParticleShaderVoronoi::setupBuffers(int width, int height)
{
	hdc = wglGetCurrentDC();
	hglrc = wglGetCurrentContext();

	pbufferOne = new nv_pbuffer(width, height, 1);

	pbufferOne->wglGetLastError();	

	// If we're sharing contexts, don't need to share lists
	if (pbufferOne->onecontext == false) 
		wglShareLists(pbufferOne->hglrc, hglrc);
	
}