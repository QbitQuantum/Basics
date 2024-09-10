int
Resample::Resample4D()
{
  newtes=new Tes();
  newtes->SetVolume(nx,ny,nz,mytes->dimt,mytes->datatype);
  newtes->voxsize[0]=fabs(xstep*mytes->voxsize[0]);
  newtes->voxsize[1]=fabs(ystep*mytes->voxsize[1]);
  newtes->voxsize[2]=fabs(zstep*mytes->voxsize[2]);

  if (mytes->origin[0]) {
    newtes->origin[0]=lround((mytes->origin[0]-x1)/xstep);
    newtes->origin[1]=lround((mytes->origin[1]-y1)/ystep);
    newtes->origin[2]=lround((mytes->origin[2]-z1)/zstep);
  }

  for (int i=0; i<mytes->dimt; i++) {
    mycube=new CrunchCube((*mytes)[i]);
    if (ResampleCube())
      return 102;
    newtes->SetCube(i,newcube);
    delete newcube;
    delete mycube;
  }

  // add new headers
  for (size_t i=0; i<newheaders.size(); i++)
    newtes->AddHeader(newheaders[i]);
  newtes->AddHeader((string)"resample_date: "+timedate());

  newtes->SetFileName(args[1]);
  newtes->SetFileFormat(mytes->GetFileFormat());
  newtes->header=mytes->header;
  AdjustCornerAndOrigin(*newtes);
  if (int err=newtes->WriteFile())
    printf("*** resample: error %d writing %s\n",err,args[1].c_str());
  else
    printf("resample: wrote %s.\n",args[1].c_str());
  return 0;
}