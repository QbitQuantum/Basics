/* ------------------------------------------------------- */
Transformation Transformation::inverse() const
{
	if ( m_isIdentity )
    {
        return *this;
    }

	Transformation result;
    if ( m_isRSMatrix )
    {
		result.setRotation(m_matrix.transpose());
        if ( m_isUniformScale )
        {		
			float invScale = 1.0f / m_scale[0];
			result.setUniformScale(invScale);
        }
        else
        {
			result.setScale(Vector3(1.0f/m_scale[0], 1.0f/m_scale[1], 1.0f/m_scale[2]));

            Matrix3 rs = m_matrix.timesDiagonal(m_scale);
            result.m_matrix = rs.inverse();
        }
		Vector3 translation = m_translate*m_matrix;
		translation[0] *= result.m_scale[0];
		translation[1] *= result.m_scale[1];
		translation[2] *= result.m_scale[2];
		result.setTranslation(-translation);
    }
    else
    {
        result.setMatrix(m_matrix.inverse());
		result.setTranslation(-(result.m_matrix*m_translate));
    }
	return result;
}