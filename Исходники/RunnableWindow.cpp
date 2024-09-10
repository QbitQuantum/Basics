void Rekd2D::Core::RunnableWindow::Render(unsigned int time)
{
	m_DefaultShader->Bind();
	MouseState state = Mouse::GetState();
	KeyboardState ks = Keyboard::GetState();
	bool hit = false;
	for (std::vector<IComponent*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
	{
		if ((*it)->GetBounds().Collides(Vector2F(state.X, state.Y)))
		{
			if (!state.MouseButtons[1] && m_OldState.MouseButtons[1])
			{
				(*it)->Click(1);
				if ((ComponentFlag::Focusable & (*it)->GetFlags()) == ComponentFlag::Focusable)
				{
					Unfocus();
					(*it)->SetFlag(ComponentFlag::Focusable, 1);
				}
				else hit = true;
			}
		}
		if ((ComponentFlag::Pushable & (*it)->GetFlags()) == ComponentFlag::Pushable) (*it)->SetFlag(ComponentFlag::Pushable, (*it)->GetBounds().Collides(Vector2F(state.X, state.Y)) && state.MouseButtons[1]);
		if ((ComponentFlag::Hoverable & (*it)->GetFlags()) == ComponentFlag::Hoverable) (*it)->SetFlag(ComponentFlag::Hoverable, (*it)->GetBounds().Collides(Vector2F(state.X, state.Y)));
		if ((ComponentFlag::HookKeyboard & (*it)->GetFlags()) == ComponentFlag::HookKeyboard)
		{
			(*it)->OnKeyboard(ks, m_OldKeyState);
		}
		(*it)->Render(m_Renderer);
	}
	if (hit) Unfocus();
	m_OldKeyState = ks;
	m_OldState = state;
}