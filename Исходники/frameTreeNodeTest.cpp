 void operator() (FrameTreeNode const * node)
 {
   cout << "get_location( wrt_node=" << node << ", source=" << m_wrt_frame << ")" << endl;
   ATrans3 t = getTransform(node, m_wrt_frame);
   cout << "xATrans(Vector3(";
   for (size_t i = 0; i < 3; ++i) {
     if (i > 0) {
       cout << ",";
     }
     cout << t.translation()[i];
   }
   cout << "), Matrix3x3(";
   for (size_t i = 0; i < 3; ++i) {
     cout << "(";
     for (size_t j = 0; j < 3; ++j) {
       if (j > 0) {
         cout << ",";
       }
       cout << t.rotation()(i, j);
     }
     cout << ")";
   }
   cout << "))" << endl << endl;
 }