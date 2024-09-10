void ViewProviderRobotObject::updateData(const App::Property* prop)
{
    Robot::RobotObject* robObj = static_cast<Robot::RobotObject*>(pcObject);
    if (prop == &robObj->RobotVrmlFile) {
        // read also from file
        const char* filename = robObj->RobotVrmlFile.getValue();
        QString fn = QString::fromUtf8(filename);
        QFile file(fn);
        SoInput in;
        pcRobotRoot->removeAllChildren();
        if (!fn.isEmpty() && file.open(QFile::ReadOnly)) {
            QByteArray buffer = file.readAll();
            in.setBuffer((void *)buffer.constData(), buffer.length());
            SoSeparator * node = SoDB::readAll(&in);
            if (node) pcRobotRoot->addChild(node);
            pcRobotRoot->addChild(pcTcpRoot);
        }
		// search for the conection points +++++++++++++++++++++++++++++++++++++++++++++++++
		Axis1Node = Axis2Node = Axis3Node = Axis4Node = Axis5Node = Axis6Node = 0;
		SoSearchAction searchAction;
		SoPath * path;

		// Axis 1
		searchAction.setName("FREECAD_AXIS1");
		searchAction.setInterest(SoSearchAction::FIRST);
		searchAction.setSearchingAll(FALSE);
		searchAction.apply(pcRobotRoot);
		path = searchAction.getPath();
		if(path){
			SoNode* node = path->getTail();
			std::string typeName = (const char*)node->getTypeId().getName();
			if (!node || node->getTypeId() != SoVRMLTransform::getClassTypeId())
				throw; // should not happen
			Axis1Node = static_cast<SoVRMLTransform *>(node);
		}
		// Axis 2
		searchAction.setName("FREECAD_AXIS2");
		searchAction.setInterest(SoSearchAction::FIRST);
		searchAction.setSearchingAll(FALSE);
		searchAction.apply(pcRobotRoot);
		path = searchAction.getPath();
		if(path){
			SoNode* node = path->getTail();
			std::string typeName = (const char*)node->getTypeId().getName();
			if (!node || node->getTypeId() != SoVRMLTransform::getClassTypeId())
				throw; // should not happen
			Axis2Node = static_cast<SoVRMLTransform *>(node);
		}
		// Axis 3
		searchAction.setName("FREECAD_AXIS3");
		searchAction.setInterest(SoSearchAction::FIRST);
		searchAction.setSearchingAll(FALSE);
		searchAction.apply(pcRobotRoot);
		path = searchAction.getPath();
		if(path){
			SoNode* node = path->getTail();
			std::string typeName = (const char*)node->getTypeId().getName();
			if (!node || node->getTypeId() != SoVRMLTransform::getClassTypeId())
				throw; // should not happen
			Axis3Node = static_cast<SoVRMLTransform *>(node);
		}
		// Axis 4
		searchAction.setName("FREECAD_AXIS4");
		searchAction.setInterest(SoSearchAction::FIRST);
		searchAction.setSearchingAll(FALSE);
		searchAction.apply(pcRobotRoot);
		path = searchAction.getPath();
		if(path){
			SoNode* node = path->getTail();
			std::string typeName = (const char*)node->getTypeId().getName();
			if (!node || node->getTypeId() != SoVRMLTransform::getClassTypeId())
				throw; // should not happen
			Axis4Node = static_cast<SoVRMLTransform *>(node);
		}
		// Axis 5
		searchAction.setName("FREECAD_AXIS5");
		searchAction.setInterest(SoSearchAction::FIRST);
		searchAction.setSearchingAll(FALSE);
		searchAction.apply(pcRobotRoot);
		path = searchAction.getPath();
		if(path){
			SoNode* node = path->getTail();
			std::string typeName = (const char*)node->getTypeId().getName();
			if (!node || node->getTypeId() != SoVRMLTransform::getClassTypeId())
				throw; // should not happen
			Axis5Node = static_cast<SoVRMLTransform *>(node);
		}
		// Axis 6
		searchAction.setName("FREECAD_AXIS6");
		searchAction.setInterest(SoSearchAction::FIRST);
		searchAction.setSearchingAll(FALSE);
		searchAction.apply(pcRobotRoot);
		path = searchAction.getPath();
		if(path){
			SoNode* node = path->getTail();
			std::string typeName = (const char*)node->getTypeId().getName();
			if (!node || node->getTypeId() != SoVRMLTransform::getClassTypeId())
				throw; // should not happen
			Axis6Node = static_cast<SoVRMLTransform *>(node);
		}
		if(Axis1Node)
			Axis1Node->rotation.setValue(SbVec3f(0.0,1.0,0.0),robObj->Axis1.getValue()*(M_PI/180));
		if(Axis2Node)
			Axis2Node->rotation.setValue(SbVec3f(0.0,1.0,0.0),robObj->Axis2.getValue()*(M_PI/180));
		if(Axis3Node)
			Axis3Node->rotation.setValue(SbVec3f(0.0,1.0,0.0),robObj->Axis3.getValue()*(M_PI/180));
		if(Axis4Node)
			Axis4Node->rotation.setValue(SbVec3f(0.0,1.0,0.0),robObj->Axis4.getValue()*(M_PI/180));
		if(Axis5Node)
			Axis5Node->rotation.setValue(SbVec3f(0.0,1.0,0.0),robObj->Axis5.getValue()*(M_PI/180));
		if(Axis6Node)
			Axis6Node->rotation.setValue(SbVec3f(0.0,1.0,0.0),robObj->Axis6.getValue()*(M_PI/180));
    }else if (prop == &robObj->Axis1) {
        if(Axis1Node){
			Axis1Node->rotation.setValue(SbVec3f(0.0,1.0,0.0),robObj->Axis1.getValue()*(M_PI/180));
            if(toolShape)
                toolShape->setTransformation((robObj->Tcp.getValue() * (robObj->ToolBase.getValue().inverse())).toMatrix());
        }
    }else if (prop == &robObj->Axis2) {
        if(Axis2Node){
			Axis2Node->rotation.setValue(SbVec3f(0.0,1.0,0.0),robObj->Axis2.getValue()*(M_PI/180));
            if(toolShape)
                toolShape->setTransformation((robObj->Tcp.getValue() * (robObj->ToolBase.getValue().inverse())).toMatrix());
        }
    }else if (prop == &robObj->Axis3) {
        if(Axis3Node){
			Axis3Node->rotation.setValue(SbVec3f(0.0,1.0,0.0),robObj->Axis3.getValue()*(M_PI/180));
            if(toolShape)
                toolShape->setTransformation((robObj->Tcp.getValue() * (robObj->ToolBase.getValue().inverse())).toMatrix());
        }
    }else if (prop == &robObj->Axis4) {
        if(Axis4Node){
			Axis4Node->rotation.setValue(SbVec3f(0.0,1.0,0.0),robObj->Axis4.getValue()*(M_PI/180));
            if(toolShape)
                toolShape->setTransformation((robObj->Tcp.getValue() * (robObj->ToolBase.getValue().inverse())).toMatrix());
        }
    }else if (prop == &robObj->Axis5) {
        if(Axis5Node){
			Axis5Node->rotation.setValue(SbVec3f(0.0,1.0,0.0),robObj->Axis5.getValue()*(M_PI/180));
            if(toolShape)
                toolShape->setTransformation((robObj->Tcp.getValue() * (robObj->ToolBase.getValue().inverse())).toMatrix());
        }
    }else if (prop == &robObj->Axis6) {
        if(Axis6Node){
			Axis6Node->rotation.setValue(SbVec3f(0.0,1.0,0.0),robObj->Axis6.getValue()*(M_PI/180));
            if(toolShape)
                toolShape->setTransformation((robObj->Tcp.getValue() * (robObj->ToolBase.getValue().inverse())).toMatrix());
        }
	}else if (prop == &robObj->Tcp) {
        Base::Placement loc = robObj->Tcp.getValue();
        SbMatrix  M;
        M.setTransform(SbVec3f(loc.getPosition().x,loc.getPosition().y,loc.getPosition().z),
                       SbRotation(loc.getRotation()[0],loc.getRotation()[1],loc.getRotation()[2],loc.getRotation()[3]),
                       SbVec3f(150,150,150)
                       );
        if(pcDragger)
            pcDragger->setMotionMatrix(M);
        if(toolShape)
            toolShape->setTransformation((robObj->Tcp.getValue() * (robObj->ToolBase.getValue().inverse())).toMatrix());
		//pcTcpTransform->translation = SbVec3f(loc.getPosition().x,loc.getPosition().y,loc.getPosition().z);
		//pcTcpTransform->rotation = SbRotation(loc.getRotation()[0],loc.getRotation()[1],loc.getRotation()[2],loc.getRotation()[3]);
	}else if (prop == &robObj->ToolShape) {
        App::DocumentObject* o = robObj->ToolShape.getValue<App::DocumentObject*>();

        if(o && (o->isDerivedFrom(Part::Feature::getClassTypeId()) || o->isDerivedFrom(App::VRMLObject::getClassTypeId())) ){
            //Part::Feature *p = dynamic_cast<Part::Feature *>(o);
            toolShape = Gui::Application::Instance->getViewProvider(o);
            toolShape->setTransformation((robObj->Tcp.getValue() * (robObj->ToolBase.getValue().inverse())).toMatrix());
        }else
            toolShape = 0;
 	}

}