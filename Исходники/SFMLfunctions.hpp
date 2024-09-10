void VertFlip(Image & Pic)
{
    Color Temp;

    for(unsigned int y = 1; y < Pic.GetHeight()/2; y++)
        for(unsigned int x = 1; x < Pic.GetWidth(); x++)
        {
            Temp = Pic.GetPixel(x, y);
            Pic.SetPixel(x, y, Pic.GetPixel(x, Pic.GetHeight() - y));
            Pic.SetPixel(x, Pic.GetHeight() - y, Temp);
        }
}