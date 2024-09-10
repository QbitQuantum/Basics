void AasRenderer::RecalcNormals(int vertexCount, const XMFLOAT4* pos, XMFLOAT4* normals, int primCount, const uint16_t* indices) {
	static XMFLOAT4 recalcNormalsBuffer[0x8000];
	memset(recalcNormalsBuffer, 0, vertexCount * sizeof(XMFLOAT4));

	// Process every TRI we have
	auto curIdx = indices;
	for (auto tri = 0; tri < primCount; ++tri) {
		// Indices of the three vertices making up this triangle
		auto idx1 = *curIdx++;
		auto idx2 = *curIdx++;
		auto idx3 = *curIdx++;

		auto pos1 = XMLoadFloat4(&pos[idx1]);
		auto pos2 = XMLoadFloat4(&pos[idx2]);
		auto pos3 = XMLoadFloat4(&pos[idx3]);

		auto v1to2(pos2 - pos1);
		auto v1to3(pos3 - pos1);

		// Calculate the surface normal of the surface defined 
		// by the two directional vectors
		auto surfNormal(XMVector3Cross(v1to2, v1to3) * -1);

		// The surface normal contributes to all three vertex normals
		XMStoreFloat4(&normals[idx1], surfNormal);
		XMStoreFloat4(&normals[idx2], surfNormal);
		XMStoreFloat4(&normals[idx3], surfNormal);
	}

	// Re-Normalize the normals we calculated
	for (auto i = 0; i < vertexCount; ++i) {
		auto normal(XMVector3Normalize(XMLoadFloat4(&normals[i])));
		XMStoreFloat4(&normals[i], normal);
	}
}