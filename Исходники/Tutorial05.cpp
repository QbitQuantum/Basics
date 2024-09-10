/////////////////////////////////////////////////////////////////
// JPE: Cargar Vertices
/////////////////////////////////////////////////////////////////
void LoadVertices(SimpleVertex** verticesDest, WORD** indicesDest, int* cantVertices, int* cantIndices )
{
	SimpleVertex* vertices = new SimpleVertex[24]();
	*(verticesDest) = vertices;
	*(cantVertices) = 24;

	// CARA ARRIBA
	vertices[0] = { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) }; // 0 
	vertices[1] = { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) }; // 1
	vertices[2] = { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) }; // 2	
	vertices[3] = { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) }; // 3	
	// CARA ABAJO
	vertices[4] = { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) }; // 4
	vertices[5] = { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) }; // 5
	vertices[6] = { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) }; // 6
	vertices[7] = { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) }; // 7
	// CARA FRENTE
	vertices[8] = { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) }; // 0
	vertices[9] = { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) }; // 1
	vertices[10] = { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) }; // 5
	vertices[11] = { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) }; // 4
	// CARA DORSO
	vertices[12] = { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) }; // 2		
	vertices[13] = { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) }; // 3	
	vertices[14] = { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) }; // 7	
	vertices[15] = { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) }; // 6	
	// CARA DERECHA
	vertices[16] = { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) }; // 1	
	vertices[17] = { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) }; // 2		
	vertices[18] = { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) }; // 6	
	vertices[19] = { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) }; // 5	
	// CARA IZQUIERDA
	vertices[20] = { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) }; // 3	
	vertices[21] = { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) }; // 0	
	vertices[22] = { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) }; // 4	
	vertices[23] = { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) }; // 7	

	// Create index buffer
	int cantInd = 36;
	*(cantIndices) = cantInd;
	
	const WORD indices[] =
	{
		// ARRIBA
		3,2,1,
		3,1,0,
		// ABAJO
		4,5,6,
		4,6,7,
		// FRENTE
		8,9,10,
		8,10,11,
		// DORSO
		12,13,14,
		12,14,15,
		// DERECHA
		16,17,18,
		16,18,19,
		// IZQUIERDA
		20,21,22,
		20,22,23,
	};

	*(indicesDest) = new WORD[cantInd];
	memcpy(*(indicesDest), (void*)indices, cantInd * sizeof(WORD));

	//JPE: Calculo de normales, tangentes y binormales.
	for (int cara = 0; cara < 6; cara++)
	{
		for (int trig = 0; trig < 2; trig++)
		{
			int idx0 = cara * 6 + trig * 3;
			int idx1 = idx0 + 1, idx2 = idx0 + 2;

			SimpleVertex& vt0 = vertices[indices[idx0]];
			SimpleVertex& vt1 = vertices[indices[idx1]];
			SimpleVertex& vt2 = vertices[indices[idx2]];

			XMFLOAT3 p0 = vt0.Pos;
			XMFLOAT3 p1 = vt1.Pos;
			XMFLOAT3 p2 = vt2.Pos;

			XMFLOAT2 t0 = vt0.texture;
			XMFLOAT2 t1 = vt1.texture;
			XMFLOAT2 t2 = vt2.texture;

			XMFLOAT3 Edge1 = XMFLOAT3(p1.x - p0.x, p1.y - p0.y, p1.z - p0.z);
			XMFLOAT3 Edge2 = XMFLOAT3(p2.x - p0.x, p2.y - p0.y, p2.z - p0.z);

			float DeltaU1 = t1.x - t0.x;
			float DeltaV1 = t1.y - t0.y;
			float DeltaU2 = t2.x - t0.x;
			float DeltaV2 = t2.y - t0.y;

			float f = 1.0f / (DeltaU1 * DeltaV2 - DeltaU2 * DeltaV1);

			XMFLOAT3 Tangent, Bitangent;

			Tangent.x = f * (DeltaV2 * Edge1.x - DeltaV1 * Edge2.x);
			Tangent.y = f * (DeltaV2 * Edge1.y - DeltaV1 * Edge2.y);
			Tangent.z = f * (DeltaV2 * Edge1.z - DeltaV1 * Edge2.z);

			Bitangent.x = f * (-DeltaU2 * Edge1.x - DeltaU1 * Edge2.x);
			Bitangent.y = f * (-DeltaU2 * Edge1.y - DeltaU1 * Edge2.y);
			Bitangent.z = f * (-DeltaU2 * Edge1.z - DeltaU1 * Edge2.z);

			Normalize(&Tangent);
			Normalize(&Bitangent);

			vt0.Tangent = Tangent;
			vt1.Tangent = Tangent;
			vt2.Tangent = Tangent;

			vt0.Binormal = Bitangent;
			vt1.Binormal = Bitangent;
			vt2.Binormal = Bitangent;

		}
	}

}