void curveColliderLocator::draw(M3dView &view, const MDagPath &path, 
								 M3dView::DisplayStyle style,
								 M3dView::DisplayStatus status)
{ 
	//
	// Get the input curve
	//
	MObject thisNode = thisMObject();
	MPlug radiusPlug(thisNode, colliderRadiusIn);
	MPlug colorPlugR(thisNode, colliderColorR);
	MPlug colorPlugG(thisNode, colliderColorG);
	MPlug colorPlugB(thisNode, colliderColorB);
	MPlug colorPlugT(thisNode, colliderTransparency);
	MPlug radiusElement;
	double radius;
	double radius2;
	double param;
	double param2;
	double paramNorm;
	radiusPlug.getValue(radius);
	MStatus stat;
	MQuaternion rotateQuat;
	double degreesToRadians = ( M_PI/ 180.0 );
	double radiansToDegrees = ( 180.0/M_PI );
	double rotateRadians;
	MVector crvNormalRotated;
	MPointArray radiusPts;
	MPoint radiusPt;
	
	// Alternate method of getting the MFnNurbsCurve:
	MPlug curvePlug(thisNode, colliderCurveIn);
	MPlugArray inputCrvArray;
	curvePlug.connectedTo(inputCrvArray, true, false);
	
	MObject crvColliderObj = inputCrvArray[0].node();
	MFnNurbsCurve cColliderFn(crvColliderObj, &stat);
	if(!stat){
		MGlobal::displayInfo(MString("Error creating MFnNurbsCurve for collider curve"));
		return;
	}
	
	MFnDagNode crvDagNode(crvColliderObj);
	MDagPath crvDagPath;
	crvDagNode.getPath(crvDagPath);
	MMatrix crvXform = crvDagPath.inclusiveMatrix();
	
	int numSpans = cColliderFn.numSpans();
	
	MPoint crvPoint;
	MPoint crvPoint2;
	
	GLUquadricObj* qobj = gluNewQuadric();
	
	view.beginGL(); 
	

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                  DRAW SMOOTH SHADED 
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if ( ( style == M3dView::kFlatShaded ) || ( style == M3dView::kGouraudShaded ) ) {
		glPushAttrib( GL_ALL_ATTRIB_BITS );
		glShadeModel(GL_SMOOTH);
		glEnable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glEnable(GL_LIGHT0);
		glMatrixMode( GL_MODELVIEW );
		
		float3 color; 
		colorPlugR.getValue(color[0]);
		colorPlugG.getValue(color[1]);
		colorPlugB.getValue(color[2]);
		float transparency;
		colorPlugT.getValue(transparency);
		
		float  diffuse[] = {color[0], color[1], color[2], transparency};
		float  specular[] = { 0.7f, 0.7f, 0.7f, transparency};
		float  shine[] = { 100.0f };
		float  ambient[] = { 0.2f, 0.2f, 0.2f, transparency };
		
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		
		// Draw the beginning and ending sphere caps
		glPushMatrix();
		cColliderFn.getPointAtParam(0, crvPoint, MSpace::kWorld);
		crvPoint = crvPoint*crvXform;
		glTranslatef(crvPoint.x, crvPoint.y, crvPoint.z);
		radiusElement = radiusPlug.elementByPhysicalIndex(0, &stat);
		radiusElement.getValue(radius);
		gluSphere(qobj, radius, 16, 16);
		glPopMatrix();

		glPushMatrix();
		cColliderFn.getPointAtParam(numSpans, crvPoint, MSpace::kWorld);
		crvPoint = crvPoint*crvXform;
		glTranslatef(crvPoint.x, crvPoint.y, crvPoint.z);
		radiusElement = radiusPlug.elementByPhysicalIndex( (radiusPlug.numElements() - 1), &stat);
		radiusElement.getValue(radius);
		gluSphere(qobj, radius, 16, 16);
		glPopMatrix();
	
		int numStacks = numSpans*30;
		int numSlices = 32;
	
		// Initialize our point array with the radius values
		radiusPts.clear();
		radiusPts.setLength(radiusPlug.numElements());
		for(int radiusItr = 0; radiusItr < radiusPlug.numElements(); radiusItr++){
			radiusElement = radiusPlug.elementByPhysicalIndex(radiusItr, &stat);
			if(!stat){MGlobal::displayError(MString("Could not get radius element.")); return;}
			radiusElement.getValue(radius);	
			radiusPt.x = (double)radius; radiusPt.y = 0.0; radiusPt.z = 0.0;
			radiusPts[radiusItr] = radiusPt;
		}
	
		if(numStacks>1){
			for(uint crvItr = 0; crvItr < numStacks - 1; crvItr++){
				
				param = (float(crvItr)/float(numStacks-1))*numSpans;
				param2 = (float(crvItr+1)/float(numStacks-1))*numSpans;
				cColliderFn.getPointAtParam(param, crvPoint, MSpace::kWorld);
				crvPoint = crvPoint*crvXform;
				cColliderFn.getPointAtParam(param2, crvPoint2, MSpace::kWorld);
				crvPoint2 = crvPoint2 * crvXform;
				
				// Determine the radius value 
				int lastRadiusIndex = radiusPlug.numElements() - 1;
				if(lastRadiusIndex == 0){
					radiusElement = radiusPlug.elementByPhysicalIndex(0, &stat);
					if(!stat){MGlobal::displayError(MString("Could not get radius element.")); return;}
					radiusElement.getValue(radius);
					radius2 = radius;
				}else if(lastRadiusIndex > 0){

					paramNorm = param/numSpans;
					radiusPt = getInterpolatedSplinePoint(paramNorm, radiusPts);
					radius = radiusPt.x;
					
					paramNorm = param2/numSpans;
					radiusPt  = getInterpolatedSplinePoint(paramNorm, radiusPts);
					radius2 = radiusPt.x;			
				}
					
				// First, we need to determine our starting position by travelling along the normal 
				MVector crvNormal = cColliderFn.normal(param, MSpace::kWorld);
				crvNormal = crvNormal * crvXform;
				MVector crvTangent = cColliderFn.tangent(param, MSpace::kWorld);
				crvTangent = crvTangent * crvXform;
				crvNormal.normalize();
				crvTangent.normalize();
				
				MVector crvNormal2 = cColliderFn.normal(param2, MSpace::kWorld);
				crvNormal2 = crvNormal2 * crvXform;
				MVector crvTangent2 = cColliderFn.tangent(param2, MSpace::kWorld);
				crvTangent2 = crvTangent2 * crvXform;
				crvNormal2.normalize();
				crvTangent2.normalize();
	//			glTranslatef(crvNormal.x, crvNormal.y, crvNormal.z);

				glBegin(GL_QUADS);
				for(int sliceItr = 0; sliceItr < numSlices; sliceItr++){
					// quad vertex 4
					rotateRadians = ((((float)sliceItr+1)/numSlices)*360)*degreesToRadians;
					rotateQuat.setAxisAngle(crvTangent, rotateRadians);
					crvNormalRotated = crvNormal.rotateBy(rotateQuat);
					glNormal3f(crvNormalRotated.x, crvNormalRotated.y, crvNormalRotated.z );
					glVertex3f((float)crvPoint.x + (crvNormalRotated.x*radius),
							   (float)crvPoint.y + (crvNormalRotated.y*radius),
							   (float)crvPoint.z + (crvNormalRotated.z*radius));		
					// quad vertex 3
					rotateRadians = ((((float)sliceItr+1)/numSlices)*360)*degreesToRadians;
					rotateQuat.setAxisAngle(crvTangent2, rotateRadians);
					crvNormalRotated = crvNormal.rotateBy(rotateQuat);
					glNormal3f(crvNormalRotated.x, crvNormalRotated.y, crvNormalRotated.z );
					glVertex3f((float)crvPoint2.x + (crvNormalRotated.x*radius2),
							   (float)crvPoint2.y + (crvNormalRotated.y*radius2),
							   (float)crvPoint2.z + (crvNormalRotated.z*radius2));
					// quad vertex 2
					rotateRadians = (((float)sliceItr/numSlices)*360)*degreesToRadians;
					rotateQuat.setAxisAngle(crvTangent2, rotateRadians);
					crvNormalRotated = crvNormal.rotateBy(rotateQuat);
					glNormal3f(crvNormalRotated.x, crvNormalRotated.y, crvNormalRotated.z );
					glVertex3f((float)crvPoint2.x + (crvNormalRotated.x*radius2),
							   (float)crvPoint2.y + (crvNormalRotated.y*radius2),
							   (float)crvPoint2.z + (crvNormalRotated.z*radius2));
					// quad vertex 1
					rotateRadians = (((float)sliceItr/numSlices)*360)*degreesToRadians;
					rotateQuat.setAxisAngle(crvTangent, rotateRadians);
					crvNormalRotated = crvNormal.rotateBy(rotateQuat);
					glNormal3f(crvNormalRotated.x, crvNormalRotated.y, crvNormalRotated.z );
					glVertex3f((float)crvPoint.x + (crvNormalRotated.x*radius),
							   (float)crvPoint.y + (crvNormalRotated.y*radius),
							   (float)crvPoint.z + (crvNormalRotated.z*radius));				
				}
				glEnd();
			}
		}
		glPopAttrib();
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                  END SMOOTH SHADED 
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                  DRAW WIREFRAME 
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if ( style == M3dView::kWireFrame ||  status == M3dView::kActive || status == M3dView::kLead) {
		glPushAttrib( GL_ALL_ATTRIB_BITS );

		// Draw the beginning and ending sphere caps
		// Quadrilateral strips
		glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
		glPushMatrix();
		cColliderFn.getPointAtParam(0, crvPoint, MSpace::kWorld);
		crvPoint = crvPoint*crvXform;
		glTranslatef(crvPoint.x, crvPoint.y, crvPoint.z);
		radiusElement = radiusPlug.elementByPhysicalIndex(0, &stat);
		radiusElement.getValue(radius);
		gluSphere(qobj, radius, 16, 16);
		glPopMatrix();
		
		glPushMatrix();
		cColliderFn.getPointAtParam(numSpans, crvPoint, MSpace::kWorld);
		crvPoint = crvPoint*crvXform;
		glTranslatef(crvPoint.x, crvPoint.y, crvPoint.z);
		radiusElement = radiusPlug.elementByPhysicalIndex( (radiusPlug.numElements() - 1), &stat);
		radiusElement.getValue(radius);
		gluSphere(qobj, radius, 16, 16);
		glPopMatrix();
		
	
		int numStacks = numSpans*10;
		int numSlices = 32;
		
		// Initialize our point array with the radius values
		radiusPts.clear();
		radiusPts.setLength(radiusPlug.numElements());
		for(int radiusItr = 0; radiusItr < radiusPlug.numElements(); radiusItr++){
			radiusElement = radiusPlug.elementByPhysicalIndex(radiusItr, &stat);
			if(!stat){MGlobal::displayError(MString("Could not get radius element.")); return;}
			radiusElement.getValue(radius);	
			radiusPt.x = (double)radius; radiusPt.y = 0.0; radiusPt.z = 0.0;
			radiusPts[radiusItr] = radiusPt;
		}
		
		for(uint crvItr = 0; crvItr < numStacks; crvItr++){
			
			param = (float(crvItr)/float(numStacks))*numSpans;
			param2 = (float(crvItr+1)/float(numStacks))*numSpans;
			cColliderFn.getPointAtParam(param, crvPoint, MSpace::kWorld);
			crvPoint = crvPoint*crvXform;
			cColliderFn.getPointAtParam(param2, crvPoint2, MSpace::kWorld);
			crvPoint2 = crvPoint2 * crvXform;
			
			// Determine the radius value 
			int lastRadiusIndex = radiusPlug.numElements() - 1;
			if(lastRadiusIndex == 0){
				radiusElement = radiusPlug.elementByPhysicalIndex(0, &stat);
				if(!stat){MGlobal::displayError(MString("Could not get radius element.")); return;}
				radiusElement.getValue(radius);
				radius2 = radius;
			}else if(lastRadiusIndex > 0){
				
				paramNorm = param/numSpans;
				radiusPt = getInterpolatedSplinePoint(paramNorm, radiusPts);
				radius = radiusPt.x;
				
				paramNorm = param2/numSpans;
				radiusPt  = getInterpolatedSplinePoint(paramNorm, radiusPts);
				radius2 = radiusPt.x;			
			}
			
			// First, we need to determine our starting position by travelling along the normal 
			MVector crvNormal = cColliderFn.normal(param, MSpace::kWorld);
			crvNormal = crvNormal * crvXform;
			MVector crvTangent = cColliderFn.tangent(param, MSpace::kWorld);
			crvTangent = crvTangent * crvXform;
			crvNormal.normalize();
			crvTangent.normalize();
			
			MVector crvNormal2 = cColliderFn.normal(param2, MSpace::kWorld);
			crvNormal2 = crvNormal2 * crvXform;
			MVector crvTangent2 = cColliderFn.tangent(param2, MSpace::kWorld);
			crvTangent2 = crvTangent2 * crvXform;
			crvNormal2.normalize();
			crvTangent2.normalize();
			//			glTranslatef(crvNormal.x, crvNormal.y, crvNormal.z);
			
			glBegin(GL_LINE_LOOP);
			for(int sliceItr = 0; sliceItr < numSlices; sliceItr++){
				// quad vertex 4
				rotateRadians = ((((float)sliceItr+1)/numSlices)*360)*degreesToRadians;
				rotateQuat.setAxisAngle(crvTangent, rotateRadians);
				crvNormalRotated = crvNormal.rotateBy(rotateQuat);
				glNormal3f(crvNormalRotated.x, crvNormalRotated.y, crvNormalRotated.z );
				glVertex3f((float)crvPoint.x + (crvNormalRotated.x*radius),
						   (float)crvPoint.y + (crvNormalRotated.y*radius),
						   (float)crvPoint.z + (crvNormalRotated.z*radius));		
				// quad vertex 3
				rotateRadians = ((((float)sliceItr+1)/numSlices)*360)*degreesToRadians;
				rotateQuat.setAxisAngle(crvTangent2, rotateRadians);
				crvNormalRotated = crvNormal.rotateBy(rotateQuat);
				glNormal3f(crvNormalRotated.x, crvNormalRotated.y, crvNormalRotated.z );
				glVertex3f((float)crvPoint2.x + (crvNormalRotated.x*radius2),
						   (float)crvPoint2.y + (crvNormalRotated.y*radius2),
						   (float)crvPoint2.z + (crvNormalRotated.z*radius2));
				// quad vertex 2
				rotateRadians = (((float)sliceItr/numSlices)*360)*degreesToRadians;
				rotateQuat.setAxisAngle(crvTangent2, rotateRadians);
				crvNormalRotated = crvNormal.rotateBy(rotateQuat);
				glNormal3f(crvNormalRotated.x, crvNormalRotated.y, crvNormalRotated.z );
				glVertex3f((float)crvPoint2.x + (crvNormalRotated.x*radius2),
						   (float)crvPoint2.y + (crvNormalRotated.y*radius2),
						   (float)crvPoint2.z + (crvNormalRotated.z*radius2));
				// quad vertex 1
				rotateRadians = (((float)sliceItr/numSlices)*360)*degreesToRadians;
				rotateQuat.setAxisAngle(crvTangent, rotateRadians);
				crvNormalRotated = crvNormal.rotateBy(rotateQuat);
				glNormal3f(crvNormalRotated.x, crvNormalRotated.y, crvNormalRotated.z );
				glVertex3f((float)crvPoint.x + (crvNormalRotated.x*radius),
						   (float)crvPoint.y + (crvNormalRotated.y*radius),
						   (float)crvPoint.z + (crvNormalRotated.z*radius));				
			}
			glEnd();
		}
		glPopAttrib();
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                  END WIREFRAME 
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
//	glEnable(GL_LIGHT0);
	view.endGL();
}