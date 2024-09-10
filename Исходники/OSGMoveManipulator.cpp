void  MoveManipulator::doMovement(TransformPtr t,
								  Int32 coord,
								  Real32 value,
								  const Vec3f		&translation,
								  const Quaternion	&rotation,
								  const Vec3f		&scaleFactor,
								  const Quaternion	&scaleOrientation )
{
	Vec3f trans(0.0f, 0.0f, 0.0f);
	trans[coord] = value;

	Matrix ma, mb, mc, md, me;
	
	ma.setTranslate( -translation        );
	mb.setRotate   (  rotation.inverse() );
	mc.setTransform(  trans              );
	md.setRotate   (  rotation           );
	me.setTranslate(  translation        );
	beginEditCP(t, Transform::MatrixFieldMask);
	{
		t->editMatrix().multLeft(ma);
		t->editMatrix().multLeft(mb);
		t->editMatrix().multLeft(mc);
		t->editMatrix().multLeft(md);
		t->editMatrix().multLeft(me);
	}	
	endEditCP(t, Transform::MatrixFieldMask);
}