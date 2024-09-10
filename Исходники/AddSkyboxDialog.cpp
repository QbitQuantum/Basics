void AddSkyboxDialog::OnCreateButtonClicked()
{
	if(editorScene)
	{
		Entity* skyboxEntity = editorScene->skyboxSystem->AddSkybox();
        skyboxEntity->Retain();

		skyboxEntity->GetParent()->RemoveNode(skyboxEntity);
        editorScene->Exec(new EntityAddCommand(skyboxEntity, editorScene)); //To enable Ctrl+Z operation
        skyboxEntity->Release();
	}
}