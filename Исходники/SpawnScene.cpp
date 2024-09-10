	static Entity createCell(Feuille& f, bool assignGridPos) {
		Entity e = theEntityManager.CreateEntityFromTemplate("spawn/cell");
		ADD_COMPONENT(e, HeriswapGrid);
	    ADD_COMPONENT(e, Twitch);

		TRANSFORM(e)->position = HeriswapGame::GridCoordsToPosition(f.X, f.Y, theHeriswapGridSystem.GridSize);
		TRANSFORM(e)->z = DL_Cell + Random::Float(0.f, 1.f) * 0.001f;
		RenderingComponent* rc = RENDERING(e);
		rc->show = true;

		TRANSFORM(e)->size = glm::vec2(0.f);
		ADSR(e)->idleValue = HeriswapGame::CellSize(theHeriswapGridSystem.GridSize, f.type).x * HeriswapGame::CellContentScale();
		HERISWAPGRID(e)->type = f.type;
		if (assignGridPos) {
			HERISWAPGRID(e)->i = f.X;
			HERISWAPGRID(e)->j = f.Y;
		}
		rc->texture = theRenderingSystem.loadTextureFile(HeriswapGame::cellTypeToTextureNameAndRotation(f.type, &TRANSFORM(e)->rotation));
		return e;
	}