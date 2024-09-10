      switch(s[0]){

      case 'b':

         saveLatBin = TRUE; break;    

      case 'm':

         if (bType != unknown)

            HError(3019,"HBuild: Can only specifiy one of -m, -n, -w, -x");

         bType = matBiGram;