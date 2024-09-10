// (static) Displays information on the console about the specified flow
// graph.
void MpFlowGraphBase::flowGraphInfo(MpFlowGraphBase* pFlowGraph)
{
   int         i;
   MpResource* pResource;

   if (NULL == pFlowGraph) {
      MpMediaTask* pMediaTask = MpMediaTask::getMediaTask(0);
      pFlowGraph = pMediaTask->getFocus();
      if (NULL == pFlowGraph) {
         pMediaTask->getManagedFlowGraphs(&pFlowGraph, 1, i);
         if (0 == i) pFlowGraph = NULL;
      }
   }
   if (NULL == pFlowGraph) {
      printf("No flowGraph to display!\n");
      return;
   }
   printf("\nFlow graph information for %p\n", pFlowGraph);
   printf("  State:                    %s\n",
             pFlowGraph->isStarted() ? "STARTED" : "STOPPED");

   printf("  Processed Frame Count:    %d\n",
             pFlowGraph->numFramesProcessed());

   printf("  Samples Per Frame:        %d\n",
             pFlowGraph->getSamplesPerFrame());

   printf("  Samples Per Second:       %d\n",
             pFlowGraph->getSamplesPerSec());

   pResource = pFlowGraph->mpResourceInProcess;
   if (pResource == NULL)
      printf("  Resource Being Processed: NULL\n");
   else
      printf("  Resource Being Processed: %p\n", pResource);

   printf("\n  Resource Information\n");
   printf("    Resources:   %d\n", pFlowGraph->numResources());
   printf("    Links: %d\n", pFlowGraph->numLinks());
   for (i=0; i < pFlowGraph->mResourceCnt; i++)
   {
      pResource = pFlowGraph->mUnsorted[i];
      pResource->resourceInfo(pResource, i);
   }
}