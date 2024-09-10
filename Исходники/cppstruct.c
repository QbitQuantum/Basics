int InitPreprocessor(void)
{
   #  define CPP_STUFF true
        #  ifdef CPP_STUFF
            FreeCPPStruct();
            InitCPPStruct();
            cpp->options.Quiet = 1;
            cpp->options.profileString = "generic";
            if (!InitAtomTable(atable, 0))
                return 1;
            if (!InitScanner(cpp))
	            return 1;
       #  endif
  return 0;
}