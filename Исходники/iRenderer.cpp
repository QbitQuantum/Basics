Vector2f IRenderer::map_2d(const int x, const int y)
{	
	float aspect = (float)viewport_width() / (float)viewport_height();
	return Vector2f(((float)x / (float)viewport_width()  * 2.0f - 1.0f) * aspect / aspect_modifier_2d(), 
			-((float)y / (float)viewport_height()  * 2.0f - 1.0f));
}