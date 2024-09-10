/**
 * draws the tree from the TreeDrawer into a volumetric 3D
 * image as a series of 2D png slices
 */
void drawImage(TreeDrawer * td, const char* rootName){
	typedef unsigned char PixelType;
	const unsigned int Dimension = 3;
	typedef itk::Image< PixelType, Dimension > ImageType;

	ImageType::Pointer image = ImageType::New();

	ImageType::SizeType size;
	size[0] = td->dim[0]; // size along X
	size[1] = td->dim[1]; // size along Y
	size[2] = td->dim[2]; // size along Z

	ImageType::IndexType start;
	start[0] = 0; // first index on X
	start[1] = 0; // first index on Y
	start[2] = 0; // first index on Z

	ImageType::RegionType region;
	region.SetSize( size );
	region.SetIndex( start );

	image->SetRegions( region );
	image->Allocate();
	
	ImageType::IndexType pixelIndex;
	pixelIndex[0] = 0; // x position
	pixelIndex[1] = 0; // y position
	pixelIndex[2] = 0; // z position

	for(int i = 0; i < td->dim[0]; i++){
		for(int j = 0; j < td->dim[1]; j++){
			for(int k = 0 ; k < td->dim[2]; k++){
				pixelIndex[0] = i;
				pixelIndex[1] = j;
				pixelIndex[2] = k;
				
				image->SetPixel(pixelIndex, td->imageAt(i, j, k));
			}
		}
	}


	typedef itk::Image< unsigned char, 2 > Image2DType;
	typedef itk::ImageSeriesWriter< ImageType, Image2DType > WriterType;
	WriterType::Pointer writer = WriterType::New();
	writer->SetInput( image);

	typedef itk::NumericSeriesFileNames NameGeneratorType;
	NameGeneratorType::Pointer nameGenerator = NameGeneratorType::New();

	std::string format = rootName;
	format += "%03d";
	format += ".jpg";
	nameGenerator->SetSeriesFormat( format.c_str() );

	const unsigned int firstSlice = start[2];
	const unsigned int lastSlice = start[2] + size[2] - 1;
	nameGenerator->SetStartIndex( firstSlice );
	nameGenerator->SetEndIndex( lastSlice );
	nameGenerator->SetIncrementIndex( 1 );

	writer->SetFileNames( nameGenerator->GetFileNames() );

	try{
		writer->Update();
	}catch( itk::ExceptionObject & excp ){
        
        throw "Exception thrown while reading the image";
        
	}

	return;
}