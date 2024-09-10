void TransformGizmo::transformSelectedEntities(const Vector3 &move, const Vector3 &scale, Number rotate) {
    
    if(firstMove) {
        firstMove = false;
        dispatchEvent(new TrasnformGizmoEvent(mode), Event::SELECT_EVENT);
    }
    
    Vector3 globalCenter = getConcatenatedMatrix().getPosition();
	for(int i=0; i < selectedEntities.size(); i++) {
        
        
        if((orientation == ORIENTATION_GLOBAL && mode != TRANSFORM_SCALE_VIEW) || (ORIENTATION_LOCAL && mode == TRANSFORM_MOVE_VIEW)) {
            entityPositions[i] += move;
            
            Quaternion q;
            Quaternion currentRotation = selectedEntities[i]->getRotationQuat();
            Vector3 axisVector = transformConstraint;
            axisVector = currentRotation.Inverse().applyTo(axisVector);
            axisVector.Normalize();
            q.fromAngleAxis(rotate, axisVector);
            
            
            Vector3 newScale = selectedEntities[i]->getRotationQuat().applyTo(scale);
            newScale.x = fabs(newScale.x);
            newScale.y = fabs(newScale.y);
            newScale.z = fabs(newScale.z);
            if(scale.x < 0 || scale.y < 0 || scale.z < 0) {
                newScale = newScale * -1.0;
            }
            
            if(centerMode == CENTER_MODE_MEDIAN) {
                Vector3 globalPosition = selectedEntities[i]->getConcatenatedMatrix().getPosition();

                Quaternion tQ;
                tQ.fromAngleAxis(rotate, transformConstraint);
                Vector3 trans = globalCenter + tQ.applyTo(globalPosition-globalCenter) - globalPosition;
                globalPosition += trans;
                
                selectedEntities[i]->setPosition(globalPosition - selectedEntities[i]->getParentEntity()->getConcatenatedMatrix().getPosition());
                selectedEntities[i]->setRotationByQuaternion(currentRotation * q);
                if(move.length() == 0.0) {
                    entityPositions[i] = selectedEntities[i]->getPosition();
                }
                
                selectedEntities[i]->setScale(selectedEntities[i]->getScale() * (Vector3(1.0, 1.0, 1.0)+newScale));
                
                if(newScale.length() > 0.0) {
                    Vector3 scalePosition;
                    scalePosition.x = globalPosition.x + ((globalPosition.x - globalCenter.x) * newScale.x);
                    scalePosition.y = globalPosition.y + ((globalPosition.y - globalCenter.y) * newScale.y);
                    scalePosition.z = globalPosition.z + ((globalPosition.z - globalCenter.z) * newScale.z);
                    scalePosition = selectedEntities[i]->getParentEntity()->getConcatenatedMatrix().Inverse().transpose() * scalePosition;
                    selectedEntities[i]->setPosition(scalePosition);
                    if(move.length() == 0.0) {
                        entityPositions[i] = selectedEntities[i]->getPosition();
                    }
                }
                
            } else {
                selectedEntities[i]->setRotationByQuaternion(currentRotation * q);
                selectedEntities[i]->setScale(selectedEntities[i]->getScale() * (Vector3(1.0, 1.0, 1.0)+newScale));
            }
        } else {
            
            entityPositions[i] += getRotationQuat().applyTo(move);
            
            Quaternion q;
            Quaternion currentRotation = selectedEntities[i]->getRotationQuat();
            Vector3 axisVector = transformConstraint;
            
            // always global in the 2d view
            if(gizmoMode != GIZMO_MODE_3D || mode == TRANSFORM_ROTATE_VIEW) {
                axisVector = currentRotation.Inverse().applyTo(axisVector);
            }
            axisVector.Normalize();
            q.fromAngleAxis(rotate, axisVector);
            
            
            if(centerMode == CENTER_MODE_MEDIAN) {
                Vector3 globalPosition = selectedEntities[i]->getConcatenatedMatrix().getPosition();
                
                Quaternion tQ;
                tQ.fromAngleAxis(rotate, getRotationQuat().applyTo(axisVector));
                Vector3 trans = globalCenter + tQ.applyTo(globalPosition-globalCenter) - globalPosition;
                globalPosition += trans;
                
                selectedEntities[i]->setPosition(globalPosition - selectedEntities[i]->getParentEntity()->getConcatenatedMatrix().getPosition());
                selectedEntities[i]->setRotationByQuaternion(currentRotation * q);
                if(move.length() == 0.0) {
                    entityPositions[i] = selectedEntities[i]->getPosition();
                }
                
                selectedEntities[i]->setScale(selectedEntities[i]->getScale() * (Vector3(1.0, 1.0, 1.0)+scale));
                
                if(scale.length() > 0.0) {
                    Vector3 scalePosition;
                    scalePosition.x = globalPosition.x + ((globalPosition.x - globalCenter.x) * scale.x);
                    scalePosition.y = globalPosition.y + ((globalPosition.y - globalCenter.y) * scale.y);
                    scalePosition.z = globalPosition.z + ((globalPosition.z - globalCenter.z) * scale.z);
                    scalePosition = selectedEntities[i]->getParentEntity()->getConcatenatedMatrix().Inverse().transpose() * scalePosition;
                    selectedEntities[i]->setPosition(scalePosition);
                    if(move.length() == 0.0) {
                        entityPositions[i] = selectedEntities[i]->getPosition();
                    }
                }
                
            } else {
                selectedEntities[i]->setRotationByQuaternion(currentRotation * q);
                selectedEntities[i]->setScale(selectedEntities[i]->getScale() * (Vector3(1.0, 1.0, 1.0)+scale));
            }

            
        }

        // snap if moving and snap is on
        if(scale.length() == 0.0 && rotate == 0.0) {
            if(snapEnabled) {
                Vector3 snappedPositon = entityPositions[i];
                snappedPositon.x = round(((Number)snappedPositon.x)/(snapSize)) * snapSize;
                snappedPositon.y = round(((Number)snappedPositon.y)/(snapSize)) * snapSize;
                snappedPositon.z = round(((Number)snappedPositon.z)/(snapSize)) * snapSize;
                selectedEntities[i]->setPosition(snappedPositon);
            } else {
                selectedEntities[i]->setPosition(entityPositions[i]);
            }
        }
		
	}
}