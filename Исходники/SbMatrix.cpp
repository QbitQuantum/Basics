void
SbMatrix::setTransform(const SbVec3f &translation,
		 const SbRotation &rotation,
		 const SbVec3f &scaleFactor,
		 const SbRotation &scaleOrientation,
		 const SbVec3f &center)
{
#define TRANSLATE(vec)		m.setTranslate(vec), multLeft(m)
#define ROTATE(rot)		rot.getValue(m), multLeft(m)
    SbMatrix m;

    makeIdentity();
    
    if (translation != SbVec3f(0,0,0))
	TRANSLATE(translation);

    if (center != SbVec3f(0,0,0))
	TRANSLATE(center);

    if (rotation != SbRotation(0,0,0,1))
	ROTATE(rotation);

    if (scaleFactor != SbVec3f(1,1,1)) {
	SbRotation so = scaleOrientation;
	if (so != SbRotation(0,0,0,1))
	    ROTATE(so);
	
	m.setScale(scaleFactor);
	multLeft(m);

	if (so != SbRotation(0,0,0,1)) {
	    so.invert();
	    ROTATE(so);
	}
    }

    if (center != SbVec3f(0,0,0))
	TRANSLATE(-center);

#undef TRANSLATE
#undef ROTATE
}