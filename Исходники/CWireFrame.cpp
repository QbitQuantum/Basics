void CWireFrame::AddLine(float x0, float y0, float x1, float y1) {
	mVertices.push_back(Vector2f(x0, y0));
	mVertices.push_back(Vector2f(x1, y1));
}