void SortLayersBy3DZOrder(nsTArray<Layer*>& aLayers)
{
  uint32_t nodeCount = aLayers.Length();
  if (nodeCount > MAX_SORTABLE_LAYERS) {
    return;
  }
  DirectedGraph<Layer*> graph;

#ifdef DEBUG
  if (gDumpLayerSortList) {
    for (uint32_t i = 0; i < nodeCount; i++) {
      if (aLayers.ElementAt(i)->GetDebugColorIndex() == 0) {
        aLayers.ElementAt(i)->SetDebugColorIndex(gColorIndex++);
        if (gColorIndex > 7) {
          gColorIndex = 1;
        }
      }
    }
    fprintf(stderr, " --- Layers before sorting: --- \n");
    DumpLayerList(aLayers);
  }
#endif

  // Iterate layers and determine edges.
  for (uint32_t i = 0; i < nodeCount; i++) {
    for (uint32_t j = i + 1; j < nodeCount; j++) {
      Layer* a = aLayers.ElementAt(i);
      Layer* b = aLayers.ElementAt(j);
      LayerSortOrder order = CompareDepth(a, b);
      if (order == ABeforeB) {
        graph.AddEdge(a, b);
      } else if (order == BBeforeA) {
        graph.AddEdge(b, a);
      }
    }
  }

#ifdef DEBUG
  if (gDumpLayerSortList) {
    fprintf(stderr, " --- Edge List: --- \n");
    DumpEdgeList(graph);
  }
#endif

  // Build a new array using the graph.
  nsTArray<Layer*> noIncoming;
  nsTArray<Layer*> sortedList;

  // Make a list of all layers with no incoming edges.
  noIncoming.AppendElements(aLayers);
  const nsTArray<DirectedGraph<Layer*>::Edge>& edges = graph.GetEdgeList();
  for (uint32_t i = 0; i < edges.Length(); i++) {
    noIncoming.RemoveElement(edges.ElementAt(i).mTo);
  }

  // Move each item without incoming edges into the sorted list,
  // and remove edges from it.
  do {
    if (!noIncoming.IsEmpty()) {
      uint32_t last = noIncoming.Length() - 1;

      Layer* layer = noIncoming.ElementAt(last);
      MOZ_ASSERT(layer); // don't let null layer pointers sneak into sortedList

      noIncoming.RemoveElementAt(last);
      sortedList.AppendElement(layer);

      nsTArray<DirectedGraph<Layer*>::Edge> outgoing;
      graph.GetEdgesFrom(layer, outgoing);
      for (uint32_t i = 0; i < outgoing.Length(); i++) {
        DirectedGraph<Layer*>::Edge edge = outgoing.ElementAt(i);
        graph.RemoveEdge(edge);
        if (!graph.NumEdgesTo(edge.mTo)) {
          // If this node also has no edges now, add it to the list
          noIncoming.AppendElement(edge.mTo);
        }
      }
    }

    // If there are no nodes without incoming edges, but there
    // are still edges, then we have a cycle.
    if (noIncoming.IsEmpty() && graph.GetEdgeCount()) {
      // Find the node with the least incoming edges.
      uint32_t minEdges = UINT_MAX;
      Layer* minNode = nullptr;
      for (uint32_t i = 0; i < aLayers.Length(); i++) {
        uint32_t edgeCount = graph.NumEdgesTo(aLayers.ElementAt(i));
        if (edgeCount && edgeCount < minEdges) {
          minEdges = edgeCount;
          minNode = aLayers.ElementAt(i);
          if (minEdges == 1) {
            break;
          }
        }
      }

      if (minNode) {
        // Remove all of them!
        graph.RemoveEdgesTo(minNode);
        noIncoming.AppendElement(minNode);
      }
    }
  } while (!noIncoming.IsEmpty());
  NS_ASSERTION(!graph.GetEdgeCount(), "Cycles detected!");
#ifdef DEBUG
  if (gDumpLayerSortList) {
    fprintf(stderr, " --- Layers after sorting: --- \n");
    DumpLayerList(sortedList);
  }
#endif

  aLayers.Clear();
  aLayers.AppendElements(sortedList);
}