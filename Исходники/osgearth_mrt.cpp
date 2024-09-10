    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor*)
    {
        if ( ea.getEventType() == ea.PUSH )
        {
            // mouse click from [-1...1]
            float nx = ea.getXnormalized();
            float ny = ea.getYnormalized();

            // clicked point in clip space:
            osg::Vec3d pn( nx, ny, -1 ); // on near plane
            osg::Vec3d pf( nx, ny,  1 ); // on far plane

            OE_NOTICE << "clip: nx=" << nx << ", ny=" << ny << std::endl;
            
            // take the view matrix as-is:
            osg::Matrix view = _view->getCamera()->getViewMatrix();

            // adjust projection matrix to include entire earth:
            double fovy, ar, zn, zf;
            _view->getCamera()->getProjectionMatrix().getPerspective(fovy, ar, zn, zf);
            osg::Matrix proj;
            proj.makePerspective(fovy, ar, 1.0, 1e10);

            // Invert the MVP to transform points from clip to model space:
            osg::Matrix MVP = view * proj;
            osg::Matrix invMVP;
            invMVP.invert(MVP);

            pn = pn * invMVP;
            pf = pf * invMVP;

            OE_NOTICE << "model: near = " << pn.x() << ", " << pn.y() << ", " << pn.z() << std::endl;
            OE_NOTICE << "model: far  = " << pf.x() << ", " << pf.y() << ", " << pf.z() << std::endl;

            // Intersect in model space.
            osgUtil::LineSegmentIntersector* lsi = new osgUtil::LineSegmentIntersector(
                osgUtil::Intersector::MODEL, pn, pf );

            lsi->setIntersectionLimit( lsi->LIMIT_NEAREST );

            osgUtil::IntersectionVisitor iv( lsi ); 
            
            _node->accept( iv );

            if ( lsi->containsIntersections() )
            {
                osg::Vec3d p = lsi->getIntersections().begin()->getWorldIntersectPoint();
                OE_NOTICE << "i = " << p.x() << ", " << p.y() << ", " << p.z() << std::endl;
            }
        }
        return false;
    }