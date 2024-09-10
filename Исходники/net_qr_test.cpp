/**
 * This is a (modified) test program written by Michael Young
 * (https://github.com/ayoungprogrammer/WebcamCodeScanner). It was modified to
 * work with the Raspicam.
 */
int main(int argc, char* argv[])
{
	PiCamera cam; // open the video camera no. 0
	ImageScanner scanner;  
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);  

	namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

	while (1)
	{
		Mat frame = cam.Snap();
		Mat grey;
		cvtColor(frame,grey,CV_BGR2GRAY);

		int width = frame.cols;  
		int height = frame.rows;  
		uchar *raw = (uchar *)grey.data;  
		// wrap image data  
		zbar::Image image(width, height, "Y800", raw, width * height);  
		// scan the image for barcodes  
		int n = scanner.scan(image);  
		// extract results  
		for(Image::SymbolIterator symbol = image.symbol_begin();  
				symbol != image.symbol_end();  
				++symbol) {  
			vector<Point> vp;  
			// do something useful with results  
			cout << "decoded " << symbol->get_type_name()  << " symbol \"" << symbol->get_data() << '"' <<" "<< endl;  
			int n = symbol->get_location_size();  
			for(int i=0;i<n;i++){  
				vp.push_back(Point(symbol->get_location_x(i),symbol->get_location_y(i))); 
			}  
			RotatedRect r = minAreaRect(vp);  
			Point2f pts[4];  
			r.points(pts);  
			for(int i=0;i<4;i++){  
				line(frame,pts[i],pts[(i+1)%4],Scalar(255,0,0),3);  
			}  
		}  

		imshow("MyVideo", frame); //show the frame in "MyVideo" window

		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break; 
		}
	}
	return 0;

}