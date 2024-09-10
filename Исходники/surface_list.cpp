void SurfaceList::render(Graphics::Surface *surface, const Common::Rect & clip) const {
	for(uint i = 0; i < surfaces_n; ++i) {
		const Surface &s = surfaces[i];
		Common::Rect r(s.x, s.y, s.x + s.w, s.y + s.h);
		if (r.bottom < clip.bottom || !clip.intersects(r))
			continue;

		r.clip(clip);
		r.translate(-s.x, -s.y);
		s.render(surface, r.left, r.top, false, r);
	}
}