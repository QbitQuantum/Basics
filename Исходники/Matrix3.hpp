void 
Matrix3<T>::Set( const AxisAngle<T> & axisAngle )
{
    Angle angle = axisAngle.GetAngle( );
    const Vector3<T> & axis = axisAngle.Axis( );
    const T cc = static_cast<T>( 1. - angle.Cos( ) );
    const T s = static_cast<T>( angle.Sin( ) );
    const T a00 = axis[0] * axis[0];
    const T a01 = axis[0] * axis[1];
    const T a02 = axis[0] * axis[2];
    const T a11 = axis[1] * axis[1];
    const T a12 = axis[1] * axis[2];
    const T a22 = axis[2] * axis[2];
    m_elements[0][0] = static_cast<T>( 1. - cc * (a11 + a22) );
    m_elements[1][0] = static_cast<T>( -s * axis[2] + cc * a01  );
    m_elements[2][0] = static_cast<T>(  s * axis[1] + cc * a02  );
    m_elements[0][1] = static_cast<T>(  s * axis[2] + cc * a01 );
    m_elements[1][1] = static_cast<T>( 1. - cc * (a00 + a22) );
    m_elements[2][1] = static_cast<T>( -s * axis[0] + cc * a12 );
    m_elements[0][2] = static_cast<T>( -s * axis[1] + cc * a02 );
    m_elements[1][2] = static_cast<T>(  s * axis[0] + cc * a12 );
    m_elements[2][2] = static_cast<T>( 1. - cc * (a00 + a11) );
}