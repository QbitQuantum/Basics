SpeedLines::SpeedLines(Ship *s)
: m_ship(s)
, m_visible(false)
, m_dir(0.f)
{
	PROFILE_SCOPED();

	// init the static data
	SpeedLines::Init();

	m_points.reserve(DEPTH * DEPTH * DEPTH);
	for (int x = -DEPTH/2; x < DEPTH/2; x++) {
		for (int y = -DEPTH/2; y < DEPTH/2; y++) {
			for (int z = -DEPTH/2; z < DEPTH/2; z++) {
				m_points.push_back(vector3f(x * SPACING, y * SPACING, z * SPACING));
			}
		}
	}

	const Uint32 doubleNumPoints = static_cast<Uint32>(m_points.size()) * 2;
	m_varray.reset(new Graphics::VertexArray(Graphics::ATTRIB_POSITION | Graphics::ATTRIB_DIFFUSE, doubleNumPoints));
	for( Uint32 i = 0; i < doubleNumPoints; i++ )
		m_varray->Add(vector3f(0.0f), Color::BLACK);

	Graphics::RenderStateDesc rsd;
	rsd.blendMode = Graphics::BLEND_ALPHA_ONE;
	rsd.depthWrite = false;
	m_renderState = Pi::renderer->CreateRenderState(rsd);

	CreateVertexBuffer( Pi::renderer, doubleNumPoints );
}