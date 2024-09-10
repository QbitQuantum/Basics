	void RenderingGame::update_stencil_material() {
		MaterialDeferredStencil* m = m_stencil_material->As<MaterialDeferredStencil>();
		LightPoint* l = m_point_light->As<LightPoint>();
		float r = l->radius();
		XMMATRIX world = XMMatrixScaling(r, r, r) * XMMatrixTranslationFromVector(l->positionv());
		m->WVP() << world * m_camera->view_projection();
	}