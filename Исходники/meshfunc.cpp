  // extern double teterrpow; 
  MESHING3_RESULT MeshVolume (MeshingParameters & mp, Mesh& mesh3d)
  {
     int oldne;
     int meshed;

     Array<INDEX_2> connectednodes;

     if (&mesh3d.LocalHFunction() == NULL) mesh3d.CalcLocalH(mp.grading);

     mesh3d.Compress();

     //  mesh3d.PrintMemInfo (cout);

     if (mp.checkoverlappingboundary)
        if (mesh3d.CheckOverlappingBoundary())
           throw NgException ("Stop meshing since boundary mesh is overlapping");

     int nonconsist = 0;
     for (int k = 1; k <= mesh3d.GetNDomains(); k++)
     {
        PrintMessage (3, "Check subdomain ", k, " / ", mesh3d.GetNDomains());

        mesh3d.FindOpenElements(k);

        /*
        bool res = mesh3d.CheckOverlappingBoundary();
        if (res)
        {
        PrintError ("Surface is overlapping !!");
        nonconsist = 1;
        }
        */

        bool res = (mesh3d.CheckConsistentBoundary() != 0);
        if (res)
        {
           PrintError ("Surface mesh not consistent");
           nonconsist = 1;
        }
     }

     if (nonconsist)
     {
        PrintError ("Stop meshing since surface mesh not consistent");
        throw NgException ("Stop meshing since surface mesh not consistent");
     }

     double globmaxh = mp.maxh;

     for (int k = 1; k <= mesh3d.GetNDomains(); k++)
       {
	 if (multithread.terminate)
           break;
	 
	 PrintMessage (2, "");
	 PrintMessage (1, "Meshing subdomain ", k, " of ", mesh3d.GetNDomains());
	 (*testout) << "Meshing subdomain " << k << endl;
	 
	 mp.maxh = min2 (globmaxh, mesh3d.MaxHDomain(k));
	 
	 mesh3d.CalcSurfacesOfNode();
	 mesh3d.FindOpenElements(k);
	 
	 if (!mesh3d.GetNOpenElements())
           continue;
	 
	 

	 Box<3> domain_bbox( Box<3>::EMPTY_BOX ); 
	 
	 for (SurfaceElementIndex sei = 0; sei < mesh3d.GetNSE(); sei++)
	   {
	     const Element2d & el = mesh3d[sei];
	     if (el.IsDeleted() ) continue;
	     
	     if (mesh3d.GetFaceDescriptor(el.GetIndex()).DomainIn() == k ||
		 mesh3d.GetFaceDescriptor(el.GetIndex()).DomainOut() == k)
	       
	       for (int j = 0; j < el.GetNP(); j++)
		 domain_bbox.Add (mesh3d[el[j]]);
	   }
	 domain_bbox.Increase (0.01 * domain_bbox.Diam());
	 
	
        for (int qstep = 1; qstep <= 3; qstep++)
	  {
	    // cout << "openquads = " << mesh3d.HasOpenQuads() << endl;
	    if (mesh3d.HasOpenQuads())
	      {
		string rulefile = ngdir;
		
		const char ** rulep = NULL;
		switch (qstep)
		  {
		  case 1:
		    rulefile += "/rules/prisms2.rls";
		    rulep = prismrules2;
		    break;
		  case 2: // connect pyramid to triangle
		    rulefile += "/rules/pyramids2.rls";
		    rulep = pyramidrules2;
		    break;
		  case 3: // connect to vis-a-vis point
		    rulefile += "/rules/pyramids.rls";
		    rulep = pyramidrules;
		    break;
		  }
		
		//		Meshing3 meshing(rulefile);
		Meshing3 meshing(rulep); 
		
		MeshingParameters mpquad = mp;
		
		mpquad.giveuptol = 15;
		mpquad.baseelnp = 4;
		mpquad.starshapeclass = 1000;
		mpquad.check_impossible = qstep == 1;   // for prisms only (air domain in trafo)
		
		
		for (PointIndex pi = mesh3d.Points().Begin(); pi < mesh3d.Points().End(); pi++)
		  meshing.AddPoint (mesh3d[pi], pi);
		
		mesh3d.GetIdentifications().GetPairs (0, connectednodes);
		for (int i = 1; i <= connectednodes.Size(); i++)
		  meshing.AddConnectedPair (connectednodes.Get(i));
		
		for (int i = 1; i <= mesh3d.GetNOpenElements(); i++)
		  {
		    Element2d hel = mesh3d.OpenElement(i);
		    meshing.AddBoundaryElement (hel);
		  }
		
		oldne = mesh3d.GetNE();
		
		meshing.GenerateMesh (mesh3d, mpquad);
		
		for (int i = oldne + 1; i <= mesh3d.GetNE(); i++)
		  mesh3d.VolumeElement(i).SetIndex (k);
		
		(*testout) 
		  << "mesh has " << mesh3d.GetNE() << " prism/pyramid elements" << endl;
		
		mesh3d.FindOpenElements(k);
	      }
	  }
	

        if (mesh3d.HasOpenQuads())
        {
           PrintSysError ("mesh has still open quads");
           throw NgException ("Stop meshing since too many attempts");
           // return MESHING3_GIVEUP;
        }


        if (mp.delaunay && mesh3d.GetNOpenElements())
        {
           Meshing3 meshing((const char**)NULL);

           mesh3d.FindOpenElements(k);

           /*
           for (PointIndex pi = mesh3d.Points().Begin(); pi < mesh3d.Points().End(); pi++)
              meshing.AddPoint (mesh3d[pi], pi);
           */
           for (PointIndex pi : mesh3d.Points().Range())
              meshing.AddPoint (mesh3d[pi], pi);

           for (int i = 1; i <= mesh3d.GetNOpenElements(); i++)
              meshing.AddBoundaryElement (mesh3d.OpenElement(i));

           oldne = mesh3d.GetNE();

           meshing.Delaunay (mesh3d, k, mp);

           for (int i = oldne + 1; i <= mesh3d.GetNE(); i++)
              mesh3d.VolumeElement(i).SetIndex (k);

           PrintMessage (3, mesh3d.GetNP(), " points, ",
              mesh3d.GetNE(), " elements");
        }


        int cntsteps = 0;
        if (mesh3d.GetNOpenElements())
           do
           {
              if (multithread.terminate)
                 break;

              mesh3d.FindOpenElements(k);
              PrintMessage (5, mesh3d.GetNOpenElements(), " open faces");
              cntsteps++;

              if (cntsteps > mp.maxoutersteps) 
                 throw NgException ("Stop meshing since too many attempts");

              string rulefile = ngdir + "/tetra.rls";
              PrintMessage (1, "start tetmeshing");

              //	  Meshing3 meshing(rulefile);
              Meshing3 meshing(tetrules);

              Array<int, PointIndex::BASE> glob2loc(mesh3d.GetNP());
              glob2loc = -1;

              for (PointIndex pi = mesh3d.Points().Begin(); pi < mesh3d.Points().End(); pi++)
                if (domain_bbox.IsIn (mesh3d[pi]))
                    glob2loc[pi] = 
                    meshing.AddPoint (mesh3d[pi], pi);

              for (int i = 1; i <= mesh3d.GetNOpenElements(); i++)
              {
                 Element2d hel = mesh3d.OpenElement(i);
                 for (int j = 0; j < hel.GetNP(); j++)
                    hel[j] = glob2loc[hel[j]];
                 meshing.AddBoundaryElement (hel);
                 // meshing.AddBoundaryElement (mesh3d.OpenElement(i));
              }

              oldne = mesh3d.GetNE();

              mp.giveuptol = 15 + 10 * cntsteps; 
              mp.sloppy = 5;
              meshing.GenerateMesh (mesh3d, mp);

              for (ElementIndex ei = oldne; ei < mesh3d.GetNE(); ei++)
                 mesh3d[ei].SetIndex (k);


              mesh3d.CalcSurfacesOfNode();
              mesh3d.FindOpenElements(k);

              // teterrpow = 2;
              if (mesh3d.GetNOpenElements() != 0)
              {
                 meshed = 0;
                 PrintMessage (5, mesh3d.GetNOpenElements(), " open faces found");

                 MeshOptimize3d optmesh(mp);

                 const char * optstr = "mcmstmcmstmcmstmcm";
                 for (size_t j = 1; j <= strlen(optstr); j++)
                 {
                    mesh3d.CalcSurfacesOfNode();
                    mesh3d.FreeOpenElementsEnvironment(2);
                    mesh3d.CalcSurfacesOfNode();

                    switch (optstr[j-1])
                    {
                    case 'c': optmesh.CombineImprove(mesh3d, OPT_REST); break;
                    case 'd': optmesh.SplitImprove(mesh3d, OPT_REST); break;
                    case 's': optmesh.SwapImprove(mesh3d, OPT_REST); break;
                    case 't': optmesh.SwapImprove2(mesh3d, OPT_REST); break;
                    case 'm': mesh3d.ImproveMesh(mp, OPT_REST); break;
                    }	  

                 }

                 mesh3d.FindOpenElements(k);	      
                 PrintMessage (3, "Call remove problem");
                 RemoveProblem (mesh3d, k);
                 mesh3d.FindOpenElements(k);
              }
              else
              {
                 meshed = 1;
                 PrintMessage (1, "Success !");
              }
           }
           while (!meshed);

           PrintMessage (1, mesh3d.GetNP(), " points, ",
              mesh3d.GetNE(), " elements");
     }

     mp.maxh = globmaxh;

     MeshQuality3d (mesh3d);

     return MESHING3_OK;
  }  