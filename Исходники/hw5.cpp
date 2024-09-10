/************************************************************************************
* Function name: findPixelLocationWithGivenValue
* Input: image, pixelvalue, foundRow, foundCol
* Output: whether a seed pixel has been found, row/column of the found seed pixel
* Description: This function sorts through the image searching for the locations of
* the circles and squares. It returns a true if it was able to find a pixel with
* the appropriate value.
*************************************************************************************/
bool findPixelLocationWithGivenValue(const Image &image, int pixelValue, int &foundRow, int &foundCol)
{
    int i,j;//i = rows, j = cols

    for(i = 0; i < image.getNumRows(); i++)
    {
        for(j = 0; j < image.getNumCols(); j++)
        {
            if(image.getPixel(i,j) == pixelValue)//Check if pixel value (255) found
            {
                foundRow = i;
                foundCol = j;
                return true;
            }
        }
    }
    return false;
}