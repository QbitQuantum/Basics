void qRansacSD::doAction()
{
    assert(m_app);
    if (!m_app)
        return;

    const ccHObject::Container& selectedEntities = m_app->getSelectedEntities();
    size_t selNum = selectedEntities.size();
    if (selNum!=1)
    {
        m_app->dispToConsole("Select only one cloud!",ccMainAppInterface::ERR_CONSOLE_MESSAGE);
        return;
    }

    ccHObject* ent = selectedEntities[0];
    assert(ent);
    if (!ent || !ent->isA(CC_POINT_CLOUD))
    {
        m_app->dispToConsole("Select a real point cloud!",ccMainAppInterface::ERR_CONSOLE_MESSAGE);
        return;
    }

    ccPointCloud* pc = static_cast<ccPointCloud*>(ent);

    //input cloud
    size_t count = (size_t)pc->size();
    bool hasNorms = pc->hasNormals();
    PointCoordinateType bbMin[3],bbMax[3];
    pc->getBoundingBox(bbMin,bbMax);

    //Convert CC point cloud to RANSAC_SD type
    PointCloud cloud;
    {
        try
        {
            cloud.reserve(count);
        }
        catch(...)
        {
            m_app->dispToConsole("Not enough memory!",ccMainAppInterface::ERR_CONSOLE_MESSAGE);
            return;
        }

        //default point & normal
        Point Pt;
        Pt.normal[0] = 0.0;
        Pt.normal[1] = 0.0;
        Pt.normal[2] = 0.0;
        for (unsigned i=0; i<(unsigned)count; ++i)
        {
            const CCVector3* P = pc->getPoint(i);
            Pt.pos[0] = P->x;
            Pt.pos[1] = P->y;
            Pt.pos[2] = P->z;
            if (hasNorms)
            {
                const PointCoordinateType* N = pc->getPointNormal(i);
                Pt.normal[0] = N[0];
                Pt.normal[1] = N[1];
                Pt.normal[2] = N[2];
            }
            cloud.push_back(Pt);
        }

        //manually set bounding box!
        Vec3f cbbMin,cbbMax;
        cbbMin[0] = bbMin[0];
        cbbMin[1] = bbMin[1];
        cbbMin[2] = bbMin[2];
        cbbMax[0] = bbMax[0];
        cbbMax[1] = bbMax[1];
        cbbMax[2] = bbMax[2];
        cloud.setBBox(cbbMin,cbbMax);
    }

    //cloud scale (useful for setting several parameters
    const float scale = cloud.getScale();

    //init dialog with default values
    ccRansacSDDlg rsdDlg(m_app->getMainWindow());
    rsdDlg.epsilonDoubleSpinBox->setValue(.01f * scale);		// set distance threshold to .01f of bounding box width
    // NOTE: Internally the distance threshold is taken as 3 * ransacOptions.m_epsilon!!!
    rsdDlg.bitmapEpsilonDoubleSpinBox->setValue(.02f * scale);	// set bitmap resolution to .02f of bounding box width
    // NOTE: This threshold is NOT multiplied internally!
    rsdDlg.supportPointsSpinBox->setValue(s_supportPoints);
    rsdDlg.normThreshDoubleSpinBox->setValue(s_normThresh);
    rsdDlg.probaDoubleSpinBox->setValue(s_proba);
    rsdDlg.planeCheckBox->setChecked(s_primEnabled[0]);
    rsdDlg.sphereCheckBox->setChecked(s_primEnabled[1]);
    rsdDlg.cylinderCheckBox->setChecked(s_primEnabled[2]);
    rsdDlg.coneCheckBox->setChecked(s_primEnabled[3]);
    rsdDlg.torusCheckBox->setChecked(s_primEnabled[4]);

    if (!rsdDlg.exec())
        return;

    //for parameters persistence
    {
        s_supportPoints = rsdDlg.supportPointsSpinBox->value();
        s_normThresh = rsdDlg.normThreshDoubleSpinBox->value();
        s_proba = rsdDlg.probaDoubleSpinBox->value();

        //consistency check
        {
            unsigned char primCount = 0;
            for (unsigned char k=0; k<5; ++k)
                primCount += (unsigned)s_primEnabled[k];
            if (primCount==0)
            {
                m_app->dispToConsole("No primitive type selected!",ccMainAppInterface::ERR_CONSOLE_MESSAGE);
                return;
            }
        }

        s_primEnabled[0] = rsdDlg.planeCheckBox->isChecked();
        s_primEnabled[1] = rsdDlg.sphereCheckBox->isChecked();
        s_primEnabled[2] = rsdDlg.cylinderCheckBox->isChecked();
        s_primEnabled[3] = rsdDlg.coneCheckBox->isChecked();
        s_primEnabled[4] = rsdDlg.torusCheckBox->isChecked();
    }

    //import parameters from dialog
    RansacShapeDetector::Options ransacOptions;
    {
        ransacOptions.m_epsilon = rsdDlg.epsilonDoubleSpinBox->value();
        ransacOptions.m_bitmapEpsilon = rsdDlg.bitmapEpsilonDoubleSpinBox->value();
        ransacOptions.m_normalThresh = rsdDlg.normThreshDoubleSpinBox->value();
        ransacOptions.m_minSupport = rsdDlg.supportPointsSpinBox->value();
        ransacOptions.m_probability = rsdDlg.probaDoubleSpinBox->value();
    }

    //progress dialog
    ccProgressDialog progressCb(false,m_app->getMainWindow());
    progressCb.setRange(0,0);

    if (!hasNorms)
    {
        progressCb.setInfo("Computing normals (please wait)");
        progressCb.start();
        QApplication::processEvents();

        cloud.calcNormals(.01f * scale);

        if (pc->reserveTheNormsTable())
        {
            for (size_t i=0; i<count; ++i)
            {
                CCVector3 N(cloud[i].normal);
                N.normalize();
                pc->addNorm(N.u);
            }
            pc->showNormals(true);

            //currently selected entities appearance may have changed!
            pc->prepareDisplayForRefresh_recursive();
        }
        else
        {
            m_app->dispToConsole("Not enough memory to compute normals!",ccMainAppInterface::ERR_CONSOLE_MESSAGE);
            return;
        }
    }

    // set which primitives are to be detected by adding the respective constructors
    RansacShapeDetector detector(ransacOptions); // the detector object

    if (rsdDlg.planeCheckBox->isChecked())
        detector.Add(new PlanePrimitiveShapeConstructor());
    if (rsdDlg.sphereCheckBox->isChecked())
        detector.Add(new SpherePrimitiveShapeConstructor());
    if (rsdDlg.cylinderCheckBox->isChecked())
        detector.Add(new CylinderPrimitiveShapeConstructor());
    if (rsdDlg.coneCheckBox->isChecked())
        detector.Add(new ConePrimitiveShapeConstructor());
    if (rsdDlg.torusCheckBox->isChecked())
        detector.Add(new TorusPrimitiveShapeConstructor());

    size_t remaining = count;
    typedef std::pair< MiscLib::RefCountPtr< PrimitiveShape >, size_t > DetectedShape;
    MiscLib::Vector< DetectedShape > shapes; // stores the detected shapes

    // run detection
    // returns number of unassigned points
    // the array shapes is filled with pointers to the detected shapes
    // the second element per shapes gives the number of points assigned to that primitive (the support)
    // the points belonging to the first shape (shapes[0]) have been sorted to the end of pc,
    // i.e. into the range [ pc.size() - shapes[0].second, pc.size() )
    // the points of shape i are found in the range
    // [ pc.size() - \sum_{j=0..i} shapes[j].second, pc.size() - \sum_{j=0..i-1} shapes[j].second )

    {
        progressCb.setInfo("Operation in progress");
        progressCb.setMethodTitle("Ransac Shape Detection");
        progressCb.start();

        //run in a separate thread
        s_detector = &detector;
        s_shapes = &shapes;
        s_cloud = &cloud;
        QFuture<void> future = QtConcurrent::run(doDetection);

        unsigned progress = 0;
        while (!future.isFinished())
        {
#if defined(_WIN32) || defined(WIN32)
            ::Sleep(500);
#else
            sleep(500);
#endif
            progressCb.update(++progress);
            //Qtconcurrent::run can't be canceled!
            /*if (progressCb.isCancelRequested())
            {
            	future.cancel();
            	future.waitForFinished();
            	s_remainingPoints = count;
            	break;
            }
            //*/
        }

        remaining = s_remainingPoints;

        progressCb.stop();
        QApplication::processEvents();
    }
    //else
    //{
    //	remaining = detector.Detect(cloud, 0, cloud.size(), &shapes);
    //}

#ifdef _DEBUG
    FILE* fp = fopen("RANS_SD_trace.txt","wt");

    fprintf(fp,"[Options]\n");
    fprintf(fp,"epsilon=%f\n",ransacOptions.m_epsilon);
    fprintf(fp,"bitmap epsilon=%f\n",ransacOptions.m_bitmapEpsilon);
    fprintf(fp,"normal thresh=%f\n",ransacOptions.m_normalThresh);
    fprintf(fp,"min support=%i\n",ransacOptions.m_minSupport);
    fprintf(fp,"probability=%f\n",ransacOptions.m_probability);

    fprintf(fp,"\n[Statistics]\n");
    fprintf(fp,"input points=%i\n",count);
    fprintf(fp,"segmented=%i\n",count-remaining);
    fprintf(fp,"remaining=%i\n",remaining);

    if (shapes.size()>0)
    {
        fprintf(fp,"\n[Shapes]\n");
        for (unsigned i=0; i<shapes.size(); ++i)
        {
            PrimitiveShape* shape = shapes[i].first;
            unsigned shapePointsCount = shapes[i].second;

            std::string desc;
            shape->Description(&desc);
            fprintf(fp,"#%i - %s - %i points\n",i+1,desc.c_str(),shapePointsCount);
        }
    }
    fclose(fp);
#endif

    if (remaining == count)
    {
        m_app->dispToConsole("Segmentation failed...",ccMainAppInterface::ERR_CONSOLE_MESSAGE);
        return;
    }

    if (shapes.size() > 0)
    {
        ccHObject* group = 0;
        for (MiscLib::Vector<DetectedShape>::const_iterator it = shapes.begin(); it != shapes.end(); ++it)
        {
            const PrimitiveShape* shape = it->first;
            size_t shapePointsCount = it->second;

            //too many points?!
            if (shapePointsCount > count)
            {
                m_app->dispToConsole("Inconsistent result!",ccMainAppInterface::ERR_CONSOLE_MESSAGE);
                break;
            }

            std::string desc;
            shape->Description(&desc);

            //new cloud for sub-part
            ccPointCloud* pcShape = new ccPointCloud(desc.c_str());

            //we fill cloud with sub-part points
            if (!pcShape->reserve((unsigned)shapePointsCount))
            {
                m_app->dispToConsole("Not enough memory!",ccMainAppInterface::ERR_CONSOLE_MESSAGE);
                delete pcShape;
                break;
            }
            bool saveNormals = pcShape->reserveTheNormsTable();

            for (size_t j=0; j<shapePointsCount; ++j)
            {
                pcShape->addPoint(CCVector3(cloud[count-1-j].pos));
                if (saveNormals)
                    pcShape->addNorm(cloud[count-1-j].normal);
            }

            //random color
            unsigned char col[3]= { (unsigned char)(255.0*(float)rand()/(float)RAND_MAX),
                                    (unsigned char)(255.0*(float)rand()/(float)RAND_MAX),
                                    0
                                  };
            col[2]=255-(col[1]+col[2])/2;
            pcShape->setRGBColor(col);
            pcShape->showColors(true);
            pcShape->showNormals(saveNormals);
            pcShape->setVisible(true);

            //convert detected primitive into a CC primitive type
            ccGenericPrimitive* prim = 0;
            switch(shape->Identifier())
            {
            case 0: //plane
            {
                const PlanePrimitiveShape* plane = static_cast<const PlanePrimitiveShape*>(shape);
                Vec3f G = plane->Internal().getPosition();
                Vec3f N = plane->Internal().getNormal();
                Vec3f X = plane->getXDim();
                Vec3f Y = plane->getYDim();

                //we look for real plane extents
                float minX,maxX,minY,maxY;
                for (size_t j=0; j<shapePointsCount; ++j)
                {
                    std::pair<float,float> param;
                    plane->Parameters(cloud[count-1-j].pos,&param);
                    if (j!=0)
                    {
                        if (minX<param.first)
                            minX=param.first;
                        else if (maxX>param.first)
                            maxX=param.first;
                        if (minY<param.second)
                            minY=param.second;
                        else if (maxY>param.second)
                            maxY=param.second;
                    }
                    else
                    {
                        minX=maxX=param.first;
                        minY=maxY=param.second;
                    }
                }

                //we recenter plane (as it is not always the case!)
                float dX = maxX-minX;
                float dY = maxY-minY;
                G += X * (minX+dX*0.5);
                G += Y * (minY+dY*0.5);

                //we build matrix from these vecctors
                ccGLMatrix glMat(CCVector3(X.getValue()),
                                 CCVector3(Y.getValue()),
                                 CCVector3(N.getValue()),
                                 CCVector3(G.getValue()));

                //plane primitive
                prim = new ccPlane(dX,dY,&glMat);

            }
            break;

            case 1: //sphere
            {
                const SpherePrimitiveShape* sphere = static_cast<const SpherePrimitiveShape*>(shape);
                float radius = sphere->Internal().Radius();
                Vec3f CC = sphere->Internal().Center();

                pcShape->setName(QString("Sphere (r=%1)").arg(radius,0,'f'));

                //we build matrix from these vecctors
                ccGLMatrix glMat;
                glMat.setTranslation(CCVector3(CC.getValue()));
                //sphere primitive
                prim = new ccSphere(radius,&glMat);
                prim->setEnabled(false);

            }
            break;

            case 2: //cylinder
            {
                const CylinderPrimitiveShape* cyl = static_cast<const CylinderPrimitiveShape*>(shape);
                Vec3f G = cyl->Internal().AxisPosition();
                Vec3f N = cyl->Internal().AxisDirection();
                Vec3f X = cyl->Internal().AngularDirection();
                Vec3f Y = N.cross(X);
                float r = cyl->Internal().Radius();
                float hMin = cyl->MinHeight();
                float hMax = cyl->MaxHeight();
                float h = hMax-hMin;
                G += N * (hMin+h*0.5);

                pcShape->setName(QString("Cylinder (r=%1/h=%2)").arg(r,0,'f').arg(h,0,'f'));

                //we build matrix from these vecctors
                ccGLMatrix glMat(CCVector3(X.getValue()),
                                 CCVector3(Y.getValue()),
                                 CCVector3(N.getValue()),
                                 CCVector3(G.getValue()));

                //cylinder primitive
                prim = new ccCylinder(r,h,&glMat);
                prim->setEnabled(false);

            }
            break;

            case 3: //cone
            {
                const ConePrimitiveShape* cone = static_cast<const ConePrimitiveShape*>(shape);
                Vec3f CC = cone->Internal().Center();
                Vec3f CA = cone->Internal().AxisDirection();
                float alpha = cone->Internal().Angle();

                //compute max height
                CCVector3 maxP(CC.getValue());
                float maxHeight = 0;
                for (size_t j=0; j<shapePointsCount; ++j)
                {
                    float h = cone->Internal().Height(cloud[count-1-j].pos);
                    if (h>maxHeight)
                    {
                        maxHeight=h;
                        maxP = CCVector3(cloud[count-1-j].pos);
                    }
                }

                pcShape->setName(QString("Cone (alpha=%1/h=%2)").arg(alpha,0,'f').arg(maxHeight,0,'f'));

                float radius = tan(alpha)*maxHeight;
                CCVector3 Z = CCVector3(CA.getValue());
                CCVector3 C = CCVector3(CC.getValue()); //cone apex

                //construct remaining of base
                Z.normalize();
                CCVector3 X = maxP - (C + maxHeight * Z);
                X.normalize();
                CCVector3 Y = Z * X;

                //we build matrix from these vecctors
                ccGLMatrix glMat(X,Y,Z,C+(maxHeight*0.5)*Z);

                //cone primitive
                prim = new ccCone(0,radius,maxHeight,0,0,&glMat);
                prim->setEnabled(false);

            }
            break;

            case 4: //torus
            {
                const TorusPrimitiveShape* torus = static_cast<const TorusPrimitiveShape*>(shape);
                if (torus->Internal().IsAppleShaped())
                {
                    m_app->dispToConsole("[qRansacSD] Apple-shaped torus are not handled by CloudCompare!",ccMainAppInterface::WRN_CONSOLE_MESSAGE);
                }
                else
                {
                    Vec3f CC = torus->Internal().Center();
                    Vec3f CA = torus->Internal().AxisDirection();
                    float minRadius = torus->Internal().MinorRadius();
                    float maxRadius = torus->Internal().MajorRadius();

                    pcShape->setName(QString("Torus (r=%1/R=%2)").arg(minRadius,0,'f').arg(maxRadius,0,'f'));

                    CCVector3 Z = CCVector3(CA.getValue());
                    CCVector3 C = CCVector3(CC.getValue());
                    //construct remaining of base
                    CCVector3 X = Z.orthogonal();
                    CCVector3 Y = Z * X;

                    //we build matrix from these vecctors
                    ccGLMatrix glMat(X,Y,Z,C);

                    //torus primitive
                    prim = new ccTorus(maxRadius-minRadius,maxRadius+minRadius,M_PI*2.0,false,0,&glMat);
                    prim->setEnabled(false);
                }

            }
            break;
            }

            //is there a primitive to add to part cloud?
            if (prim)
            {
                prim->applyGLTransformation_recursive();
                pcShape->addChild(prim);
                prim->setDisplay(pcShape->getDisplay());
                prim->setColor(col);
                prim->showColors(true);
                prim->setVisible(true);
            }

            if (!group)
            {
                group = new ccHObject(QString("Ransac Detected Shapes (%1)").arg(ent->getName()));
                m_app->addToDB(group,true,0,false);
            }
            group->addChild(pcShape);
            m_app->addToDB(pcShape,true,0,false);

            count -= shapePointsCount;

            QApplication::processEvents();
        }

        if (group)
        {
            assert(group->getChildrenNumber()!=0);

            //we hide input cloud
            pc->setEnabled(false);
            m_app->dispToConsole("[qRansacSD] Input cloud has been automtically hidden!",ccMainAppInterface::WRN_CONSOLE_MESSAGE);

            //we add new group to DB/display
            group->setVisible(true);
            group->setDisplay_recursive(pc->getDisplay());
            group->prepareDisplayForRefresh_recursive();
            m_app->refreshAll();
        }
    }
}