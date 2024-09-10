void EditorToolBar::onLeftMouseDown()
{
	ASSERT(world!=0, "world was null!  Call setWorld first!");

	if(g_GUI.mouseOverSomeWidget) return;

	// Get a position on the ground beneath the cursor
	float e = selected ? selected->getPos().y : 0.0f;
	const vec3 groundPos = getGroundPickPos(e);

	// Grab the pool of objects we are working from
	ActorSet &objects = world->getObjects();

	// Get the id of the object under the mouse cursor
	OBJECT_ID id = objects.getClosest<Actor>(groundPos, 2.0f);

	// Process the action depending on the current tool
	switch(toolBarTools->getTool())
	{
	case ToolBarForEditorTools::EDITOR_SELECT_TOOL:
		if(objects.isMember(id))
		{
			Actor * p = &objects.get(id);
			showActorPane(p);
		}
		else
		{
			hideActorPane();
		}
		break;

	case ToolBarForEditorTools::EDITOR_MOVE_TOOL:
		{
			if(selected)
			{
				// Hold the right mouse button to slide objects along the y-axis
				if(g_Input.MouseRight)
				{
					vec3 delta = groundPos - selected->getPos();
					delta.y=0;
					float dist = delta.getMagnitude()*0.3f;

					// Place the object on this spot
					selected->Place(vec3(selected->getPos().x, dist, selected->getPos().z));
				}
				else
				{
					selected->Place(groundPos);
				}
			}
		}
		break;

	case ToolBarForEditorTools::EDITOR_ROTATE_TOOL:
		{
			if(selected)
			{
				const vec3 delta = vec3(selected->getPos().x-groundPos.x, 0, selected->getPos().z-groundPos.z);
				const vec3 zAxis = delta.getNormal();
				const vec3 yAxis = vec3(0,1,0);
				const vec3 xAxis = yAxis.cross(zAxis).getNormal();

				mat4 orientation = selected->getOrientation();
				orientation.setAxisZ(zAxis);
				orientation.setAxisY(yAxis);
				orientation.setAxisX(xAxis);
				orientation.setPos(vec3(0,0,0));
				selected->setOrientation(orientation);
			}
		}
		break;

	case ToolBarForEditorTools::EDITOR_ROTATE_X_TOOL:
		{
			if(selected)
			{
				vec3 delta = groundPos - selected->getPos();
				float angle = atan2f(delta.x, delta.y) * 0.1f;

				mat4 rot;
				rot.rotateX(angle);

		                mat4 orientation = selected->getOrientation();

				orientation *= rot;

				selected->setOrientation(orientation);
			}
		}
		break;

	case ToolBarForEditorTools::EDITOR_ROTATE_Z_TOOL:
		{
			if(selected)
			{
				vec3 delta = groundPos - selected->getPos();
				float angle = atan2f(delta.x, delta.y) * 0.1f;

				mat4 rot;
				rot.rotateZ(angle);

		                mat4 orientation = selected->getOrientation();

				orientation *= rot;

				selected->setOrientation(orientation);
			}
		}
		break;

	case ToolBarForEditorTools::EDITOR_CREATE_TOOL:
		if(!leftClickDebounce)
		{
			leftClickDebounce=true;

			// Create objects from a palette of available types
			string nextObject = getNextObject();

            // Gets the objects for the object palette
			string editorDataFile = pathAppend("data/objects/", nextObject);

			PropertyBag ThisObjBag;
            ThisObjBag.loadFromFile(editorDataFile);

			string rtti;
			ThisObjBag.get("type", rtti);

			// Create the object inside the game world
			OBJECT_ID id = objects.create(rtti, world);
			if(id != INVALID_ID)
			{
				Actor &object = objects.get(id);
				object.load(ThisObjBag);
				object.editorDataFile = editorDataFile;

				// Do not affect object y with the move command
				vec3 groundPos = getGroundPickPos(0.0f);

				// Place the object on this spot
				object.Place(groundPos);

				// Select the new object
				selected = &object;
			}
		}
		break;

	case ToolBarForEditorTools::EDITOR_DESTROY_TOOL:
		if(objects.isMember(id))
		{
			objects.removeObjectNow(id);
			hideActorPane();
		}
		break;

	case ToolBarForEditorTools::EDITOR_TILE_PENCIL_TOOL:
		{
			// get a reference to the map
			Map &map =  world->getMap();

			// Get the position on the ground plane that was clicked
			vec3 groundPos = getGroundPickPos(0.0f);

			if(map.onATile(groundPos.x, groundPos.z))
			{
				// get the tile that was picked
				Tile &tile = map.getTile(groundPos.x, groundPos.z);

#if 1
                tile.create(map.tileX(groundPos.x),
							map.tileZ(groundPos.z),
							tileEditor_type,
							tileEditor_properties,
							tileEditor_height,
							tileEditor_floorTextureFile,
							tileEditor_wallTextureFile,
							map);
#else
                tile.setMaterials(tileEditor_wallTextureFile,
                                  tileEditor_floorTextureFile,
                                  map);
#endif

				// Rebuild the map display list
				map.reaquire();

				g_SoundSystem.play("data/sound/click.wav");
			}
		}
		break;

	case ToolBarForEditorTools::EDITOR_TILE_BLOCK_TOOL:
		{
			// Drag entered
			if(!drag)
			{
				drag = true;

				g_SoundSystem.play("data/sound/click.wav");

				mouseDownPos = getGroundPickPos(0.0f);
			}
		}
		break;
	};
}