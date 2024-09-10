void
text_write()
{  
  for( size_t ii=0; ii<ntxt; ii++ )
    { 
      TLatex latex;
      if( txtNDC[ii] ) latex.SetNDC();    
      latex.SetTextFont(txtFont[ii]);
      latex.SetTextSize(txtSize[ii]);    
      latex.SetTextColor(txtColor[ii]);    
      latex.SetTextAlign(txtAlign[ii]); 
      latex.DrawLatex(txtX[ii],txtY[ii],txt[ii].c_str());
    }
}