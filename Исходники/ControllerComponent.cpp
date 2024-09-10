void ControllerComponent::MoveRight(GridMap * currMap)
{
	auto infoC = this->getParent()->getComponent<InformationComponent>();
	if (infoC)
	{
		infoC->setRotation(Vector3(0.f, 0.f, 0.f));

		float indexX = infoC->getPosition().x / (currMap->getMapWidth() * currMap->getTileSize()) * currMap->getMapWidth();
		float indexY = infoC->getPosition().y / (currMap->getMapHeight() * currMap->getTileSize()) * currMap->getMapHeight();
		int playerIndexX = (int)indexX;
		int playerIndexY = currMap->getMapHeight() - (int)indexY;

		if (((int)indexX + 1) < currMap->getMapWidth())
		{
			if (currMap->getGridMap()[playerIndexY][playerIndexX + 1]->getTileID() == Grid::TILE_FLOOR)
			{
				if (currMap->getGridMap()[playerIndexY][playerIndexX + 1]->getGridEntity() != NULL)
				{
					auto gridObject = dynamic_cast<EntityGridObject*>(currMap->getGridMap()[playerIndexY][playerIndexX + 1]->getGridEntity());
					if (gridObject)
					{
						if (currMap->PushObjects(playerIndexX, playerIndexY, GridMap::DIRECTION_RIGHT, gridObject->getObjectType(), this->getParent()))
						{
							//currMap->getGridMap()[playerIndexY][playerIndexX]->removeEntity();
							this->m_sMovement = MovementUpdate(
								playerIndexX,
								playerIndexY,
								GridMap::DIRECTION_RIGHT,
								currMap->getGridMap()[playerIndexY][playerIndexX + 1]->getGridPos(),
								true
								);
						}
					}
				}
				else
				{
					//currMap->getGridMap()[playerIndexY][playerIndexX]->removeEntity();
					this->m_sMovement = MovementUpdate(
						playerIndexX,
						playerIndexY,
						GridMap::DIRECTION_RIGHT,
						currMap->getGridMap()[playerIndexY][playerIndexX + 1]->getGridPos(),
						true
						);
				}
			}
		}
	}
	m_dMoveDelay = 0.0;
}