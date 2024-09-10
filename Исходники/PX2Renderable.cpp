//----------------------------------------------------------------------------
void Renderable::GetVisibleSet (Culler& culler, bool)
{
	AdjustTransparent();

	const Camera *camera = culler.GetCamera();

	assertion(camera!=0, "camera must not be 0.");

	AVector cameraDir = camera->GetDVector();
	AVector diff = WorldBound.GetCenter() - camera->GetPosition();

	mEyeDistance = cameraDir.Dot(diff);

	culler.Insert(this);
}