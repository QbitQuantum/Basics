int grinliz::IntersectRayAllAABB(	const Vector3F& origin, const Vector3F& dir,
                                    const Rectangle3F& aabb,
                                    int* inTest,
                                    Vector3F* inIntersect,
                                    int *outTest,
                                    Vector3F* outIntersect )
{
    // Could be more efficient, but looking for simplicity as I write this.
    float t;

    // First check if we hit the box at all, and that establishes in test.
    *inTest = IntersectRayAABB( origin, dir, aabb, inIntersect, &t );
    if ( *inTest == grinliz::REJECT ) {
        *outTest = grinliz::REJECT;
        return grinliz::REJECT;
    }

    // Could get fancy and intersect from the inside. But that's hard, so I'll run
    // the ray out and shoot it backwards.
    float deltaLen = aabb.SizeX() + aabb.SizeY() + aabb.SizeZ();

    Vector3F dirNormal = dir;
    dirNormal.Normalize();
    Vector3F invOrigin = origin + dir*deltaLen;
    Vector3F invDir = -dirNormal;

    *outTest = IntersectRayAABB( invOrigin, invDir, aabb, outIntersect, &t );

    GLASSERT( *outTest != grinliz::INSIDE );	// bad algorith.
    if ( *outTest == grinliz::REJECT ) {
        // some strange floating point thing. Hit a corner. Reject everything.
        *inTest = grinliz::REJECT;
        return grinliz::REJECT;
    }
    return grinliz::INTERSECT;
}