void bimWorld::MovingCamera::translation(double startx, double starty, double endx, double endy)
{
	auto manip = static_cast<PersonManipulator*>(m_host->_CameraManipulator()->getCameraManipulator());
	if (!manip)
		return;

	manip->translation(startx, starty, endx, endy, m_host->_CameraManipulator()->getCamera());

	m_host->_RenderingThreads()->updateSeveralTimes();
}