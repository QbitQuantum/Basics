// создать карту нормалей по карте высот
void DynamicReg::CreateMaps() {

	// создание карты высот
	for (int i(0); i < Const::regionCellSize + 3; i++) {
		for (int j(0); j < Const::regionCellSize + 3; j++) {
			NumXY<float> worldPosition(regionAdress.x * (float)Const::regionCellSize + i - 1.0f, regionAdress.y * (float)Const::regionCellSize + j - 1.0f);
			regionHeightMap[i][j] = Mediator::superFunct->HeightFunction(worldPosition);
		}
	}

	// создание карты нормалей
	for (int i(0); i < Const::regionCellSize + 1; i++) {
		for (int j(0); j < Const::regionCellSize + 1; j++) {
			float grad1 = regionHeightMap[i + 2][j + 1] - regionHeightMap[i][j + 1];
			float grad2 = regionHeightMap[i + 1][j + 2] - regionHeightMap[i + 1][j];
			XMVECTOR vector1 = { 1.0f, grad1, 0.0f };
			XMVECTOR vector2 = { 0.0f, grad2, 1.0f };
			XMVECTOR vectorNormal = -XMVector3Normalize(XMVector3Cross(vector1, vector2));
			XMFLOAT3 vectorNormalF;
			XMStoreFloat3(&vectorNormalF, vectorNormal);
			regionNormalMap[i][j] = vectorNormalF;
			regionTangentMap[i][j] = XMFLOAT3(1.0f, regionHeightMap[i + 2][j + 1] - regionHeightMap[i + 1][j + 1], 0.0f);

		}
	}

}