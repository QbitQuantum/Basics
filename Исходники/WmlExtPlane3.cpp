Real ExtPlane3<Real>::IntersectRay( const Wml::Vector3<Real> & vOrigin,
								    const Wml::Vector3<Real> & vDirection ) const
{
	Wml::Vector3<Real> vN(this->Normal);
	Real fDenom = vDirection.Dot(vN);
	if ( fDenom == 0 )
		return std::numeric_limits<Real>::max();
	return (this->Constant - vOrigin.Dot(vN)) / fDenom; 
}