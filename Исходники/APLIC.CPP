void __fastcall TForm1::BGuardarClick(TObject *Sender)
{
  fitsfile *fptr;       /* pointer to the FITS file, defined in fitsio.h */
  int status;
  AnsiString N;

  ejex = X2;
  ejey = Y2;
  long n = X2*Y2;
  if(SD1->Execute())
  {
    status = 0;
    N = SD1->FileName + ".fit";
    if(ffinit(&fptr, N.c_str(), &status))
    {
      printerror( status );
      status = 0;
      if ( fits_open_file(&fptr, N.c_str(), READWRITE, &status) )
      {
         printerror(status);
        return;
      }
    }
  }
  else
    return;

  long axes[2];
  axes[0] = ejex;
  axes[1] = ejey;
  if(ffcrim(fptr, 16, 2, axes, &status))
  {
    printerror(status);
    return;
  }

  unsigned short *datos;

  datos = new unsigned short [ejex*ejey];
  memset(datos, 0, ejex*ejey*2);
  for(int py = 0; py < ejey; py++)
  {
    for (int px = ejex; px > 0; px--)
    {
      datos[n--] = Foto[py][px];
    }
  }

  status = 0;
  if(fits_write_img(fptr, TSHORT, 1, ejex*ejey, datos, &status))
  {
    printerror( status );
  }
  delete datos;
  return;
}