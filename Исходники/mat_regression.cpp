//---------------------------------------------------------
const SG_Char * CSG_Regression::asString(void)
{
	static CSG_String	s;

	s.Printf(
		SG_T("N = %d\n")
		SG_T("  Min. = %.6f  Max. = %.6f\n  Arithmetic Mean = %.6f\n  Variance = %.6f\n  Standard Deviation = %.6f\n")
		SG_T("  Min. = %.6f  Max. = %.6f\n  Arithmetic Mean = %.6f\n  Variance = %.6f\n  Standard Deviation = %.6f\n")
		SG_T("Linear Regression:\n  Y = %.6f * X %+.6f\n  (r=%.4f, r\xc2\xb2=%.4f)"),
		m_nValues,
		m_xMin, m_xMax, m_xMean, m_xVar, sqrt(m_xVar),
		m_yMin, m_yMax, m_yMean, m_yVar, sqrt(m_yVar),
		m_RCoeff, m_RConst, m_R, m_R*m_R
	);

	return( s );
}