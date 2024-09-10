int
gemIntegration(gemQuilt *quilt,       /* (in)  the quilt to integrate upon */
               int      geomFlag,     /* (in)  0 - data ref, 1 - geom based */
               int      eIndex,       /* (in)  element index (bias 1) */
               int      rank,         /* (in)  data depth */
               double   data[],       /* (in)  values (rank*npts in length) */
               double   result[])     /* (out) integrated result - (rank) */
{
  int    i, in[3];
  double x1[3], x2[3], x3[3], area;

  /* element indices */

  in[0] = quilt->elems[eIndex-1].gIndices[0] - 1;
  in[1] = quilt->elems[eIndex-1].gIndices[1] - 1;
  in[2] = quilt->elems[eIndex-1].gIndices[2] - 1;
  
  x1[0] = quilt->points[in[1]].xyz[0] - quilt->points[in[0]].xyz[0];
  x2[0] = quilt->points[in[2]].xyz[0] - quilt->points[in[0]].xyz[0];
  x1[1] = quilt->points[in[1]].xyz[1] - quilt->points[in[0]].xyz[1];
  x2[1] = quilt->points[in[2]].xyz[1] - quilt->points[in[0]].xyz[1];
  x1[2] = quilt->points[in[1]].xyz[2] - quilt->points[in[0]].xyz[2];
  x2[2] = quilt->points[in[2]].xyz[2] - quilt->points[in[0]].xyz[2];
  CROSS(x3, x1, x2);
  area  = sqrt(DOT(x3, x3))/2.0;      /* 1/2 for area */

  if (geomFlag == 0) {
    in[0] = quilt->elems[eIndex-1].dIndices[0] - 1;
    in[1] = quilt->elems[eIndex-1].dIndices[1] - 1;
    in[2] = quilt->elems[eIndex-1].dIndices[2] - 1;
  }
  for (i = 0; i < rank; i++)
    result[i] = area*(data[rank*in[0]+i] + data[rank*in[1]+i] +
                      data[rank*in[2]+i])/3.0;

  return GEM_SUCCESS;
}