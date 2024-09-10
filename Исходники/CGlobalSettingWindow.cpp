void CGlobalSettingWindow::UpdateShowing()
{
	EditorScene* scene = EditorScene::getInstance();

	char text[256];
	ILightNode* light = scene->mDirectionalLightNode;

	sprintf_s(text, "%.5f", scene->mSceneManager->getAmbient().x);
	SetWindowTextA(mAmbientTextField, text);

	sprintf_s(text, "%.5f", light->getDiffuse().x);
	SetWindowTextA(mDiffuseTextField, text);

	sprintf_s(text, "%.5f", light->getSpecular().x);
	SetWindowTextA(mSpecularTextField, text);
}