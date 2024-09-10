void Particles::setPosition(Vec3f pos)
{
	Matrix mOrig = particleTrans->getMatrix();
	Matrix mNew = mOrig;
	mNew.setTranslate(pos);
	beginEditCP(particleTrans, Transform::MatrixFieldMask);
		particleTrans->setMatrix(mNew);
	endEditCP(particleTrans, Transform::MatrixFieldMask);

	mOrig.invert();
//	mNew.multLeft(mOrig);
	mNew.mult(mOrig);
	beginEditCP(particleTransNode);
		DynamicVolume &v = particleTransNode->getVolume(false);
		v.transform(mNew);
	endEditCP(particleTransNode);

} // setPosition