void QRScanner::init(char *raw, int width,int height){
	// create a reader
	ImageScanner scanner;

	// configure the reader
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

	myImage = new Image(width, height, "Y800", raw, width * height);

	// scan the image for barcodes
	numLines = scanner.scan(*myImage);
}