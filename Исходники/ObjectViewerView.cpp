void ObjectViewerView::Draw3D()
{
	m_renderer->ClearScreen();
	float znear, zfar;
	m_renderer->GetNearFarRange(znear, zfar);
	m_renderer->SetPerspectiveProjection(75.f, Pi::GetScrAspect(), znear, zfar);
	m_renderer->SetTransform(matrix4x4f::Identity());

	Graphics::Light light;
	light.SetType(Graphics::Light::LIGHT_DIRECTIONAL);

	if (Pi::MouseButtonState(SDL_BUTTON_RIGHT)) {
		int m[2];
		Pi::GetMouseMotion(m);
		m_camRot = matrix4x4d::RotateXMatrix(-0.002*m[1]) *
				matrix4x4d::RotateYMatrix(-0.002*m[0]) * m_camRot;
	}

	Body *body = Pi::player->GetNavTarget();
	if (body) {
		if (body->IsType(Object::STAR))
			light.SetPosition(vector3f(0.f));
		else {
			light.SetPosition(vector3f(0.577f));
		}
		m_renderer->SetLights(1, &light);

		body->Render(m_renderer, 0, vector3d(0,0,-viewingDist), m_camRot);
	}
}