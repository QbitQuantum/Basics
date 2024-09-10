static void defSurfaceSquare(const float3& center, float xsize, float zsize)
{
	// FIXME: terrain contouring
	const float3 p0 = center + float3(-xsize, 0.0f, -zsize);
	const float3 p1 = center + float3( xsize, 0.0f, -zsize);
	const float3 p2 = center + float3( xsize, 0.0f,  zsize);
	const float3 p3 = center + float3(-xsize, 0.0f,  zsize);

	CVertexArray* va = GetVertexArray();
	va->Initialize();
		va->AddVertex0(p0.x, CGround::GetHeightAboveWater(p0.x, p0.z, false), p0.z);
		va->AddVertex0(p1.x, CGround::GetHeightAboveWater(p1.x, p1.z, false), p1.z);
		va->AddVertex0(p2.x, CGround::GetHeightAboveWater(p2.x, p2.z, false), p2.z);
		va->AddVertex0(p3.x, CGround::GetHeightAboveWater(p3.x, p3.z, false), p3.z);
	va->DrawArray0(GL_LINE_LOOP);
}