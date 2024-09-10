  bool SpinDensity::put(xmlNodePtr cur)
  {
    using std::ceil;
    using std::sqrt;
    reset();
    string write_report = "no";
    OhmmsAttributeSet attrib;
    attrib.add(myName,"name");
    attrib.add(write_report,"report");
    attrib.put(cur);

    bool have_dr = false;
    bool have_grid = false;
    bool have_center = false;
    bool have_corner = false;
    bool have_cell = false;

    PosType dr;
    PosType center;
    Tensor<RealType,DIM> axes;

    int test_moves = 0;

    xmlNodePtr element = cur->xmlChildrenNode;
    while(element!=NULL)
    {
      string ename((const char*)element->name);
      if(ename=="parameter")
      {
        string name((const char*)(xmlGetProp(element,(const xmlChar*)"name")));
        if(name=="dr")      
        {
          have_dr = true;
          putContent(dr,element);   
        }
        else if(name=="grid") 
        {
          have_grid = true;
          putContent(grid,element);        
        }
        else if(name=="corner") 
        {
          have_corner = true;
          putContent(corner,element);        
        }
        else if(name=="center") 
        {
          have_center = true;
          putContent(center,element);        
        }
        else if(name=="cell") 
        {
          have_cell = true;
          putContent(axes,element);        
        }
        else if(name=="test_moves") 
          putContent(test_moves,element);        
      }
      element = element->next;
    }

    if(have_dr && have_grid)
    {
      APP_ABORT("SpinDensity::put  dr and grid are provided, this is ambiguous");
    }
    else if(!have_dr && !have_grid)
      APP_ABORT("SpinDensity::put  must provide dr or grid");

    if(have_corner && have_center)
      APP_ABORT("SpinDensity::put  corner and center are provided, this is ambiguous");
    if(have_cell)
    {
      cell.set(axes);
      if(!have_corner && !have_center)
        APP_ABORT("SpinDensity::put  must provide corner or center");
    }
    else
      cell = Ptmp->Lattice;

    if(have_center)
      corner = center-cell.Center;

    if(have_dr)
      for(int d=0;d<DIM;++d)
        grid[d] = (int)ceil(sqrt(dot(cell.Rv[d],cell.Rv[d]))/dr[d]);

    npoints = 1;
    for(int d=0;d<DIM;++d)
      npoints *= grid[d];
    gdims[0] = npoints/grid[0];
    for(int d=1;d<DIM;++d)
      gdims[d] = gdims[d-1]/grid[d];

    if(write_report=="yes")
      report("  ");
    if(test_moves>0)
      test(test_moves,*Ptmp);

    return true;
  }