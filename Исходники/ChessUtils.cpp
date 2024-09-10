MatrixTransform* ChessUtils::loadOSGModel(string name, float modelSize, Material* material, bool overrideMaterial,
	Vec3 modelCenterShift, double rotationAngle, Vec3 rotationAxis,
	Vec3 modelCenterOffsetPercentage) {
	// create a new node by reading in model from file
	Node* modelNode = osgDB::readNodeFile(name);
	if (modelNode != NULL) {
		// apply material
		if (material != NULL) {
			if (overrideMaterial) {
				modelNode->getOrCreateStateSet()->setAttributeAndModes(material, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
			} else {
				modelNode->getOrCreateStateSet()->setAttributeAndModes(material, osg::StateAttribute::ON);
			}
		}

		//put model in origin			
		//osg::BoundingSphere bound = modelNode->getBound();
		osg::ComputeBoundsVisitor cbVisitorOrigin;
		modelNode->accept(cbVisitorOrigin);
		osg::BoundingBox bound = cbVisitorOrigin.getBoundingBox();
		
		double scaleRatio = modelSize / bound.radius();

		MatrixTransform* unitTransform = new MatrixTransform();		
		unitTransform->postMult(Matrix::translate(-bound.center().x(), -bound.center().y(), -bound.center().z()));
		unitTransform->postMult(Matrix::rotate(rotationAngle, rotationAxis));
		unitTransform->postMult(Matrix::scale(scaleRatio, scaleRatio, scaleRatio));
		unitTransform->addChild(modelNode);		

		// put model in specified location
		osg::ComputeBoundsVisitor cbVisitor;
		unitTransform->accept(cbVisitor);
		osg::BoundingBox boundingBox = cbVisitor.getBoundingBox();
				
		float modelXOffset = (boundingBox.xMax() - boundingBox.xMin()) * modelCenterOffsetPercentage.x();
		float modelYOffset = (boundingBox.yMax() - boundingBox.yMin()) * modelCenterOffsetPercentage.y();
		float modelZOffset = (boundingBox.zMax() - boundingBox.zMin()) * modelCenterOffsetPercentage.z();
		unitTransform->postMult(Matrix::translate(modelXOffset, modelYOffset, modelZOffset));		

		MatrixTransform* modelPositionTransform = new MatrixTransform();		
		modelPositionTransform->postMult(Matrix::translate(modelCenterShift));
		modelPositionTransform->addChild(unitTransform);		

		return modelPositionTransform;
	}

	return NULL;
}