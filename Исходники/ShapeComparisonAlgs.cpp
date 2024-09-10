double ShapeComparisonAlgs::calculateCommonBlackAndWhitePixels(ImageType::Pointer& im1, ImageType::Pointer& im2)
{
	// Cantidad de negros y blancos
	int cantidad = 0;
	
	for (int i=0; i!=TEMPLATE_SIZE*TEMPLATE_SIZE; i++)
	{
		ImageType::IndexType index;
		index[0] = i/TEMPLATE_SIZE;
		index[1] = i%TEMPLATE_SIZE;
		
		// Si ambos son del mismo color
		if (im1->GetPixel(index) == im2->GetPixel(index))
		{
			cantidad ++;
		}
	}
	
	// Retorna un porcentaje
	return cantidad / ((double)TEMPLATE_SIZE*TEMPLATE_SIZE);
}