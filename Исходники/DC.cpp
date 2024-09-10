void CDC::MapMode(const CSize& rDeviceUnits, const CSize& rLogicalUnits)
{
	MapMode(MM_ANISOTROPIC);
	SetWindowExtEx(m_hDC,   rLogicalUnits.cx, rLogicalUnits.cy, NULL);
	SetViewportExtEx(m_hDC, rDeviceUnits.cx,  rDeviceUnits.cy, NULL);
}