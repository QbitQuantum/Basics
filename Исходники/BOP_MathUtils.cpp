/**
 * Returns if a quad (coplanar) is convex.
 * @return true if the quad is convex, false otherwise
 */
bool BOP_convex(const MT_Point3& p1, const MT_Point3& p2, const MT_Point3& p3, const MT_Point3& p4)
{
	MT_Vector3 v1 = p3 - p1;
	MT_Vector3 v2 = p4 - p2;
	MT_Vector3 quadPlane = v1.cross(v2);
	// plane1 is the perpendicular plane that contains the quad diagonal (p2,p4)
	MT_Plane3 plane1(quadPlane.cross(v2),p2);
	// if p1 and p3 are classified in the same region, the quad is not convex 
	if (BOP_classify(p1,plane1) == BOP_classify(p3,plane1)) return false;
	else {
		// Test the other quad diagonal (p1,p3) and perpendicular plane
		MT_Plane3 plane2(quadPlane.cross(v1),p1);
		// if p2 and p4 are classified in the same region, the quad is not convex
		return (BOP_classify(p2,plane2) != BOP_classify(p4,plane2));
	}
}