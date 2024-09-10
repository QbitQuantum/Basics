void CAnim::Play(UINT AnimName,CRect rect,BOOL Static,int Loop,BOOL Transparent,int Rate,
                 CPoint Dest,short FuncIndex,BYTE* CBParam,int ParamSize,CRect BackAnim,
                 int LoopStartFrame, int Frames)
{
  if (Rate != 6 && Rate != 12)
  {
    //the animation can play only in 6.25 and 12.5 fps
    ASSERT(0);
  }

  m_nRate = Rate;
  m_bSkipFrame = TRUE;

  if (m_bPlaying)
  {
      Close (TRUE,TRUE);
  }

  m_bPlaying=TRUE;

  //load the bitmap    from gif
  m_pBitmap=NULL;

  int PictNum=FindPicture(AnimName);

  if (PictNum!=-1)
  {
    m_pBitmap=m_aBitmaps[PictNum];
    m_nBMWidth =m_aBitmapSize[PictNum].cx;
    m_nBMHeight=m_aBitmapSize[PictNum].cy;
    m_aPictUsageCount[PictNum]++;
  }
  else
  {
    BITMAP      mybm;
    LoadPicture(AnimName);
    m_pBitmap->GetObject(sizeof(BITMAP),&mybm);
    m_nBMWidth=mybm.bmWidth;
    m_nBMHeight=mybm.bmHeight;
  }

  ASSERT(m_pBitmap);

  //if transparent make the mask bitmap
  if (Transparent)
  {
    if (PictNum == -1 || m_aMaskBitmaps[PictNum]==NULL)
    {
      CDC  BmpDC;
      CDC  MaskDC;

      BmpDC.CreateCompatibleDC(NULL);
      COLORREF BgColor=BmpDC.SetBkColor(RGB(0,0,0));
      CBitmap * pOldBmp=BmpDC.SelectObject(m_pBitmap);

      m_pMaskBitmap=new(CBitmap);
      m_pMaskBitmap->CreateBitmap(((m_nBMWidth+7)/8)*8,
                                    ((m_nBMHeight+7)/8)*8,
                                    1,1,NULL);
      MaskDC.CreateCompatibleDC(NULL);
      CBitmap * pOldmask=MaskDC.SelectObject(m_pMaskBitmap);
      BOOL ret5=MaskDC.BitBlt(0,0,
                                m_nBMWidth,
                                m_nBMHeight,
                                &BmpDC,0,0,SRCCOPY);

      MaskDC.SelectObject(pOldmask);
      BmpDC.SetBkColor(BgColor);
      BmpDC.SelectObject(pOldBmp);
    }
    else
    {
      ASSERT(m_aMaskBitmaps[PictNum]);
      m_pMaskBitmap=m_aMaskBitmaps[PictNum];
    }

    if (Static)
    {
       CDC*    pDC;
       CDC  BackgroundDC;
       CDC  BackImageDC;
       CBitmap* pBackImage;
       CUbqGamePiece* p;
       CUbqMultImage* m;
       CObject* o;

       pDC=m_pWnd->GetDC();

       CPalette* OldPal= pDC->SelectPalette(&(CBmp::m_cPalette),FALSE);
       pDC->RealizePalette();

       BackgroundDC.CreateCompatibleDC(pDC);
       BackImageDC.CreateCompatibleDC(pDC);
       m_pBackgroundBitmap=new(CBitmap);
       m_pBackgroundBitmap->CreateCompatibleBitmap(pDC,
                                                   rect.Width(),
                                                   rect.Height());

       CBitmap* pOldBg =BackgroundDC.SelectObject(m_pBackgroundBitmap);

       //copying the background image
       pBackImage=&((CUbqGameBoard*)m_pWnd)->m_cBoardBmp;
       //pBackImage=((CUbqGameBoard*)m_pWnd)->m_pImageBoard->m_picture.GetBitmap();

       CBitmap* pOldBg2=BackImageDC.SelectObject(pBackImage);

       BOOL ret=BackgroundDC.BitBlt(0,0,
                              rect.Width(),
                              rect.Height(),
                              &BackImageDC,
                              rect.left,
                              rect.top,
                              SRCCOPY);

       BackImageDC.SelectObject(pOldBg2);

       //copying the pieces
       int size = ((CUbqGameBoard*)m_pWnd)->m_vecPieces.GetSize();
       for (int i=0; i<size; i++)  // bottom to top to preserve Z order
       {
         o = ((CUbqGameBoard*)m_pWnd)->m_vecPieces.GetAt(i);
         p = (CUbqGamePiece*) o;
         if ((p->GetAttribute() & PA_INVISIBLE) == 0 && ( p != ((CUbqGameBoard*)m_pWnd)->m_pDraggedPiece ))
         {
           CRect  rIntersect;
           if (rIntersect.IntersectRect(rect,p->m_rArea))
           {
             CPoint ap=p->m_rArea.TopLeft();
#ifdef WIN32
             ap-=rect.TopLeft();
#else
             ap.x-=rect.TopLeft().x;
             ap.y-=rect.TopLeft().y;
#endif
             (((CUbqGameBoard*)m_pWnd)->m_pApplet)->DrawImage(p->m_pImage,ap,BackgroundDC);
           }
         }
       }

       //copying the multi images
       size = ((CUbqGameBoard*)m_pWnd)->m_vecMultipleImages.GetSize();
       for (i=0; i<size; i++)  // bottom to top to preserve Z order
       {
         o = ((CUbqGameBoard*)m_pWnd)->m_vecMultipleImages.GetAt(i);
         m = (CUbqMultImage*) o;

         CRect  rIntersect;
         if (rIntersect.IntersectRect(rect,m->m_rArea))
         {
           CPoint ap=m->m_rArea.TopLeft();
#ifdef WIN32
           ap-=rect.TopLeft();
#else
           ap.x-=rect.TopLeft().x;
           ap.y-=rect.TopLeft().y;
#endif
           (((CUbqGameBoard*)m_pWnd)->m_pApplet)->DrawImage(m->GetCurrImage(),ap,BackgroundDC);
         }
       }

       BackgroundDC.SelectObject(pOldBg);

       pDC->SelectPalette(OldPal,FALSE);
       pDC->RealizePalette();

       m_pWnd->ReleaseDC(pDC);
    }
  }

  //save parameters
  m_rArea=rect;
  m_cEndPoint=Dest;
  m_cCurrPoint=m_cStartPoint=rect.TopLeft();
  m_bStatic=Static;
  m_nLoopStartFrame = LoopStartFrame;
  m_nLoops=Loop;
  if (m_nLoops==0)  //loops 0 is realy 1
    m_nLoops++;
  if (m_nLoops!=1 && !m_bStatic)
    ASSERT(0);
  m_nFuncIndex = FuncIndex;
  m_bTransparent=Transparent;
  if (ParamSize>0)
  {
     m_nCBParamSize=ParamSize;
     m_pCBParam=new BYTE[ParamSize];
     if (!m_pCBParam)
       ASSERT(0);
     memcpy(m_pCBParam,CBParam,ParamSize);
  }
  else
    m_pCBParam=NULL;
  m_rBackAnim=BackAnim;

  //add to list of gifs
  if (PictNum == -1)
  {
    BOOL Found=FALSE;
    for(int i=0;i<MAX_ANIM_GIFS && !Found;i++)
    {
      if (m_aPictName[i]==0)
      {
        m_aPictName[i]=AnimName;
          Found=TRUE;
          m_aPictUsageCount[i]=1;
        m_aBitmaps[i]=m_pBitmap;
        PictNum=i;
      }
    }
  }
  if (m_aMaskBitmaps[PictNum] == NULL && m_pMaskBitmap != NULL) //this is done here due to preloaded bitmaps
    m_aMaskBitmaps[PictNum]=m_pMaskBitmap;

  //do some calculations ...
  if (Frames)
  {
    m_nLastFrame=Frames;
    m_bOneFrame=TRUE;
  }
  else
  {
    m_nLastFrame=m_nBMHeight/m_rArea.Height();
    m_bOneFrame=FALSE;
  }
  m_nFrame=0;
  m_bClosing=FALSE;

  // draw the first frame
  NextFrame();

  //register the animation vector
  AnimTimer.AddAnim((CObject *)this,BackAnim!=CRect(0,0,0,0));
}