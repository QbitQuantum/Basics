	void LightRendererImageInfo::render(Camera* cam, Layer* layer, RenderList& instances, RenderBackend* renderbackend) {
		Point p = m_anchor.getCalculatedPoint(cam, layer, true);
		if(m_anchor.getLayer() == layer) {
			Rect r;
			Rect viewport = cam->getViewPort();
			uint32_t width = static_cast<uint32_t>(round(m_image->getWidth() * cam->getZoom()));
			uint32_t height = static_cast<uint32_t>(round(m_image->getHeight() * cam->getZoom()));
			r.x = p.x-width/2;
			r.y = p.y-height/2;
			r.w = width;
			r.h = height;

			if(r.intersects(viewport)) {
				uint8_t lm = renderbackend->getLightingModel();
				m_image->render(r);
				if (m_stencil) {
					renderbackend->changeRenderInfos(RENDER_DATA_WITHOUT_Z, 1, m_src, m_dst, false, true, m_stencil_ref, INCR, GEQUAL);
				} else if (lm == 1) {
					renderbackend->changeRenderInfos(RENDER_DATA_WITHOUT_Z, 1, m_src, m_dst, false, true, 255, KEEP, NOTEQUAL);
				}
			}
		}
	}