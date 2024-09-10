void FX_DreamPrecalc(CinematicBitmap * bi, float amp, float fps) {
	
	float a = DreamAng;
	float a2 = DreamAng2;
	
	Vec2f s;
	s.x = float(bi->m_count.x) * std::cos(glm::radians(0.f));
	s.y = float(bi->m_count.y) * std::cos(glm::radians(0.f));
	
	Vec2i n;
	n.x = (bi->m_count.x + 1) << 1;
	n.y = (bi->m_count.y + 1) << 1;
	
	Vec2f nn = Vec2f(n) + s;
	
	Vec2f o;
	o.x = amp * ((2 * (std::sin(nn.x / 20) + std::sin(nn.x * nn.y / 2000)
	                  + std::sin((nn.x + nn.y) / 100) + std::sin((nn.y - nn.x) / 70) + std::sin((nn.x + 4 * nn.y) / 70)
	                  + 2 * std::sin(hypotf(256 - nn.x, (150 - nn.y / 8)) / 40))));
	o.y = amp * (((std::cos(nn.x / 31) + std::cos(nn.x * nn.y / 1783) +
	              + 2 * std::cos((nn.x + nn.y) / 137) + std::cos((nn.y - nn.x) / 55) + 2 * std::cos((nn.x + 8 * nn.y) / 57)
	              + std::cos(hypotf(384 - nn.x, (274 - nn.y / 9)) / 51))));
	
	float * t = DreamTable;
	n.y = ((bi->m_count.y * bi->grid.m_scale) + 1);
	
	while(n.y) {
		n.x = ((bi->m_count.x * bi->grid.m_scale) + 1);
		while(n.x) {
			s.x = float(bi->m_count.x) * std::cos(glm::radians(a));
			s.y = float(bi->m_count.y) * std::cos(glm::radians(a2));
			a -= 15.f;
			a2 += 8.f;
			
			nn.x = float(n.x) + s.x;
			nn.y = float(n.y) + s.y;
			
			*t++ = (-o.x + amp * ((2 * (std::sin(nn.x / 20) + std::sin(nn.x * nn.y / 2000)
			                                  + std::sin((nn.x + nn.y) / 100) + std::sin((nn.y - nn.x) / 70) + std::sin((nn.x + 4 * nn.y) / 70)
			                                  + 2 * std::sin(hypotf(256 - nn.x, (150 - nn.y / 8)) / 40)))));
			*t++ = (-o.y + amp * (((std::cos(nn.x / 31) + std::cos(nn.x * nn.y / 1783) +
			                              + 2 * std::cos((nn.x + nn.y) / 137) + std::cos((nn.y - nn.x) / 55) + 2 * std::cos((nn.x + 8 * nn.y) / 57)
			                              + std::cos(hypotf(384 - nn.x, (274 - nn.y / 9)) / 51)))));
			
			n.x--;
		}
		n.y--;
	}
	
	DreamAng += 4.f * fps;
	DreamAng2 -= 2.f * fps;
}