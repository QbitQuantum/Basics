void code_qr::decoder(Mat& img_qr, string& message){
	ImageScanner scanner;
      	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
	Mat img;
	img_qr.copyTo(img);
	//if( !img.data ){
          	//return 0;
      	//}
	Mat imgout;
      	cvtColor(img,imgout,CV_GRAY2RGB);
      	int width = img.cols;
      	int height = img.rows;
   	uchar *raw = (uchar *)img.data;
	Image image(width, height, "Y800", raw, width * height);
	int n = scanner.scan(image);
	for(Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol) {
		message = symbol->get_data();	     	
		//cout << "decoded " << symbol->get_type_name()<< " symbol \"" << symbol->get_data() << '"' <<" "<< endl;
		
	}
	image.set_data(NULL, 0);

}