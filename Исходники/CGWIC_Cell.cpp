void CGWIC_Cell::SaveTerrainBitmap()
{
	path flnm = GWIC_TERRAIN_DIR;
	flnm += (GetCellFileSuffix() + ".bmp");
	dimension2d<u32> dim(256,256);
	IImage *img = irDriver->createImage(ECF_R8G8B8,dim);
	u32 VertexCount = terrain->getMesh()->getMeshBuffer(0)->getVertexCount();
	S3DVertex2TCoords* verts = reinterpret_cast<S3DVertex2TCoords*> (terrain->getMesh()->getMeshBuffer(0)->getVertices());
	S3DVertex2TCoords* vertex;
	u8 y;
	u32 x,z;
	for (u32 i=0; i<VertexCount; i++) {
		vertex = verts + i;
		x = static_cast<u32> (vertex->Pos.X);
		y = static_cast<u8> (vertex->Pos.Y);
		z = static_cast<u32> (vertex->Pos.Z);
		img->setPixel(x,z,SColor(0,y,y,y));
	}
	irDriver->writeImageToFile(img,flnm,0);
	img->drop();
	std::cout << "Cell " << posX << ';' << posY << " terrain bitmap saved!" << std::endl;
}