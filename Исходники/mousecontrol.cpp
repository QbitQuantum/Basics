float CMouseControl::MovePointerRel (float dx, float dy, int* dxRes, int* dyRes)
{
	OnDisplayChanged ();

	// Apply factors
	dx*= m_fDx;
	dy*= m_fDy;

	// Low-pass filter	
	dx= dx * (1.0f - m_actualMotionWeight) + m_dxant * m_actualMotionWeight;
	dy= dy * (1.0f - m_actualMotionWeight) + m_dyant * m_actualMotionWeight;
	m_dxant= dx; m_dyant= dy;

	// Acceleration
	float distance= (float) ::sqrt (dx * dx + dy * dy);

	unsigned int iAccelArray= (unsigned int) (distance + 0.5f);
	if (iAccelArray>= ACCEL_ARRAY_SIZE) iAccelArray= ACCEL_ARRAY_SIZE - 1;
	dx*= m_accelArray[iAccelArray];
	dy*= m_accelArray[iAccelArray];

	// Apply delta threshold
	if (-m_minDeltaThreshold < dx && dx < m_minDeltaThreshold) dx= 0.0f;
	if (-m_minDeltaThreshold < dy && dy < m_minDeltaThreshold) dy= 0.0f;
	
	int idx= (int) roundf(dx);
	int idy= (int) roundf(dy);
	int mouseX, mouseY;
	if (m_enabledRestrictedWorkingArea && !m_enabledWrapPointer) {
		GetPointerLocation (mouseX, mouseY);
		if (mouseX + idx< m_minScreenX) idx= m_minScreenX - mouseX;
		else if (mouseX + idx > m_maxScreenX) idx= m_maxScreenX - mouseX;
		if (mouseY + idy < m_minScreenY) idy= m_minScreenY - mouseY;
		else if (mouseY + idy > m_maxScreenY) idy= m_maxScreenY - mouseY;
	}
	
	if (m_enabledWrapPointer) {
		int minWrapX= 0;
		int maxWrapX= m_ScreenWidth;
		int minWrapY= 0;
		int maxWrapY= m_ScreenHeight;
				
		if (m_enabledRestrictedWorkingArea) {
			minWrapX= m_minScreenX;
			maxWrapX= m_maxScreenX;
			minWrapY= m_minScreenY;
			maxWrapY= m_maxScreenY;
		}

		GetPointerLocation(mouseX, mouseY);
		if (mouseX + idx < minWrapX) {
			idx -= mouseX - minWrapX;
			DoMovePointerAbs(maxWrapX, mouseY);
		}		
		if (mouseX + idx > maxWrapX) {
			idx -= maxWrapX - mouseX;
			DoMovePointerAbs(minWrapX, mouseY);
		}
		if (mouseY + idy < minWrapY) {
			idy -= mouseY - minWrapY;
			DoMovePointerAbs(mouseX, maxWrapY);
		}
		if (mouseY + idy > maxWrapY) {
			idy -= maxWrapY - mouseY;
			DoMovePointerAbs(mouseX, minWrapY);
		}
	}

	DoMovePointerRel (idx, idy);
	if (dxRes) *dxRes= idx;
	if (dyRes) *dyRes= idy;

	return (float) sqrt((double)(idx * idx + idy * idy));
}