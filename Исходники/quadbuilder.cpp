int main(int argc, char** argv)
{
  if (argc<4)
  {
    fprintf(stderr,"%s node_in_file edge_in_file map_out_path",argv[0]);
    exit(-1);
  }
  const char* node_in_fname = argv[1];
  const char* edge_in_fname = argv[2];
  const char* map_out_path = argv[3];
  MFRNodeArray nodes(node_in_fname);
  MFREdgeArray edges(edge_in_fname, nodes);

  
  fprintf(stderr,"Sort edges\n");fflush(stderr);
  qsort(edges.edges, edges.nredges, sizeof(MFREdgeInt), strength_compare);

  fprintf(stderr,"Max edge strength: %d\n",edges.edges[0].strength);
  if (edges.edges[0].strength < edges.edges[edges.nredges-1].strength)
  {
    fprintf(stderr, "@@@@@@@@@@@@@@@@@@@@\nWrong sorting\n@@@@@@@@@@@@@@@@@@@@@@\n");
    exit(-1);
  }
  fprintf(stderr,"Finished sorting edges\n");fflush(stderr);

  fprintf(stderr,"Count edges and store with nodes\n");fflush(stderr);
  {
    int i;
    for (i=0;i<edges.nredges;i++)
    {
      edges.edges[i].nodeA->totalnredges ++;
      edges.edges[i].nodeB->totalnredges ++;
    }
  }
//ier@
  fprintf(stderr,"Finished counting edges\n");fflush(stderr);



  fprintf(stderr,"Cleaning names (should perhaps be done earlier?)\n");fflush(stderr);
  nodes.CleanNames();
  fprintf(stderr,"Finished cleaning names\n");fflush(stderr);


//  nodes.debug_show_if_sorted(12);
  
  MFRQuadTree quadTree(nodes, quadLevels);
  
#define MAX_NODES_PER_QUAD 50  
  
  quadTree.BuildTree(MAX_NODES_PER_QUAD);

  quadTree.AssignQuadIds();

  fprintf(stderr,"Writing out quadtree\n");fflush(stderr);

  nrquadnodeswritten = 0;

  int nredges = edges.nredges;
  int i;

#define MAX_EDGES_PER_NODE 25

  fprintf(stderr,"Collecting edges for quads (limited to max 25 per node)\n");fflush(stderr);
  CollectEdgesIntoQuads(nodes, edges, quadTree, MAX_EDGES_PER_NODE);
  fprintf(stderr, "Done assigning edges to quads (max 25 edges per node)\n");fflush(stderr);
  quadTree.DetermineStats(edges);
  fprintf(stderr,"Writing nodeid lookup table\n");fflush(stderr);
  WriteHashtable(map_out_path, nodes, edges, quadTree);
  WriteMap(map_out_path, nodes, edges, quadTree);
  {
    char fnamebuilder[1024];
    if (quadLevels)
    {
      sprintf(fnamebuilder,"%squad_",map_out_path);
      WriteRootJSON(fnamebuilder, nodes, edges, quadTree, quadTree.root, ECompactModeCompact);

      sprintf(fnamebuilder,"%sequad_",map_out_path);
      WriteRootJSON(fnamebuilder, nodes, edges, quadTree, quadTree.root, ECompactModeExpanded);

      fprintf(stderr,"Collecting edges for quads (unlimited)\n");fflush(stderr);
      CollectEdgesIntoQuads(nodes, edges, quadTree, 0);
      fprintf(stderr, "Done assigning edges to quads (unlimited)\n");fflush(stderr);
      sprintf(fnamebuilder,"%sxquad_",map_out_path);
      WriteRootJSON(fnamebuilder, nodes, edges, quadTree, quadTree.root, ECompactModeFull);
    }
    else
    {
      sprintf(fnamebuilder,"%squad_",map_out_path);
      WriteRootJSON(fnamebuilder, nodes, edges, quadTree, quadTree.root, 0);
    }
  }
  fprintf(stderr,"Finisned\n");fflush(stderr);
  return 0;
}