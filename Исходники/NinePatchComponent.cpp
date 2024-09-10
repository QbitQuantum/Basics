void NinePatchComponent::buildVertices()
{
	if(mVertices != NULL)
		delete[] mVertices;

	if(mColors != NULL)
		delete[] mColors;

	mTexture = TextureResource::get(mPath);

	if(mTexture->getSize() == Eigen::Vector2i::Zero())
	{
		mVertices = NULL;
		mColors = NULL;
		LOG(LogWarning) << "NinePatchComponent missing texture!";
		return;
	}

	mVertices = new Vertex[6 * 9];
	mColors = new GLubyte[6 * 9 * 4];
	updateColors();

	const Eigen::Vector2f ts = mTexture->getSize().cast<float>();

	//coordinates on the image in pixels, top left origin
	const Eigen::Vector2f pieceCoords[9] = {
		Eigen::Vector2f(0,  0),
		Eigen::Vector2f(16, 0),
		Eigen::Vector2f(32, 0),
		Eigen::Vector2f(0,  16),
		Eigen::Vector2f(16, 16),
		Eigen::Vector2f(32, 16),
		Eigen::Vector2f(0,  32),
		Eigen::Vector2f(16, 32),
		Eigen::Vector2f(32, 32),
	};

	const Eigen::Vector2f pieceSizes = getCornerSize();

	//corners never stretch, so we calculate a width and height for slices 1, 3, 5, and 7
	float borderWidth = mSize.x() - (pieceSizes.x() * 2); //should be pieceSizes[0] and pieceSizes[2]
	//if(borderWidth < pieceSizes.x())
	//	borderWidth = pieceSizes.x();

	float borderHeight = mSize.y() - (pieceSizes.y() * 2); //should be pieceSizes[0] and pieceSizes[6]
	//if(borderHeight < pieceSizes.y())
	//	borderHeight = pieceSizes.y();

	mVertices[0 * 6].pos = pieceCoords[0]; //top left
	mVertices[1 * 6].pos = pieceCoords[1]; //top middle
	mVertices[2 * 6].pos = pieceCoords[1] + Eigen::Vector2f(borderWidth, 0); //top right

	mVertices[3 * 6].pos = mVertices[0 * 6].pos + Eigen::Vector2f(0, pieceSizes.y()); //mid left
	mVertices[4 * 6].pos = mVertices[3 * 6].pos + Eigen::Vector2f(pieceSizes.x(), 0); //mid middle
	mVertices[5 * 6].pos = mVertices[4 * 6].pos + Eigen::Vector2f(borderWidth, 0); //mid right

	mVertices[6 * 6].pos = mVertices[3 * 6].pos + Eigen::Vector2f(0, borderHeight); //bot left
	mVertices[7 * 6].pos = mVertices[6 * 6].pos + Eigen::Vector2f(pieceSizes.x(), 0); //bot middle
	mVertices[8 * 6].pos = mVertices[7 * 6].pos + Eigen::Vector2f(borderWidth, 0); //bot right

	int v = 0;
	for(int slice = 0; slice < 9; slice++)
	{
		Eigen::Vector2f size;

		//corners
		if(slice == 0 || slice == 2 || slice == 6 || slice == 8)
			size = pieceSizes;

		//vertical borders
		if(slice == 1 || slice == 7)
			size << borderWidth, pieceSizes.y();

		//horizontal borders
		if(slice == 3 || slice == 5)
			size << pieceSizes.x(), borderHeight;

		//center
		if(slice == 4)
			size << borderWidth, borderHeight;

		//no resizing will be necessary
		//mVertices[v + 0] is already correct
		mVertices[v + 1].pos = mVertices[v + 0].pos + size;
		mVertices[v + 2].pos << mVertices[v + 0].pos.x(), mVertices[v + 1].pos.y();

		mVertices[v + 3].pos << mVertices[v + 1].pos.x(), mVertices[v + 0].pos.y();
		mVertices[v + 4].pos = mVertices[v + 1].pos;
		mVertices[v + 5].pos = mVertices[v + 0].pos;

		//texture coordinates
		//the y = (1 - y) is to deal with texture coordinates having a bottom left corner origin vs. verticies having a top left origin
		mVertices[v + 0].tex << pieceCoords[slice].x() / ts.x(), 1 - (pieceCoords[slice].y() / ts.y());
		mVertices[v + 1].tex << (pieceCoords[slice].x() + pieceSizes.x()) / ts.x(), 1 - ((pieceCoords[slice].y() + pieceSizes.y()) / ts.y());
		mVertices[v + 2].tex << mVertices[v + 0].tex.x(), mVertices[v + 1].tex.y();

		mVertices[v + 3].tex << mVertices[v + 1].tex.x(), mVertices[v + 0].tex.y();
		mVertices[v + 4].tex = mVertices[v + 1].tex;
		mVertices[v + 5].tex = mVertices[v + 0].tex;

		v += 6;
	}

	// round vertices
	for(int i = 0; i < 6*9; i++)
	{
		mVertices[i].pos = roundVector(mVertices[i].pos);
	}
}