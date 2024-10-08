STKUNIT_UNIT_TEST(nodeRegistry, test_parallel_1_0)
{
  EXCEPTWATCH;
  MPI_Barrier( MPI_COMM_WORLD );

  // start_demo_nodeRegistry_test_parallel_1

  percept::PerceptMesh eMesh(3u);

  unsigned p_size = eMesh.get_parallel_size();
  unsigned p_rank = eMesh.get_rank();
  Util::setRank(eMesh.get_rank());

  eMesh.new_mesh(percept::GMeshSpec(std::string("1x1x")+toString(p_size)+std::string("|bbox:0,0,0,1,1,1")));

  // prepare for adding some quadratic elements
  mesh::Part& block_hex_20 = eMesh.get_fem_meta_data()->declare_part("block_hex_20", eMesh.element_rank());
  /// set cell topology for the part block_hex_20
  mesh::fem::set_cell_topology< shards::Hexahedron<20>  >( block_hex_20 );
  stk_classic::io::put_io_part_attribute(block_hex_20);

  eMesh.commit();
  eMesh.print_info();
  eMesh.save_as("./cube1x1x2_hex-20-orig.e");

  mesh::Part* block_hex_8 = const_cast<mesh::Part *>(eMesh.getPart("block_1"));

  NodeRegistry nodeRegistry(eMesh);
  nodeRegistry.initialize();

  if (p_size <= 2)
  {
    // pick an element on the processor boundary
    unsigned elem_num_local = 1;
    unsigned elem_num_ghost = 2;
    if (p_size == 1)
      elem_num_ghost = 1;

    stk_classic::mesh::Entity* element_local_p = eMesh.get_bulk_data()->get_entity(eMesh.element_rank(), elem_num_local);
    stk_classic::mesh::Entity* element_ghost_p = eMesh.get_bulk_data()->get_entity(eMesh.element_rank(), elem_num_ghost);
    if (p_rank == 1)
    {
      element_local_p = eMesh.get_bulk_data()->get_entity(eMesh.element_rank(), elem_num_ghost);
      element_ghost_p = eMesh.get_bulk_data()->get_entity(eMesh.element_rank(), elem_num_local);
    }

    dw() << "P["<<p_rank<<"] elem_num_local = " << elem_num_local << DWENDL;
    dw() << "P["<<p_rank<<"] elem_num_ghost = " << elem_num_ghost << DWENDL;

    stk_classic::mesh::Entity& element_local = *element_local_p;
    stk_classic::mesh::Entity& element_ghost = *element_ghost_p;

    std::cout << "P["<<p_rank<<"] element_local = " << element_local << std::endl;
    std::cout << "P["<<p_rank<<"] element_ghost = " << element_ghost << std::endl;

    // choose edges to be used for new node locations (i.e., this would model a serendipity-like element with only edge Lagrange nodes)
    stk_classic::mesh::EntityRank stk_mesh_Edge = 1;
    NeededEntityType needed_entity_rank( stk_mesh_Edge, 1u);
    std::vector<NeededEntityType> needed_entity_ranks(1, needed_entity_rank);

    /*
     * 1st of three steps to create and associate new nodes - register need for new nodes, then check if node is remote, then get
     *   from remote proc if necessary; finally, the local node database is ready to be queried
     *
     * The pattern is to begin the step, loop over all elements (including ghosts) and invoke the local operation
     * The method doForAllSubEntities is a utility for performing the operation on all the sub entities.
     * If more granularity is desired, the member functions can be invoked directly for a particular sub-entity.
     */
    nodeRegistry.beginRegistration();
    nodeRegistry.doForAllSubEntities(&NodeRegistry::registerNeedNewNode, element_local, needed_entity_ranks);
    nodeRegistry.doForAllSubEntities(&NodeRegistry::registerNeedNewNode, element_ghost, needed_entity_ranks);
    nodeRegistry.endRegistration();

    std::cout << "P["<<p_rank<<"] nodeRegistry size  = " << nodeRegistry.total_size() << std::endl;
    std::cout << "P["<<p_rank<<"] nodeRegistry lsize = " << nodeRegistry.local_size() << std::endl;

    dw() << "P["<<p_rank<<"] nodeRegistry size       = " << nodeRegistry.total_size() << DWENDL;
    dw() << "P["<<p_rank<<"] nodeRegistry lsize      = " << nodeRegistry.local_size() << DWENDL;

    // could do local create of elements here
    nodeRegistry.beginLocalMeshMods();
    nodeRegistry.endLocalMeshMods();

    // check if the newly requested nodes are local or remote
    nodeRegistry.beginCheckForRemote();
    nodeRegistry.doForAllSubEntities(&NodeRegistry::checkForRemote, element_local, needed_entity_ranks);
    nodeRegistry.doForAllSubEntities(&NodeRegistry::checkForRemote, element_ghost, needed_entity_ranks);
    nodeRegistry.endCheckForRemote();

    // get the new nodes from other procs if they are nonlocal
    nodeRegistry.beginGetFromRemote();
    nodeRegistry.doForAllSubEntities(&NodeRegistry::getFromRemote, element_local, needed_entity_ranks);
    nodeRegistry.doForAllSubEntities(&NodeRegistry::getFromRemote, element_ghost, needed_entity_ranks);
    nodeRegistry.endGetFromRemote();

    // now we can get the new node's id and entity
    unsigned iSubDimOrd = 4u;
    if (p_rank)
    {
      iSubDimOrd = 0u;
    }
    NodeIdsOnSubDimEntityType& nodeIds_onSE_0 = *( nodeRegistry.getNewNodesOnSubDimEntity(element_local, needed_entity_rank.first, iSubDimOrd));
    stk_classic::mesh::Entity*  node_0   = eMesh.get_bulk_data()->get_entity(stk_classic::mesh::fem::FEMMetaData::NODE_RANK, nodeIds_onSE_0[0]->identifier());

    // should be the same node on each proc
    std::cout << "P[" << p_rank << "] nodeId_0 = " << nodeIds_onSE_0 << " node_0= " << node_0 << std::endl;

    // end_demo

#if STK_ADAPT_HAVE_YAML_CPP
    if (p_size == 1)
      {
        if (1) {
          YAML::Emitter out;
          out << YAML::Anchor("NodeRegistry::map");
          out << YAML::BeginMap;
          out << YAML::Key << YAML::BeginSeq << 1 << 2 << YAML::EndSeq << YAML::Value << YAML::BeginSeq << -1 << -2 << YAML::EndSeq;
          out << YAML::Key << 1;
          out << YAML::Value << 2;
          out << YAML::Key << 3;
          out << YAML::Value << 4;
          out << YAML::EndMap;
          //std::cout << "out=\n" << out.c_str() << "\n=out" << std::endl;
          std::string expected_result = "&NodeRegistry::map\n?\n  - 1\n  - 2\n:\n  - -1\n  - -2\n1: 2\n3: 4";
          //std::cout << "out2=\n" << expected_result << std::endl;
          STKUNIT_EXPECT_TRUE(expected_result == std::string(out.c_str()));
        }

        YAML::Emitter yaml;
        std::cout << "\nnodeRegistry.serialize_write(yaml)" << std::endl;
        SerializeNodeRegistry::serialize_write(nodeRegistry, yaml, 0);
        //std::cout << yaml.c_str() << std::endl;
        if (!yaml.good())
          {
            std::cout << "Emitter error: " << yaml.good() << " " <<yaml.GetLastError() << "\n";
            STKUNIT_EXPECT_TRUE(false);
          }
        std::ofstream file1("out.yaml");
        file1 << yaml.c_str();
        file1.close();
        std::ifstream file2("out.yaml");
        YAML::Parser parser(file2);
        YAML::Node doc;

        try {
          while(parser.GetNextDocument(doc)) {
            std::cout << "\n read doc.Type() = " << doc.Type() << " doc.Tag()= " << doc.Tag() << " doc.size= " << doc.size() << std::endl;
            if (doc.Type() == YAML::NodeType::Map)
              {
                for(YAML::Iterator it=doc.begin();it!=doc.end();++it) {
                  int key, value;
                  std::cout << "read it.first().Type() = " << it.first().Type() << " it.first().Tag()= " << it.first().Tag() << std::endl;
                  std::cout << "read it.second().Type() = " << it.second().Type() << " it.second().Tag()= " << it.second().Tag() << std::endl;
                  const YAML::Node& keySeq = it.first();
                  for(YAML::Iterator itk=keySeq.begin();itk!=keySeq.end();++itk) {
                    *itk >> key;
                    std::cout << "read key= " << key << std::endl;
                  }
              
                  const YAML::Node& valSeq = it.second();
                  for(YAML::Iterator itv=valSeq.begin();itv!=valSeq.end();++itv) {
                    *itv >> value;
                    std::cout << "read value= " << value << std::endl;
                  }
              
                }
              }
          }
        }
        catch(YAML::ParserException& e) {
          std::cout << e.what() << "\n";
          STKUNIT_EXPECT_TRUE(false);
        }

        file2.close();
        std::ifstream file3("out.yaml");
        NodeRegistry nrNew(eMesh);
        SerializeNodeRegistry::serialize_read(nrNew, file3);
        YAML::Emitter yaml3;
        std::cout << "\nnrNew.serialize_write(yaml3)" << std::endl;
        SerializeNodeRegistry::serialize_write(nrNew, yaml3, 0);
        std::cout << yaml3.c_str() << std::endl;
        
        //exit(1);
      }
#endif
    // start_demo_nodeRegistry_test_parallel_1_quadratic_elem

    // change element to be a serendipity quadratic element
    eMesh.get_bulk_data()->modification_begin();

    //getCellTopologyData< shards::Node  >()
    const CellTopologyData *const cell_topo_data =stk_classic::percept::PerceptMesh::get_cell_topology(block_hex_20);
    CellTopology cell_topo(cell_topo_data);

    for (unsigned isd = 0; isd < 12; isd++)
    {
      nodeRegistry.makeCentroidCoords(element_local, needed_entity_rank.first, isd);
      NodeIdsOnSubDimEntityType& nodeIds_onSE_0_loc = *( nodeRegistry.getNewNodesOnSubDimEntity(element_local, needed_entity_rank.first, isd));

      stk_classic::mesh::Entity*  node   = eMesh.get_bulk_data()->get_entity(stk_classic::mesh::fem::FEMMetaData::NODE_RANK, nodeIds_onSE_0_loc[0]->identifier());

      unsigned edge_ord = 8u + isd;
      //unsigned n_edge_ord = cell_topo_data->edge[isd].topology->node_count;
      //std::cout << "n_edge_ord = " << n_edge_ord << std::endl;
      edge_ord = cell_topo_data->edge[isd].node[2];
      eMesh.get_bulk_data()->declare_relation(element_local, *node, edge_ord);
    }

    std::vector<stk_classic::mesh::Part*> add_parts(1, &block_hex_20);
    std::vector<stk_classic::mesh::Part*> remove_parts(1, block_hex_8);
    eMesh.get_bulk_data()->change_entity_parts( element_local, add_parts, remove_parts );

    eMesh.get_bulk_data()->modification_end();
    eMesh.print_info("After quadratic");

    eMesh.save_as("./cube1x1x2_hex-20.e");
    //exit(1);
  }