void CDecalsDrawerGL4::UpdateOverlap_GenerateQueries(const std::vector<int>& candidatesForOverlap)
{
	glStencilFunc(GL_GREATER, MAX_OVERLAP, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	CVertexArray* va = GetVertexArray();
	for (int i: candidatesForOverlap) {
		Decal& d0 = decals[i];
		GLuint q;
		glGenQueries(1, &q);
		glBeginQuery(GL_ANY_SAMPLES_PASSED_CONSERVATIVE, q);

		va->Initialize();
		DRAW_DECAL(va, &d0);
		va->DrawArray2dT(GL_QUADS);

		glEndQuery(GL_ANY_SAMPLES_PASSED_CONSERVATIVE);
		waitingOverlapGlQueries.emplace_back(i, q);
	}
}