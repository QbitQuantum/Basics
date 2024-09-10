void CNodeInfoWindow::OnClickUpdateTransformButton()
{
	EditorScene* scene = EditorScene::getInstance();
	SNodeInfo* info = scene->GetSelectedNodeInfo();
	if (!info)
		return;

	f32 position[3];
	f32 rotation[3];
	f32 scaling[3];

	char text[256];
	for (u32 i = 0; i < 3; i++)
	{
		GetWindowTextA(mPosTextFields[i], text, 256);
		int err = sscanf_s(text, "%f", &position[i]);
		if (err < 1 || err == EOF)
		{
			MessageBoxA(mParentHwnd, "cannot convert position value", "Error", NULL);
			return;
		}
	}

	for (u32 i = 0; i < 3; i++)
	{
		GetWindowTextA(mRotTextFields[i], text, 256);
		int err = sscanf_s(text, "%f", &rotation[i]);
		if (err < 1 || err == EOF)
		{
			MessageBoxA(mParentHwnd, "cannot convert rotation value", "Error", NULL);
			return;
		}
	}

	for (u32 i = 0; i < 3; i++)
	{
		GetWindowTextA(mScaleTextFields[i], text, 256);
		int err = sscanf_s(text, "%f", &scaling[i]);
		if (err < 1 || err == EOF)
		{
			MessageBoxA(mParentHwnd, "cannot convert scale value", "Error", NULL);
			return;
		}
	}

	info->Position.x = position[0];
	info->Position.y = position[1];
	info->Position.z = position[2];

	info->Rotation.x = rotation[0] * XM_PI / 180.0f;
	info->Rotation.y = rotation[1] * XM_PI / 180.0f;
	info->Rotation.z = rotation[2] * XM_PI / 180.0f;

	info->Scaling.x = scaling[0];
	info->Scaling.y = scaling[1];
	info->Scaling.z = scaling[2];

	scene->UpdateNodeInfo(info);
	UpdateShowing(info);
}