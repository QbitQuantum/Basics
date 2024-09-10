void PointGridSearch::get_neighborhood_points_sorted(
  DLIList<CubitPoint*> &point_list,
  const CubitVector& center, double cut_off)
{
  point_list.clean_out();
  DLIList<CubitPoint*> temp_point_list;
  int i;

  for (int k = boundingCellMinimumZ; k <= boundingCellMaximumZ; k++)
  {
    int kn = numberGridCellsY * k;
    for (int j = boundingCellMinimumY; j <= boundingCellMaximumY; j++)
    {
      int jn = numberGridCellsX * (kn + j);
      for ( i = boundingCellMinimumX; i <= boundingCellMaximumX; i++)
      {
	int in = jn + i;
        if (neighborhoodList[in])
        {
          temp_point_list += *(neighborhoodList[in]);
        }
      }
    }
  }

  // evaluate point distance to center ... remove those larger than cut_off
  SDLByDouble sorted_index_list;
  IndexedDouble *ID;  
  CubitVector vec;
  cut_off *= cut_off;
  temp_point_list.reset();
  for ( i = 0; i < temp_point_list.size(); i++)
  {
    vec = center - temp_point_list.get_and_step()->coordinates();
    double distance = vec.length_squared();
    if (distance < cut_off)
    {
      ID = new IndexedDouble( i, distance );
      sorted_index_list.append( ID );
    }
  }

  sorted_index_list.sort();
  temp_point_list.reset();
  for ( i = 0; i < sorted_index_list.size(); i++ )
  {
    ID = sorted_index_list.get_and_step();
    point_list.append( temp_point_list.next( ID->index() ) );
    delete ID;
  }
}