	void GenericRendererAnimationInfo::render(Camera* cam, Layer* layer, RenderList& instances, RenderBackend* renderbackend) {
		Point p = m_anchor.getCalculatedPoint(cam, layer, m_zoomed);
		if(m_anchor.getLayer() == layer) {
			int32_t animtime = scaleTime(m_time_scale, TimeManager::instance()->getTime() - m_start_time) % m_animation->getDuration();
			ImagePtr img = m_animation->getFrameByTimestamp(animtime);
			Rect r;
			Rect viewport = cam->getViewPort();
			uint32_t width, height;
			if(m_zoomed) {
				width = static_cast<uint32_t>(round(img->getWidth() * cam->getZoom()));
				height = static_cast<uint32_t>(round(img->getHeight() * cam->getZoom()));
			} else {
				width = img->getWidth();
				height = img->getHeight();
			}
			r.x = p.x-width/2;
			r.y = p.y-height/2;
			r.w = width;
			r.h = height;
			if(r.intersects(viewport)) {
				img->render(r);
			}
		}
	}