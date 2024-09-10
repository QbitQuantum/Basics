int main(int argc,char** argv)
{
  AnalyzeImage imgin,imgout;
  int x,y,z,labelsToChange,i;
  int intstatus;  
  int inlabel,outlabel;
  bool clobber = true;
  bool status;
  div_t divtmp;

  if(argc < 5) {
    cout << "Usage: relabel_analyze inputfile outputfile inlabel1 outlabel1" << endl;
    return(1);
  }
  intstatus = readImage(argv[1],&imgin);
  if(intstatus != 0) {
    cout << "Could not read the file" << argv[1] << endl;
    return(2);
  }
  status = copyImage(&imgin,&imgout);
  divtmp = div(argc - 3,2);
  if(divtmp.rem == 0) {
    labelsToChange = divtmp.quot;
    
  }
  else {
    cout << " wrong number of inputs" << endl;
    return(3);
  }
  for(i = 0;i < labelsToChange;i++) {
    inlabel = atoi(argv[2*i + 3]);
    outlabel = atoi(argv[2*i + 4]);
    cout << "Changing" << inlabel << "->" << outlabel << endl;
    for(x = 0;x < imgin.header.x_dim;x++) {
      for(y = 0;y < imgin.header.y_dim;y++) {
        for(z = 0;z < imgin.header.z_dim;z++) {
          if(fabs(getVoxelValue(&imgin,x,y,z) - inlabel) < 0.0001)
	    putVoxelValue(&imgout,x,y,z,outlabel);
        }
      }
    }
  }
  intstatus = writeImage(argv[2],&imgout,clobber);
  if(intstatus != 0) {
    cout << "Could not write the file" << argv[2] << endl;
    return(3);
  }
  return(0);



}