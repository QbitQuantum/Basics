// Read normalized values
Vector L3G4200D::readNormalize()
{
    readRaw();

    if (useCalibrate)
    {
	n.XAxis = (r.XAxis - d.XAxis) * dpsPerDigit;
	n.YAxis = (r.YAxis - d.YAxis) * dpsPerDigit;
	n.ZAxis = (r.ZAxis - d.ZAxis) * dpsPerDigit;
    } else
    {
	n.XAxis = r.XAxis * dpsPerDigit;
	n.YAxis = r.YAxis * dpsPerDigit;
	n.ZAxis = r.ZAxis * dpsPerDigit;
    }

    if (actualThreshold > 0)
    {
	if (abs(n.XAxis) < t.XAxis) n.XAxis = 0;
	if (abs(n.YAxis) < t.YAxis) n.YAxis = 0;
	if (abs(n.ZAxis) < t.ZAxis) n.ZAxis = 0;
    }

    return n;
}