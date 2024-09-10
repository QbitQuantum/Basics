 static std::vector<std::string> find(::osg::Node &node)
 {
     FindFrameNames finder;
     node.accept(finder);
     return finder.getNames();
 }