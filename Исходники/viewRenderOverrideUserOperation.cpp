/*
	Some simple code to draw a wireframe bounding box
	in OpenGL
*/
void
MCustomSceneDraw::drawBounds( const MDagPath &dagPath,
							  const MBoundingBox &box)
{
	MMatrix  matrix = dagPath.inclusiveMatrix();
	MPoint	minPt = box.min();
	MPoint	maxPt = box.max();

	double bottomLeftFront[3] =		{ minPt.x, minPt.y, minPt.z };
	double topLeftFront[3] = 		{ minPt.x, maxPt.y, minPt.z };
	double bottomRightFront[3] =	{ maxPt.x, minPt.y, minPt.z };
	double topRightFront[3] =		{ maxPt.x, maxPt.y, minPt.z };
	double bottomLeftBack[3] =		{ minPt.x, minPt.y, maxPt.z };
	double topLeftBack[3] =			{ minPt.x, maxPt.y, maxPt.z };
	double bottomRightBack[3] =		{ maxPt.x, minPt.y, maxPt.z };
	double topRightBack[3] =		{ maxPt.x, maxPt.y, maxPt.z };

	gGLFT->glMatrixMode( MGL_MODELVIEW );
	gGLFT->glPushMatrix();
	gGLFT->glMultMatrixd( &(matrix.matrix[0][0]) );

	gGLFT->glBegin(MGL_LINE_STRIP);
	gGLFT->glVertex3dv( bottomLeftFront );
	gGLFT->glVertex3dv( bottomLeftBack );
	gGLFT->glVertex3dv( topLeftBack );
	gGLFT->glVertex3dv( topLeftFront );
	gGLFT->glVertex3dv( bottomLeftFront );
	gGLFT->glVertex3dv( bottomRightFront );
	gGLFT->glVertex3dv( bottomRightBack);
	gGLFT->glVertex3dv( topRightBack );
	gGLFT->glVertex3dv( topRightFront );
	gGLFT->glVertex3dv( bottomRightFront );
	gGLFT->glEnd();

	gGLFT->glBegin(MGL_LINES);
	gGLFT->glVertex3dv(bottomLeftBack);
	gGLFT->glVertex3dv(bottomRightBack);

	gGLFT->glVertex3dv(topLeftBack);
	gGLFT->glVertex3dv(topRightBack);

	gGLFT->glVertex3dv(topLeftFront);
	gGLFT->glVertex3dv(topRightFront);
	gGLFT->glEnd();

	gGLFT->glPopMatrix();
}