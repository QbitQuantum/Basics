//----------------------------------------------------------------------------
void GamePlayApp::ZoomCamera (Camera *cam, float zoom)
{
	if (!cam)
		return;

	Vector3f position = cam->GetPosition();
	AVector dir = cam->GetDVector();
	dir.Normalize();

	position += dir*zoom;
	cam->SetPosition(position);
}