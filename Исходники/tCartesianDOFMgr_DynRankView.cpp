TEUCHOS_UNIT_TEST(tCartesianDOFMgr_DynRankView, threed)
{
  typedef CartesianConnManager<int,Ordinal64> CCM;
  typedef panzer::DOFManager<int,Ordinal64> DOFManager;

  // build global (or serial communicator)
  #ifdef HAVE_MPI
    Teuchos::MpiComm<int> comm(MPI_COMM_WORLD);
  #else
    THIS_REALLY_DOES_NOT_WORK
  #endif

  int np = comm.getSize(); // number of processors
  int rank = comm.getRank(); // processor rank

  // mesh description
  Ordinal64 nx = 10, ny = 7, nz = 4;
  int px = np, py = 1, pz = 1;
  int bx =  1, by = 2, bz = 1;

  // build velocity, temperature and pressure fields
  RCP<const panzer::FieldPattern> pattern_U = buildFieldPattern<Intrepid2::Basis_HGRAD_HEX_C2_FEM<PHX::Device,double,double> >();
  RCP<const panzer::FieldPattern> pattern_P = buildFieldPattern<Intrepid2::Basis_HGRAD_HEX_C1_FEM<PHX::Device,double,double> >();
  RCP<const panzer::FieldPattern> pattern_T = buildFieldPattern<Intrepid2::Basis_HGRAD_HEX_C1_FEM<PHX::Device,double,double> >();
  RCP<const panzer::FieldPattern> pattern_B = buildFieldPattern<Intrepid2::Basis_HDIV_HEX_I1_FEM<PHX::Device,double,double> >();
  RCP<const panzer::FieldPattern> pattern_E = buildFieldPattern<Intrepid2::Basis_HCURL_HEX_I1_FEM<PHX::Device,double,double> >();

  // build the topology
  RCP<CCM> connManager = rcp(new CCM);
  connManager->initialize(comm,nx,ny,nz,px,py,pz,bx,by,bz);

  // build the dof manager, and assocaite with the topology
  RCP<DOFManager> dofManager = rcp(new DOFManager);
  dofManager->setConnManager(connManager,*comm.getRawMpiComm());

  // add TEMPERATURE field to all element blocks (MHD and solid)
  dofManager->addField("TEMPERATURE",pattern_T);

  // add velocity (U) and PRESSURE fields to the MHD element block
  dofManager->addField("eblock-0_0_0","UX",pattern_U);
  dofManager->addField("eblock-0_0_0","UY",pattern_U);
  dofManager->addField("eblock-0_0_0","UZ",pattern_U);
  dofManager->addField("eblock-0_0_0","PRESSURE",pattern_P);
  dofManager->addField("eblock-0_0_0","B",pattern_B);
  dofManager->addField("eblock-0_0_0","E",pattern_E);

  // add velocity (U) fields to the solid element block
  dofManager->addField("eblock-0_1_0","UX",pattern_U);
  dofManager->addField("eblock-0_1_0","UY",pattern_U);
  dofManager->addField("eblock-0_1_0","UZ",pattern_U);

  // int temp_num = dofManager->getFieldNum("TEMPERATURE");
  int ux_num   = dofManager->getFieldNum("UX");
  int uy_num   = dofManager->getFieldNum("UY");
  // int uz_num   = dofManager->getFieldNum("UZ");
  // int p_num    = dofManager->getFieldNum("PRESSURE");
  // int b_num    = dofManager->getFieldNum("B");
  // int e_num    = dofManager->getFieldNum("E");

  // build global unknowns (useful comment!)
  dofManager->buildGlobalUnknowns();
 
  // print out some diagnostic information 
  ///////////////////////////////////////////////////////////

  dofManager->printFieldInformation(out); 

  out << std::endl << "Load balancing: " << printUGILoadBalancingInformation(*dofManager) << std::endl;

  out << std::endl << "Mesh Topology: " << std::endl;
  printMeshTopology(out,*dofManager);

  auto myOffset   = connManager->getMyOffsetTriplet();
  auto myElements = connManager->getMyElementsTriplet();

  out << "My Offset   = " << myOffset.x << " " << myOffset.y << " " << myOffset.z << std::endl;
  out << "My myElements = " << myElements.x << " " << myElements.y << " " << myElements.z << std::endl;

  // check sharing locally on this processor
  {
    // choose an element in the middle of the day
    Triplet element;
    element.x = myOffset.x + myElements.x/2-1;
    element.y = myOffset.y + myElements.y/2-1;
    element.z = myOffset.z + myElements.z/2-1;

    out << "Root element = " << element.x << " " << element.y << " " << element.z << std::endl;

    int localElmtId    = connManager->computeLocalElementIndex(element);
    int localElmtId_px = connManager->computeLocalElementIndex(Triplet(element.x+1,element.y,element.z));
    int localElmtId_py = connManager->computeLocalElementIndex(Triplet(element.x,element.y+1,element.z));
    int localElmtId_pz = connManager->computeLocalElementIndex(Triplet(element.x,element.y,element.z+1));

    TEST_ASSERT(localElmtId>=0);
    TEST_ASSERT(localElmtId_px>=0);
    TEST_ASSERT(localElmtId_py>=0);
    TEST_ASSERT(localElmtId_pz>=0);

    std::string eblock    = getElementBlock(element,*connManager);
    std::string eblock_px = getElementBlock(Triplet(element.x+1,element.y,element.z),*connManager);
    std::string eblock_py = getElementBlock(Triplet(element.x,element.y+1,element.z),*connManager);
    std::string eblock_pz = getElementBlock(Triplet(element.x,element.y,element.z+1),*connManager);

    std::vector<Ordinal64> gids, gids_px, gids_py, gids_pz;

    dofManager->getElementGIDs(   localElmtId,   gids);
    dofManager->getElementGIDs(localElmtId_px,gids_px);
    dofManager->getElementGIDs(localElmtId_py,gids_py);
    dofManager->getElementGIDs(localElmtId_pz,gids_pz);

    {
      out << "Elements " << localElmtId << " " << localElmtId_px << std::endl;
      auto offsets   = dofManager->getGIDFieldOffsets_closure(   eblock,ux_num,2,1); // +x
      auto offsets_n = dofManager->getGIDFieldOffsets_closure(eblock_px,ux_num,2,3); // -x

      TEST_EQUALITY(offsets.first.size(),offsets_n.first.size());

      std::vector<Ordinal64> gid_sub, gid_sub_px;
      for(std::size_t i=0;i<offsets.first.size();i++) {
        gid_sub.push_back(gids[offsets.first[i]]);
        gid_sub_px.push_back(gids_px[offsets_n.first[i]]);
      }

      std::sort(gid_sub.begin(),gid_sub.end());
      std::sort(gid_sub_px.begin(),gid_sub_px.end());

      for(std::size_t i=0;i<gid_sub.size();i++)
        TEST_EQUALITY(gid_sub[i],gid_sub_px[i]);
    }

    {
      out << "Elements " << localElmtId << " " << localElmtId_py << std::endl;
      auto offsets   = dofManager->getGIDFieldOffsets_closure(   eblock,ux_num,2,2); // +y
      auto offsets_n = dofManager->getGIDFieldOffsets_closure(eblock_py,ux_num,2,0); // -y

      TEST_EQUALITY(offsets.first.size(),offsets_n.first.size());

      std::vector<Ordinal64> gid_sub, gid_sub_py;
      for(std::size_t i=0;i<offsets.first.size();i++) {
        gid_sub.push_back(gids[offsets.first[i]]);
        gid_sub_py.push_back(gids_py[offsets_n.first[i]]);
      }

      std::sort(gid_sub.begin(),gid_sub.end());
      std::sort(gid_sub_py.begin(),gid_sub_py.end());

      for(std::size_t i=0;i<gid_sub.size();i++)
        TEST_EQUALITY(gid_sub[i],gid_sub_py[i]);
    }

    {
      out << "Elements " << localElmtId << " " << localElmtId_pz << std::endl;
      auto offsets   = dofManager->getGIDFieldOffsets_closure(   eblock,ux_num,2,5); // +z
      auto offsets_n = dofManager->getGIDFieldOffsets_closure(eblock_pz,ux_num,2,4); // -z

      TEST_EQUALITY(offsets.first.size(),offsets_n.first.size());

      std::vector<Ordinal64> gid_sub, gid_sub_pz;
      for(std::size_t i=0;i<offsets.first.size();i++) {
        gid_sub.push_back(gids[offsets.first[i]]);
        gid_sub_pz.push_back(gids_pz[offsets_n.first[i]]);
      }

      std::sort(gid_sub.begin(),gid_sub.end());
      std::sort(gid_sub_pz.begin(),gid_sub_pz.end());

      for(std::size_t i=0;i<gid_sub.size();i++)
        TEST_EQUALITY(gid_sub[i],gid_sub_pz[i]);
    }
  }

  // assuming a 1d partition, check shared boundaries between processors
  {
    Triplet element_l;
    element_l.x = myOffset.x;
    element_l.y = myOffset.y + myElements.y/2;
    element_l.z = myOffset.z + myElements.z/2;

    Triplet element_r;
    element_r.x = myOffset.x + myElements.x-1;
    element_r.y = myOffset.y + myElements.y/2;
    element_r.z = myOffset.z + myElements.z/2;

    int localElmtId_l    = connManager->computeLocalElementIndex(element_l);
    int localElmtId_r    = connManager->computeLocalElementIndex(element_r);

    TEST_ASSERT(localElmtId_l>=0);
    TEST_ASSERT(localElmtId_r>=0);

    std::vector<Ordinal64> gids_l, gids_r;
    dofManager->getElementGIDs(   localElmtId_l,   gids_l);
    dofManager->getElementGIDs(   localElmtId_r,   gids_r);

    std::string eblock_l = getElementBlock(element_l,*connManager);
    std::string eblock_r = getElementBlock(element_r,*connManager);

    auto offsets_l   = dofManager->getGIDFieldOffsets_closure(   eblock_l,uy_num,2,3); // -x
    auto offsets_r   = dofManager->getGIDFieldOffsets_closure(   eblock_r,uy_num,2,1); // +x

    TEST_EQUALITY(offsets_l.first.size(),offsets_r.first.size());

    out << "Elements L/R " << localElmtId_l << " " << localElmtId_r << std::endl;
    std::vector<Ordinal64> gid_sub_l, gid_sub_r;
    for(std::size_t i=0;i<offsets_l.first.size();i++) {
      gid_sub_l.push_back(gids_l[offsets_l.first[i]]);
      gid_sub_r.push_back(gids_r[offsets_r.first[i]]);
    }

    std::sort(gid_sub_l.begin(),gid_sub_l.end());
    std::sort(gid_sub_r.begin(),gid_sub_r.end());

    // send left
    if(rank!=0) {
      Teuchos::send(comm,Teuchos::as<int>(gid_sub_l.size()),&gid_sub_l[0],rank-1);
    }

    // recieve right, check 
    if(rank!=np-1) {
      std::vector<Ordinal64> gid_remote(gid_sub_r.size(),-1);
      Teuchos::receive(comm,rank+1,Teuchos::as<int>(gid_sub_r.size()),&gid_remote[0]);

      for(std::size_t i=0;i<gid_sub_r.size();i++)
        TEST_EQUALITY(gid_sub_r[i],gid_remote[i]);
    }
  }
    
}