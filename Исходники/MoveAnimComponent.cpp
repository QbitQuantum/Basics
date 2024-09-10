void MoveAnimComponent::executeEvent(GameEvent *event)
{
	switch(event->id())
	{
	case GameEvent::E_SET_TRANSFORMATION:
		{
			Matrix4f absTrans = Matrix4f(static_cast<const float*>(event->data()));
			static Vec3f s;
			absTrans.decompose(m_newPos, m_rotation, s);
		}
		break;
	case GameEvent::E_AILOD_CHANGE:
		m_lod = *static_cast<int*>(event->data());
		break;
	case GameEvent::E_SET_TRANSLATION:
		m_newPos = *static_cast<Vec3f*>(event->data());
		break;
	case GameEvent::E_SET_MOVE_ANIM:
		std::pair<std::string, std::string>* data = 
			static_cast<std::pair<std::string, std::string>*>(event->data());
		changeMoveAnim(data->first, data->second);
		break;
	}
}