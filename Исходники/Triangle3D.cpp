toxi::geom::Vec3D toxi::geom::Triangle3D::closestPointOnSurface( Vec3D & p )
{
    Vec3D ab = b.sub( a );
    Vec3D ac = c.sub( a );
    Vec3D bc = c.sub( b );

    Vec3D pa = p.sub( a );
    Vec3D pb = p.sub( b );
    Vec3D pc = p.sub( c );

    Vec3D ap = a.sub( p );
    Vec3D bp = b.sub( p );
    Vec3D cp = c.sub( p );

    // Compute parametric position s for projection P' of P on AB,
    // P' = A + s*AB, s = snom/(snom+sdenom)
    float snom = pa.dot( ab );

    // Compute parametric position t for projection P' of P on AC,
    // P' = A + t*AC, s = tnom/(tnom+tdenom)
    float tnom = pa.dot( ac );

    if ( snom <= 0.0f && tnom <= 0.0f ) {
        return a; // Vertex region early out
    }

    float sdenom = pb.dot( a.sub( b ) );
    float tdenom = pc.dot( a.sub( c ) );

    // Compute parametric position u for projection P' of P on BC,
    // P' = B + u*BC, u = unom/(unom+udenom)
    float unom = pb.dot( bc );
    float udenom = pc.dot( b.sub( c ) );

    if ( sdenom <= 0.0f && unom <= 0.0f ) {
        return b; // Vertex region early out
    }
    if ( tdenom <= 0.0f && udenom <= 0.0f ) {
        return c; // Vertex region early out
    }

    // P is outside (or on) AB if the triple scalar product [N PA PB] <= 0
    Vec3D n = ab.cross( ac );
    float vc = n.dot( ap.crossSelf( bp ) );

    // If P outside AB and within feature region of AB,
    // return projection of P onto AB
    if ( vc <= 0.0f && snom >= 0.0f && sdenom >= 0.0f ) {
        // return a + snom / (snom + sdenom) * ab;
        return a.add( ab.scaleSelf( snom / ( snom + sdenom ) ) );
    }

    // P is outside (or on) BC if the triple scalar product [N PB PC] <= 0
    float va = n.dot( bp.crossSelf( cp ) );
    // If P outside BC and within feature region of BC,
    // return projection of P onto BC
    if ( va <= 0.0f && unom >= 0.0f && udenom >= 0.0f ) {
        // return b + unom / (unom + udenom) * bc;
        return b.add( bc.scaleSelf( unom / ( unom + udenom ) ) );
    }

    // P is outside (or on) CA if the triple scalar product [N PC PA] <= 0
    float vb = n.dot( cp.crossSelf( ap ) );
    // If P outside CA and within feature region of CA,
    // return projection of P onto CA
    if ( vb <= 0.0f && tnom >= 0.0f && tdenom >= 0.0f ) {
        // return a + tnom / (tnom + tdenom) * ac;
        return a.add( ac.scaleSelf( tnom / ( tnom + tdenom ) ) );
    }

    // P must project inside face region. Compute Q using barycentric
    // coordinates
    float u = va / ( va + vb + vc );
    float v = vb / ( va + vb + vc );
    float w = 1.0f - u - v; // = vc / (va + vb + vc)
    // return u * a + v * b + w * c;
    return a.scale( u ).addSelf( b.scale( v ) ).addSelf( c.scale( w ) );
}