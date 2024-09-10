void Inventory::touchMove(Vector2 position)
{
	if (iconTouched != NULL)
	{
		if (!menuRec.contains(position.x, position.y)){
			if (iconTouched->visible == true || iconTouched->preview == false){
				iconTouched->visible = false;

				

				// add ghost
				Vector2 fieldCoords = playField->screenToFieldCoordinates(position);
				
	/*			iconTouched->preview =
					iconTouched->item->addPreviewToPlayField
					(playField
					, playField->getScene()
					, fieldCoords);*/
				if (iconTouched->item->canPlace(fieldCoords, playField)){
					Item::ClearLists();
					iconTouched->preview = true;
					iconTouched->item->SetStatus(Item::PREVIEW);
					iconTouched->item->SetPosition(fieldCoords.x, fieldCoords.y, playField);
					iconTouched->item->AddToEntityList();
					Item::LoadAssets();
					Item::BuildAndFinish(playField->getScene());
					Item::ClearLists();
				}
				
				

				// scoot menu back to docked
				Vector2 menuPos(menuRec.x, menuRec.y);
				if (menuPos != dockPosition){
					float dockLength = (menuPos - dockPosition).length();
					slideTo(dockPosition, dockLength / dockToOutLength * SLIDE_TIME);				
				}

			}
			else{
				

				Vector2 fieldCoords = playField->screenToFieldCoordinates(position);
				// check to see if fieldCoords is within character's radius
				float length = fieldCoords.distance(belongsTo->GetPosition());
				if (length < belongsTo->GetRadius())
					belongsTo->ghostEquipItem(iconTouched->item);
				else
					//iconTouched->ghost =
						iconTouched->item->SetPosition(fieldCoords.x, fieldCoords.y, playField);
			}
		}
		else{
			iconTouched->rec.x = position.x + iconTouched->offset.x;
			iconTouched->rec.y = position.y + iconTouched->offset.y;

			if (iconTouched->visible == false){
				iconTouched->visible = true;
				// remove ghost
		//		iconTouched->item->removeFromPlayField(playField->getScene());
				iconTouched->item->SetStatus(Item::ABSTRACT);
				
				iconTouched->preview = false;		

				// scoot menu back to docked
				Vector2 menuPos(menuRec.x, menuRec.y);
				if (menuPos != outPosition){
					float outLength = (menuPos - outPosition).length();
					slideTo(outPosition, outLength / dockToOutLength * SLIDE_TIME);
				}
			}
			else{
			//	iconTouched->rec.x = position.x + iconTouched->offset.x;
			//	iconTouched->rec.y = position.y + iconTouched->offset.y;
			}
		}
		
		

		
	}
	else{
		menuRec.x = position.x + touchOffset.x;
		menuRec.y = position.y + touchOffset.y;

		// adjust it to not go out of bounds
		if (menuRec.x < outPosition.x)
			menuRec.x = outPosition.x;
		if (menuRec.y > outPosition.y)
			menuRec.y = outPosition.y;
		if (menuRec.x > dockPosition.x)
			menuRec.x = dockPosition.x;
		if (menuRec.y < dockPosition.y)
			menuRec.y = dockPosition.y;

		setIconPositions();
	}

}