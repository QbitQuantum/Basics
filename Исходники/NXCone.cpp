 Cone::Cone(const float fLongAxis, const float fShortAxis, const float fHeight, const NX::vector<float, 3> &T, const NX::Matrix<float, 3, 3> &R):m_vCenter(0.0f, 0.0f, 0.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vLongAxis(1.0f, 0.0f, 0.0f), m_vShortAxis(0.0f, 0.0f, 1.0f){
     m_fLongAxis   = fLongAxis;
     m_fShortAxis  = fShortAxis;
     m_fHeight     = fHeight;
     Transform(T, R);
 }