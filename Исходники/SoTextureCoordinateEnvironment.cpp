const SbVec4f &
SoTextureCoordinateEnvironment::valueCallback(void *action,
    const SbVec3f &point,
    const SbVec3f &normal)
//
////////////////////////////////////////////////////////////////////////
{
    SoAction *a = (SoAction *)action;

    //
    // See the glTexGen() man page for the math here.
    //

    // First, map normal and point into eye space:
    const SbMatrix &mm = SoModelMatrixElement::get(a->getState());
    const SbMatrix &vm = SoViewingMatrixElement::get(a->getState());

    // Compute the matrix that transforms normals from object-space to
    // eye-space; use the inverse transpose to scale correctly
    SbVec3f normalE;
    SbMatrix nm = (vm * mm).inverse().transpose();
    nm.multDirMatrix(normal, normalE);

    SbVec3f pointE;
    mm.multVecMatrix(point, pointE);  // Gives world-space point
    vm.multVecMatrix(pointE, pointE); // ... to eye-space.

    // Get the normalized vector from the eye (which is conveniently
    // at 0,0,0 in eye space) to the point.
    pointE.normalize();

    // Now, figure out reflection vector, from formula:
    // R = P - 2 (N . N) pointE
    SbVec3f reflection = pointE - 2.0 * normalE.dot(normalE) * pointE;

    // Finally, compute s/t coordinates...
    reflection[2] += 1.0;
    float magnitude = reflection.length();

    // This is static so we can return a reference to it
    static SbVec4f result;
    result.setValue(reflection[0] / magnitude + 0.5,
		    reflection[1] / magnitude + 0.5,
		    0.0, 1.0);

    return result;
}