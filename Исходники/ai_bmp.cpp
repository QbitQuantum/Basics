/********************************************************************************************

>	BOOL AIBitmapProcessor::DecodeXI( AI5EPSFilter& filter )

	Author:		Colin_Barfoot (Xara Group Ltd) <*****@*****.**>
	Created:	23/03/00
	Returns:	TRUE if the definition was processed, 
				FALSE if not used by this filter..
	Purpose:	Decodes the EPS XI, bitmap definition in an Illustrator 5 file

	The format of the operator is:

	[ a b c d tx ty ] llx lly urx ury h w bits ImageType AlphaChannelCount reserved bin-ascii ImageMask XI

********************************************************************************************/
BOOL AIBitmapProcessor::DecodeXI( AI5EPSFilter& filter )
{
	// Graeme (18/4/00) - This code isn't very pretty, but it's necessary because of the way
	// in which the bitmap is stored. If I try a GetCoordPair () to get the bitmap positions,
	// the image will be misrendered because the transformation should take place due to the
	// tx and ty components of the matrix. Note also that the bitmap's position in Adobe
	// Illustrator is taken from the top left corner, whilst we use the bottom left.

	/////////////////
	// Get the page origin.
	/////////////////

	// Graeme (18/4/00) - Declare variables to get the origin of the page within Camelot's
	// co-ordinate space.
	Document	*pDocument	= filter.GetDocument ();
	Spread		*pSpread	= pDocument->FindFirstSpread ();
	Page		*pPage		= pSpread->FindFirstPageInSpread ();
	DocCoord	Origin		= pPage->GetPageRect ().lo;

	/////////////////
	// decode the bitmap parameters
	/////////////////

	Matrix ImageMatrix;
	DocCoord Translation;

	INT32 h, w, bits, ImageType, AlphaChannelCount, reserved, bin_ascii, ImageMask;
	INT32 llx, lly, urx, ury;

	INT32 nLength = 0;
	INT32 nLineLength = 0;
	INT32 nMaxLineOffset = 0;

	INT32 nChannels = 0;

	NodeBitmap* pNodeBitmap = NULL;
	DocCoord p;

	// Graeme (18/4/00) - I've replaced the Pop with PopCoordPair for extracting the
	// bounding co-ordinates of the bitmap. This means that they will be scaled up
	// into the Xara co-ordinate space. I've also reversed the popping of h and w
	// from the stack - their order is incorrect in the AI documentation.
	if (	!filter.GetStack().Pop(&ImageMask) 	  || 
			!filter.GetStack().Pop(&bin_ascii) || 
			!filter.GetStack().Pop(&reserved) || 
			!filter.GetStack().Pop(&AlphaChannelCount) || 
			!filter.GetStack().Pop(&ImageType) || 
			!filter.GetStack().Pop(&bits) || 
			!filter.GetStack().Pop(&h) || 
			!filter.GetStack().Pop(&w) || 
			!filter.GetStack().PopCoord(&ury) || 
			!filter.GetStack().PopCoord(&urx) || 
			!filter.GetStack().PopCoord(&lly) || 
			!filter.GetStack().PopCoord(&llx) || 
			!filter.GetStack().Pop( &ImageMatrix, TRUE )
		)
		goto EPSError;

	/////////////////
	// create space for the tentative bitmap
	/////////////////

	///////////////////
	//	ImageType gives the number of channels per pixel
	//	bits is the bits per channel
	//	However we will convert CMYK bitmaps to RGB
	///////////////////

	switch ( ImageType )
	{
		case 1:	// greyscale
			nChannels = 1;
			break;
		case 3:	// rgb
			nChannels = 3;
			break;
		case 4:	// CMYK
			nChannels = 3;
			break;
		default: // unknown
			goto EPSError;
	}

	mpNewBitmap = new KernelBitmap( w, h, bits * nChannels, 96 );
	if ( !mpNewBitmap )
		goto EPSError;

	///////////////////
	//	We can import greyscale bitmaps as well
	///////////////////

	if ( ImageType == 1 )
		mpNewBitmap->SetAsGreyscale();


	/////////////////
	// get the binary data
	/////////////////

	nLength = mpNewBitmap->GetActualBitmap()->GetBitmapSize();
	nLineLength = mpNewBitmap->GetActualBitmap()->GetScanlineSize();
	nMaxLineOffset = (( w * mpNewBitmap->GetActualBitmap()->GetBPP() ) / 8) - 1;

	if ( !ReadImageData( filter, ImageType, mpNewBitmap->GetBitmapBits(), nLength, nLineLength, nMaxLineOffset ) )
		goto EPSError;

	/////////////////////
	//	insert the image into the document
	/////////////////////

	// Get a new NodeBitmap object to import into. Don't know what the 12,12 bit does
	pNodeBitmap = new NodeBitmap;

	if ( !pNodeBitmap || !pNodeBitmap->SetUpPath(12,12) )
		goto EPSError;

	pNodeBitmap->GetBitmapRef()->Attach( mpNewBitmap, filter.GetDocument() );

	/////////////////
	//	set up the bounds of the shape containing the bitmap
	/////////////////

	// Graeme (18/4/00) - Adjust the values of lly and ury before they're transformed.
	lly -= h * EPSScaleFactor;
	ury -= h * EPSScaleFactor;

	// Graeme (18/4/00) - Modify the matrix to place the bitmap in the correct place.
	ImageMatrix.GetTranslation ( Translation );		// Extract the translation component.
	Translation += Origin;							// Add the page origin to it.
	ImageMatrix.SetTranslation ( Translation );		// And reset the value in the matrix.

	// Graeme (17/4/00) - Colin overlooked setting up the bounding parallelogram when he
	// wrote this code, and I've just added this.
	p.x = llx;
	p.y = ury;
	ImageMatrix.transform( &p );
	pNodeBitmap->InkPath.InsertMoveTo( p );
	pNodeBitmap->Parallel [0] = p;

	p.x = urx;
	p.y = ury;
	ImageMatrix.transform( &p );
	pNodeBitmap->InkPath.InsertLineTo( p );
	pNodeBitmap->Parallel [1] = p;

	p.x = urx;
	p.y = lly;
	ImageMatrix.transform( &p );
	pNodeBitmap->InkPath.InsertLineTo( p );
	pNodeBitmap->Parallel [2] = p;

	p.x = llx;
	p.y = lly;
	ImageMatrix.transform( &p );
	pNodeBitmap->InkPath.InsertLineTo( p );
	pNodeBitmap->Parallel [3] = p;

	p.x = llx;
	p.y = ury;
	ImageMatrix.transform( &p );
	pNodeBitmap->InkPath.InsertLineTo( p );

	pNodeBitmap->InkPath.CloseSubPath();

	// Graeme (18/4/00) - It is necessary to set the default attributes up for a
	// new node bitmap before inserting it into the tree. Otherwise it's rendered
	// as a greyscale image, even if it is colour, because there's a start colour
	// value set.
	pNodeBitmap->ApplyDefaultBitmapAttrs ( NULL );

	filter.AddNewNode( pNodeBitmap );

	return TRUE;

EPSError:
	if ( mpNewBitmap )
	{
		delete mpNewBitmap;
		mpNewBitmap = 0;
	}

	return FALSE;
}