bool NpcCls::MouseOver(MouseHandler& mouse)
{
	if(m_hitbox.contains(mouse.GetPosition().x, mouse.GetPosition().y))
	{
		mouse.SetCursor(7);
		return true;
	}
	return false;
}