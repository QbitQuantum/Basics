Texture* TextureReader::read()
{
    verifySignature(reader);
    initialisePNGReader(reader);

    const unsigned char* data = readImageData();
    const unsigned int width = png_get_image_width(_png, _pngInfo);
    const unsigned int height = png_get_image_height(_png, _pngInfo);

    _data = (GLubyte*)data;
    Texture* texture = new Texture(_data, width, height, 0);
    texture->setData(data);
    delete[] data;
    png_destroy_read_struct(&_png, &_pngInfo, NULL);

    return texture;
}