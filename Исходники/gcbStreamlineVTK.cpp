void compute_streamlines() 
{
  srand (time(NULL));
	LOG("");

  float from[3], to[3]; 

  from[0] = minLen[0];   from[1] = minLen[1];   from[2] = minLen[2]; 
  to[0] = maxLen[0];   to[1] = maxLen[1];   to[2] = maxLen[2]; 

  printf("generating seeds...\n"); 
  osuflow->SetRandomSeedPoints(from, to, 400);
  int nSeeds; 
  VECTOR3* seeds = osuflow->GetSeeds(nSeeds); 
  for (int i=0; i<nSeeds; i++) 
    printf(" seed no. %d : [%f %f %f]\n", i, seeds[i][0], 
	   seeds[i][1], seeds[i][2]); 

  sl_list.clear(); 

  printf("compute streamlines..\n"); 
  osuflow->SetIntegrationParams(.001, .001);
  osuflow->GenStreamLines(sl_list , BACKWARD_AND_FORWARD, 2000, 0);
  printf(" done integrations\n"); 
  printf("list size = %d\n", (int)sl_list.size()); 

	// ADD-BY-LEETEN 07/07/2010-BEGIN
	for(int i = 0; i < sl_list.size(); i++)
	{
		VECTOR4 v4Color;
#if 0
		switch((i/2)%7)
		{
		case 0: v4Color = VECTOR4(1.0f, 0.0f, 0.0f, 1.0f);	break;
		case 1: v4Color = VECTOR4(0.0f, 1.0f, 0.0f, 1.0f);	break;
		case 2: v4Color = VECTOR4(0.0f, 0.0f, 1.0f, 1.0f);	break;
		case 3: v4Color = VECTOR4(1.0f, 1.0f, 0.0f, 1.0f);	break;
		case 4: v4Color = VECTOR4(1.0f, 0.0f, 1.0f, 1.0f);	break;
		case 5: v4Color = VECTOR4(0.0f, 1.0f, 1.0f, 1.0f);	break;
		case 6: v4Color = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);	break;
		}
#else
		switch((i/2)%10)
		{
		case 0: v4Color = VECTOR4(164.f/255.f, 196.f/255.f, 0.0f, 1.0f);	break;
		case 1: v4Color = VECTOR4(96.f/255.f, 169.f/255.f, 23.f/255.f, 1.0f);	break;
		case 2: v4Color = VECTOR4(0, 138.f/255.f, 0, 1.0f);	break;
		case 3: v4Color = VECTOR4(0, 171.f/255.f, 169.f/255.f, 1.0f);	break;
		case 4: v4Color = VECTOR4(27.f/255.f, 161.f/255.f, 226.f/255.f, 1.0f);	break;
		case 5: v4Color = VECTOR4(0, 80.f/255.f, 239.f/255.f, 1.0f);	break;
		case 6: v4Color = VECTOR4(106.f/255.f, 0, 1.f, 1.0f);	break;
		case 7: v4Color = VECTOR4(170.f/255.f, 0, 1.f, 1.0f);	break;
		case 8: v4Color = VECTOR4(244.f/255.f, 114.f/255.f, 208.f/255.f, 1.0f);	break;
		case 9: v4Color = VECTOR4(216.f/255.f, 0, 115.f/255.f, 1.0f);	break;
		}
#endif
		liv4Colors.push_back(v4Color);
	}
	// ADD-BY-LEETEN 07/07/2010-END
	cLineRenderer._Update();
}