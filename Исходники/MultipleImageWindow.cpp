MultipleImageWindow::MultipleImageWindow(string window_title, int cols, int rows, int flags)
{
    this->window_title= window_title;
    this->cols= cols;
    this->rows= rows;
    namedWindow(window_title, flags);
    moveWindow(window_title, 0, 0);
    // ToDo: detect resolution of desktop and show fullresolution canvas
    this->canvas_width= 1200;
    this->canvas_height= 700;
    this->canvas= Mat(this->canvas_height, this->canvas_width, CV_8UC3);     
    imshow(this->window_title, this->canvas);
}