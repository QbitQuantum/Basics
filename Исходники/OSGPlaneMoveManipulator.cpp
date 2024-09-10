/*! The mouseMove is called by the viewer when the mouse is moved in the
    viewer and this handle is the active one.

    \param x the x-pos of the mouse (pixel)
    \param y the y-pos of the mouse (pixel)
 */
void PlaneMoveManipulator::mouseMove(const Int16 x,
                            const Int16 y)
{
    SLOG << "==============================" << endLog;
    SLOG << "PlaneMoveManipulator::mouseMove() enter x=" << x << " y=" << y << endLog;

    // get the beacon's core (must be ComponentTransform) and it's center
    if( getTarget() == NULL )
    {
        SWARNING << "Handle has no target.\n";
        return;
        
    }
    // get transformation of beacon
    Transform *t = dynamic_cast<Transform *>(getTarget()->getCore());

    if( t == NULL )
    {
        SWARNING << "handled object has no parent transform!\n";
        return;
    }

    Vec3f      translation;       // for matrix decomposition
    Quaternion rotation;
    Vec3f      scaleFactor;
    Quaternion scaleOrientation;

    t->getMatrix().getTransform(translation, rotation, scaleFactor,
                                scaleOrientation);

    OSG::Line viewray;
    getViewport()->getCamera()->calcViewRay(viewray, x, y, *getViewport());

    SLOG << "Manipulator::mouseMove(): viewray: " << viewray << endLog;

    // Get manipulator axes into world space
    OSG::Matrix tm = getTarget()->getToWorld();
    
    Vec3f rot_axis;
    tm.multFull(Vec3f(0,1,0), rot_axis);

    Plane pl(rot_axis, getClickPoint());

    Pnt3f plpoint;
    
    if (pl.intersect(viewray, plpoint) == true) // Ignore moving out of the plane...
    {
        SLOG << "Manipulator::mouseMove(): plpoint: " << plpoint << endLog;
         
        Vec3f      trans = getBaseTranslation();
        Quaternion rot   = getBaseRotation();

        // Get manipulator axes into world space
        Vec3f xp,zp;

        tm.multFull(Vec3f(1,0,0), xp);
        tm.multFull(Vec3f(0,0,1), zp);
        
        if (getActiveSubHandle() == getHandleXNode())
        {
            Line xaxis(getClickPoint(), xp);
            Line zaxis(getClickPoint(), zp);

            Real32 fx = xaxis.getClosestPointT(plpoint);
            Real32 fz = zaxis.getClosestPointT(plpoint);

            SLOG << "Manipulator::mouseMove(): xaxis: " << xaxis << " zaxis: " << zaxis <<endLog;
            SLOG << "Manipulator::mouseMove(): fx: " << fx << " fz: " << fz <<endLog;
        
            // Alternative: transform hitpoint into manip space
            OSG::Matrix m = getTarget()->getToWorld();
            m.invert();
            
            Pnt3f mpoint;
            m.mult(plpoint, mpoint);
            
            SLOG << "Manipulator::mouseMove(): mpoint:" << mpoint << endLog;

            trans = trans + xp * fx + zp * fz;
        }
        else if (getActiveSubHandle() == getHandleZNode())
        {
            Pnt3f wcenter;
            
            tm.multFull(Pnt3f(0,getLength()[1],0), wcenter);
            
            Vec3f vclick, vcurrent;
            
            vclick = getClickPoint() - wcenter;
            vcurrent = plpoint - wcenter;
            
            vclick.normalize();
            vcurrent.normalize();
            
            Real32 a = vclick.enclosedAngle(vcurrent);
            
            SLOG << "Manipulator::mouseMove(): wcenter:" << wcenter << "" <<endLog;
            SLOG << "Manipulator::mouseMove(): vclick:" << vclick << " vcurrent:" << vcurrent <<endLog;
            SLOG << "Manipulator::mouseMove(): angle:" << a << " deg: " << osgRad2Degree(a) << endLog;
        }
        
        Matrix m;

        m.setTransform(trans, rot, scaleFactor, scaleOrientation);

        t->setMatrix(m);
        
    }

    setLastMousePos(Pnt2f(Real32(x), Real32(y)));
    updateHandleTransform();

    //SLOG << "Manipulator::mouseMove() leave\n" << std::flush;
}