void CStandardApertureViewStatic::Draw(CDC* dc)
{
   CCEtoODBDoc* doc = getCamCadDoc();
   CCamCadDocGraph camCadDocGraph(doc);

   static bool writeCcFileForDebugFlag = false;

   if (writeCcFileForDebugFlag)
   {
      //doc->SaveDatafile("C:\\CStandardApertureViewStatic-Debug.cc");
   }

   if (m_camCadFrame == NULL)
   {
      return;
   }

   LOGFONT logFont;
   logFont.lfHeight         = 0;
   logFont.lfWidth          = 0;
   logFont.lfEscapement     = 0;
   logFont.lfOrientation    = 0;
   logFont.lfWeight         = FW_NORMAL;
   logFont.lfItalic         = 0;
   logFont.lfUnderline      = 0;
   logFont.lfStrikeOut      = 0;
   logFont.lfCharSet        = ANSI_CHARSET;
   logFont.lfOutPrecision   = OUT_DEFAULT_PRECIS;
   logFont.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
   logFont.lfQuality        = ANTIALIASED_QUALITY;
   logFont.lfPitchAndFamily = DEFAULT_PITCH || FF_SWISS;
   strncpy(logFont.lfFaceName,"Microsoft Sans Serif",LF_FACESIZE);

   CSize windowExtents = dc->GetWindowExt();
   CPoint windowOrigin = dc->GetWindowOrg();

   for (int displayLayerIndex = 0;displayLayerIndex < m_camCadFrame->getDisplayedLayerCount();displayLayerIndex++)
   {
      int layerIndex = m_camCadFrame->getDisplayedLayerIndex(displayLayerIndex);
      LayerStruct* layer = doc->getLayerAt(layerIndex);

      bool stencilLayerFlag = ((layer->getName().CompareNoCase(QDimStencilPad)    == 0) ||
                               (layer->getName().CompareNoCase(QBrightStencilPad) == 0)    );

      for (POSITION filePos = doc->getFileList().GetHeadPosition();filePos != NULL;)
      {
         FileStruct *file = doc->getFileList().GetNext(filePos);

         if (!file->isShown() || file->isHidden() || file->notPlacedYet())
            continue;

         if (file->getBlock() == NULL)
            continue;

         CTMatrix matrix;
         matrix.translateCtm(file->getInsertX(),file->getInsertY());
         matrix.rotateRadiansCtm(file->getRotation());
         matrix.scale(file->getScale(),file->getScale());

         double fileX = file->getInsertX();
         double fileRot = file->getRotation();
         int fileMirror = (doc->getBottomView() ? MIRROR_FLIP : 0) ^ (file->isMirrored() ? MIRROR_FLIP | MIRROR_LAYERS : 0);
         if (doc->getBottomView())
         {
            fileX = -fileX;
            fileRot = -fileRot;
            matrix.scale(-1.,1.);
         }

         matrix.scale(1./m_scaleFactor,1./m_scaleFactor);
         matrix.translate(-windowExtents.cx * m_scaleFactor/2.,-windowExtents.cy * m_scaleFactor/2.);

         Mat2x2 m;
         RotMat2(&m, fileRot);
         
         for (POSITION dataPos = file->getBlock()->getDataList().GetHeadPosition();dataPos != NULL;)
         {
            DataStruct *data = file->getBlock()->getDataList().GetNext(dataPos);
            LayerStruct* layerStruct = doc->getLayerAt(data->getLayerIndex());

            if (layerStruct->getLayerIndex() != layerIndex)
            {
               continue;
            }

            switch (data->getDataType())
            {
            case dataTypeText:
               {
                  TextStruct* textStruct = data->getText();
                  dc->SetTextColor(layerStruct->getColor());
                  drawText(dc,textStruct);
               }

               break;

            case dataTypeInsert:
               {
                  switch (data->getInsert()->getInsertType())
                  {
                  case insertTypeUnknown:
                  case insertTypePcbComponent:  
                  case insertTypePcb:
                  case insertTypeDrillTool:
                  case insertTypeSymbol:
                  case insertTypeStencilHole:
                     break;
                     
                  default:
                     continue;
                  }

                  if (data->getInsert()->getPlacedBottom() ^ (doc->getBottomView() != 0))
                     continue;

                  BlockStruct *subblock = doc->Find_Block_by_Num(data->getInsert()->getBlockNumber());

                  Point2 point2;
                  point2.x = data->getInsert()->getOriginX() * file->getScale();
                  if (fileMirror & MIRROR_FLIP)
                     point2.x = -point2.x;
                  point2.y = data->getInsert()->getOriginY() * file->getScale();
                  TransPoint2(&point2, 1, &m, fileX, file->getInsertY());

                  if ( (subblock->getFlags() & BL_TOOL) || (subblock->getFlags() & BL_BLOCK_TOOL) ||
                        (subblock->getFlags() & BL_APERTURE) || (subblock->getFlags() & BL_BLOCK_APERTURE) )
                  {
                     dc->SetPixelV(round(point2.x / m_scaleFactor), round(point2.y / m_scaleFactor), doc->get_layer_color(data->getLayerIndex(), fileMirror));
                  }
                  else if (subblock->extentIsValid())
                  {
                     double _rot;
                     if (fileMirror & MIRROR_FLIP)
                        _rot = fileRot - data->getInsert()->getAngle();
                     else
                        _rot = fileRot + data->getInsert()->getAngle();
                     int _mirror = fileMirror ^ data->getInsert()->getMirrorFlags();
                     double _scale = file->getScale() * data->getInsert()->getScale();


                     double xmin, xmax, ymin, ymax;
                     TransformInsertExtents(&xmin, &xmax, &ymin, &ymax, subblock, point2.x, point2.y, _scale, _rot, _mirror);
      
                     HPEN orgPen, hPen;
                     HBRUSH orgBrush;
                     hPen = CreatePen(PS_SOLID, 0, doc->getSettings().HideDetailColor);
                     orgPen = (HPEN) SelectObject(dc->m_hDC, hPen);
                     orgBrush = (HBRUSH) dc->SelectStockObject(HOLLOW_BRUSH);
                     dc->Rectangle(round(xmin / m_scaleFactor), round(ymax / m_scaleFactor), round(xmax / m_scaleFactor), round(ymin / m_scaleFactor));
                     DeleteObject(SelectObject(dc->m_hDC, orgPen));
                     SelectObject(dc->m_hDC, orgBrush);
                  }
               }
               break;

            case dataTypePoint:
               {
                  if (!doc->FindLayer(data->getLayerIndex())->isWorldView())
                     continue;

                  Point2 point2;
                  point2.x = data->getPoint()->x * file->getScale();
                  if (fileMirror)
                     point2.x = -point2.x;
                  point2.y = data->getPoint()->y * file->getScale();
                  TransPoint2(&point2, 1, &m, fileX, file->getInsertY());

                  dc->SetPixelV(round(point2.x / m_scaleFactor), round(point2.y / m_scaleFactor), doc->get_layer_color(data->getLayerIndex(), fileMirror));
               }
               break;

            case dataTypePoly:
               {
                  COLORREF layerColor = doc->get_layer_color(data->getLayerIndex(), fileMirror);
                  int widthIndex = -2;

                  HPEN orgPen, hPen;
                  hPen = CreatePen(PS_SOLID, 0, layerColor);
                  orgPen = (HPEN) SelectObject(dc->m_hDC, hPen);

                  HBRUSH originalBrush,brush;

                  if (stencilLayerFlag)
                  {
                     brush = CreateHatchBrush(HS_DIAGCROSS,layerColor);
                  }
                  else
                  {
                     brush = CreateSolidBrush(layerColor);
                  }

                  originalBrush = (HBRUSH)SelectObject(dc->m_hDC,brush);

                  POSITION polyPos = data->getPolyList()->GetHeadPosition();
                  while (polyPos != NULL)
                  {
                     CPoly *poly = data->getPolyList()->GetNext(polyPos);

                     if (poly->getWidthIndex() != widthIndex)
                     {
                        widthIndex = poly->getWidthIndex();
                        double width = doc->getWidth(widthIndex);
                        int pixels = round(width / m_scaleFactor);

                        HPEN hPen = CreatePen(PS_SOLID,pixels, layerColor);
                        DeleteObject(SelectObject(dc->m_hDC,hPen));
                     }

                     if (poly->isFilled())
                     {
                        dc->BeginPath();
                     }

                     double bulge, lastx, lasty;

                     BOOL First = TRUE;
                     POSITION pntPos = poly->getPntList().GetHeadPosition();
                     while (pntPos)
                     {
                        CPnt *pnt = poly->getPntList().GetNext(pntPos);

                        Point2 point2;
                        point2.x = pnt->x * file->getScale();
                        if (fileMirror & MIRROR_FLIP)
                           point2.x = -point2.x;
                        point2.y = pnt->y * file->getScale();
                        TransPoint2(&point2, 1, &m, fileX, file->getInsertY());

                        if (First)
                           dc->MoveTo(round(point2.x / m_scaleFactor), round(point2.y / m_scaleFactor));
                        else
                        {
                           if (fabs(bulge) < BULGE_THRESHOLD)
                              dc->LineTo(round(point2.x / m_scaleFactor), round(point2.y / m_scaleFactor));
                           else
                           {
                              double da, sa, r, cx, cy;
                              da = atan(bulge) * 4;
                              if (fileMirror & MIRROR_FLIP)
                                 da = -da;
                              ArcPoint2Angle(lastx, lasty, point2.x, point2.y, da, &cx, &cy, &r, &sa);

                              if (Platform == WINNT) // Windows NT
                              {
                                 dc->SetArcDirection(da<0.0 ? AD_CLOCKWISE : AD_COUNTERCLOCKWISE);
                                 dc->ArcTo(lround((cx - r) / m_scaleFactor), lround((cy + r) / m_scaleFactor), 
                                       lround((cx + r) / m_scaleFactor), lround((cy - r) / m_scaleFactor),
                                       lround(lastx / m_scaleFactor), lround(lasty / m_scaleFactor), 
                                       lround(point2.x / m_scaleFactor), lround(point2.y / m_scaleFactor));  
                                 dc->SetArcDirection(AD_COUNTERCLOCKWISE);

                                 dc->LineTo(lround(point2.x / m_scaleFactor),lround(point2.y / m_scaleFactor));
                              }
                              else // Windows 95
                              {
                                 if (cx / m_scaleFactor > doc->maxXCoord || cx / m_scaleFactor < doc->minXCoord || 
                                       cy / m_scaleFactor > doc->maxYCoord || cy / m_scaleFactor < doc->minYCoord)
                                    dc->LineTo((int)(point2.x / m_scaleFactor),(int)(point2.y / m_scaleFactor));
                                 else if (poly->isFilled())// && showFills)
                                    AngleArc_Lines95(dc, (int)(cx / m_scaleFactor), (int)(cy / m_scaleFactor), 
                                          r / m_scaleFactor, sa, da);
                                 else
                                 {
                                    if (da < 0.0) // clockwise
                                    {     
                                       dc->Arc((int)((cx - r) / m_scaleFactor), (int)((cy + r) / m_scaleFactor), 
                                             (int)((cx + r) / m_scaleFactor), (int)((cy - r) / m_scaleFactor),
                                             (int)(point2.x / m_scaleFactor), (int)(point2.y / m_scaleFactor),
                                             (int)(lastx / m_scaleFactor), (int)(lasty / m_scaleFactor));
                                    }
                                    else // counter-clockwise
                                    {
                                       dc->Arc((int)((cx - r) / m_scaleFactor), (int)((cy + r) / m_scaleFactor), 
                                             (int)((cx + r) / m_scaleFactor), (int)((cy - r) / m_scaleFactor),
                                             (int)(lastx / m_scaleFactor), (int)(lasty / m_scaleFactor), 
                                             (int)(point2.x / m_scaleFactor), (int)(point2.y / m_scaleFactor));  
                                    }
                                    dc->MoveTo((int)(point2.x / m_scaleFactor),(int)(point2.y / m_scaleFactor));
                                 }
                              }

                           }
                        }
                        First = FALSE;

                        bulge = pnt->bulge;
                        lastx = point2.x;
                        lasty = point2.y;
                     }

                     if (poly->isFilled()) 
                     {
                        dc->EndPath();
                        dc->StrokeAndFillPath();
                     }
                  }

                  DeleteObject(SelectObject(dc->m_hDC, orgPen));
                  DeleteObject(SelectObject(dc->m_hDC, originalBrush));
               }
               break;
            }
         }
      }
   }
}