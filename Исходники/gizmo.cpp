void Gizmo::transform(ComponentIndex camera, int x, int y, int relx, int rely, bool use_step)
{
	if (!m_is_transforming) return;

	if (m_mode == Mode::ROTATE)
	{
		rotate(relx, rely, use_step);
	}
	else
	{
		Vec3 intersection = getMousePlaneIntersection(camera, x, y);
		Vec3 delta = intersection - m_transform_point;
		if (!use_step || delta.length() > float(getStep()))
		{
			if (use_step) delta = delta.normalized() * float(getStep());

			Array<Vec3> new_positions(m_editor.getAllocator());
			for (int i = 0, ci = m_editor.getSelectedEntities().size(); i < ci; ++i)
			{
				Vec3 pos = m_editor.getUniverse()->getPosition(m_editor.getSelectedEntities()[i]);
				pos += delta;
				new_positions.push(pos);
			}
			m_editor.setEntitiesPositions(&m_editor.getSelectedEntities()[0],
				&new_positions[0],
				new_positions.size());
			if (m_is_autosnap_down) m_editor.snapDown();

			m_transform_point = intersection;
		}
	}
}