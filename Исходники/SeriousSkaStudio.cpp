// convert only one animation in animset 
BOOL CSeriousSkaStudioApp::ConvertAnimationInAnimSet(CAnimSet *pas,Animation *pan)
{
  DisableRendering();
  CTFileName fnTemp = (CTString)"Temp/animset";
  
  // try to save model instance
  CTString strAnimSet;
  CTString strCustomSpeed;
  CTString strCompresion = "FALSE";
  if(pan->an_bCompresed) strCompresion = "TRUE";
  if(pan->an_bCustomSpeed) strCustomSpeed.PrintF("  ANIMSPEED %g;",pan->an_fSecPerFrame);
  strAnimSet.PrintF("ANIMSETLIST\n{\n  TRESHOLD %g;\n  COMPRESION %s;\n%s\n  #INCLUDE \"%s\"\n}\n",
    pan->an_fTreshold,(const char*)strCompresion,(const char*)strCustomSpeed,(const char*)pan->an_fnSourceFile);

  try
  {
    strAnimSet.Save_t(fnTemp + ".aal");
    if(!ConvertAnimSet(fnTemp + ".aal")) {
      EnableRendering();
      return FALSE;
    }
    CAnimSet as;
    // load new animset
    as.Load_t(fnTemp + ".ba");
    if(as.as_Anims.Count()>0)
    {
      Animation &anNew = as.as_Anims[0];
      // overwrite old animation with new one
      *pan = anNew;
    }
    // clear new animset
    as.Clear();
  }
  catch(char *strErr)
  {
    ErrorMessage(strErr);
    EnableRendering();
    return FALSE;
  }
  EnableRendering();
  return TRUE;
}