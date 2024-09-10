void RemoveNonHighwayNodes(NodesX *nodesx,SegmentsX *segmentsx)
{
 NodeX nodex;
 index_t total=0,highway=0,nothighway=0;
 ll_bin_t lat_min_bin,lat_max_bin,lon_min_bin,lon_max_bin;
 latlong_t lat_min,lat_max,lon_min,lon_max;
 int fd;

 /* Print the start message */

 printf_first("Checking Nodes: Nodes=0");

 /* While we are here we can work out the range of data */

 lat_min=radians_to_latlong( 2);
 lat_max=radians_to_latlong(-2);
 lon_min=radians_to_latlong( 4);
 lon_max=radians_to_latlong(-4);

 /* Re-open the file read-only and a new file writeable */

 nodesx->fd=ReOpenFile(nodesx->filename);

 DeleteFile(nodesx->filename);

 fd=OpenFileNew(nodesx->filename);

 /* Modify the on-disk image */

 while(!ReadFile(nodesx->fd,&nodex,sizeof(NodeX)))
   {
    if(!IsBitSet(segmentsx->usednode,total))
       nothighway++;
    else
      {
       nodex.id=highway;

       WriteFile(fd,&nodex,sizeof(NodeX));

       nodesx->idata[highway]=nodesx->idata[total];
       highway++;

       if(nodex.latitude<lat_min)
          lat_min=nodex.latitude;
       if(nodex.latitude>lat_max)
          lat_max=nodex.latitude;
       if(nodex.longitude<lon_min)
          lon_min=nodex.longitude;
       if(nodex.longitude>lon_max)
          lon_max=nodex.longitude;
      }

    total++;

    if(!(total%10000))
       printf_middle("Checking Nodes: Nodes=%"Pindex_t" Highway=%"Pindex_t" not-Highway=%"Pindex_t,total,highway,nothighway);
   }

 nodesx->number=highway;

 /* Close the files */

 nodesx->fd=CloseFile(nodesx->fd);
 CloseFile(fd);

 /* Work out the number of bins */

 lat_min_bin=latlong_to_bin(lat_min);
 lon_min_bin=latlong_to_bin(lon_min);
 lat_max_bin=latlong_to_bin(lat_max);
 lon_max_bin=latlong_to_bin(lon_max);

 nodesx->latzero=lat_min_bin;
 nodesx->lonzero=lon_min_bin;

 nodesx->latbins=(lat_max_bin-lat_min_bin)+1;
 nodesx->lonbins=(lon_max_bin-lon_min_bin)+1;

 /* Free the now-unneeded index */

 free(segmentsx->usednode);
 segmentsx->usednode=NULL;

 /* Allocate and set the super-node markers */

 nodesx->super=(uint8_t*)malloc((1+nodesx->number/8)*sizeof(uint8_t));

 assert(nodesx->super); /* Check calloc() worked */

 memset(nodesx->super,~0,(1+nodesx->number/8));

 /* Print the final message */

 printf_last("Checked Nodes: Nodes=%"Pindex_t" Highway=%"Pindex_t" not-Highway=%"Pindex_t,total,highway,nothighway);
}