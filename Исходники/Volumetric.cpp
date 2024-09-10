/*! @brief Recalculates inertia tensor of a body after translation away from (default) or towards its centroid.
 *
 * @param I inertia tensor in the original coordinates; it is assumed to be upper-triangular (elements below the diagonal are ignored).
 * @param m mass of the body; if positive, translation is away from the centroid; if negative, towards centroid.
 * @param off offset of the new origin from the original origin
 * @return inertia tensor in the new coordinate system; the matrix is symmetric.
 */
Matrix3r woo::Volumetric::inertiaTensorTranslate(const Matrix3r& I, const Real m, const Vector3r& off){
	// short eigen implementation; check it gives the same result as above
	return I+m*(off.dot(off)*Matrix3r::Identity()-off*off.transpose());
}