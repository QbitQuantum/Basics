/** Override of the default implementation to account for versioning. */
void CustomJoint::
updateFromXMLNode(SimTK::Xml::Element& aNode, int versionNumber)
{
	int documentVersion = versionNumber;
	if ( documentVersion < XMLDocument::getLatestVersion()){
		if (Object::getDebugLevel()>=1)
			cout << "Updating CustomJoint to latest format..." << endl;
		// Version before refactoring spatialTransform
		if (documentVersion<10901){
			// replace TransformAxisSet with SpatialTransform
			/////renameChildNode("TransformAxisSet", "SpatialTransform");
			// Check how many TransformAxes are defined
			SimTK::Xml::element_iterator spatialTransformNode = 
                aNode.element_begin("TransformAxisSet");
			if (spatialTransformNode == aNode.element_end()) return;

			SimTK::Xml::element_iterator axesSetNode = 
                spatialTransformNode->element_begin("objects");
			/////if (axesSetNode != NULL)
			/////	spatialTransformNode->removeChild(axesSetNode);
			/////DOMElement*grpNode = XMLNode::GetFirstChildElementByTagName(spatialTransformNode,"groups");
			/////if (grpNode != NULL)
			/////	spatialTransformNode->removeChild(grpNode);
			// (0, 1, 2 rotations & 3, 4, 5 translations then remove the is_rotation node)
			SimTK::Array_<SimTK::Xml::Element> list = 
                axesSetNode->getAllElements();
			unsigned int listLength = list.size();
			int objectsFound = 0;
			Array<int> translationIndices(-1, 0);
			Array<int>  rotationIndices(-1, 0);
			int nextAxis = 0;
			std::vector<TransformAxis *> axes;
			// Add children for all six axes here
			//////_node->removeChild(SpatialTransformNode);
			
			// Create a blank Spatial Transform and use it to populate the 
            // XML structure
			for(int i=0; i<6; i++)
				updSpatialTransform()[i].setFunction(new OpenSim::Constant(0));
			
			Array<OpenSim::TransformAxis*> oldAxes;
			for(unsigned int j=0;j<listLength;j++) {
				// getChildNodes() returns all types of DOMNodes including 
                // comments, text, etc., but we only want
				// to process element nodes
				SimTK::Xml::Element objElmt = list[j];
				string objectType = objElmt.getElementTag();
                // (sherm) this is cleaning up old TransformAxis here but
                // that should really be done in TransformAxis instead.
				if (objectType == "TransformAxis"){
					OpenSim::TransformAxis* readAxis = 
                        new OpenSim::TransformAxis(objElmt);
					assert(nextAxis <=5);
					bool isRotation = false;
					SimTK::Xml::element_iterator rotationNode = 
                        objElmt.element_begin("is_rotation");
					if (rotationNode != objElmt.element_end()){
						SimTK::String sValue = 
                            rotationNode->getValueAs<SimTK::String>();
						bool value = (sValue.toLower() == "true");
								isRotation = value;
						objElmt.eraseNode(rotationNode);
							}
					SimTK::Xml::element_iterator coordinateNode = 
                        objElmt.element_begin("coordinate");
					SimTK::String coordinateName = 
                        coordinateNode->getValueAs<SimTK::String>();
					Array<std::string> names("");
					names.append(coordinateName);
					readAxis->setCoordinateNames(names);
					SimTK::Xml::element_iterator axisNode = 
                        objElmt.element_begin("axis");
					
					SimTK::Vec3 axisVec= axisNode->getValueAs<SimTK::Vec3>();
					readAxis->setAxis(axisVec);
					if (isRotation){
						rotationIndices.append(nextAxis);
					}
					else {
						translationIndices.append(nextAxis);
					}
					axes.push_back(readAxis);
					nextAxis++;
				}
			}
			assert(rotationIndices.getSize() <=3);
			assert(translationIndices.getSize() <=3);
			//XMLNode::RemoveChildren(SpatialTransformAxesNode);
			int nRotations = rotationIndices.getSize();
			int nTranslations = translationIndices.getSize();
			// Now copy coordinateName, Axis, Function into proper slot
			for (int i=0; i<nRotations; i++){
				updSpatialTransform()[i] = *axes[rotationIndices[i]];
			}
			updSpatialTransform().constructIndependentAxes(nRotations, 0);
			// Add Translations from old list then pad with default ones, 
            // make sure no singularity.
			for (int i=0; i<nTranslations; i++){
				updSpatialTransform()[i+3] = *axes[translationIndices[i]];
			}
			updSpatialTransform().constructIndependentAxes(nTranslations, 3);
		}
	}

    // Delegate to superclass now.
	Super::updateFromXMLNode(aNode, versionNumber);

	const CoordinateSet& coordinateSet = get_CoordinateSet();

	// Fix coordinate type post deserialization
	// Fix coordinate type post deserialization
	for (int i=0; i<coordinateSet.getSize(); i++){
		OpenSim::Coordinate& nextCoord = coordinateSet.get(i);
		// Find TransformAxis for the coordinate and use it to set Coordinate's motionType
		for(int axisIndex=0; axisIndex<6; axisIndex++){
			const TransformAxis& nextAxis = getSpatialTransform()[axisIndex];
			const Property<std::string>& coordNames = nextAxis.getCoordinateNames();
			if (coordNames.findIndex(nextCoord.getName())!=-1){
				coordinateSet.get(i).setMotionType((axisIndex>2)? 
						Coordinate::Translational : Coordinate::Rotational);
				break;
			}
		}
	}
	// Axes should be independent otherwise Simbody throws an exception in addToSystem
	double tol = 1e-5;
    // Verify that none of the rotation axes are colinear
	const std::vector<SimTK::Vec3> axes=getSpatialTransform().getAxes();
	for(int startIndex=0; startIndex<=3; startIndex+=3){
        if(((axes[startIndex+0]%axes[startIndex+1]).norm() < tol)||
			((axes[startIndex+0]%axes[startIndex+2]).norm() < tol)||
			((axes[startIndex+1]%axes[startIndex+2]).norm() < tol)){
				throw(Exception("CustomJoint " + getName() + 
                    " has colinear axes and so is not well-defined."
                    " Please fix and retry loading.."));
		}
	}
    updProperty_SpatialTransform().setValueIsDefault(false);
}