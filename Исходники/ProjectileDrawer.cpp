void CProjectileDrawer::DrawFlyingPieces(int modelType, int numFlyingPieces, int* drawnPieces)
{
	static FlyingPieceContainer* containers[MODELTYPE_OTHER] = {
		&ph->flyingPieces3DO,
		&ph->flyingPiecesS3O,
		NULL
	};

	FlyingPieceContainer* container = containers[modelType];
	FlyingPieceContainer::render_iterator fpi;

	if (container != NULL) {
		CVertexArray* va = GetVertexArray();

		va->Initialize();
		va->EnlargeArrays(numFlyingPieces * 4, 0, VA_SIZE_TN);

		size_t lastTex = -1;
		size_t lastTeam = -1;

		for (fpi = container->render_begin(); fpi != container->render_end(); ++fpi) {
			(*fpi)->Draw(modelType, &lastTeam, &lastTex, va);
		}

		(*drawnPieces) += (va->drawIndex() / 32);
		va->DrawArrayTN(GL_QUADS);
	}
}