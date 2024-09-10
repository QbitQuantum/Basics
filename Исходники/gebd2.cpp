int main(int argc,char **argv)
{
	using std::strncmp;
	
  int arg=1;
  bool prnt=0;
  bool res=0;
  bool time=0;

  while(arg<argc)
  {
    if(strncmp(argv[arg],"-w",2)==0)
      prnt=1;
    else if(strncmp(argv[arg],"-r",2)==0)
      res=1;
    else if(strncmp(argv[arg],"-t",2)==0)
      time=1;
#ifdef MPREAL
    else if(strncmp(argv[arg],"-P",4)==0)
    {
      int prec=53;
      arg++;
      if(arg<argc)
	prec=atoi(argv[arg]);
      mpfr::mpreal::set_default_prec(prec);
    }
#endif
    else
    {
      usage(argv[0]);
      return 1;
    }
    arg++;
  }

  if (test_gebd2<Real,Real>(prnt, res, time) !=0)
    usage(argv[0]);

  return 0;
}