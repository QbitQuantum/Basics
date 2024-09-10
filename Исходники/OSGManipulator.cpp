/*! The mouseMove is called by the viewer when the mouse is moved in the
    viewer and this handle is the active one.

    \param x the x-pos of the mouse (pixel)
    \param y the y-pos of the mouse (pixel)
 */
void Manipulator::mouseMove(const Int16 x,
                            const Int16 y)
{
    //SLOG << "Manipulator::mouseMove() enter\n" << std::flush;

    // get the beacon's core (must be ComponentTransform) and it's center
    if( getTarget() != NULL )
    {
        // get transformation of beacon
        Transform *t = dynamic_cast<Transform *>(getTarget()->getCore());

        if( t != NULL )
        {
            UInt16     coord(0);          // active coordinate: X=0, Y=1, Z=2

            Int16      xDiff;             // the mousepos x delta
            Int16      yDiff;             // the mousepos y delta

            Vec3f      centerV;           // center of beacon
            Vec3f      handleCenterV;     // center of subhandle
            Vec2f      mouseScreenV;      // mouse move vector
            Vec2f      handleScreenV;     // handle vec in (cc)
            Real32     handleScreenVLen;  // len of handle vec in (cc)

            Vec3f      translation;       // for matrix decomposition
            Quaternion rotation;
            Vec3f      scaleFactor;
            Quaternion scaleOrientation;

            // TODO: das ist ja schon ein wenig haesslich
            static const Vec3f coordVector[3] = {
                Vec3f(1.0f, 0.0f, 0.0f),
                Vec3f(0.0f, 1.0f, 0.0f),
                Vec3f(0.0f, 0.0f, 1.0f)
            };

            //  check for the active handle
            if(     getActiveSubHandle() == getHandleXNode())
            {
                coord = 0;
            }
            else if(getActiveSubHandle() == getHandleYNode())
            {
                coord = 1;
            }
            else if(getActiveSubHandle() == getHandleZNode())
            {
                coord = 2;
            }

            // TODO: only for debugging, -> FDEBUG
            //SLOG << "moving " << ( coord == 0 ? "x\n" :
            //                       coord == 1 ? "y\n" :
            //                       "z\n" )
            //     << std::flush;

            // calculate diffs between current and last mouse position
            xDiff = x - Int16(getLastMousePos()[0]);
            yDiff = y - Int16(getLastMousePos()[1]);

            // set the vector resulting from user mouse movement and calc its length
            mouseScreenV.setValues(xDiff, -yDiff);

            t->getMatrix().getTransform(translation, rotation, scaleFactor,
                                        scaleOrientation);


            // calculate the camera coordinate of the center
            centerV            = translation;
            Pnt2f centerPixPos = calcScreenProjection(centerV.addToZero(),
                                                      getViewport());


            // calculate the camera coordinate of the handle center
            handleCenterV            = centerV + coordVector[coord]*getLength()[coord];
            Pnt2f handleCenterPixPos = calcScreenProjection(handleCenterV.addToZero(),
                                                            getViewport());

            handleScreenV    = handleCenterPixPos - centerPixPos;
            handleScreenVLen = handleScreenV.length();

            Real32 s = handleScreenV.dot(mouseScreenV) / handleScreenVLen;

            doMovement(t, coord, s * getLength()[coord] * 0.01, translation,
                       rotation, scaleFactor, scaleOrientation);
        }
        else
        {
            SWARNING << "handled object has no parent transform!\n";
        }
        callExternalUpdateHandler();
    }
    else
    {
        SWARNING << "Handle has no target.\n";
    }

    setLastMousePos(Pnt2f(Real32(x), Real32(y)));
    updateHandleTransform();

    //SLOG << "Manipulator::mouseMove() leave\n" << std::flush;
}