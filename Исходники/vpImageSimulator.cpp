/*!
  Get the view of the virtual camera. Be carefull, the image I is modified. The projected image is not added as an overlay!
  
  To take into account the projection of several images, a matrix \f$ zBuffer \f$ is given as argument. This matrix contains the z coordinates of all the pixel of the image \f$ I \f$ in the camera frame. During the projection, the pixels are updated if there is no other plan between the camera and the projected image. The matrix \f$ zBuffer \f$ is updated in this case.
  
  \param I : The image used to store the result.
  \param cam : The parameters of the virtual camera.
  \param zBuffer : A matrix containing the z coordinates of the pixels of the image \f$ I \f$
*/
void
vpImageSimulator::getImage(vpImage<vpRGBa> &I, const vpCameraParameters &cam, 
			   vpMatrix &zBuffer)
{
  if (I.getWidth() != (unsigned int)zBuffer.getCols() || I.getHeight() != (unsigned int)zBuffer.getRows())
    throw (vpMatrixException(vpMatrixException::incorrectMatrixSizeError, " zBuffer must have the same size as the image I ! "));
  
  if (cleanPrevImage)
  {
    for (unsigned int i = 0; i < I.getHeight(); i++)
    {
      for (unsigned int j = 0; j < I.getWidth(); j++)
      {
        I[i][j] = bgColor;
      }
    }
  }
  if(visible)
  {
    if(!needClipping)
      getRoi(I.getWidth(),I.getHeight(),cam,pt,rect);
    else
      getRoi(I.getWidth(),I.getHeight(),cam,ptClipped,rect);
    
    double top = rect.getTop();
    double bottom = rect.getBottom();
    double left = rect.getLeft();
    double right= rect.getRight();
    
    vpRGBa *bitmap = I.bitmap;
    unsigned int width = I.getWidth();
    vpImagePoint ip;
    int nb_point_dessine = 0;

    for (unsigned int i = (unsigned int)top; i < (unsigned int)bottom; i++)
    {
      for (unsigned int j = (unsigned int)left; j < (unsigned int)right; j++)
      {
        double x=0,y=0;
        ip.set_ij(i,j);
        vpPixelMeterConversion::convertPoint(cam,ip, x,y);
        ip.set_ij(y,x);
        if (colorI == GRAY_SCALED)
        {
          unsigned char Ipixelplan;
          if(getPixel(ip,Ipixelplan))
          {
            if (Xinter_optim[2] < zBuffer[i][j] || zBuffer[i][j] < 0)
            {
              vpRGBa pixelcolor;
              pixelcolor.R = Ipixelplan;
              pixelcolor.G = Ipixelplan;
              pixelcolor.B = Ipixelplan;
              *(bitmap+i*width+j) = pixelcolor;
              nb_point_dessine++;
              zBuffer[i][j] = Xinter_optim[2];
            }
          }
        }
        else if (colorI == COLORED)
        {
          vpRGBa Ipixelplan;
          if(getPixel(ip,Ipixelplan))
          {
            if (Xinter_optim[2] < zBuffer[i][j] || zBuffer[i][j] < 0)
            {
              *(bitmap+i*width+j) = Ipixelplan;
              nb_point_dessine++;
              zBuffer[i][j] = Xinter_optim[2];
            }
          }
        }
      }
    }
  }
}