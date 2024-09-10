// Read normalized values
Vector ADXL345::readNormalize(void)
{
    readRaw();
    // (4 mg/LSB scale factor in Full Res) * Earth gravity
    n.XAxis = r.XAxis * 0.004 * 9.80665f;
    n.YAxis = r.YAxis * 0.004 * 9.80665f;
    n.ZAxis = r.ZAxis * 0.004 * 9.80665f;
    return n;
}