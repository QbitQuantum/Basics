  void MapPainterCanvas::DrawContourLabel(const Projection& projection,
                                          const MapParameter& parameter,
                                          const PathTextStyle& style,
                                          const std::string& text,
                                          size_t transStart, size_t transEnd)
  {
    jmethodID methodId=mJniEnv->GetMethodID(mPainterClass, "drawContourLabel",
                     "(Ljava/lang/String;IFF[F[F)V");
    
    if (!methodId)
      return;

    jstring javaText=mJniEnv->NewStringUTF(text.c_str());

    jint textColor=GetColorInt(style.GetTextColor());

    jfloat pathLenght=0.0;

    int numPoints=transEnd-transStart+1;
    
    float *x=new float[numPoints];
    float *y=new float[numPoints];

    if (transBuffer.buffer[transStart].x<=transBuffer.buffer[transEnd].x)
    {
      // Path orientation is from left to right
      // Direct copy of the data
    
      for(int i=0; i<numPoints; i++)
      {
        x[i]=(float)transBuffer.buffer[transStart+i].x;
        y[i]=(float)transBuffer.buffer[transStart+i].y;

        if (i!=0)
          pathLenght+=sqrt(pow(x[i]-x[i-1], 2.0)+pow(y[i]-y[i-1], 2.0));
      }
    }
    else
    {
      // Path orientation is from right to left
      // Inverse copy of the data

      for(int i=0; i<numPoints; i++)
      {
        x[i]=(float)transBuffer.buffer[transEnd-i].x;
        y[i]=(float)transBuffer.buffer[transEnd-i].y;

        if (i!=0)
          pathLenght+=sqrt(pow(x[i]-x[i-1], 2.0)+pow(y[i]-y[i-1], 2.0));
      }
    }
    
    jfloatArray jArrayX=mJniEnv->NewFloatArray(numPoints);
    jfloatArray jArrayY=mJniEnv->NewFloatArray(numPoints);
    
    mJniEnv->SetFloatArrayRegion(jArrayX, 0, numPoints, x);
    mJniEnv->SetFloatArrayRegion(jArrayY, 0, numPoints, y);
        
    mJniEnv->CallVoidMethod(mPainterObject, methodId, javaText,
                            textColor, (jfloat)style.GetSize(),
                            pathLenght, jArrayX, jArrayY);

    delete x;
    delete y;

    mJniEnv->DeleteLocalRef(jArrayX);
    mJniEnv->DeleteLocalRef(jArrayY);
  }