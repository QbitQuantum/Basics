int
main(int argc,char *argv[])
{
  tokenlist args;
  Tes *tes;
  Cube *cub;
  int ind=0;
  stringstream tmps;

  args.Transfer(argc-1,argv+1);

  if (args.size() == 0) {
    tes2cub_help();
    exit(0);
  }

  if (args.size() != 2 && args.size() != 3) {
    tes2cub_help();
    exit(5);
  }

  if (args.size() == 3)
    ind = strtol(args[2]);
  tes = new Tes();
  if (tes->ReadFile(args[0])) {
    tmps.str("");
    tmps << "tes2cub: couldn't read tes file " << args[0];
    printErrorMsg(VB_ERROR,tmps.str());
    exit(5);
  }
  if (!tes->data_valid) {
    tmps.str("");
    tmps << "tes2cub: tes file " << args[0] << "isn't valid.";
    printErrorMsg(VB_ERROR,tmps.str());
    exit(5);
  }
  if (ind > tes->dimt) {
    tmps.str("");
    tmps << "tes2cub: index (" << ind << ") is beyond the last image (" << tes->dimt << ").";
    printErrorMsg(VB_ERROR,tmps.str());
    exit(5);
  } 
  cub = new Cube((*tes)[ind]);
  if (!cub->data_valid) {
    tmps.str("");
    tmps << "tes2cub: error extracting the cube from the 4D file (shouldn't happen!).";
    printErrorMsg(VB_ERROR,tmps.str());
    exit(5);
  } 
  if (!cub->WriteFile(args[1])) {
    tmps.str("");
    tmps << "tes2cub: wrote cube " << ind << " to file " << args[1] << ".";
    printErrorMsg(VB_INFO,tmps.str());
    exit(0);
  }
  else {
    tmps.str("");
    tmps << "tes2cub: failed to write extracted cube to file " << args[1] << ".";
    printErrorMsg(VB_INFO,tmps.str());
    exit(5);
  }
  exit(0);
}