void renderCodeDatamatrix(OROPage *page, const QRectF &qrect, const QString &qstr, ORBarcodeData * bc)
{

	//5 pixel par carré
  //qreal pix = 5;
  //lecture du type de datamatrix
  QRegExp regex("[a-zA-Z]{10}_([0-9]{1,2})_([LCR]{1})");
  regex.indexIn(bc->format);
  int type = regex.cap(1).toInt();
  QString align = regex.cap(2);

	size_t          width, height, bytesPerPixel;

  //pointer declaration
  unsigned char  *pxl = NULL;
  DmtxEncode     *enc = NULL;
  DmtxImage      *img = NULL;
  ORORect        *rect = NULL;
  int valeur = 0;

	/* 1) ENCODE a new Data Matrix barcode image (in memory only) */
	enc = dmtxEncodeCreate();

  //see DmtxSymbolSize in dmtx.h for more details
  enc->sizeIdxRequest = type;
	enc->marginSize = 0;
  //number of pixel for one square
	enc->moduleSize = 1;

  try
  {
    //assert(enc != NULL);
    dmtxEncodeDataMatrix(enc, qstr.size(), (unsigned char*)qstr.toStdString().c_str());

    /* 2) COPY the new image data before releasing encoding memory */

    width = dmtxImageGetProp(enc->image, DmtxPropWidth);
    height = dmtxImageGetProp(enc->image, DmtxPropHeight);
    bytesPerPixel = dmtxImageGetProp(enc->image, DmtxPropBytesPerPixel);

    if(width > 1000000000)
    {
			throw std::runtime_error("Code is to big for the Datamatrix");
    }

    pxl = (unsigned char *)malloc(width * height * bytesPerPixel);
    //assert(pxl != NULL);
    memcpy(pxl, enc->image->pxl, width * height * bytesPerPixel);

    dmtxEncodeDestroy(&enc);

    /* 3) DECODE the Data Matrix barcode from the copied image */
    img = dmtxImageCreate(pxl, width, height, DmtxPack24bppRGB);


    QPen pen(Qt::NoPen);
    QBrush brush(QColor("black"));

    qreal Xo = 0;
    qreal Yo = 0;
    //length of square
    qreal pas = 0;

    datamatrixGeometry(align,qrect,img,&Xo,&Yo,&pas);

    //draw the datamatrix
    for(int y = 0; y < img->height; y++)
    {
      for(int x = 0; x < img->width; x++)
      {
        dmtxImageGetPixelValue(img,x,y,0,&valeur);
        rect = new ORORect(bc);
        rect->setPen(pen);

        if(valeur == 0)
        {
          brush.setColor(Qt::black);
          rect->setBrush(brush);
          rect->setRect(QRectF(	Xo + x*pas,
                                Yo - y*pas,
                                pas,
                                pas));
          rect->setRotationAxis(qrect.topLeft());
          page->addPrimitive(rect);
        }
      }
      delete rect;
    }

    //memory cleanning
    free(pxl);
    dmtxEncodeDestroy(&enc);
    dmtxImageDestroy(&img);
  }
  catch(...)
  {
    //there is a problem with the datamatrix
    //RR is printed
    printRR(page,bc,qrect);

    //memory cleaning
    if(rect != NULL)
    {
      delete rect;
    }
    if(enc != NULL)
    {
      dmtxEncodeDestroy(&enc);
    }
    if(img != NULL)
    {
      dmtxImageDestroy(&img);
    }
    if(pxl!=NULL)
    {
      free(pxl);
    }
  }
}