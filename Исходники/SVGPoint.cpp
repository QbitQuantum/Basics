wxSVGPoint wxSVGPoint::MatrixTransform(const wxSVGMatrix& matrix) const
{
  wxSVGPoint res(m_x*matrix.GetA() + m_y*matrix.GetC() + matrix.GetE(),
	m_x*matrix.GetB() + m_y*matrix.GetD() + matrix.GetF());
  return res;
}