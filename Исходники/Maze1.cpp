void walls_init()
{
  glNewList( cu32NorthWallID, GL_COMPILE );
  polygon(north_vertices,0,1,2,3);
  polygon(north_vertices,1,5,6,2);
  polygon(north_vertices,4,5,6,7);
  polygon(north_vertices,0,4,7,3);
  polygon(north_vertices,0,1,5,4);
  polygon(north_vertices,3,2,6,7);

  glEndList();

  glNewList( cu32EastWallID, GL_COMPILE );

  polygon(east_vertices,0,1,2,3);
  polygon(east_vertices,1,5,6,2);
  polygon(east_vertices,4,5,6,7);
  polygon(east_vertices,0,4,7,3);
  polygon(east_vertices,0,1,5,4);
  polygon(east_vertices,3,2,6,7);

  glEndList();

}