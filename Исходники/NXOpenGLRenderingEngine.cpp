void NXOpenGLRenderingEngine::resetView(void)
{
    // create axis-aligned bounding box
    if(currentFrameIndex < 0)
        return;

    NXMoleculeSet *molSetPtr = moleculeSets[currentFrameIndex];
    BoundingBox bbox = GetBoundingBox(molSetPtr);
    Vector bboxMin = bbox.min();
    Vector bboxMax = bbox.max();

    real const bboxXWidth = 1.0*(bboxMax.x() - bboxMin.x());
    real const bboxYWidth = 1.0*(bboxMax.y() - bboxMin.y());
    real const bboxZDepth = 1.0*(bboxMax.z() - bboxMin.z());

    real const projCubeWidth = max(bboxXWidth, max(bboxYWidth, bboxZDepth));
    real const circumSphereRad = sqrt(3.0*0.25*projCubeWidth*projCubeWidth);
//         sqrt(sqr(max(bboxMax.x(), bboxMin.x())) +
//              sqr(max(bboxMax.y(), bboxMin.y())) +
//              sqr(max(bboxMax.z(), bboxMin.z())) );
    real const circumSphereDia = 2.0 * circumSphereRad;
    Vector const bboxCenter = bbox.center();

    real l, r, b, t;
    real const n = 0.25 * circumSphereRad;
    real const f = 12.0 * circumSphereRad;
    real const aspect = real(width()) / real(height());
    if(aspect < 1.0) {
//         l = bboxCenter.x() - circumSphereDia;
//         r = bboxCenter.x() + circumSphereDia;
//         b = bboxCenter.y() - circumSphereDia / aspect;
//         t = bboxCenter.y() + circumSphereDia / aspect;
        l = -circumSphereRad;
        r = -l;
        b = -circumSphereRad / aspect;
        t = -b;
    }
    else {
//         l = bboxCenter.x() - aspect * circumSphereDia;
//         r = bboxCenter.x() + aspect * circumSphereDia;
//         b = bboxCenter.y() - circumSphereDia;
//         t = bboxCenter.y() + circumSphereDia;
        l = -aspect * circumSphereRad;
        r = -l;
        b = -circumSphereRad;
        t = -b;
    }

    // makeCurrent();
//     camera.gluLookAt(bboxCenter.x(), bboxCenter.y(),
//                      bboxCenter.z()+circumSphereDia,
//                      bboxCenter.x(), bboxCenter.y(), bboxCenter.z(),
//                      0.0, 1.0, 0.0);
    // camera.gluPerspective(60.0, double(width())/double(height()), n, f);

//     camera.gluLookAt(0.0, 0.0, circumSphereRad,
//                      0.0, 0.0, 0.0,
//                      0.0, 1.0, 0.0);
//     camera.glOrtho(l, r, b, t, n, f);

    NXNamedView defaultView("DefaultView",
                            NXQuaternion<double>(1.0, 0.0, 0.0, 1.0),
                            bboxYWidth,
                            NXVector3d(-bboxCenter.x(),
                                       -bboxCenter.y(),
                                       -bboxCenter.z()),
                            1.0);
    cerr << defaultView << endl;
    camera.setNamedView(defaultView);

    // default HomeView: (1, 0, 0, 0) (10) (0, 0, 0) (1)
    // orthographic projection as in GLPane.py::_setup_projection()

//     double const SCALE = 10.0 * 1.0e-13;
//     double const VDIST = 6.0 * SCALE;
//     camera.gluLookAt(0.0, 0.0, VDIST,
//                      0.0, 0.0, 0.0,
//                      0.0, 1.0, 0.0);
//     double const NEAR = 0.25, FAR = 12.0;
//     camera.glOrtho(-SCALE * aspect, SCALE * aspect,
//                    -SCALE         , SCALE,
//                    VDIST * NEAR   , VDIST * FAR);

    updateGL();
}