void CProjectileHandler::DrawProjectilesMiniMap(const ProjectileContainer& pc) {
	if (pc.render_size() > 0) {
		CVertexArray* lines = GetVertexArray();
		CVertexArray* points = GetVertexArray();

		lines->Initialize();
		lines->EnlargeArrays(pc.render_size() * 2, 0, VA_SIZE_C);

		points->Initialize();
		points->EnlargeArrays(pc.render_size(), 0, VA_SIZE_C);

		for (ProjectileContainer::render_iterator pci = pc.render_begin(); pci != pc.render_end(); ++pci) {
			CProjectile* p = *pci;

			if ((p->owner() && (p->owner()->allyteam == gu->myAllyTeam)) ||
				gu->spectatingFullView || loshandler->InLos(p, gu->myAllyTeam)) {
				p->DrawOnMinimap(*lines, *points);
			}
		}

		lines->DrawArrayC(GL_LINES);
		points->DrawArrayC(GL_POINTS);
	}
}