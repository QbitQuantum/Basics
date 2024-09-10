// (static) Displays information on the console about the media processing
// task.
MpFlowGraphBase* MpMediaTask::mediaInfo(void)
{
   MpFlowGraphBase* flowGraphs[20];
   int              i;
   int              numItems;
   MpMediaTask*     pMediaTask;
   MpFlowGraphBase* pFlowGraph;
   OsStatus         res;

   pMediaTask = MpMediaTask::getMediaTask(0);

   printf("\nMedia processing task information\n");
   printf("  Debug mode:                      %s\n",
             pMediaTask->getDebugMode() ? "TRUE" : "FALSE");

   printf("  Processed Frame Count:           %d\n",
             pMediaTask->numProcessedFrames());

   printf("  Processing Time Limit:           %d usecs\n",
             pMediaTask->getTimeLimit());

   printf("  Processing Limit Exceeded Count: %d\n",
             pMediaTask->getLimitExceededCnt());

   i = pMediaTask->getWaitTimeout();
   if (i < 0)
      printf("  Frame Start Wait Timeout:        INFINITE\n");
   else
      printf("  Frame Start Wait Timeout:        %d\n", i);

   printf("  Wait Timeout Exceeded Count:     %d\n",
             pMediaTask->getWaitTimeoutCnt());

   printf("\n  Flow Graph Information\n");
   printf("    Managed:      %d\n", pMediaTask->numManagedFlowGraphs());
   printf("    Started:      %d\n", pMediaTask->numStartedFlowGraphs());

   pFlowGraph = pMediaTask->getFocus();
   if (pFlowGraph == NULL)
      printf("    Focus:        NULL\n");
   else
      printf("    Focus:        %p\n", pFlowGraph);

   res = pMediaTask->getManagedFlowGraphs(flowGraphs, 20, numItems);
   for (i=0; i < numItems; i++)
      printf("    FlowGraph[%d]: %p\n", i, flowGraphs[i]);
   return pFlowGraph;
}