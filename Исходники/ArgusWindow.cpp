//______________________________________________________________________________
void ArgusWindow::CloseWindow()
{
   if (fTabWindow) {
      gROME->WindowClosed();
   } else {
      ArgusTab* tab = GetTabObjectAt(fCurrentTabIndex);
      ROMEString str;
      gROME->GetWindow()->SetSubWindowRunningAt(fWindowId, kFALSE);
      ClearEventHandlingRequest();
      ClearEventHandlingForced();
      
      // When a sub window is newly opened or it is closed,
      // calling TGMainFrame::CloseWindow() causes BadWindow
      // and/or BadDrawable error on X11, which terminates
      // the program. In order avoid this, just unmap the sub
      // window rather than closing it. This also makes it
      // possible to map the sub window again instead of
      // creating a new sub window.
      
//               TGMainFrame::CloseWindow();
      UnmapWindow();

      tab->SetRegisteringActive(true);
      if (!tab->IsTabActive()) {
         tab->UnRegisterObjects();
      }
   }
}