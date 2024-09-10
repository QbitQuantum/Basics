int main(){
    int N = 3;
    CGAL::Timer cost;
    std::vector<Point_d> points;
   

   Point_d point1(1,3,5);
   Point_d point2(4,8,10);
   Point_d point3(2,7,9);

    Point_d point(1,2,3);


    points.push_back(point1);
    points.push_back(point2);
    points.push_back(point3);
   
    K Kernel 
    D Dt(d,Kernel,Kernel);
  //  CGAL_assertion(Dt.empty());
   
    // insert the points in the triangulation
    cost.reset();cost.start();
    std::cout << "  Delaunay triangulation of "<<N<<" points in dim "<<d<< std::flush;
    std::vector<Point_d>::iterator it;
    for(it = points.begin(); it!= points.end(); ++it){
	Dt.insert(*it); 
    }
    std::list<Simplex_handle> NL = Dt.all_simplices(D::NEAREST);
    std::cout << " done in "<<cost.time()<<" seconds." << std::endl;
    CGAL_assertion(Dt.is_valid() );
    CGAL_assertion(!Dt.empty());
 
   
    Vertex_handle v = Dt.nearest_neighbor(point);
    Simplex_handle s = Dt.simplex(v);    
     
    std::vector<Point_d> Simplex_vertices;
    for(int j=0; j<=d; ++j){
 	  Vertex_handle vertex = Dt.vertex_of_simplex(s,j);
       	  Simplex_vertices.push_back(Dt.associated_point(vertex));
     }
    
    std::vector<K::FT> coords;
    K::Barycentric_coordinates_d BaryCoords;
    BaryCoords(Simplex_vertices.begin(), Simplex_vertices.end(),point,std::inserter(coords, coords.begin()));
    std::cout << coords[0] << std::endl; 
   return 0;
}