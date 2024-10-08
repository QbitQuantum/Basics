/**
 * Note that it always return EXIT_SUCCESS if .off file is read successfully.
 */
int main(void)
{	
    Polyhedron mesh;
    if( !read_to_polyhedron("./data/cactus.off", mesh) ) { return 1; }
  
    typedef std::map<Polyhedron::Facet_const_handle, double> Facet_double_map;
    Facet_double_map internal_map;
    
    CGAL::Timer timer; timer.start();
    std::pair<double, double> min_max_sdf = CGAL::sdf_values(mesh, 
      boost::associative_property_map<Facet_double_map>(internal_map) );
    std::cout << "minimum sdf: " << min_max_sdf.first << " maximum sdf: " << min_max_sdf.second << std::endl;
    std::cout << "Calculation time (fast traversal on): *** " << timer.time() << std::endl;

    timer.reset();
    Facet_double_map internal_map_2;
    min_max_sdf = CGAL::sdf_values<false>(mesh, 
      boost::associative_property_map<Facet_double_map>(internal_map_2) );
    std::cout << "minimum sdf: " << min_max_sdf.first << " maximum sdf: " << min_max_sdf.second << std::endl;
    std::cout << "Calculation time (fast traversal off): *** " << timer.time() << std::endl;

    timer.reset();
    typedef std::map<Polyhedron::Facet_const_handle, std::size_t> Facet_int_map;
    Facet_int_map internal_segment_map;
    // calculate SDF values and segment the mesh using default parameters.
    std::size_t number_of_segments = CGAL::segmentation_via_sdf_values(mesh, 
      boost::associative_property_map<Facet_int_map>(internal_segment_map));
    std::cout << "Number of segments: " << number_of_segments << std::endl;
    std::cout << "Calculation time (fast traversal on): *** " << timer.time() << std::endl;

    timer.reset();
    Facet_int_map internal_segment_map_2;
    // calculate SDF values and segment the mesh using default parameters.
    number_of_segments = CGAL::segmentation_via_sdf_values<false>(mesh, 
      boost::associative_property_map<Facet_int_map>(internal_segment_map_2));
    std::cout << "Number of segments: " << number_of_segments << std::endl;
    std::cout << "Calculation time (fast traversal off): *** " << timer.time() << std::endl;

}