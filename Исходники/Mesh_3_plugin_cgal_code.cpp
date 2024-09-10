Meshing_thread* cgal_code_mesh_3(const Polyhedron* pMesh,
                                 const Polylines_container& polylines,
                                 QString filename,
                                 const double facet_angle,
                                 const double facet_sizing,
                                 const double facet_approx,
                                 const double tet_sizing,
                                 const double tet_shape,
                                 bool protect_features,
                                 CGAL::Three::Scene_interface* scene)
{
  if(!pMesh) return 0;

  std::cerr << "Meshing file \"" << qPrintable(filename) << "\"\n";
  std::cerr << "  angle: " << facet_angle << std::endl
            << "  facets size bound: " << facet_sizing << std::endl
            << "  approximation bound: " << facet_approx << std::endl
            << "  tetrahedra size bound: " << tet_sizing << std::endl;
  std::cerr << "Build AABB tree...";
  CGAL::Timer timer;
  timer.start();
  // Create domain
  Polyhedral_mesh_domain* p_domain = new Polyhedral_mesh_domain(*pMesh);
  if(polylines.empty() && protect_features) {
      p_domain->detect_features();
  }
  if(! polylines.empty()){
    p_domain->add_features(polylines.begin(), polylines.end());
    protect_features = true; // so that it will be passed in make_mesh_3
  }

  std::cerr << "done (" << timer.time() << " ms)" << std::endl;

  Scene_c3t3_item* p_new_item = new Scene_c3t3_item;
  p_new_item->set_scene(scene);

  Mesh_parameters param;
  param.facet_angle = facet_angle;
  param.facet_sizing = facet_sizing;
  param.facet_approx = facet_approx;
  param.tet_sizing = tet_sizing;
  param.tet_shape = tet_shape;
  param.protect_features = protect_features;

  typedef ::Mesh_function<Polyhedral_mesh_domain> Mesh_function;
  Mesh_function* p_mesh_function = new Mesh_function(p_new_item->c3t3(),
                                                     p_domain, param);
  return new Meshing_thread(p_mesh_function, p_new_item);
}