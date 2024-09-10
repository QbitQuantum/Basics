void jrOSGHighlightVisitor::apply(osg::Node &node) {
	if (node.getName().find("LowerArm_Rotator") != std::string::npos) {

		std::cout << "highlighting: " << node.getName() << std::endl;
		osgFX::Scribe* scribe = new osgFX::Scribe();
		osg::Group* parent = node.getParent(0);
		
		scribe->setName("highlighted");
		scribe->setWireframeColor(osg::Vec4(0,1,0,0.5));
		scribe->addChild(&node);
		
		parent->replaceChild(&node, scribe);

		parent = node.getParent(0);
		
		osg::MatrixTransform* transform = new osg::MatrixTransform;
		
		const double angle = 0.1;
		const osg::Vec3d axis(-1, 0, 0);
		transform->setMatrix(osg::Matrix::rotate(angle, axis));
		transform->setName("trans");
		transform->addChild(&node);
		parent->replaceChild(&node, transform);
	} 	
	else if (node.getName().find("highlighted") != std::string::npos) {
		std::cout << "removing highlight on: " << node.getName() << std::endl;
		osg::Group* parent = node.getParent(0);
		osgFX::Scribe* scribe = dynamic_cast<osgFX::Scribe*>(&node);
		parent->replaceChild(&node, scribe->getChild(0));
		return;
	} 
	else if (node.getName().find("trans") != std::string::npos) {
		std::cout << "altering: " << node.getName() << std::endl;
		osg::Group* parent = node.getParent(0);
		osg::MatrixTransform* transform = dynamic_cast<osg::MatrixTransform*>(&node);
	
		osg::Quat currentRotate = transform->getMatrix().getRotate();
		osg::Matrix currentMatrix = transform->getMatrix();
		osg::Vec4 currentVec = currentRotate.asVec4();

		std::cout << "current: " << currentVec[3] << " " << std::endl;

		const double angle = currentVec[3] + 0.1;
		const osg::Vec3d axis(-1, 0, 0);
		transform->setMatrix(osg::Matrix::rotate(angle, axis));

		std::cout << "current: " << angle << " " << std::endl;


		//currentRotate.set(currentVec[0] + 0.1,0,0,0);
		//currentMatrix.setRotate(currentRotate);

		//transform->setMatrix(currentMatrix);
			
		//transform.setMatrix());
		parent->replaceChild(&node, transform);
		return;
	}




	traverse(node);
}