void ShadowVolumeGenerator::generateShadowVolumes(ShadowMesh* mesh, const Vector4& osLightPos,
		vector<uint32_t>& vindices)
{
	Vector3 osLightPos3(osLightPos);

	bool* frontFacing = new bool[mesh->numFaces];

	for (uint32_t faceIdx = 0 ; faceIdx < mesh->numFaces ; faceIdx++) {
		Vector3& normal = *((Vector3*) (mesh->faceNormals + faceIdx*3));
		Vector3& v1 = *((Vector3*) (mesh->vertices + mesh->indices[faceIdx*6]*4));

		Vector3 faceToLight = osLightPos3 - v1*osLightPos.getW();

		frontFacing[faceIdx] = (faceToLight * normal) > 0;
	}

	// Compute the caps
	for (uint32_t i = 0 ; i < mesh->numFaces ; i++) {
		uint32_t idx1 = mesh->indices[i*6];
		uint32_t idx2 = mesh->indices[i*6 + 2];
		uint32_t idx3 = mesh->indices[i*6 + 4];

		if (!frontFacing[i]) {
			uint32_t oldIdx2 = idx2;
			idx2 = idx3;
			idx3 = oldIdx2;
		}

		// Front cap
		vindices.push_back(idx1);
		vindices.push_back(idx2);
		vindices.push_back(idx3);

		// Back cap
		vindices.push_back(mesh->numVertices + idx1);
		vindices.push_back(mesh->numVertices + idx3);
		vindices.push_back(mesh->numVertices + idx2);
	}

	// Compute the silhouette sides
	for (uint32_t faceIdx = 0 ; faceIdx < mesh->numFaces ; faceIdx++) {
		for (uint32_t j = 0 ; j < 3 ; j++) {
			uint32_t edgeIdx1 = mesh->indices[faceIdx*6 + j*2];
			uint32_t neighborIdx = mesh->indices[faceIdx*6 + j*2 + 1];
			uint32_t edgeIdx2 = mesh->indices[faceIdx*6 + (j*2 + 2) % 6];

			uint32_t neighborFaceIdx = mesh->adjacentFaces[faceIdx*3 + j];

			if (faceIdx == 15  &&  neighborFaceIdx == 16) {
				//printf("Here we are!\n");
			}

			if (neighborIdx >= mesh->numVertices  ||  frontFacing[faceIdx] != frontFacing[neighborFaceIdx]) {
				// This is a possible silhouette side

				uint32_t sideIdx1 = frontFacing[faceIdx] ? edgeIdx1 : edgeIdx2;
				uint32_t sideIdx2 = frontFacing[faceIdx] ? edgeIdx2 : edgeIdx1;

				vindices.push_back(sideIdx1);
				vindices.push_back(mesh->numVertices + sideIdx1);
				vindices.push_back(sideIdx2);

				vindices.push_back(sideIdx2);
				vindices.push_back(mesh->numVertices + sideIdx1);
				vindices.push_back(mesh->numVertices + sideIdx2);
			}
		}
	}

	delete[] frontFacing;
}