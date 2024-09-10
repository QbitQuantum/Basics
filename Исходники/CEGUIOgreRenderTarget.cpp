//----------------------------------------------------------------------------//
void OgreRenderTarget::unprojectPoint(const GeometryBuffer& buff,
                                      const Vector2& p_in, Vector2& p_out) const
{
    if (!d_matrixValid)
        updateMatrix();

    const OgreGeometryBuffer& gb = static_cast<const OgreGeometryBuffer&>(buff);

    const Ogre::Real midx = d_area.getWidth() * 0.5f;
    const Ogre::Real midy = d_area.getHeight() * 0.5f;

    // viewport matrix
    const Ogre::Matrix4 vpmat(
        midx,    0,    0,    d_area.d_left + midx,
         0,    -midy,  0,    d_area.d_top + midy,
         0,      0,    1,    0,
         0,      0,    0,    1
    );

    // matrices used for projecting and unprojecting points
    const Ogre::Matrix4 proj(gb.getMatrix() * d_matrix * vpmat);
    const Ogre::Matrix4 unproj(proj.inverse());

    Ogre::Vector3 in;

    // unproject the ends of the ray
    in.x = midx;
    in.y = midy;
    in.z = -d_viewDistance;
    const Ogre::Vector3 r1(unproj * in);
    in.x = p_in.d_x;
    in.y = p_in.d_y;
    in.z = 0;
    // calculate vector of picking ray
    const Ogre::Vector3 rv(r1 - unproj * in);

    // project points to orientate them with GeometryBuffer plane
    in.x = 0.0;
    in.y = 0.0;
    const Ogre::Vector3 p1(proj * in);
    in.x = 1.0;
    in.y = 0.0;
    const Ogre::Vector3 p2(proj * in);
    in.x = 0.0;
    in.y = 1.0;
    const Ogre::Vector3 p3(proj * in);

    // calculate the plane normal
    const Ogre::Vector3 pn((p2 - p1).crossProduct(p3 - p1));
    // calculate distance from origin
    const Ogre::Real plen = pn.length();
    const Ogre::Real dist = -(p1.x * (pn.x / plen) +
                              p1.y * (pn.y / plen) +
                              p1.z * (pn.z / plen));

    // calculate intersection of ray and plane
    const Ogre::Real pn_dot_rv = pn.dotProduct(rv);
    const Ogre::Real tmp = pn_dot_rv != 0.0 ?
                            (pn.dotProduct(r1) + dist) / pn_dot_rv :
                            0.0;

    p_out.d_x = static_cast<float>(r1.x - rv.x * tmp);
    p_out.d_y = static_cast<float>(r1.y - rv.y * tmp);
}