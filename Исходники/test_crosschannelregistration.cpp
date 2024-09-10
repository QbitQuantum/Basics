void test_crosschannelregistration(UnitTest &ut) {

  ut.begin_test_set("CrossChannelRegistration");

  Segmentation<uint16> segmenter;

  EuclideanDistanceMap<uint16> edm;
  Watershed<uint16> wat;
  Invert<uint16> inv;
  NWThreshold<uint16> nwt(5,0.5,60000,NWThreshold<uint16>::mask_type_square);//0.75 beautiful

  SwiftImage<uint16> c1a_i1("./Images/smallfake2/c1_a.tif");
  cout << "Load complete" << endl;
  SwiftImage<uint16> c1a_i2 = nwt.process(c1a_i1);
  cout << "Thresholding complete" << endl;
  SwiftImage<uint16> c1a_i3 = edm.process(c1a_i2);
  cout << "EDM complete" << endl;
  SwiftImage<uint16> c1a_i4 = inv.process(c1a_i3);
  cout << "INV complete" << endl;
  SwiftImage<uint16> c1a_i5 = wat.process(c1a_i4);
  cout << "Wat complete" << endl;
  SwiftImage<uint16> c1a_i6 = c1a_i2 && c1a_i5;
  vector<SwiftImageObject<> > c1a_objs1 = segmenter.process(c1a_i6);
  
  SwiftImage<uint16> c2a_i1("./Images/smallfake2/c2_a.tif");
  cout << "Load complete" << endl;
  SwiftImage<uint16> c2a_i2 = nwt.process(c2a_i1);
  cout << "Thresholding complete" << endl;
  SwiftImage<uint16> c2a_i3 = edm.process(c2a_i2);
  cout << "EDM complete" << endl;
  SwiftImage<uint16> c2a_i4 = inv.process(c2a_i3);
  cout << "INV complete" << endl;
  SwiftImage<uint16> c2a_i5 = wat.process(c2a_i4);
  cout << "Wat complete" << endl;
  SwiftImage<uint16> c2a_i6 = c2a_i2 && c2a_i5;
  vector<SwiftImageObject<> > c2a_objs1 = segmenter.process(c2a_i6);
  
  SwiftImage<uint16> c1t_i1("./Images/smallfake2/c1_t.tif");
  cout << "Load complete" << endl;
  SwiftImage<uint16> c1t_i2 = nwt.process(c1t_i1);
  cout << "Thresholding complete" << endl;
  SwiftImage<uint16> c1t_i3 = edm.process(c1t_i2);
  cout << "EDM complete" << endl;
  SwiftImage<uint16> c1t_i4 = inv.process(c1t_i3);
  cout << "INV complete" << endl;
  SwiftImage<uint16> c1t_i5 = wat.process(c1t_i4);
  cout << "Wat complete" << endl;
  SwiftImage<uint16> c1t_i6 = c1t_i2 && c1t_i5;
  vector<SwiftImageObject<> > c1t_objs1 = segmenter.process(c1t_i6);
  
  SwiftImage<uint16> c2t_i1("./Images/smallfake2/c2_t.tif");
  cout << "Load complete" << endl;
  SwiftImage<uint16> c2t_i2 = nwt.process(c2t_i1);
  cout << "Thresholding complete" << endl;
  SwiftImage<uint16> c2t_i3 = edm.process(c2t_i2);
  cout << "EDM complete" << endl;
  SwiftImage<uint16> c2t_i4 = inv.process(c2t_i3);
  cout << "INV complete" << endl;
  SwiftImage<uint16> c2t_i5 = wat.process(c2t_i4);
  cout << "Wat complete" << endl;
  SwiftImage<uint16> c2t_i6 = c2t_i2 && c2t_i5;
  vector<SwiftImageObject<> > c2t_objs1 = segmenter.process(c2t_i6);
  
 
  // Now have c1_objs1 and c2_objs1 for registration

  vector<vector<SwiftImageObject<> > > a_cycles;
  a_cycles.push_back(c1a_objs1);
  a_cycles.push_back(c2a_objs1);
  
  vector<vector<SwiftImageObject<> > > t_cycles;
  t_cycles.push_back(c1t_objs1);
  t_cycles.push_back(c2t_objs1);

  ChannelRegistration<> chanreg(c2a_i6.image_width(),c2a_i6.image_height());
  vector<vector<SwiftImageCluster<> > > a_clusters = chanreg.process_channel_registration(a_cycles,SwiftImageCluster<>::base_a);
  vector<vector<SwiftImageCluster<> > > c_clusters = chanreg.process_channel_registration(t_cycles,SwiftImageCluster<>::base_c);
  vector<vector<SwiftImageCluster<> > > g_clusters = chanreg.process_channel_registration(a_cycles,SwiftImageCluster<>::base_g);
  vector<vector<SwiftImageCluster<> > > t_clusters = chanreg.process_channel_registration(t_cycles,SwiftImageCluster<>::base_t);
 
  CrossChannelRegistration<> crosschanreg(c2a_i6.image_width(),c2a_i6.image_height(),true,3);
  vector<vector<SwiftImageCluster<> > > all_clusters = crosschanreg.process_crosschannel_registration(a_clusters,
                                                                                                      c_clusters,
                                                                                                      g_clusters,
                                                                                                      t_clusters);


  for(int n=0;n<all_clusters.size();n++) {
    ut.test(static_cast<int>(all_clusters[n].size()),2);
  }
   
  ut.test(static_cast<int>(all_clusters.size()),5);
  
  // Cluster 1, Cycle 1
  ut.test(static_cast<int>(all_clusters[0][0].features[SwiftImageCluster<>::base_a].size()),1);
  ut.test(static_cast<int>(all_clusters[0][0].features[SwiftImageCluster<>::base_t].size()),1);
  ut.test(static_cast<int>(all_clusters[0][0].features[SwiftImageCluster<>::base_g].size()),1);
  ut.test(static_cast<int>(all_clusters[0][0].features[SwiftImageCluster<>::base_c].size()),1);

  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.x,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.y,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_a][0].pixels[0].length,2);
  
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.x,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.y,2);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_a][0].pixels[1].length,2);
  

  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.x,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.y,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_t][0].pixels[0].length,2);
  
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.x,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.y,2);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_t][0].pixels[1].length,2);
  

  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.x,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.y,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_g][0].pixels[0].length,2);
  
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,2);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_c][0].pixels[1].length,2);

  
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.x,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.y,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_c][0].pixels[0].length,2);
  
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,2);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_c][0].pixels[1].length,2);

  // Cluster 1, Cycle 2
  ut.test(static_cast<int>(all_clusters[0][1].features[SwiftImageCluster<>::base_a].size()),1);
  ut.test(static_cast<int>(all_clusters[0][1].features[SwiftImageCluster<>::base_t].size()),1);
  ut.test(static_cast<int>(all_clusters[0][1].features[SwiftImageCluster<>::base_g].size()),1);
  ut.test(static_cast<int>(all_clusters[0][1].features[SwiftImageCluster<>::base_c].size()),1);

  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.x,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.y,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_a][0].pixels[0].length,2);
  
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.x,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.y,2);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_a][0].pixels[1].length,2);
  

  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.x,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.y,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_t][0].pixels[0].length,2);
  
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.x,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.y,2);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_t][0].pixels[1].length,2);
  

  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.x,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.y,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_g][0].pixels[0].length,2);
  
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,2);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_c][0].pixels[1].length,2);

  
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.x,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.y,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_c][0].pixels[0].length,2);
  
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,2);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_c][0].pixels[1].length,2);

  // Cluster 2, Cycle 1
  ut.test(static_cast<int>(all_clusters[1][0].features[SwiftImageCluster<>::base_a].size()),2);
  ut.test(static_cast<int>(all_clusters[1][0].features[SwiftImageCluster<>::base_t].size()),1);
  ut.test(static_cast<int>(all_clusters[1][0].features[SwiftImageCluster<>::base_g].size()),2);
  ut.test(static_cast<int>(all_clusters[1][0].features[SwiftImageCluster<>::base_c].size()),1);
  
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.x,1);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.y,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][0].pixels[0].length,2);
  
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.x,1);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.y,6);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][0].pixels[1].length,2);

  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][1].pixels[0].pos.x,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][1].pixels[0].pos.y,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][1].pixels[0].length,2);
  
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][1].pixels[1].pos.x,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][1].pixels[1].pos.y,6);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][1].pixels[1].length,2);

  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.x,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.y,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_t][0].pixels[0].length,2);
  
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.x,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.y,6);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_t][0].pixels[1].length,2);

  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.x,1);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.y,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][0].pixels[0].length,2);
  
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.x,1);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.y,6);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][0].pixels[1].length,2);

  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][1].pixels[0].pos.x,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][1].pixels[0].pos.y,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][1].pixels[0].length,2);
  
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][1].pixels[1].pos.x,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][1].pixels[1].pos.y,6);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][1].pixels[1].length,2);

  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.x,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.y,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_c][0].pixels[0].length,2);
  
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,6);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_c][0].pixels[1].length,2);

  
  // Cluster 2, Cycle 2
  ut.test(static_cast<int>(all_clusters[1][1].features[SwiftImageCluster<>::base_a].size()),1);
  ut.test(static_cast<int>(all_clusters[1][1].features[SwiftImageCluster<>::base_t].size()),1);
  ut.test(static_cast<int>(all_clusters[1][1].features[SwiftImageCluster<>::base_g].size()),1);
  ut.test(static_cast<int>(all_clusters[1][1].features[SwiftImageCluster<>::base_c].size()),1);
  
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.x,1);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.y,5);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_a][0].pixels[0].length,6);
  
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.x,1);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.y,6);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_a][0].pixels[1].length,6);

  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.x,1);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.y,5);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_t][0].pixels[0].length,6);
  
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.x,1);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.y,6);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_t][0].pixels[1].length,6);
   
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.x,1);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.y,5);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_g][0].pixels[0].length,6);
  
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.x,1);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.y,6);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_g][0].pixels[1].length,6);
  
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.x,1);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.y,5);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_c][0].pixels[0].length,6);
  
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,1);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,6);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_c][0].pixels[1].length,6);
 

  // Cluster 3, Cycle 1
  ut.test(static_cast<int>(all_clusters[2][0].features[SwiftImageCluster<>::base_a].size()),1);
  ut.test(static_cast<int>(all_clusters[2][0].features[SwiftImageCluster<>::base_t].size()),1);
  ut.test(static_cast<int>(all_clusters[2][0].features[SwiftImageCluster<>::base_g].size()),1);
  ut.test(static_cast<int>(all_clusters[2][0].features[SwiftImageCluster<>::base_c].size()),1);

  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.x,5);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.y,1);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_a][0].pixels[0].length,2);
  
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.x,5);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.y,2);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_a][0].pixels[1].length,2);
  
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.x,5);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.y,1);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_t][0].pixels[0].length,2);
  
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.x,5);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.y,2);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_t][0].pixels[1].length,2);
  
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.x,5);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.y,1);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_g][0].pixels[0].length,2);
  
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.x,5);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.y,2);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_g][0].pixels[1].length,2);
  
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.x,5);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.y,1);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_c][0].pixels[0].length,2);
  
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,5);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,2);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_c][0].pixels[1].length,2);
  
  // Cluster 3, Cycle 2
  ut.test(static_cast<int>(all_clusters[2][1].features[SwiftImageCluster<>::base_a].size()),1);
  ut.test(static_cast<int>(all_clusters[2][1].features[SwiftImageCluster<>::base_t].size()),1);
  ut.test(static_cast<int>(all_clusters[2][1].features[SwiftImageCluster<>::base_g].size()),1);
  ut.test(static_cast<int>(all_clusters[2][1].features[SwiftImageCluster<>::base_c].size()),1);

  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.x,5);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.y,1);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_a][0].pixels[0].length,2);
  
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.x,5);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.y,2);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_a][0].pixels[1].length,2);
  
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.x,5);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.y,1);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_t][0].pixels[0].length,2);
  
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.x,5);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.y,2);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_t][0].pixels[1].length,2);
  
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.x,5);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.y,1);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_g][0].pixels[0].length,2);
  
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.x,5);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.y,2);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_g][0].pixels[1].length,2);
  
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.x,5);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.y,1);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_c][0].pixels[0].length,2);
  
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,5);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,2);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_c][0].pixels[1].length,2);

  // Cluster 4, Cycle 1
  ut.test(static_cast<int>(all_clusters[3][0].features[SwiftImageCluster<>::base_a].size()),1);
  ut.test(static_cast<int>(all_clusters[3][0].features[SwiftImageCluster<>::base_t].size()),1);
  ut.test(static_cast<int>(all_clusters[3][0].features[SwiftImageCluster<>::base_g].size()),1);
  ut.test(static_cast<int>(all_clusters[3][0].features[SwiftImageCluster<>::base_c].size()),1);

  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.x,8);
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.y,5);
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_a][0].pixels[0].length,2);
  
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.x,8);
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.y,6);
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_a][0].pixels[1].length,2);
  
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.x,8);
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.y,5);
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_t][0].pixels[0].length,2);
  
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.x,8);
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.y,6);
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_t][0].pixels[1].length,2);
  
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.x,8);
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.y,5);
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_g][0].pixels[0].length,2);
  
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.x,8);
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.y,6);
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_g][0].pixels[1].length,2);
  
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.x,8);
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.y,5);
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_c][0].pixels[0].length,2);
  
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,8);
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,6);
  ut.test(all_clusters[3][0].features[SwiftImageCluster<>::base_c][0].pixels[1].length,2);
 
  // Cluster 4, Cycle 2
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.x,8);
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.y,5);
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_a][0].pixels[0].length,2);
  
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.x,8);
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.y,6);
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_a][0].pixels[1].length,2);
  
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.x,8);
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.y,5);
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_t][0].pixels[0].length,2);
  
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.x,8);
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.y,6);
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_t][0].pixels[1].length,2);
  
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.x,8);
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.y,5);
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_g][0].pixels[0].length,2);
  
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.x,8);
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.y,6);
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_g][0].pixels[1].length,2);
  
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.x,8);
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.y,5);
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_c][0].pixels[0].length,2);
  
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,8);
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,6);
  ut.test(all_clusters[3][1].features[SwiftImageCluster<>::base_c][0].pixels[1].length,2);
 
  
  all_clusters = crosschanreg.process_crosschannel_registration_inv(a_clusters,
                                                                    c_clusters,
                                                                    g_clusters,
                                                                    t_clusters);
  
  for(int n=0;n<all_clusters.size();n++) {
    ut.test(static_cast<int>(all_clusters[n].size()),2);
  }
   
  ut.test(static_cast<int>(all_clusters.size()),5);
  
  // Cluster 1, Cycle 1
  ut.test(static_cast<int>(all_clusters[0][0].features[SwiftImageCluster<>::base_a].size()),1);
  ut.test(static_cast<int>(all_clusters[0][0].features[SwiftImageCluster<>::base_t].size()),1);
  ut.test(static_cast<int>(all_clusters[0][0].features[SwiftImageCluster<>::base_g].size()),1);
  ut.test(static_cast<int>(all_clusters[0][0].features[SwiftImageCluster<>::base_c].size()),1);

  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.x,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.y,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_a][0].pixels[0].length,2);
  
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.x,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.y,2);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_a][0].pixels[1].length,2);
  

  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.x,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.y,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_t][0].pixels[0].length,2);
  
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.x,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.y,2);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_t][0].pixels[1].length,2);
  

  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.x,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.y,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_g][0].pixels[0].length,2);
  
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,2);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_c][0].pixels[1].length,2);

  
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.x,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.y,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_c][0].pixels[0].length,2);
  
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,1);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,2);
  ut.test(all_clusters[0][0].features[SwiftImageCluster<>::base_c][0].pixels[1].length,2);

  // Cluster 1, Cycle 2
  ut.test(static_cast<int>(all_clusters[0][1].features[SwiftImageCluster<>::base_a].size()),1);
  ut.test(static_cast<int>(all_clusters[0][1].features[SwiftImageCluster<>::base_t].size()),1);
  ut.test(static_cast<int>(all_clusters[0][1].features[SwiftImageCluster<>::base_g].size()),1);
  ut.test(static_cast<int>(all_clusters[0][1].features[SwiftImageCluster<>::base_c].size()),1);

  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.x,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.y,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_a][0].pixels[0].length,2);
  
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.x,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.y,2);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_a][0].pixels[1].length,2);
  

  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.x,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.y,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_t][0].pixels[0].length,2);
  
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.x,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.y,2);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_t][0].pixels[1].length,2);
  

  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.x,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.y,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_g][0].pixels[0].length,2);
  
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,2);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_c][0].pixels[1].length,2);

  
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.x,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.y,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_c][0].pixels[0].length,2);
  
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,1);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,2);
  ut.test(all_clusters[0][1].features[SwiftImageCluster<>::base_c][0].pixels[1].length,2);

  // Cluster 2, Cycle 1
  ut.test(static_cast<int>(all_clusters[1][0].features[SwiftImageCluster<>::base_a].size()),2);
  ut.test(static_cast<int>(all_clusters[1][0].features[SwiftImageCluster<>::base_t].size()),1);
  ut.test(static_cast<int>(all_clusters[1][0].features[SwiftImageCluster<>::base_g].size()),2);
  ut.test(static_cast<int>(all_clusters[1][0].features[SwiftImageCluster<>::base_c].size()),1);
  
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.x,1);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.y,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][0].pixels[0].length,2);
  
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.x,1);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.y,6);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][0].pixels[1].length,2);

  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][1].pixels[0].pos.x,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][1].pixels[0].pos.y,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][1].pixels[0].length,2);
  
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][1].pixels[1].pos.x,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][1].pixels[1].pos.y,6);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_a][1].pixels[1].length,2);

  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.x,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.y,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_t][0].pixels[0].length,2);
  
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.x,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.y,6);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_t][0].pixels[1].length,2);

  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.x,1);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.y,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][0].pixels[0].length,2);
  
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.x,1);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.y,6);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][0].pixels[1].length,2);

  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][1].pixels[0].pos.x,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][1].pixels[0].pos.y,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][1].pixels[0].length,2);
  
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][1].pixels[1].pos.x,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][1].pixels[1].pos.y,6);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_g][1].pixels[1].length,2);

  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.x,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.y,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_c][0].pixels[0].length,2);
  
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,5);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,6);
  ut.test(all_clusters[1][0].features[SwiftImageCluster<>::base_c][0].pixels[1].length,2);

  
  // Cluster 2, Cycle 2
  ut.test(static_cast<int>(all_clusters[1][1].features[SwiftImageCluster<>::base_a].size()),1);
  ut.test(static_cast<int>(all_clusters[1][1].features[SwiftImageCluster<>::base_t].size()),1);
  ut.test(static_cast<int>(all_clusters[1][1].features[SwiftImageCluster<>::base_g].size()),1);
  ut.test(static_cast<int>(all_clusters[1][1].features[SwiftImageCluster<>::base_c].size()),1);
  
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.x,1);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.y,5);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_a][0].pixels[0].length,6);
  
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.x,1);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.y,6);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_a][0].pixels[1].length,6);

  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.x,1);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.y,5);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_t][0].pixels[0].length,6);
  
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.x,1);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.y,6);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_t][0].pixels[1].length,6);
   
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.x,1);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.y,5);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_g][0].pixels[0].length,6);
  
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.x,1);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.y,6);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_g][0].pixels[1].length,6);
  
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.x,1);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.y,5);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_c][0].pixels[0].length,6);
  
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,1);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,6);
  ut.test(all_clusters[1][1].features[SwiftImageCluster<>::base_c][0].pixels[1].length,6);
 

  // Cluster 3, Cycle 1
  ut.test(static_cast<int>(all_clusters[4][0].features[SwiftImageCluster<>::base_a].size()),1);
  ut.test(static_cast<int>(all_clusters[4][0].features[SwiftImageCluster<>::base_t].size()),1);
  ut.test(static_cast<int>(all_clusters[4][0].features[SwiftImageCluster<>::base_g].size()),1);
  ut.test(static_cast<int>(all_clusters[4][0].features[SwiftImageCluster<>::base_c].size()),1);

  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.x,5);
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.y,1);
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_a][0].pixels[0].length,2);
  
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.x,5);
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.y,2);
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_a][0].pixels[1].length,2);
  
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.x,5);
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.y,1);
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_t][0].pixels[0].length,2);
  
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.x,5);
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.y,2);
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_t][0].pixels[1].length,2);
  
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.x,5);
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.y,1);
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_g][0].pixels[0].length,2);
  
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.x,5);
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.y,2);
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_g][0].pixels[1].length,2);
  
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.x,5);
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.y,1);
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_c][0].pixels[0].length,2);
  
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,5);
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,2);
  ut.test(all_clusters[4][0].features[SwiftImageCluster<>::base_c][0].pixels[1].length,2);
  
  // Cluster 3, Cycle 2
  ut.test(static_cast<int>(all_clusters[4][1].features[SwiftImageCluster<>::base_a].size()),1);
  ut.test(static_cast<int>(all_clusters[4][1].features[SwiftImageCluster<>::base_t].size()),1);
  ut.test(static_cast<int>(all_clusters[4][1].features[SwiftImageCluster<>::base_g].size()),1);
  ut.test(static_cast<int>(all_clusters[4][1].features[SwiftImageCluster<>::base_c].size()),1);

  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.x,5);
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.y,1);
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_a][0].pixels[0].length,2);
  
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.x,5);
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.y,2);
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_a][0].pixels[1].length,2);
  
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.x,5);
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.y,1);
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_t][0].pixels[0].length,2);
  
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.x,5);
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.y,2);
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_t][0].pixels[1].length,2);
  
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.x,5);
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.y,1);
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_g][0].pixels[0].length,2);
  
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.x,5);
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.y,2);
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_g][0].pixels[1].length,2);
  
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.x,5);
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.y,1);
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_c][0].pixels[0].length,2);
  
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,5);
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,2);
  ut.test(all_clusters[4][1].features[SwiftImageCluster<>::base_c][0].pixels[1].length,2);

  // Cluster 4, Cycle 1
  ut.test(static_cast<int>(all_clusters[2][0].features[SwiftImageCluster<>::base_a].size()),1);
  ut.test(static_cast<int>(all_clusters[2][0].features[SwiftImageCluster<>::base_t].size()),1);
  ut.test(static_cast<int>(all_clusters[2][0].features[SwiftImageCluster<>::base_g].size()),1);
  ut.test(static_cast<int>(all_clusters[2][0].features[SwiftImageCluster<>::base_c].size()),1);

  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.x,8);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.y,5);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_a][0].pixels[0].length,2);
  
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.x,8);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.y,6);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_a][0].pixels[1].length,2);
  
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.x,8);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.y,5);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_t][0].pixels[0].length,2);
  
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.x,8);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.y,6);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_t][0].pixels[1].length,2);
  
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.x,8);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.y,5);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_g][0].pixels[0].length,2);
  
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.x,8);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.y,6);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_g][0].pixels[1].length,2);
  
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.x,8);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.y,5);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_c][0].pixels[0].length,2);
  
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,8);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,6);
  ut.test(all_clusters[2][0].features[SwiftImageCluster<>::base_c][0].pixels[1].length,2);
 
  // Cluster 4, Cycle 2
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.x,8);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_a][0].pixels[0].pos.y,5);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_a][0].pixels[0].length,2);
  
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.x,8);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_a][0].pixels[1].pos.y,6);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_a][0].pixels[1].length,2);
  
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.x,8);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_t][0].pixels[0].pos.y,5);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_t][0].pixels[0].length,2);
  
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.x,8);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_t][0].pixels[1].pos.y,6);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_t][0].pixels[1].length,2);
  
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.x,8);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_g][0].pixels[0].pos.y,5);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_g][0].pixels[0].length,2);
  
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.x,8);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_g][0].pixels[1].pos.y,6);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_g][0].pixels[1].length,2);
  
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.x,8);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_c][0].pixels[0].pos.y,5);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_c][0].pixels[0].length,2);
 
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.x,8);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_c][0].pixels[1].pos.y,6);
  ut.test(all_clusters[2][1].features[SwiftImageCluster<>::base_c][0].pixels[1].length,2);

  ut.end_test_set();
}