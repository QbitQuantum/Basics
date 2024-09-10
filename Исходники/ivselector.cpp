IvJointDragger::IvJointDragger(QtCoinViewerPtr viewer, ItemPtr pItem, int iSelectedLink, float draggerScale, int iJointIndex, bool bHilitJoint) : IvDragger(viewer, pItem, draggerScale)
{
    KinBodyItemPtr pbody = boost::dynamic_pointer_cast<KinBodyItem>(pItem);
    BOOST_ASSERT( !!pItem );

    _trackball = NULL;
    _draggerRoot = NULL;

    if( !pbody || !pbody->GetBody() ) {
        return;
    }
    if((iSelectedLink < 0)||(iSelectedLink >= (int)pbody->GetBody()->GetLinks().size())) {
        return;
    }
    if((iJointIndex < 0)||(iJointIndex >= (int)pbody->GetBody()->GetJoints().size())) {
        return;
    }

    _iSelectedLink = iSelectedLink;
    _iJointIndex = iJointIndex;
    KinBody::JointConstPtr pjoint = pbody->GetBody()->GetJoints().at(iJointIndex);

    _jointtype = pjoint->GetType();
    _dofindex = pjoint->GetDOFIndex();
    _jointname = pjoint->GetName();
    _jointoffset = 0; //pjoint->GetOffset();
    pjoint->GetLimits(_vlower,_vupper);

    _pLinkNode = pbody->GetIvLink(iSelectedLink);
    if( _pLinkNode == NULL ) {
        RAVELOG_WARN("no link is selected\n");
        return;
    }

    Transform tlink = pbody->GetBody()->GetLinks().at(iSelectedLink)->GetTransform();

    // create a root node for the dragger nodes
    _draggerRoot = new SoSeparator;
    SoTransform* draggertrans = new SoTransform();
    _pLinkNode->insertChild(_draggerRoot, 1); // insert right after transform

    // add a new material to change the color of the nodes being dragged
    _bHilitJoint = bHilitJoint;
    if (_bHilitJoint) {
        _material = new SoMaterial;
        _material->set("diffuseColor 0.8 0.6 0.2");
        _material->setOverride(true);
        _pLinkNode->insertChild(_material, 1);
    }

    Vector vaxes[3];
    for(int i = 0; i < pjoint->GetDOF(); ++i) {
        vaxes[i] = tlink.inverse().rotate(pjoint->GetAxis(i));
    }

    // need to make sure the rotation is pointed towards the joint axis
    Vector vnorm = Vector(1,0,0).cross(vaxes[0]);
    dReal fsinang = RaveSqrt(vnorm.lengthsqr3());
    if( fsinang > 0.0001f ) {
        vnorm /= fsinang;
    }
    else vnorm = Vector(1,0,0);

    Vector vtrans = tlink.inverse()*pjoint->GetAnchor();
    draggertrans->translation.setValue(vtrans.x, vtrans.y, vtrans.z);
    draggertrans->rotation = SbRotation(SbVec3f(vnorm.x, vnorm.y, vnorm.z), atan2f(fsinang,vaxes[0].x));
    _draggerRoot->addChild(draggertrans);

    // construct an Inventor trackball dragger
    float scale = _scale;
    _trackball = new SoTrackballDragger;
    AABB ab;
    _GetBounds(_pLinkNode, ab);
    _trackball->scaleFactor.setValue(ab.extents.x * scale, ab.extents.y * scale, ab.extents.z * scale);
    _trackball->setAnimationEnabled(false);
    _draggerRoot->addChild(_trackball);

    // get the material nodes that govern the color of the dragger and
    // note the dragger's normal color
    const char* rotators[3] = { "XRotator", "YRotator", "ZRotator" };
    const char* rotatorsActive[3] = { "XRotatorActive", "YRotatorActive", "ZRotatorActive" };

    // enable or disable each axis
    for (int i = 0; i < 3; i++) {
        if (i < pjoint->GetDOF()) {
            SoSeparator *s = (SoSeparator *)_trackball->getPart(rotators[i], false);
            _draggerMaterial[i] = (SoMaterial *) s->getChild(0);
            _normalColor = _draggerMaterial[i]->diffuseColor[0];
        }
        else {
            // disable the rotator on this axis
            _trackball->setPart(rotators[i], NULL);
            _trackball->setPart(rotatorsActive[i], NULL);
            _draggerMaterial[i] = NULL;
        }
    }

    // add a motion callback handler for the dragger
    _trackball->addMotionCallback(_MotionHandler, this);

    UpdateDragger();
}