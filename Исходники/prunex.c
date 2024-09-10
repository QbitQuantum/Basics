void PruneIsolatedRegions(NodesX *nodesx,SegmentsX *segmentsx,WaysX *waysx,distance_t minimum)
{
 WaysX *newwaysx;
 WayX tmpwayx;
 transport_t transport;
 BitMask *connected,*region;
 index_t *regionsegments,*othersegments;
 index_t nallocregionsegments,nallocothersegments;

 if(nodesx->number==0 || segmentsx->number==0)
    return;

 /* Map into memory / open the files */

#if !SLIM
 nodesx->data=MapFile(nodesx->filename_tmp);
 segmentsx->data=MapFileWriteable(segmentsx->filename_tmp);
 waysx->data=MapFile(waysx->filename_tmp);
#else
 nodesx->fd=SlimMapFile(nodesx->filename_tmp);
 segmentsx->fd=SlimMapFileWriteable(segmentsx->filename_tmp);
 waysx->fd=SlimMapFile(waysx->filename_tmp);

 InvalidateNodeXCache(nodesx->cache);
 InvalidateSegmentXCache(segmentsx->cache);
 InvalidateWayXCache(waysx->cache);
#endif

 newwaysx=NewWayList(0,0);
 CloseFileBuffered(newwaysx->fd);

 newwaysx->fd=SlimMapFileWriteable(newwaysx->filename_tmp);

 connected=AllocBitMask(segmentsx->number);
 region   =AllocBitMask(segmentsx->number);

 logassert(connected,"Failed to allocate memory (try using slim mode?)"); /* Check AllocBitMask() worked */
 logassert(region,"Failed to allocate memory (try using slim mode?)");    /* Check AllocBitMask() worked */

 regionsegments=(index_t*)malloc((nallocregionsegments=1024)*sizeof(index_t));
 othersegments =(index_t*)malloc((nallocothersegments =1024)*sizeof(index_t));

 logassert(regionsegments,"Failed to allocate memory (try using slim mode?)"); /* Check malloc() worked */
 logassert(othersegments,"Failed to allocate memory (try using slim mode?)");  /* Check malloc() worked */

 /* Loop through the transport types */

 for(transport=Transport_None+1;transport<Transport_Count;transport++)
   {
    index_t i,j;
    index_t nregions=0,npruned=0,nadjusted=0;
    const char *transport_str=TransportName(transport);
    transports_t transports=TRANSPORTS(transport);

    if(!(waysx->allow&transports))
       continue;

    /* Print the start message */

    printf_first("Pruning Isolated Regions (%s): Segments=0 Adjusted=0 Pruned=0",transport_str);

    /* Loop through the segments and find the disconnected ones */

    ClearAllBits(connected,segmentsx->number);
    ClearAllBits(region   ,segmentsx->number);

    for(i=0;i<segmentsx->number;i++)
      {
       index_t nregionsegments=0,nothersegments=0;
       distance_t total=0;
       SegmentX *segmentx;
       WayX *wayx;

       if(IsBitSet(connected,i))
          goto endloop;

       segmentx=LookupSegmentX(segmentsx,i,1);

       if(IsPrunedSegmentX(segmentx))
          goto endloop;

       if(segmentx->way<waysx->number)
          wayx=LookupWayX(waysx,segmentx->way,1);
       else
          SlimFetch(newwaysx->fd,(wayx=&tmpwayx),sizeof(WayX),(segmentx->way-waysx->number)*sizeof(WayX));

       if(!(wayx->way.allow&transports))
          goto endloop;

       othersegments[nothersegments++]=i;
       SetBit(region,i);

       do
         {
          index_t thissegment,nodes[2];

          thissegment=othersegments[--nothersegments];

          if(nregionsegments==nallocregionsegments)
             regionsegments=(index_t*)realloc(regionsegments,(nallocregionsegments+=1024)*sizeof(index_t));

          regionsegments[nregionsegments++]=thissegment;

          segmentx=LookupSegmentX(segmentsx,thissegment,1);

          nodes[0]=segmentx->node1;
          nodes[1]=segmentx->node2;
          total+=DISTANCE(segmentx->distance);

          for(j=0;j<2;j++)
            {
             NodeX *nodex=LookupNodeX(nodesx,nodes[j],1);

             if(!(nodex->allow&transports))
                continue;

             segmentx=FirstSegmentX(segmentsx,nodes[j],1);

             while(segmentx)
               {
                index_t segment=IndexSegmentX(segmentsx,segmentx);

                if(segment!=thissegment)
                  {
                   if(segmentx->way<waysx->number)
                      wayx=LookupWayX(waysx,segmentx->way,1);
                   else
                      SlimFetch(newwaysx->fd,(wayx=&tmpwayx),sizeof(WayX),(segmentx->way-waysx->number)*sizeof(WayX));

                   if(wayx->way.allow&transports)
                     {
                      /* Already connected - finish */

                      if(IsBitSet(connected,segment))
                        {
                         total=minimum;
                         goto foundconnection;
                        }

                      /* Not in region - add to list */

                      if(!IsBitSet(region,segment))
                        {
                         if(nothersegments==nallocothersegments)
                            othersegments=(index_t*)realloc(othersegments,(nallocothersegments+=1024)*sizeof(index_t));

                         othersegments[nothersegments++]=segment;
                         SetBit(region,segment);
                        }
                     }
                  }

                segmentx=NextSegmentX(segmentsx,segmentx,nodes[j]);
               }
            }
         }
       while(nothersegments>0 && total<minimum);

      foundconnection:

       /* Prune the segments or mark them as connected */

       if(total<minimum)        /* not connected - delete them */
         {
          nregions++;

          for(j=0;j<nregionsegments;j++)
            {
             SegmentX *segmentx;
             WayX *wayx,tmpwayx;

             SetBit(connected,regionsegments[j]); /* not really connected, but don't need to check again */
             ClearBit(region,regionsegments[j]);

             segmentx=LookupSegmentX(segmentsx,regionsegments[j],1);

             if(segmentx->way<waysx->number)
                wayx=LookupWayX(waysx,segmentx->way,1);
             else
                SlimFetch(newwaysx->fd,(wayx=&tmpwayx),sizeof(WayX),(segmentx->way-waysx->number)*sizeof(WayX));

             if(wayx->way.allow==transports)
               {
                prune_segment(segmentsx,segmentx);

                npruned++;
               }
             else
               {
                if(segmentx->way<waysx->number) /* create a new way */
                  {
                   tmpwayx=*wayx;

                   tmpwayx.way.allow&=~transports;

                   segmentx->way=waysx->number+newwaysx->number;

                   SlimReplace(newwaysx->fd,&tmpwayx,sizeof(WayX),(segmentx->way-waysx->number)*sizeof(WayX));

                   newwaysx->number++;

                   PutBackSegmentX(segmentsx,segmentx);
                  }
                else            /* modify the existing one */
                  {
                   tmpwayx.way.allow&=~transports;

                   SlimReplace(newwaysx->fd,&tmpwayx,sizeof(WayX),(segmentx->way-waysx->number)*sizeof(WayX));
                  }

                nadjusted++;
               }
            }
         }
       else                     /* connected - mark as part of the main region */
         {
          for(j=0;j<nregionsegments;j++)
            {
             SetBit(connected,regionsegments[j]);
             ClearBit(region,regionsegments[j]);
            }

          for(j=0;j<nothersegments;j++)
            {
             SetBit(connected,othersegments[j]);
             ClearBit(region,othersegments[j]);
            }
         }

      endloop:

       if(!((i+1)%10000))
          printf_middle("Pruning Isolated Regions (%s): Segments=%"Pindex_t" Adjusted=%"Pindex_t" Pruned=%"Pindex_t" (%"Pindex_t" Regions)",transport_str,i+1,nadjusted,npruned,nregions);
      }

    /* Print the final message */

    printf_last("Pruned Isolated Regions (%s): Segments=%"Pindex_t" Adjusted=%"Pindex_t" Pruned=%"Pindex_t" (%"Pindex_t" Regions)",transport_str,segmentsx->number,nadjusted,npruned,nregions);
   }

 /* Unmap from memory / close the files */

 free(region);
 free(connected);

 free(regionsegments);
 free(othersegments);

#if !SLIM
 nodesx->data=UnmapFile(nodesx->data);
 segmentsx->data=UnmapFile(segmentsx->data);
 waysx->data=UnmapFile(waysx->data);
#else
 nodesx->fd=SlimUnmapFile(nodesx->fd);
 segmentsx->fd=SlimUnmapFile(segmentsx->fd);
 waysx->fd=SlimUnmapFile(waysx->fd);
#endif

 SlimUnmapFile(newwaysx->fd);

 waysx->number+=newwaysx->number;

 waysx->fd=OpenFileBufferedAppend(waysx->filename_tmp);

 newwaysx->fd=ReOpenFileBuffered(newwaysx->filename_tmp);

 while(!ReadFileBuffered(newwaysx->fd,&tmpwayx,sizeof(WayX)))
    WriteFileBuffered(waysx->fd,&tmpwayx,sizeof(WayX));

 CloseFileBuffered(waysx->fd);
 CloseFileBuffered(newwaysx->fd);

 FreeWayList(newwaysx,0);
}