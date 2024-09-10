void Scene::FlatFacet (Facet& f)
//
// If shading is 'Flat' the facet is drawn using flat shading, otherwise
// if shading is 'false' it will be filled with the background color. 
//
// Uses the global intermediate storage array pix.
//
{
    int i,j;
    float cx,cy,cz,nx,ny,nz,nk;
    short r,g,b;
    long color;
    
    // number of vertices
    int n = f.GetNumVertices();
    
    // facet is degenerate (a line) ----- CURRENTLY DEGENERATE NOT ALLOWED
    if (n == 2) {
	Line(f[0].p,f[1].p);
	return;
    }

    // can't happen !
    if (n < 2 || n > MaxVertices) {
	Warn("Scene::FlatFacet: number of vertices out of range");
	return;
    }

    static Material M;
    Material *Mp;
    if (coloring == Global) {
	Mp = f.GetMaterial();
    } else {
        M.color = f.front;
	if (f.material) {
	    M.ambient  = f.material->ambient;
	    M.specular = f.material->specular;
	    M.exponent = f.material->exponent;
	} else {
	    M.ambient = mat.ambient;
	    M.specular = mat.specular;
	    M.exponent = mat.exponent;
	}
	Mp = &M;
    } 
     
    // copy projected vertex coordinates to polygon array
    for (i = 0; i < n; i++) pix[i] = f[i].p;
     
    // compute color of facet from reflection properties
    if (shading == Facet::Flat) { 
	
	f.Normal(nx,ny,nz,nk);
	f.Center(cx,cy,cz);

	PhongColor(cx,cy,cz,nx,ny,nz,Mp,r,g,b);

	// find color in colormap
	//color = LookupColor(r,g,b,f.GetMaterial());
	color = LookupColor(r,g,b,&mat);

    // else if (shading == false) then use the background color
    } else
        color = backcolor;

    // =======================================================
    // testing: fog for edgelines to get a depth cueing effect
    // =======================================================
    ColorF previous_color;
    if (fog_opacity) {
      previous_color = foreground_color;
      SetColor( ColorF_Weighted(0.5*(1-tanh((6/fog_opacity)
			        *(hypot(cx,cy,cz)-fog_distance-1))),
				previous_color,fog_color) );
    }

    // draw outlines if requested
    if (edgelines == 1) 
        Polygon(n,pix,color,Outline|Fill);
    else if (edgelines == 0)
        Polygon(n,pix,color,Fill);
    else if (edgelines == Facet::Individual ) {
	if (f.edgelines == 1)
	    Polygon(n,pix,color,Outline|Fill); 
	else if (f.edgelines == 0)
	    Polygon(n,pix,color,Fill);
	else if (f.edgelines == Facet::Individual) {
	    Polygon(n,pix,color,Fill);
	    for (i = 0, j = n-1; i < n; j = i++) 
	      if ( f.GetEdgeLine(j) ) Line(pix[j],pix[i]);
	}	
    }

    if (fog_opacity) SetColor(previous_color);
}