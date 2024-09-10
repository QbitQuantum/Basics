 bool match(HashGrid::Ptr grid, const Vector3F& v) {
     VectorI candidates = grid->get_items_near_point(v);
     if (candidates.size() != 1) {
         std::cout << "<" << v.transpose() << "> : " << candidates.transpose()
             << std::endl;
     }
     return candidates.size() > 0;
 }