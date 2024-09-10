void ColorizeOperator::process(int tick)
{
    if (texture == 0)
        texture = new Texture();

    Texture* srcTexture = getInput(0)->texture;
    texture->lock();
    srcTexture->lock();

    float hue = getByteProperty(0) / 256.0f;
    float saturation = getByteProperty(1) / 256.0f ;
    float light = (getByteProperty(2) - 128) / 128.0f;

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
        {
            float h, s, l;
            D3DCOLOR srcColor = srcTexture->getPixel(x, y);
            RGB2HSL(D3DCOLOR_R(srcColor),
                    D3DCOLOR_G(srcColor),
                    D3DCOLOR_B(srcColor),
                    h,
                    s,
                    l);
            int r, g, b;
            HSL2RGB(hue, saturation, l + light, r, g, b);
            texture->putPixel(x, y, D3DCOLOR_XRGB(r, g, b));
        }
    }

    texture->unlock();
    srcTexture->unlock();
    texture->setDirty();
}