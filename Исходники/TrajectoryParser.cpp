int calculateVirtualStreamPos(struct VirtualStream * stream,ObjectIDHandler ObjID,unsigned int timeAbsMilliseconds,float * pos)
{
   if (stream==0) { fprintf(stderr,"calculateVirtualStreamPos called with null stream\n"); return 0; }
   if (stream->object==0) { fprintf(stderr,"calculateVirtualStreamPos called with null object array\n"); return 0; }
   if (stream->numberOfObjects<=ObjID) { fprintf(stderr,"calculateVirtualStreamPos ObjID %u is out of bounds (%u)\n",ObjID,stream->numberOfObjects); return 0; }
   if (stream->object[ObjID].frame == 0 )  { fprintf(stderr,"calculateVirtualStreamPos ObjID %u does not have a frame array allocated\n",ObjID); return 0; }
   if (stream->object[ObjID].numberOfFrames == 0 ) { fprintf(stderr,"calculateVirtualStreamPos ObjID %u has 0 frames\n",ObjID); return 0; }


   if (stream->autoRefresh != 0 )
    {
         //Check for refreshed version ?
       if (stream->autoRefresh < timeAbsMilliseconds-stream->lastRefresh )
          {
            unsigned long current_size = getFileSize(stream->filename);
            if (current_size != stream->fileSize)
             {
              refreshVirtualStream(stream);
              stream->lastRefresh = timeAbsMilliseconds;
             }
          }
    }

   unsigned int FrameIDToReturn = 0;
   unsigned int FrameIDLast = 0;
   unsigned int FrameIDNext = 0;


   /*!OK , Two major cases here..! The one is a simple Next frame getter , the second is a more complicated interpolated frame getter..! */
   if ( (stream->object[ObjID].MAX_numberOfFrames == 0 ) )
   {
       fillPosWithNull(stream,ObjID,pos);
       return 1;
   } else
   if  ( (stream->ignoreTime) || (stream->object[ObjID].MAX_numberOfFrames == 1 ) )
   {
    //We might want to ignore time and just return frame after frame on each call!
    //Also if we only got one frame for the object there is no point in trying to interpolate time etc.. so just handle things here..
    if ( stream->object[ObjID].lastFrame +1 >= stream->object[ObjID].MAX_numberOfFrames ) { stream->object[ObjID].lastFrame  = 0; }
    FrameIDToReturn = stream->object[ObjID].lastFrame;
    ++stream->object[ObjID].lastFrame;

    fillPosWithFrame(stream,ObjID,FrameIDToReturn,pos);

    FrameIDLast = FrameIDToReturn;
    FrameIDNext = FrameIDToReturn+1;
    if ( FrameIDNext >= stream->object[ObjID].numberOfFrames )
     {
       FrameIDNext  = 0;
     }

     return 1;

   } /*!END OF SIMPLE FRAME GETTER*/
   else
   { /*!START OF INTERPOLATED FRAME GETTER*/
     //This is the case when we respect time , we will pick two frames and interpolate between them
     if ( timeAbsMilliseconds > stream->object[ObjID].MAX_timeOfFrames )
     {
       //This means we have passed the last frame.. so lets find out where we really are..
       timeAbsMilliseconds = timeAbsMilliseconds % stream->object[ObjID].MAX_timeOfFrames;
       //timeAbsMilliseconds should contain a valid value now somewhere from 0->MAX_timeOfFrames
     }

     #if PRINT_DEBUGGING_INFO
     fprintf(stderr,"Object %u has %u frames , lets search where we are \n",ObjID,stream->object[ObjID].numberOfFrames);
     #endif

     //We scan all the frames to find out the "last one" and the "next one"
     unsigned int i =0;
     for ( i=0; i <stream->object[ObjID].MAX_numberOfFrames-1; i++ )
      {
       if (( stream->object[ObjID].frame[i].time <= timeAbsMilliseconds )
                 &&
           ( timeAbsMilliseconds <= stream->object[ObjID].frame[i+1].time )  )
            {
               //This is the "next" frame!
               FrameIDLast = i;
               FrameIDNext = i+1;
               //This should be handled by raw response to zero elemetn :P
              break;
            }
      }

    //We now have our Last and Next frame , all that remains is extracting the
    //interpolated time between them..!
    return fillPosWithInterpolatedFrame(stream,ObjID,pos,FrameIDLast,FrameIDNext,timeAbsMilliseconds);

   } /*!END OF INTERPOLATED FRAME GETTER*/

    return 0;
}