  virtual void visit(const ConstElementPtr& e)
  {
    if (e->getElementType() == ElementType::Way)
    {
      const ConstWayPtr& w = boost::dynamic_pointer_cast<const Way>(e);

      vector<long> nodes = w->getNodeIds();
      if (nodes[0] != nodes[nodes.size() - 1])
      {
        nodes.push_back(nodes[0]);
      }

      Coordinate last = _map.getNode(nodes[0])->toCoordinate();
      for (size_t i = 1; i < nodes.size(); i++)
      {
        Coordinate c = _map.getNode(nodes[i])->toCoordinate();
        double distance = c.distance(last);
        double theta = atan2(c.y - last.y, c.x - last.x);
        _h.addAngle(theta, distance);
        last = c;
      }
    }
  }