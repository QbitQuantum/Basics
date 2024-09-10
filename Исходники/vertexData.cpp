    void normal(osg::Vec3 v1, osg::Vec3 v2, osg::Vec3 v3)
    {
        osg::Vec3 u,v;

        // right hand system, CCW triangle
        u = v2 - v1;
        v = v3 - v1;
        triNormal = u^v;
        triNormal.normalize();
    }