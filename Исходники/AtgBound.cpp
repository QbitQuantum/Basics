//-----------------------------------------------------------------------------
// Name: Bound::operator*
// Desc: transforms the bound by the current matrix
//-----------------------------------------------------------------------------
Bound Bound::operator*( CXMMATRIX World ) const
{
    //$OPTIMIZE: store matrix decomposed    
    XMVECTOR Translation = World.r[3];
    FLOAT Scale = XMVectorGetX( XMVector3Length( World.r[2] ) );
    XMVECTOR Rotation = XMQuaternionNormalize( XMQuaternionRotationMatrix( World ) );

    // switch based off this bounds type and call the correct
    // bound transform function
    switch( m_Type )
    {
        case Bound::Sphere_Bound:
        {
            Sphere WorldSphere = GetSphere();
            TransformSphere( &WorldSphere,
                             &WorldSphere,
                             Scale,
                             Rotation,
                             Translation );
            return Bound( WorldSphere );
        }
        case Bound::Frustum_Bound:
        {
            Frustum WorldFrustum = GetFrustum();
            TransformFrustum( &WorldFrustum,
                              &WorldFrustum,
                              Scale,
                              Rotation,
                              Translation );
            return Bound( WorldFrustum );
        }
        case Bound::OBB_Bound:
        {
            OrientedBox WorldObb = GetObb();
            TransformOrientedBox( &WorldObb,
                                  &WorldObb,
                                  Scale,
                                  Rotation,
                                  Translation );
            return Bound( WorldObb );
        }
        case Bound::AABB_Bound:
        {
            AxisAlignedBox WorldAabb = GetAabb();
            TransformAxisAlignedBox( &WorldAabb,
                                     &WorldAabb,
                                     Scale,
                                     Rotation,
                                     Translation );
            return Bound( WorldAabb );
        }
        case Bound::No_Bound:
            return Bound();
    }

    return Bound();
}