void DirectLight::apply()
{
	const Matrix4x4&	wt		= cachedWorldTransform();
	Vector3				wrotz	= Vector3( wt(0,2),wt(1,2),wt(2,2) );

	float wrotzlen = wrotz.length();
	if ( wrotzlen > Float::MIN_VALUE )
	{
		wrotz *= 1.f / wrotzlen;
		float intens = intensity();

		gd::LightState ls;
		GdUtil::setLightState( ls,
			gd::LightState::LIGHT_DIRECT,
			diffuseColor()*intens, specularColor()*intens, ambientColor()*intens,
			wt.translation(), wrotz.normalize(),
			MAX_RANGE, 1.f, 0.f, 0.f,
			1.f, MAX_CONE_ANGLE, MAX_CONE_ANGLE );

		gd::GraphicsDevice*	dev = Context::device();
		dev->addLight( ls );
	}
}