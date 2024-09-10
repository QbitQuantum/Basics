/////////////////////////////////////////////////////////////////////////////
// SAX message handlers
BOOL SAX::OnInitDialog() 
{
   CDialog::OnInitDialog();
   
   ITypeLib **pptLib = new (ITypeLib *);
   CString tlb, path;
   tlb = path = getApp().getCamcadExeFolderPath();
   tlb += "camcad.tlb";

   if (LoadTypeLib(tlb.AllocSysString(), pptLib) != S_OK || RegisterTypeLib(*pptLib, tlb.AllocSysString(), path.AllocSysString()) != S_OK)
      MessageBox("Type libraries not avalible for browsing.");

   delete (pptLib);

//#Reference {F8DE4B05-FBC2-11D1-BA40-0080ADB36DBB}#1.0#0#C:\camcad\WinDebug\Camcad.tlb#CAMCAD
   dispatch = NULL;
// HRESULT hr = __CreateObject(OLESTR("CAMCAD.Application"), &dispatch);
// if (FAILED(hr))
// {
      m_sbpro.SetCode("Sub Main\r\n\tDim objCAMCAD\r\n\tSet objCAMCAD = CreateObject(\"CAMCAD.Application\")\r\n\r\n\t'example\r\n\t'objCAMCAD.ZoomLevel 2, 1\r\n\r\nEnd Sub");
      m_sbpro.AddExtension("{F8DE4B05-FBC2-11D1-BA40-0080ADB36DBB}#1.0#0#", NULL);
// }
// else
//    m_sbpro.AddExtension("", dispatch);

   m_sbpro.SetDefaultDataType("CAMCAD.Application");
   m_sbpro.SetHighlightExtension(0x804000);
   
   
   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}