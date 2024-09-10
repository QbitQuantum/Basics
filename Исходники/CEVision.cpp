//---------------------------------------------------------
void __fastcall CEVision::DrawAll(HDC hDC)
{
        TCanvas *tempCanvas = new TCanvas;
        tempCanvas->Handle=hDC;

       m_ImageTmpBW8.Draw(tempCanvas->Handle,m_dScaleSizeX,m_dScaleSizeY);
       tempCanvas->Pen->Width=2;
       tempCanvas->Pen->Style=psSolid;
       tempCanvas->Pen->Color= clRed;

       if(m_bShowLayout)
          for(int nIndex=0;nIndex<m_vectRect.size();nIndex++)
          {
                tempCanvas->FrameRect(Rect(m_vectRect[nIndex].Left*m_dScaleSizeX,m_vectRect[nIndex].Top*m_dScaleSizeY,
                        m_vectRect[nIndex].Right*m_dScaleSizeX,m_vectRect[nIndex].Bottom*m_dScaleSizeY));
                tempCanvas->TextOutA( m_vectRect[nIndex].left*m_dScaleSizeX, m_vectRect[nIndex].top*m_dScaleSizeY ,IntToStr(nIndex+1));
          }

        for(int nIndex=0;nIndex<3;nIndex++)
        {
                tempCanvas->Pen->Color= clRed;
                if(m_bShowMarkROI[nIndex]) m_roiMark[nIndex].DrawFrame(tempCanvas->Handle,E_FRAME_ON, TRUE,m_dScaleSizeX,m_dScaleSizeY);

                tempCanvas->Pen->Color= clLime;
                if(m_bShowPatternROI[nIndex]) m_roiMarkPattern[nIndex].DrawFrame(tempCanvas->Handle,E_FRAME_ON, TRUE,m_dScaleSizeX,m_dScaleSizeY);

                if(m_bShowMatchResult[nIndex]) m_markMatch[nIndex].DrawPositions(tempCanvas->Handle,m_dScaleSizeX,m_dScaleSizeY);
        }
       
       if(m_bShowMatchResultAll)
       for(int nIndex=0;nIndex<m_vectPattern.size();nIndex++)
       {
               m_vectPattern[nIndex].DrawPositions(tempCanvas->Handle,m_dScaleSizeX,m_dScaleSizeY);
       }

       if(m_bShowMarkROI[2])
       {
        tempCanvas->Pen->Width=1;
        tempCanvas->Pen->Style=psDot;
        tempCanvas->Pen->Color=clRed;

        tempCanvas->MoveTo(320*m_dScaleSizeX,230*m_dScaleSizeY);
        tempCanvas->LineTo(320*m_dScaleSizeX,250*m_dScaleSizeY);
        tempCanvas->MoveTo(310*m_dScaleSizeX,240*m_dScaleSizeY);
        tempCanvas->LineTo(330*m_dScaleSizeX,240*m_dScaleSizeY);
        }



       delete tempCanvas;
}