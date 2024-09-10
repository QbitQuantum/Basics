void myKeyHandler(unsigned char ch, int x, int y)
{
  int i;
  static int subdiv=0;
  struct point_t *slice;
  struct point_t *linecur;
  struct point_t *cur;
  struct point_t *new_points;

  struct slice_t *cur_slice,*cur2_slice;
  struct point_t *cur2;
  struct point_t points[5];
  double a,b,c;

  GLfloat v1[3],v2[3],v3[3];

  double deginc;

  //  struct slice_t *cur_slice;

  switch(ch)
    {
    case 'q':
      endSubdiv(0);
      break;

    case 'z':
      mode=(~mode)&1;
      printf("%s\n",mode?"3D mode":"2D mode");
      switch(mode)
	{
	case 0:
	  resetCamera();
	  break;
	case 1:
	  reset3DCamera();
	  break;
	}
      break;

    case 'k':
      /* test phong stuff */
      cur_slice = slices;
      cur2_slice = slices->n;
      //while(cur_slice!=NULL)
	{
	  cur = cur_slice->line;
	  cur2 = cur2_slice->line;
	  //while(cur->n!=NULL)
	    {
	      /* right vertex */
	      add_vec(&(cur->nx),&(cur->n->nx),&(points[0].nx));
	      normalize(&(points[0].nx));
	      sub_vec(&(cur->n->x),&(cur->x),v1);
	      v1[0] /= 2; v1[1] /= 2; v1[2] /= 2;
	      add_vec(&(cur->x),v1,&(points[0].x));
	      
	      /* top vertex */
	      add_vec(&(cur->nx),&(cur2->nx),&(points[1].nx));
	      normalize(&(points[1].nx));
	      sub_vec(&(cur2->x),&(cur->x),v1);
	      v1[0] /= 2; v1[1] /= 2; v1[2] /= 2;
	      add_vec(&(cur->x),v1,&(points[1].x));
	      
	      /* left vertex */
	      add_vec(&(cur2->nx),&(cur2->n->nx),&(points[2].nx));
	      normalize(&(points[2].nx));
	      sub_vec(&(cur2->n->x),&(cur2->x),v1);
	      v1[0] /= 2; v1[1] /= 2; v1[2] /= 2;
	      add_vec(&(cur2->x),v1,&(points[2].x));
	      
	      /* bottom vertex */
	      add_vec(&(cur2->n->nx),&(cur->n->nx),&(points[3].nx));
	      normalize(&(points[3].nx));
	      sub_vec(&(cur->n->x),&(cur2->n->x),v1);
	      v1[0] /= 2; v1[1] /= 2; v1[2] /= 2;
	      add_vec(&(cur2->n->x),v1,&(points[3].x));
	      
	      /* center vertex */
	      add_vec(&(points[0].nx),&(points[1].nx),v1);
	      add_vec(&(points[2].nx),&(points[3].nx),v2);
	      add_vec(v1,v2,&(points[4].nx));
	      normalize(&(points[4].nx));
	      sub_vec(&(points[3].x),&(cur2->n->x),v1);
	      sub_vec(&(points[2].x),&(cur2->n->x),v2);
	      add_vec(v1,v2,v3);
	      normalize(v3);
	      a=sqrt(v1[0]*v1[0]+v1[1]*v1[1]+v1[2]*v1[2]);
	      b=sqrt(v2[0]*v2[0]+v2[1]*v2[1]+v2[2]*v2[2]);
	      c=sqrt(a*a+b*b);
	      v3[0] *= c; v3[1] *= c; v3[2] *= c;
	      add_vec(&(cur2->n->x),v3,&(points[4].x));

	      printf("v2[0]=%f,v2[1]=%f,v2[2]=%f\nv3[0]=%f,v3[1]=%f,v3[2]=%f\n",v2[0],v2[1],v2[2],v3[0],v3[1],v3[2]);

	      for(i=0; i<5; i++)
		printf("points[%d]->x=%f,points[%d]->y=%f,points[%d]->z=%f\n",
		       i,points[i].x,i,points[i].y,i,points[i].z);
	      printf("cur->x=%f,cur->y=%f,cur->z=%f\ncur->n->x=%f,cur->n->y=%f,cur->n->z=%f\n",
		     cur->x,cur->y,cur->z,cur->n->x,cur->n->y,cur->n->z);
	      printf("cur2->x=%f,cur2->y=%f,cur2->z=%f\ncur2->n->x=%f,cur2->n->y=%f,cur2->n->z=%f\n",
		     cur2->x,cur2->y,cur2->z,cur2->n->x,cur2->n->y,cur2->n->z);

	      cur = cur->n;
	      cur2 = cur2->n;
	    }

	  cur_slice = cur_slice->n;
	  cur2_slice = cur2_slice->n != NULL ? cur2_slice->n : slices; /* circle around */
	}
      break;

    case 'n':
      normals=(~normals)&1;
      printf("Normal mode %s\n",normals?"on":"off");
      break;

    case 'e':
      solid=(~solid)&1;
      printf("%s\n",solid?"Solid mode":"Wireframe mode");
      switch(solid)
	{
	case 0:
	  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	  break;
	case 1:
	  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	  break;
	}
      break;

    case 'r':
      faces=(~faces)&1;
      printf("%s\n",faces?"Faces mode":"Control points mode");
      break;

    case 'w': /* calculate initial 3d object */
      if(num<5)
	printf("There must be at least 5 control points.\n");
      else if(!mode)
	{
	  mode=(~mode)&1;
	  printf("%s\n",mode?"3D mode":"2D mode");
	  switch(mode)
	    {
	    case 0:
	      resetCamera();
	      break;
	    case 1:
	      reset3DCamera();
	      break;
	    }
	  freeModel();
	  subdiv_v = 0;
	  subdiv_h = NUMSLICES;

	  /* the radius of the circle for each of the points is x */
	  for(i=0;i<subdiv_h;i++)
	    {
	      ALLOC_POINT(slice);
	      cur=slice;

	      linecur=line;
	      while(linecur!=NULL)
		{
		  cur->z = linecur->x*sin(DEGINC*i);
		  cur->x = linecur->x*cos(DEGINC*i);
		  cur->y = linecur->y;

		  linecur = linecur->n;
		  if(linecur!=NULL)
		    {
		      ALLOC_POINT(cur->n);
		      cur = cur->n;
		    }
		}

	      addSlice(slice);
	    }
	}

      recompute_normals();

      break;
     
    case 's': /* horizontal subdivision */

      if(!mode || slices==NULL) break;

      /* backup the original slice */
      new_points = duplicate_slice(slices->line);
      freeModel();

      subdiv_h<<=1;
      subdiv++;
      printf("Horizontal subdivision level %d\n",subdiv);
     
      deginc = 2*M_PI/subdiv_h;

      for(i=0;i<subdiv_h;i++)
	{
	  ALLOC_POINT(slice);
	  cur=slice;

	  linecur=new_points;
	  while(linecur!=NULL)
	    {
	      cur->z = linecur->x*sin(deginc*i);
	      cur->x = linecur->x*cos(deginc*i);
	      cur->y = linecur->y;

	      linecur = linecur->n;
	      if(linecur!=NULL)
		{
		  ALLOC_POINT(cur->n);
		  cur = cur->n;
		}
	    }

	  addSlice(slice);
	}

      recompute_normals();

      break;

    case 'a': /* vertical subdivision */

      if(!mode || slices==NULL) break;
      cur_slice=slices;
      
      subdiv_v++;
      printf("Vertical subdivision level %d\n",subdiv_v);
            
      linecur = cur_slice->line;
      /* calc the first point */
      cur = new_points = calc_point(linecur,linecur,linecur->n,linecur->n->n);
      
      /* calc middle and last points */
      while(linecur->n->n!=NULL)
	{
	  if(linecur->n->n->n!=NULL) /* middle points */
	    cur->n = calc_point(linecur,linecur->n,linecur->n->n,linecur->n->n->n);
	  else
	    cur->n = calc_point(linecur,linecur->n,linecur->n->n,linecur->n->n);
	  cur = cur->n;
	  linecur = linecur->n;
	}
      
      interleave(cur_slice->line,new_points);
      
      new_points = duplicate_slice(cur_slice->line);
      
      deginc = 2*M_PI/subdiv_h;

      freeModel();

      for(i=0;i<subdiv_h;i++)
	{
	  ALLOC_POINT(slice);
	  cur=slice;

	  linecur=new_points;
	  while(linecur!=NULL)
	    {
	      cur->z = linecur->x*sin(deginc*i);
	      cur->x = linecur->x*cos(deginc*i);
	      cur->y = linecur->y;

	      linecur = linecur->n;
	      if(linecur!=NULL)
		{
		  ALLOC_POINT(cur->n);
		  cur = cur->n;
		}
	    }
	  
	  addSlice(slice);
	}

      recompute_normals();

	break;

    case 'd':
      shading=(~shading)&1;
      printf("%s shading\n",shading?"Phong":"Gouraud");
      break;

    case '<':
      if(mode)
	{
	  glMatrixMode(GL_MODELVIEW);
	  glRotatef(1,0.0,1.0,0.0);
	}
      break;
    case '>':
      if(mode)
	{
	  glMatrixMode(GL_MODELVIEW);
	  glRotatef(-1,0.0,1.0,0.0);
	}
      break;

    default:
      /* Unrecognized keypress */
      return;
    }
  
  glutPostRedisplay();
  
  return;
}