	void EXPORT_API InitTetrasShapeMatchingJB(btVector3* initialPositions,float* invMasses, bool* posLocks, Tetrahedron* tetras, btVector3* restCMs, float* invRestMat, int tetrasCount)
	{
		for (int i = 0; i < tetrasCount; i++)
		{
			Tetrahedron tetra = tetras[i];

			Eigen::Vector3f x1_0(initialPositions[tetra.idA].x(), initialPositions[tetra.idA].y(), initialPositions[tetra.idA].z());
			Eigen::Vector3f x2_0(initialPositions[tetra.idB].x(), initialPositions[tetra.idB].y(), initialPositions[tetra.idB].z());
			Eigen::Vector3f x3_0(initialPositions[tetra.idC].x(), initialPositions[tetra.idC].y(), initialPositions[tetra.idC].z());
			Eigen::Vector3f x4_0(initialPositions[tetra.idD].x(), initialPositions[tetra.idD].y(), initialPositions[tetra.idD].z());


			float w1 = posLocks[tetra.idA] ? 0.0f : invMasses[tetra.idA];
			float w2 = posLocks[tetra.idB] ? 0.0f : invMasses[tetra.idB];
			float w3 = posLocks[tetra.idC] ? 0.0f : invMasses[tetra.idC];
			float w4 = posLocks[tetra.idD] ? 0.0f : invMasses[tetra.idD];

			Eigen::Vector3f restCM;
			Eigen::Matrix3f A;


			Eigen::Vector3f x0[4] = { x1_0, x2_0, x3_0, x4_0 };
			float w[4] = { w1, w2, w3, w4 };
			Eigen::Vector3f corr[4];

			PBD::PositionBasedDynamics::initShapeMatchingRestInfo(x0, w, 4, restCM, A);

			restCMs[i] = btVector3(restCM.x(), restCM.y(), restCM.z());

			invRestMat[16 * i + 0] = A(0, 0); invRestMat[16 * i + 1] = A(0, 1); invRestMat[16 * i + 2] = A(0, 2);
			invRestMat[16 * i + 4] = A(1, 0); invRestMat[16 * i + 5] = A(1, 1); invRestMat[16 * i + 6] = A(1, 2);
			invRestMat[16 * i + 8] = A(2, 0); invRestMat[16 * i + 9] = A(2, 1); invRestMat[16 * i +10] = A(2, 2);
		}
	}