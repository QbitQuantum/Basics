SegmentsX *CreateSuperSegments(NodesX *nodesx,SegmentsX *segmentsx,WaysX *waysx)
{
 index_t i;
 SegmentsX *supersegmentsx;
 index_t sn=0,ss=0;

 supersegmentsx=NewSegmentList(0);

 if(segmentsx->number==0 || waysx->number==0)
    return(supersegmentsx);

 /* Print the start message */

 printf_first("Creating Super-Segments: Super-Nodes=0 Super-Segments=0");

 /* Map into memory / open the files */

#if !SLIM
 segmentsx->data=MapFile(segmentsx->filename);
 waysx->data=MapFile(waysx->filename);
#else
 segmentsx->fd=ReOpenFile(segmentsx->filename);
 waysx->fd=ReOpenFile(waysx->filename);
#endif

 /* Create super-segments for each super-node. */

 for(i=0;i<nodesx->number;i++)
   {
    if(IsBitSet(nodesx->super,i))
      {
       SegmentX *segmentx;
       int count=0,match;
       Way prevway[MAX_SEG_PER_NODE];

       segmentx=FirstSegmentX(segmentsx,i,1);

       while(segmentx)
         {
          WayX *wayx=LookupWayX(waysx,segmentx->way,1);

          /* Check that this type of way hasn't already been routed */

          match=0;

          if(count>0)
            {
             int j;

             for(j=0;j<count;j++)
                if(!WaysCompare(&prevway[j],&wayx->way))
                  {
                   match=1;
                   break;
                  }
            }

          assert(count<MAX_SEG_PER_NODE); /* Only a limited amount of history stored. */

          prevway[count++]=wayx->way;

          /* Route the way and store the super-segments. */

          if(!match)
            {
             Results *results=FindRoutesWay(nodesx,segmentsx,waysx,i,&wayx->way);
             Result *result=FirstResult(results);

             while(result)
               {
                if(IsBitSet(nodesx->super,result->node) && result->segment!=NO_SEGMENT)
                  {
                   if(wayx->way.type&Way_OneWay && result->node!=i)
                      AppendSegment(supersegmentsx,segmentx->way,i,result->node,DISTANCE((distance_t)result->score)|ONEWAY_1TO2);
                   else
                      AppendSegment(supersegmentsx,segmentx->way,i,result->node,DISTANCE((distance_t)result->score));

                   ss++;
                  }

                result=NextResult(results,result);
               }

             FreeResultsList(results);
            }

          segmentx=NextSegmentX(segmentsx,segmentx,i);
         }

       sn++;

       if(!(sn%10000))
          printf_middle("Creating Super-Segments: Super-Nodes=%"Pindex_t" Super-Segments=%"Pindex_t,sn,ss);
      }
   }

 /* Unmap from memory / close the files */

#if !SLIM
 segmentsx->data=UnmapFile(segmentsx->filename);
 waysx->data=UnmapFile(waysx->filename);
#else
 segmentsx->fd=CloseFile(segmentsx->fd);
 waysx->fd=CloseFile(waysx->fd);
#endif

 /* Print the final message */

 printf_last("Created Super-Segments: Super-Nodes=%"Pindex_t" Super-Segments=%"Pindex_t,sn,ss);

 return(supersegmentsx);
}