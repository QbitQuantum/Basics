//[-------------------------------------------------------]
//[ Private virtual PLScene::SNMTransformGizmo functions  ]
//[-------------------------------------------------------]
void SNMTransformGizmoRotationController::UpdateSelection(Renderer &cRenderer, const VisNode &cVisNode)
{
	// Get the frontend instance
	Frontend &cFrontend = static_cast<FrontendApplication*>(CoreApplication::GetApplication())->GetFrontend();

	// Check whether or not the mouse is currently over the frontend
	if (cFrontend.IsMouseOver()) {
		// Get current mouse cursor position inside the widget
		const int nMousePosX = cFrontend.GetMousePositionX();
		const int nMousePosY = cFrontend.GetMousePositionY();

		// Calculate the clip space to object space matrix
		Matrix4x4 mClipSpaceToObjectSpace = m_mObjectSpaceToClipSpace;
		mClipSpaceToObjectSpace.Invert();

		// Check where the mouse is over
		// Get the ray starting from the camera position in direction of the mouse position
		Vector3 v2DPos(static_cast<float>(nMousePosX), static_cast<float>(nMousePosY), 0.0001f);
		Vector3 vCamPos = v2DPos.To3DCoordinate(mClipSpaceToObjectSpace, cRenderer.GetViewport());
		v2DPos.z = 0.9999f;
		Vector3 vEndPos = v2DPos.To3DCoordinate(mClipSpaceToObjectSpace, cRenderer.GetViewport());

		// Determine the current selected axis by using a picking ray
		Ray cRay;
		cRay.Set(vCamPos, vEndPos);
		m_nSelected = DetermineSelected(cRay);
	} else {
		m_nSelected = 0;
	}
}