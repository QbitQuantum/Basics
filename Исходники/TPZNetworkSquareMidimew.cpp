void TPZNetworkSquareMidimew :: initialize()
{
   if( isInitializated() ) return;
   
   /* Check consistency of parameters */
   if(getSizeY()!=1 ||getSizeZ()!=1)
   {
     TPZString err;
     err.sprintf( ERR_TPZTONET_002, (char*)getRouterId() );
     err.sprintf("\nSquare Midimew Network Ysize and Zsize must be 1. Al nodes in Xsize!");
     EXIT_PROGRAM(err); 
   }

   if((int)ceil(sqrt((float)getSizeX()))%2 || getSizeX() < 4 )
   {
     TPZString err;
     err.sprintf( ERR_TPZTONET_002, (char*)getRouterId() );
     err.sprintf("\n Square Midimew Network Xsize must be an even 2's power(4,16,64,256,1024,4096...)");
     EXIT_PROGRAM(err); 
   }

   if( !getSizeX() || !getSizeY() || !getSizeZ() )
   {
      TPZString err;
      err.sprintf(ERR_TPZTONET_001, getSizeX(), getSizeY(), getSizeZ() );
      EXIT_PROGRAM(err);
   }

   /* Create the routers for each node */
   int i;     
   for( i=0; i<getSizeX(); i++ )
   {
      TPZPosition pos(i,0,0);
      TPZRouter* newRouter = (TPZRouter*)
                             (TPZRouter::routerBuilder->createComponentWithId(getRouterId(),this));
      if( ! newRouter )
      {
          TPZString err;
          err.sprintf( ERR_TPZTONET_002, (char*)getRouterId() );
          EXIT_PROGRAM(err);
      }
      newRouter->setPosition(pos);                       
      addRouter(newRouter);
   }

   /* Connect the routers together */
   for( i=0; i<getSizeX(); i++ )
   {
      initializeConnectionsFor(TPZPosition(i,0,0));
   }
  
   /* Other initialization tasks */
   generateRoutingTable();

   setInitializated(true);
   setSimulation(getSimulation());
}