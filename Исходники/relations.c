Relations *LoadRelationList(const char *filename)
{
 Relations *relations;
#if SLIM
 int i;
#endif

 relations=(Relations*)malloc(sizeof(Relations));

#if !SLIM

 relations->data=MapFile(filename);

 /* Copy the RelationsFile header structure from the loaded data */

 relations->file=*((RelationsFile*)relations->data);

 /* Set the pointers in the Relations structure. */

 relations->turnrelations=(TurnRelation*)(relations->data+sizeof(RelationsFile));

#else

 relations->fd=ReOpenFile(filename);

 /* Copy the RelationsFile header structure from the loaded data */

 ReadFile(relations->fd,&relations->file,sizeof(RelationsFile));

 relations->troffset=sizeof(RelationsFile);

 for(i=0;i<sizeof(relations->cached)/sizeof(relations->cached[0]);i++)
    relations->incache[i]=NO_RELATION;

#endif

 if(relations->file.trnumber>0)
   {
    TurnRelation *relation;

    relation=LookupTurnRelation(relations,0,1);

    relations->via_start =relation->via;

    relation=LookupTurnRelation(relations,relations->file.trnumber-1,1);

    relations->via_end =relation->via;
   }

 return(relations);
}