TPZComponent* TPZNetworkBuilder::parseComponentDefinition( const TPZTag* tag,
                                                           TPZComponent* owner,
                                                           INDEX& index )
{
   TPZString tagName = tag->tagName();
   TPZComponent* rComponent = 0;

   if( tagName == TPZ_TAG_TORUSNET )
   {
      rComponent = TPZNetworkTorus::newFrom(tag,owner);
   }
   else if( tagName == TPZ_TAG_MESHNET )
   {
      rComponent = TPZNetworkMesh::newFrom(tag,owner);
   }
   else if (tagName == TPZ_TAG_MIDIMEWNET )
   {
      rComponent = TPZNetworkMidimew::newFrom(tag,owner);
   }
   else if (tagName == TPZ_TAG_SQUAREMIDIMEWNET )
   {
      rComponent = TPZNetworkSquareMidimew::newFrom(tag,owner);
   }
   else
   {
      TPZString err;
      err.sprintf( ERR_TPZNBLDR_001, (char*)tagName );
      EXIT_PROGRAM(err);
   }

   return rComponent;
}