    bool BaseDotVisitor::run( osg::Node& root, std::ostream* fout ) {
    setTraversalMode( TRAVERSE_ALL_CHILDREN );
    if ( fout && *fout ) {
      root.accept( *this );

      *fout << "digraph osg_scenegraph { "<<_rankdir<< std::endl;

      *fout << _nodes.str() << _edges.str();

      *fout << "}" << std::endl;

      _nodes.clear();
      _edges.clear();
      _objectMap.clear();

      return true;
    }

    return false;
  }