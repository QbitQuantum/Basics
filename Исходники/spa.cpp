  // Set up spanning tree initialization
  void SysSPA::spanningTree(int node)
  {
    int nnodes = nodes.size();

    // set up an index from nodes to their constraints
    vector<vector<int> > cind;
    cind.resize(nnodes);

    for(size_t pi=0; pi<p2cons.size(); pi++)
      {
        ConP2 &con = p2cons[pi];
        int i0 = con.ndr;
        int i1 = con.nd1;
        cind[i0].push_back(i1);
        cind[i1].push_back(i0);        
      }

    // set up breadth-first algorithm
    VectorXd dist(nnodes);
    dist.setConstant(1e100);
    if (node >= nnodes)
      node = 0;
    dist[node] = 0.0;
    multimap<double,int> open;  // open list, priority queue - can have duplicates
    open.insert(std::make_pair<double,int>(0.0,int(node)));

    // do breadth-first computation
    while (!open.empty())
      {
        // get top node, remove it
        int ni = open.begin()->second;
        double di = open.begin()->first;
        open.erase(open.begin());
        if (di > dist[ni]) continue; // already dealt with

        // update neighbors
        Node &nd = nodes[ni];
        Matrix<double,3,4> n2w;
        transformF2W(n2w,nd.trans,nd.qrot); // from node to world coords

        vector<int> &nns = cind[ni];
        for (int i=0; i<(int)nns.size(); i++)
          {
            ConP2 &con = p2cons[nns[i]];
            double dd = con.tmean.norm(); // incremental distance
            // neighbor node index
            int nn = con.nd1;
            if (nn == ni)
              nn = con.ndr;
            Node &nd2 = nodes[nn];
            Vector3d tmean = con.tmean;
            Quaterniond qpmean = con.qpmean;
            if (nn == con.ndr)       // wrong way, reverse
              {
                qpmean = qpmean.inverse();
                tmean = nd.qrot.toRotationMatrix().transpose()*nd2.qrot.toRotationMatrix()*tmean;
              }
                
            if (dist[nn] > di + dd) // is neighbor now closer?
              {
                // set priority queue
                dist[nn] = di+dd;
                open.insert(std::make_pair<double,int>(di+dd,int(nn)));
                // update initial pose
                Vector4d trans;
                trans.head(3) = tmean;
                trans(3) = 1.0;
                nd2.trans.head(3) = n2w*trans;
                nd2.qrot = qpmean*nd.qrot;
                nd2.normRot();
                nd2.setTransform();
                nd2.setDr(true);
              }
          }
      }
    
  }