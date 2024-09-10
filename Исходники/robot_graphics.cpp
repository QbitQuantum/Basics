void robot_graphics_t::renderJoints(BodyNode *_node, RenderInterface *_ri, int _depth) {
	if(!_node)
		return;

	// render self geometry
    Joint *_jointParent = _node->getParentJoint();
    int nt = _jointParent->getNumTransforms();

    if(_depth > 0) {
        // lines?
        glColor3d(1,1,1);
        glLineWidth(2.0);
        glDisable(GL_LIGHTING);
        glBegin(GL_LINES);

        glVertex3d(0, 0, 0);

        Matrix4d locTrans = _jointParent->getLocalTransform();

        // Lines?
        glVertex3d(locTrans(0,3), locTrans(1,3), locTrans(2,3));
        glEnd();

        glEnable(GL_LIGHTING);
    }

	_ri->pushMatrix();
	for(int i=0; i < _jointParent->getNumTransforms(); ++i) {
		_jointParent->getTransform(i)->applyGLTransform(_ri);

//		if(i == _jointParent->getNumTransforms()-1) {
//			// dof transform
//			cout << "BodyNode: " << _node->getName() << endl;
//			cout << "Trfm: " << _jointParent->getTransform(i)->getName() << endl;
//			cout << "Tfrm Type: " << _jointParent->getTransform(i)->getType() << endl;
//			cout << "= \n" << _jointParent->getTransform(i)->getTransform() << endl;
//			cout << "ParentJoint: " << _jointParent->getName() << endl;
//			for(int i=0; i < 3; i++) {
//				cout << "axis " << i << "= \n"
//					 << _jointParent->getAxis(i) << endl;
//			}
//		}
	}

	// axis 0 is joint axis of rotation (i think)
	Vector3d ax = _jointParent->getAxis(0).normalized();
	Vector3d zx = Vector3d::UnitZ();
	Vector3d perp = zx.cross(ax);
	double y = perp.norm();
	double x = zx.dot(ax);
	double ang = atan2(y,x) * 180.0 / M_PI;

	_ri->pushMatrix();

	double radius = 0.02;
	double height = 0.05;

	_ri->rotate(perp, ang);

		_ri->pushMatrix();
		glTranslated(0.0,0.0,-height/2);
		glColor3d(0.0, 0.3, 1.0);
		QUAD_OBJ_INIT;
		gluCylinder(quadObj, radius, radius, height, 8, 8);
		gluDisk(quadObj, 0, radius, 8, 8);
		glTranslated(0.0,0.0,height);
		gluDisk(quadObj, 0, radius, 8, 8);
		_ri->popMatrix();

	//glColor3d(0.0, 1.0, 0.0);
	//_ri->drawCylinder(radius, height);
	_ri->popMatrix();


	// render subtree
	for(int i=0; i < _node->getNumChildJoints(); ++i) {
		BodyNode *child = _node->getChildJoint(i)->getChildNode();
		renderJoints(child, _ri, _depth+1);
	}
	_ri->popMatrix();
}