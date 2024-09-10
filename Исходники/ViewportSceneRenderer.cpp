/******************************************************************************
* Renders the construction grid.
******************************************************************************/
void ViewportSceneRenderer::renderGrid()
{
	if(isPicking())
		return;

	FloatType gridSpacing;
	Box2I gridRange;
	std::tie(gridSpacing, gridRange) = determineGridRange(viewport());
	if(gridSpacing <= 0) return;

	// Determine how many grid lines need to be rendered.
	int xstart = gridRange.minc.x();
	int ystart = gridRange.minc.y();
	int numLinesX = gridRange.size(0) + 1;
	int numLinesY = gridRange.size(1) + 1;

	FloatType xstartF = (FloatType)xstart * gridSpacing;
	FloatType ystartF = (FloatType)ystart * gridSpacing;
	FloatType xendF = (FloatType)(xstart + numLinesX - 1) * gridSpacing;
	FloatType yendF = (FloatType)(ystart + numLinesY - 1) * gridSpacing;

	// Allocate vertex buffer.
	int numVertices = 2 * (numLinesX + numLinesY);
	std::unique_ptr<Point3[]> vertexPositions(new Point3[numVertices]);
	std::unique_ptr<ColorA[]> vertexColors(new ColorA[numVertices]);

	// Build lines array.
	ColorA color = Viewport::viewportColor(ViewportSettings::COLOR_GRID);
	ColorA majorColor = Viewport::viewportColor(ViewportSettings::COLOR_GRID_INTENS);
	ColorA majorMajorColor = Viewport::viewportColor(ViewportSettings::COLOR_GRID_AXIS);

	Point3* v = vertexPositions.get();
	ColorA* c = vertexColors.get();
	FloatType x = xstartF;
	for(int i = xstart; i < xstart + numLinesX; i++, x += gridSpacing, c += 2) {
		*v++ = Point3(x, ystartF, 0);
		*v++ = Point3(x, yendF, 0);
		if((i % 10) != 0)
			c[0] = c[1] = color;
		else if(i != 0)
			c[0] = c[1] = majorColor;
		else
			c[0] = c[1] = majorMajorColor;
	}
	FloatType y = ystartF;
	for(int i = ystart; i < ystart + numLinesY; i++, y += gridSpacing, c += 2) {
		*v++ = Point3(xstartF, y, 0);
		*v++ = Point3(xendF, y, 0);
		if((i % 10) != 0)
			c[0] = c[1] = color;
		else if(i != 0)
			c[0] = c[1] = majorColor;
		else
			c[0] = c[1] = majorMajorColor;
	}
	OVITO_ASSERT(c == vertexColors.get() + numVertices);

	// Render grid lines.
	setWorldTransform(viewport()->gridMatrix());
	if(!_constructionGridGeometry || !_constructionGridGeometry->isValid(this))
		_constructionGridGeometry = createLinePrimitive();
	_constructionGridGeometry->setVertexCount(numVertices);
	_constructionGridGeometry->setVertexPositions(vertexPositions.get());
	_constructionGridGeometry->setVertexColors(vertexColors.get());
	_constructionGridGeometry->render(this);
}