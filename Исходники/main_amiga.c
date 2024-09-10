/*>HandleEvent(APTR object)
   ------------------------
   Dispatch menu events.
   12.03.92 Original.
   30.03.92 Modified MenuEdit to call OpenFile() directly.
   31.03.92 Modified MenuSave to call SaveAsFile() directly.
   05.05.92 Added Rexx menu handling
   12.06.92 Removed fill grey/hatch items and replaced with requester
   02.07.92 Added MenuPalette
   13.07.92 Added MenuScrBack
   20.07.92 Added DEMO_VERSION conditional
   07.08.92 Added RemoveFills()
*/
HandleEvent(APTR object)
{
   if(object == (APTR)MenuOpen)     { OpenFile(object);        return(0); }
   if(object == (APTR)MenuSave)     { SaveAsFile(object);      return(0); }
   if(object == (APTR)MenuSaveAs)   { SaveAsFile(object);      return(0); }
   if(object == (APTR)MenuEdit)     { OpenFile(object);        return(0); }
   if(object == (APTR)MenuPaper)    { SetPaper(object);        return(0); }
   if(object == (APTR)MenuSetPens)  { SetPens(object);         return(0); }
   if(object == (APTR)MenuPalette)  { SetPalette(object);      return(0); }
   if(object == (APTR)MenuScrBack)  { ScreenToBack(MyScreen);  return(0); }
   if(object == (APTR)MenuAbout)    { About(object);           return(0); }
   if(object == (APTR)MenuQuit)     { QuitProgram(object);     return(0); }
#ifndef DEMO_VERSION
   if(object == (APTR)MenuPS)       { PlotPS(object);          return(0); }
   if(object == (APTR)MenuHPGL)     { PlotHPGL(object);        return(0); }
   if(object == (APTR)MenuDR2D)     { PlotDR2D(object);        return(0); }
#endif
   if(object == (APTR)MenuXY)       { StyleXY(object);         return(0); }
   if(object == (APTR)MenuScatter)  { StyleScatter(object);    return(0); }
   if(object == (APTR)MenuBar)      { StyleBar(object);        return(0); }
   if(object == (APTR)MenuPie)      { StylePie(object);        return(0); }
   if(object == (APTR)MenuErrors)   { ToggleErrors(object);    return(0); }
   if(object == (APTR)MenuEject)    { EjectSlice(object);      return(0); }
   if(object == (APTR)MenuLineSet)  { SetLine(object);         return(0); }
   if(object == (APTR)MenuBarSet)   { SetBar(object);          return(0); }
   if(object == (APTR)MenuPieSet)   { SetPie(object);          return(0); }
   if(object == (APTR)MenuLogX)     { ToggleLogX(object);      return(0); }
   if(object == (APTR)MenuLogY)     { ToggleLogY(object);      return(0); }
   if(object == (APTR)MenuBoxed)    { ToggleBoxed(object);     return(0); }
   if(object == (APTR)MenuGrid)     { ToggleGrid(object);      return(0); }
   if(object == (APTR)MenuAxes)     { SetAxes(object);         return(0); }
   if(object == (APTR)MenuFZero)    { ToggleFZero(object);     return(0); }
   if(object == (APTR)MenuTitle)    { SetTitle(object);        return(0); }
   if(object == (APTR)MenuAxTitle)  { SetAxTitle(object);      return(0); }
   if(object == (APTR)MenuAxLabel)  { SetAxLabel(object);      return(0); }
   if(object == (APTR)MenuKey)      { SetKey(object);          return(0); }
   if(object == (APTR)MenuLabel)    { SetLabel(object);        return(0); }
   if(object == (APTR)MenuPen)      { ChangePen(object);       return(0); }
   if(object == (APTR)MenuFillType) { FillControl(object);     return(0); }
   if(object == (APTR)MenuRegress)  { SetRegress(object);      return(0); }
   if(object == (APTR)MenuRobust)   { ToggleRobust(object);    return(0); }
   if(object == (APTR)MenuFourier)  { SetFourier(object);      return(0); }
   if(object == (APTR)MenuRexxFit)  { RexxFit(object);         return(0); }
   if(object == (APTR)MenuRexx)     { InstallMacro(object);    return(0); }
   if(object == (APTR)MenuRunRexx)  { RunMacro(object);        return(0); }
   if(object == (APTR)MenuDebRexx)  { ToggleRexxDeb(object);   return(0); }
   if(object == (APTR)MenuLS1)      { SetLineDash(object);     return(0); }
   if(object == (APTR)MenuLS2)      { SetLineDash(object);     return(0); }
   if(object == (APTR)MenuLS3)      { SetLineDash(object);     return(0); }
   if(object == (APTR)MenuLS4)      { SetLineDash(object);     return(0); }
   if(object == (APTR)MenuLS5)      { SetLineDash(object);     return(0); }
   if(object == (APTR)MenuLS6)      { SetLineDash(object);     return(0); }
   if(object == (APTR)MenuFT1)      { SetFillType(object);     return(0); }
   if(object == (APTR)MenuFT2)      { SetFillType(object);     return(0); }
   if(object == (APTR)MenuFT3)      { SetFillType(object);     return(0); }
   if(object == (APTR)MenuFT4)      { SetFillType(object);     return(0); }
   if(object == (APTR)MenuFT5)      { SetFillType(object);     return(0); }
   if(object == (APTR)MenuFT6)      { SetFillType(object);     return(0); }
   if(object == (APTR)MenuNoFills)  { RemoveFills(object);     return(0); }

   return(0);
}