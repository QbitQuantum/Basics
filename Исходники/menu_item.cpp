void Button::RenderItem(Controller * ctrl, ScreenUniformData * u_data, Sprite * m_sprite, GLuint frame, GLuint action)
{
	u_data->ApplyMatrix(Translation(this->m_prop->position)*Scale(this->m_prop->size));


	glm::vec4 color;
	if (action == NONE)
		color = this->m_prop->color;
	else if (action == HOVER)
		color = this->m_prop->color * glm::vec4(1.2f, 1.2f, 1.2f, 1.0f);
	else if (action == PRESSED)
		color = this->m_prop->color * glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);



	u_data->SetAmbientLight(color);


	m_sprite->Render(frame);


}