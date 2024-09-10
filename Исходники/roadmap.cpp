gm::Point positionOnGrid (const unsigned n, const unsigned g, const Roadmap& r,
                          const tmap::TopologicalMap& tmap) 
{
  const msg::RoadmapNode& info = r.nodeInfo(n);
  const unsigned g2 = info.grid;
  if (g2==g)
  {
    return info.position;
  }
  else
  {
    const tmap::GraphVertex v = tmap.node(g);
    const tmap::GraphVertex v2 = tmap.node(g2);
    pair<tmap::GraphEdge, bool> res = edge(v, v2, tmap);
    ROS_ASSERT_MSG (res.second, "No edge between grid %u and grid %u "
                    "containing %u", g, g2, n);
    const bool flip = (tmap[res.first].dest == g);
    const tf::Pose offset = gmu::toPose(tmap[res.first].offset);
    const tf::Transform tr = flip ? offset.inverse() : offset;
    return gmu::transformPoint(tr, info.position);
  }
}