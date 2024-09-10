bool TerrainClass::LoadHeightMap(char* filename)
{
    FILE* filePtr;
    int error;
    unsigned int count;
    BITMAPFILEHEADER bitmapFileHeader;
    BITMAPINFOHEADER bitmapInfoHeader;
    int imageSize, i, j, k, index;
    unsigned char* bitmapImage;
    unsigned char height;


    // Open the height map file in binary.
    error = fopen_s(&filePtr, filename, "rb");
    if(error != 0)
    {
        return false;
    }

    // Read in the file header.
    count = fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
    if(count != 1)
    {
        return false;
    }

    // Read in the bitmap info header.
    count = fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
    if(count != 1)
    {
        return false;
    }

    // Save the dimensions of the terrain.
    m_terrainWidth = bitmapInfoHeader.biWidth;
    m_terrainHeight = bitmapInfoHeader.biHeight;

    // Calculate the size of the bitmap image data.
    imageSize = m_terrainWidth * m_terrainHeight * 3;

    // Allocate memory for the bitmap image data.
    bitmapImage = new unsigned char[imageSize];
    if(!bitmapImage)
    {
        return false;
    }

    // Move to the beginning of the bitmap data.
    fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

    // Read in the bitmap image data.
    count = fread(bitmapImage, 1, imageSize, filePtr);
    if(count != imageSize)
    {
        return false;
    }

    // Close the file.
    error = fclose(filePtr);
    if(error != 0)
    {
        return false;
    }

    // Create the structure to hold the height map data.
    m_heightMap = new HeightMapType[m_terrainWidth * m_terrainHeight];
    if(!m_heightMap)
    {
        return false;
    }

    // Initialize the position in the image data buffer.
    k=0;

    // Read the image data into the height map.
    for(j=0; j<m_terrainHeight; j++)
    {
        for(i=0; i<m_terrainWidth; i++)
        {
            height = bitmapImage[k];

            index = (m_terrainHeight * j) + i;

            m_heightMap[index].x = (float)i;
            m_heightMap[index].y = (float)height;
            m_heightMap[index].z = (float)j;

            k+=3;
        }
    }

    // Release the bitmap image data.
    delete [] bitmapImage;
    bitmapImage = 0;

    return true;
}