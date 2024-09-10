/* ==================================== */
int32_t lmaxdiameter(struct xvimage *image, int32_t connex)
/* ==================================== */
{
  int32_t x;                       /* index muet de pixel */
  int32_t rs = rowsize(image);     /* taille ligne */
  int32_t cs = colsize(image);     /* taille colonne */
  int32_t ds = depth(image);       /* nb plans */
  int32_t ps = rs * cs;            /* taille plan */
  int32_t N = ps * ds;             /* taille image */
  uint8_t *I = UCHARDATA(image);     /* l'image de depart */
  struct xvimage *tmp;
  uint8_t *T;
  //GUJUN
  int32_t x1, x1max;
  int32_t y1, y1max;
  int32_t z1, z1max;
  int32_t x2, x2max;
  int32_t y2, y2max;
  int32_t z2, z2max;
  double distance = -1;
  double temp = 0;
  int32_t i;

  switch(datatype(image))
  {
    case VFF_TYP_1_BYTE:
      tmp = copyimage(image);
      if (tmp == NULL)
      {
        fprintf(stderr, "lmaxdiameter: copyimage failed\n");
        return 0;
      }
      T = UCHARDATA(tmp);
      switch (connex)
      {
        case 4:
          for (x = 0; x < N; x++)
            if (T[x] && (nbvoisc8(T,x,rs,N)) == 0) I[x] = NDG_MIN;
          break;
        case 8:
          for (x = 0; x < N; x++)
            if (T[x] && (nbvoisc4(T,x,rs,N)) == 0) I[x] = NDG_MIN;
          break;
        case 6:
          for (x = 0; x < N; x++)
            if (T[x] && (mctopo3d_nbvoisc6(T,x,rs,ps,N)) == 0) I[x] = NDG_MIN;
          break;
        case 18:
          for (x = 0; x < N; x++)
            if (T[x] && (mctopo3d_nbvoisc18(T,x,rs,ps,N)) == 0) I[x] = NDG_MIN;
          break;
        case 26:
          for (x = 0; x < N; x++)
            if (T[x] && (mctopo3d_nbvoisc26(T,x,rs,ps,N)) == 0) I[x] = NDG_MIN;
          break;
        default:
          fprintf(stderr, "lmaxdiameter: mauvaise connexite: %d\n", connex);
          return 0;
      } /* switch (connex) */
      //GUJun
      //Deux dimentions x et y
	if ((connex == 4)||(connex == 8))
	{
		for( x = 0; x < N; x++)
		{
		        // Le premier point au border
		    	if( I[x] != NDG_MIN )
			{
				x1 = x%rs;
				y1 = x/rs;
				for (i = x+1; i < N; i++)
				{
					//Le deuxième point au border
					if( I[i] != NDG_MIN )
					{
						x2 = i%rs;
						y2 = i/rs;
						temp = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
						//Le plus int32_t axe
						if (temp > distance)
						{
						     distance = temp;
                                                     x1max = x1; y1max = y1; 
                                                     x2max = x2; y2max = y2; 
						}

					}

				}

			}

		}

                for( x = 0; x < N; x++) I[x] = NDG_MIN;
                I[x1max+y1max*rs] = NDG_MAX;
                I[x2max+y2max*rs] = NDG_MAX;

	}
	//Trois dimentions x,y et z
	else if ((connex == 6)||(connex == 18)||(connex == 26))
	{
		for ( x = 0; x < N; x++)
		{
			if( I[x] != NDG_MIN )
			{
				z1 = x/ps;
				x1 = (x%ps)%rs;
				y1 = (x%ps)/rs;
				for(i = x+1; i < N; i++)
				{
					if( I[i] != NDG_MIN )
					{
						z2 = i/ps;
						x2 = (i%ps)%rs;
						y2 = (i%ps)/rs;
						temp = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
						if (temp > distance)
						{
   						     distance = temp;
                                                     x1max = x1; y1max = y1; z1max = z1; 
                                                     x2max = x2; y2max = y2; z2max = z2; 
						}
					}

				}

			}

		}


                for( x = 0; x < N; x++) I[x] = NDG_MIN;
                I[x1max+y1max*rs+z1max*ps] = NDG_MAX;
                I[x2max+y2max*rs+z2max*ps] = NDG_MAX;
	}


      //GUJun
      break;
    default:
      fprintf(stderr,"lmaxdiameter() : bad data type %d\n", datatype(image));
      return 0;
  } /* switch(datatype(image)) */

  if (distance == -1)
  {
      fprintf(stderr,"lmaxdiameter() : not enough data\n");
      return 0;
  }

  freeimage(tmp);
  return(1);
}