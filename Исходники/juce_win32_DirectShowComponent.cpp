 bool checkDShowAvailability()
 {
     ComSmartPtr <IGraphBuilder> graph;
     return SUCCEEDED (graph.CoCreateInstance (CLSID_FilterGraph));
 }