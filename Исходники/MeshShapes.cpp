TriMeshf sphere(const float radius, const ml::vec3f& pos, const size_t stacks /*= 10*/, const size_t slices /*= 10*/, const ml::vec4f& color /*= ml::vec4f(1,1,1,1) */) {
	MeshDataf meshdata;
	auto& V = meshdata.m_Vertices;
	auto& I = meshdata.m_FaceIndicesVertices;
	auto& N = meshdata.m_Normals;
	auto& C = meshdata.m_Colors;
	const float thetaDivisor = 1.0f / stacks * ml::math::PIf;
	const float phiDivisor = 1.0f / slices * 2.0f * ml::math::PIf; 
	for (size_t t = 0; t < stacks; t++) { // stacks increment elevation (theta)
		float theta1 = t * thetaDivisor;
		float theta2 = (t + 1) * thetaDivisor;

		for (size_t p = 0; p < slices; p++) { // slices increment azimuth (phi)
			float phi1 = p * phiDivisor;
			float phi2 = (p + 1) * phiDivisor;

			const auto sph2xyz = [&](float r, float theta, float phi) {
				const float sinTheta = sinf(theta), sinPhi = sinf(phi), cosTheta = cosf(theta), cosPhi = cosf(phi);
				return ml::vec3f(r * sinTheta * cosPhi, r * sinTheta * sinPhi, r * cosTheta);
			};

			// phi2   phi1
			//  |      |
			//  2------1 -- theta1
			//  |\ _   |
			//  |    \ |
			//  3------4 -- theta2
			//  
			// Points
			const ml::vec3f c1 = pos + sph2xyz(radius, theta1, phi1),
				c2 = pos + sph2xyz(radius, theta1, phi2),
				c3 = pos + sph2xyz(radius, theta2, phi2),
				c4 = pos + sph2xyz(radius, theta2, phi1);
			V.push_back(c1);
			V.push_back(c2);
			V.push_back(c3);
			V.push_back(c4);

			// Colors
			for (int i = 0; i < 4; i++) {
				C.push_back(color);
			}

			// Normals
			N.push_back(c1.getNormalized());
			N.push_back(c2.getNormalized());
			N.push_back(c3.getNormalized());
			N.push_back(c4.getNormalized());

			const UINT baseIdx = static_cast<UINT>(t * slices * 4 + p * 4);

			// Indices
			std::vector<unsigned int> indices;
			if ( t == 0 ) {  // top cap -- t1p1, t2p2, t2p1
				indices.push_back(baseIdx + 0);
				indices.push_back(baseIdx + 2);
				indices.push_back(baseIdx + 3);
				I.push_back(indices);
			}
			else if ( t + 1 == stacks ) {  // bottom cap -- t2p2, t1p1, t1p2
				indices.push_back(baseIdx + 2);
				indices.push_back(baseIdx + 0);
				indices.push_back(baseIdx + 1);
				I.push_back(indices);
			}
			else {  // regular piece
				indices.push_back(baseIdx + 0);
				indices.push_back(baseIdx + 1);
				indices.push_back(baseIdx + 3);
				I.push_back(indices);
				indices.clear();
				indices.push_back(baseIdx + 1);
				indices.push_back(baseIdx + 2);
				indices.push_back(baseIdx + 3);
				I.push_back(indices);
			}
		}
	}
	//meshdata.mergeCloseVertices(0.00001f, true);
	return TriMeshf(meshdata);
}