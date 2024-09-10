 QString getId( const Soprano::Node& node ) {
     if ( node.isResource() ) {
         return QString::fromLatin1( node.uri().toEncoded() );
     }
     else if ( node.isBlank() ) {
         return bnodeIdPrefix() + node.toString();
     }
     else {
         return QString();
     }
 }