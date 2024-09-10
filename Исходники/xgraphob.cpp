/*@ XBitmap::LoadBMP(const char* filename)
@group loading a bitmap
@remarks Load a bitmap from a file. This method works faster than Load() but can only load bitmpas in OS2-BMP format
@parameters   char * fileName   filename of the file to load
@exceptions   If the method fails to create a new bitmap an exception of the type XException is thrown.
*/
void XBitmap :: LoadBMP(const char* filename)
{
   if (hbm)
      GpiDeleteBitmap(hbm);
   hbm = 0;

   XFile file;
   PBITMAPFILEHEADER p;
   if (file.Open(filename, XFILE_FAIL_IF_NEW | XFILE_OPEN_EXISTING, XFILE_READONLY, XFILE_SHARE_DENYNONE ) == 0)
   {
      XFileInfo info;
      file.GetFileInfo(&info);
      file.Seek(0, XFILE_BEGIN);
      p = (PBITMAPFILEHEADER) malloc(info.GetFileSize());
      file.Read(p, info.GetFileSize());
      file.Close();
   }
   else
      OOLThrow( "couldnït open file!", -1);

   if (owner )
   {
      hps = WinGetPS(owner->GetHandle());
      hbm = GpiCreateBitmap(hps, (PBITMAPINFOHEADER2) &p->bmp, CBM_INIT, (PBYTE) p + p->offBits, (PBITMAPINFO2) &p->bmp);
      if(hbm == 0)
         OOLThrow("error creating bitmap", 3);
   }
   else
      SetData((BITMAPINFOHEADER2 *) &p->bmp, p->offBits);
   free(p);
   XSize s;
   GetDimensions(&s);
   width = cx = s.GetWidth();
   height = cy = s.GetHeight();

   if (hbm == GPI_ERROR)
   {
      ULONG error = WinGetLastError(XApplication::GetApplication()->GetAnchorBlock());
      OOLThrow("couldnït load bitmap", error);
   }

   return;
}