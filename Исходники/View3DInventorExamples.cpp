void LightManip(SoSeparator * root)
{

  SoInput in;
  in.setBuffer((void *)scenegraph, std::strlen(scenegraph));
  SoSeparator * _root = SoDB::readAll( &in );
  if ( _root == NULL ) return; // Shouldn't happen.
  root->addChild(_root);
  root->ref();

  const char * pointlightnames[3] = { "RedLight", "GreenLight", "BlueLight" };
  SoSearchAction sa;

  for (int i = 0; i < 3; i++) {
    sa.setName( pointlightnames[i] );
    sa.setInterest( SoSearchAction::FIRST );
    sa.setSearchingAll( false );
    sa.apply( root );
    SoPath * path = sa.getPath();
    if ( path == NULL) return; // Shouldn't happen.

    SoPointLightManip * manip = new SoPointLightManip;
    manip->replaceNode( path );
  }


} 