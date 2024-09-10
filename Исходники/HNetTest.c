void LoadNetwork()
{
   FILE *nf;
   Boolean isPipe;
   int n=0;

   CreateHeap(&wdNetHeap,"Lattice heap",MSTAK,1,0.0,4000,4000);
   if ( (nf = FOpen(wdNetFn,NetFilter,&isPipe)) == NULL)
      HError(3210,"LoadNetwork: Cannot open Word Net file %s",wdNetFn);
   if((wdNet = ReadLattice(nf,&wdNetHeap,&vocab,TRUE,FALSE))==NULL)
      HError(3210,"LoadNetwork: ReadLattice failed");
   FClose(nf,isPipe);

   printf("Read Word Network with %d nodes / %d arcs\n",wdNet->nn,wdNet->na);

   CreateHeap(&netHeap,"Net heap",MSTAK,1,0,
      wdNet->na*sizeof(NetLink),wdNet->na*sizeof(NetLink));

   net = ExpandWordNet(&netHeap,wdNet,&vocab,&hset);
   printf("Created network with %d nodes / %d links\n",
      net->numNode,net->numLink);

}