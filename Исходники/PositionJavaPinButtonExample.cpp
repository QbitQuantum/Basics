void PositionJavaPinButtonExample::Project (const Eegeo::Space::LatLongAltitude& location, Eegeo::v3& screenPosition)
{
	//project a 3D Ecef location to the screen
	Eegeo::m44 finalMatrix;

	Eegeo::Camera::RenderCamera renderCamera(GetGlobeCameraController().GetRenderCamera());

	Eegeo::m44::Mul (finalMatrix,
	                 renderCamera.GetProjectionMatrix(),
	                 renderCamera.GetViewMatrix());

	Eegeo::v3 local = (location.ToECEF() - renderCamera.GetEcefLocation()).ToSingle();
	Eegeo::v4 inVector(local, 1.0f);

	// get clip space coords
	Eegeo::v4 outVector = Eegeo::v4::Mul(inVector, finalMatrix);

	// divide through by w to get normalized device space coords -- range [-1, 1]
	screenPosition.SetX((outVector.GetX()/outVector.GetW()));
	screenPosition.SetY((outVector.GetY()/outVector.GetW()));
	screenPosition.SetZ((outVector.GetZ()/outVector.GetW()));

	// transform from [-1, 1] to [0, 1]
	screenPosition.SetX((screenPosition.GetX() + 1.0f) * 0.5f);
	screenPosition.SetY(1.0f - ((screenPosition.GetY() + 1.0f) * 0.5f));

	float viewport[] = {0, 0, renderCamera.GetViewportWidth(), renderCamera.GetViewportHeight()};

	// transform from [0, 1] to screen coords.
	screenPosition.SetX((screenPosition.GetX()*(viewport[2]-viewport[0])) + viewport[0]);
	screenPosition.SetY((screenPosition.GetY()*(viewport[3]-viewport[1])) + viewport[1]);
}