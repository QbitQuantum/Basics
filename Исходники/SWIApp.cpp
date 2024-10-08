void SWIApp::draw()
{
	if (!best_list.empty()) {
		float s=40;
		float aspect = RenderUtil::height / (float)RenderUtil::width;
		RenderUtil::beginCamera(Box2(-s,-s*aspect,s,s*aspect));
		glColor3ub(0,0,255);
		glPushMatrix();
			glTranslatef(-20.0f, 0.0f, 0.0f);
			best->render(15.0f);
			RenderUtil::drawCircle(Vector2(), best->radius, false);
		glPopMatrix();
		glColor3ub(0,0,255);
		SqcConfig* last_best = best_list.back();
		glPushMatrix();
			glTranslatef(20.0f, 0.0f, 0.0f);
			last_best->render(15.0f);
			RenderUtil::drawCircle(Vector2(), last_best->radius, false);
		glPopMatrix();
		RenderUtil::endCamera();

		graph.render(Box2(20, 500, 800-20, 590));

		glColor4ub(255,255,255,255);
		GlyphRenderer::getDefaultRenderer()->drawString(Vector2(100, 50), 20.0f, SPrintf("Overall r=%f. F=%f", best->radius, best->fitness).c_str());
		GlyphRenderer::getDefaultRenderer()->drawString(Vector2(500, 50), 20.0f, SPrintf("Last r=%f. F=%f", last_best->radius, last_best->fitness).c_str());
	}
	GlyphRenderer::getDefaultRenderer()->drawString(Vector2(100, 70), 20.0f, SPrintf("Swarm Intelligence Demo.  Sigma=%f", sigma).c_str());
}