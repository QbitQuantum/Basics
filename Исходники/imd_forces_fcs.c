void do_boundaries_fcs(int nloc, fcs_float *pos)
{
  int l, i;

  /* PBC in x direction */
  if (1==pbc_dirs.x)
    for (l=0; l<3*nloc; l+=3) {
      i = -FLOOR( SPRODFCS(pos+l,tbox_x) );
      pos[l  ] += i * box_x.x;
      pos[l+1] += i * box_x.y;
      pos[l+2] += i * box_x.z;
    }

  /* PBC in y direction */
  if (1==pbc_dirs.y)
    for (l=0; l<3*nloc; l+=3) {
      i = -FLOOR( SPRODFCS(pos+l,tbox_y) );
      pos[l  ] += i * box_y.x;
      pos[l+1] += i * box_y.y;
      pos[l+2] += i * box_y.z;
    }

  /* PBC in z direction */
  if (1==pbc_dirs.z)
    for (l=0; l<3*nloc; l+=3) {
      i = -FLOOR( SPRODFCS(pos+l,tbox_z) );
      pos[l  ] += i * box_z.x;
      pos[l+1] += i * box_z.y;
      pos[l+2] += i * box_z.z;
    }

}