template <typename T> U32 TVector4<T>::GetBGRAU32( void ) const
{	U32 r = U32(GetX()*T(255.0f));
	U32 g = U32(GetY()*T(255.0f));
	U32 b = U32(GetZ()*T(255.0f));
	U32 a = U32(GetW()*T(255.0f));
	
	return U32( (b<<24)|(g<<16)|(r<<8)|a );
}