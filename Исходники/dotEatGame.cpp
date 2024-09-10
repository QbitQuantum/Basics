void draw_car()
{
	g_db.setCursorPos(g_car.m_pos.first*2, g_car.m_pos.second);
	g_db.setColor(DblBuffer::GREEN, DblBuffer::BLACK);
	g_db.write("＠");
}