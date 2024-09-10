void QSceneGraphTreeView::ShowSceneGraphMenu(const QModelIndex &index, const QPoint &point)
{
    if(!index.isValid())
    {
        return;
    }
    
    QMenu menu;
    
	// For "custom" Particles Editor nodes the "generic" ones aren't needed".
    if (sceneGraphModel->GetParticlesEditorSceneModelHelper().NeedDisplaySceneEditorPopupMenuItems(index))
    {
		SceneData *activeScene = SceneDataManager::Instance()->SceneGetActive();
		LandscapesController *landsacpesController = activeScene->GetLandscapesController();

		SceneEditorScreenMain *screen = static_cast<SceneEditorScreenMain *>(UIScreenManager::Instance()->GetScreen(SCREEN_MAIN_OLD));
		EditorBodyControl *c = screen->FindCurrentBody()->bodyControl;

		bool canChangeScene = !landsacpesController->EditorLandscapeIsActive() && !c->LandscapeEditorActive();
		if(!canChangeScene)
			return;



		AddActionToMenu(&menu, QString("Look at Object"), new CommandLockAtObject());
		AddActionToMenu(&menu, QString("Remove Object"), new CommandRemoveSceneNode());
	
		AddActionToMenu(&menu, QString("Debug Flags"), new CommandDebugFlags());
    
		Entity *node = static_cast<Entity *>(sceneGraphModel->ItemData(index));
		if (node)
		{
            SceneData *activeScene = SceneDataManager::Instance()->SceneGetActive();
            if(node->GetParent() == activeScene->GetScene())
            {
                KeyedArchive *properties = node->GetCustomProperties();
                if (properties && properties->IsKeyExists(String(ResourceEditor::EDITOR_REFERENCE_TO_OWNER)))
                {
                    String filePathname = properties->GetString(String(ResourceEditor::EDITOR_REFERENCE_TO_OWNER));

                    AddActionToMenu(&menu, QString("Remove Root Nodes"), new CommandRemoveRootNodes());
				}
			}
			FilePath filePathForSaveAs(activeScene->GetScenePathname());
			AddActionToMenu(&menu, QString("Save Scene As"), new CommandSaveSpecifiedScene(node, filePathForSaveAs));
		}
	}
	
	// For "custom" Particles Editor nodes the "generic" ones aren't needed".
    // We might need more menu items/actions for Particles Editor.
    sceneGraphModel->GetParticlesEditorSceneModelHelper().AddPopupMenuItems(menu, index);

    connect(&menu, SIGNAL(triggered(QAction *)), this, SLOT(SceneGraphMenuTriggered(QAction *)));
    menu.exec(point);
}