bool TextureIO::saveTexture(const string &imgPath, const Texture &texture, bool flip)
{
    Mat outMat(texture.getHeight(), texture.getWidth(), CV_8UC4);
    texture.bind(); 
    glGetTexImage( GL_TEXTURE_2D, 0, GL_BGRA, GL_UNSIGNED_BYTE, outMat.data );
    
    if(flip){cv::flip(outMat, outMat, 0);}
    return imwrite(imgPath, outMat);
}