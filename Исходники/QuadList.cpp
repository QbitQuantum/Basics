void QuadList::addQuad(float *quadvertices, float *quadtexcoords)
{
	// Allocate more memory and copy data
	float *newvertices = new float[vertexcount * 3 + 12];
	memcpy(newvertices, vertices, vertexcount * 3 * sizeof(float));
	if (vertices)
		delete[] vertices;
	vertices = newvertices;
	newvertices = &vertices[vertexcount * 3];
	memcpy(newvertices, quadvertices, 12 * sizeof(float));
	float *newtexcoords = new float[vertexcount * 2 + 8];
	memcpy(newtexcoords, texcoords, vertexcount * 2 * sizeof(float));
	if (texcoords)
		delete[] texcoords;
	texcoords = newtexcoords;
	newtexcoords = &texcoords[vertexcount * 2];
	memcpy(newtexcoords, quadtexcoords, 8 * sizeof(float));
	vertexcount += 4;
	// Set initial bounding rectangle if this is the first quad
	if (vertexcount == 4)
	{
		boundingrect.x = newvertices[0];
		boundingrect.y = newvertices[1];
	}
	// Increase bounding rectangle
	boundingrect.insertPoint(Vector2F(newvertices[0], newvertices[1]));
	boundingrect.insertPoint(Vector2F(newvertices[3], newvertices[4]));
	boundingrect.insertPoint(Vector2F(newvertices[6], newvertices[7]));
	boundingrect.insertPoint(Vector2F(newvertices[9], newvertices[10]));
}