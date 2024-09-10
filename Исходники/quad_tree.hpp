 void query_node(Envelope<double> const& box, result_t & result, node * node_) const
 {
    if (node_)
    {
       Envelope<double> const& node_extent = node_->extent();
       if (box.intersects(node_extent))
       {
          node_data_iterator i=node_->begin();
          node_data_iterator end=node_->end();
          while ( i!=end)
          {
             result.push_back(&(*i));
             ++i;
          }
          for (int k = 0; k < 4; ++k)
          {
             query_node(box,result,node_->children_[k]);
          }
       }
    }
 }