int treeReadLen (FILE *fp, tree *tr, boolean readBranches, boolean readNodeLabels, boolean topologyOnly)
{
  nodeptr  
    p;
  
  int      
    i, 
    ch, 
    lcount = 0; 

  for (i = 1; i <= tr->mxtips; i++) 
    {
      tr->nodep[i]->back = (node *) NULL; 
      /*if(topologyOnly)
	tr->nodep[i]->support = -1;*/
    }

  for(i = tr->mxtips + 1; i < 2 * tr->mxtips; i++)
    {
      tr->nodep[i]->back = (nodeptr)NULL;
      tr->nodep[i]->next->back = (nodeptr)NULL;
      tr->nodep[i]->next->next->back = (nodeptr)NULL;
      tr->nodep[i]->number = i;
      tr->nodep[i]->next->number = i;
      tr->nodep[i]->next->next->number = i;

      /*if(topologyOnly)
	{
	  tr->nodep[i]->support = -2;
	  tr->nodep[i]->next->support = -2;
	  tr->nodep[i]->next->next->support = -2;
	  }*/
    }

  if(topologyOnly)
    tr->start       = tr->nodep[tr->mxtips];
  else
    tr->start       = tr->nodep[1];

  tr->ntips       = 0;
  tr->nextnode    = tr->mxtips + 1;      
 
  for(i = 0; i < tr->numBranches; i++)
    tr->partitionSmoothed[i] = FALSE;
  
  tr->rooted      = FALSE;     

  p = tr->nodep[(tr->nextnode)++]; 
  
  while((ch = treeGetCh(fp)) != '(');
      
  if(!topologyOnly)
    assert(readBranches == FALSE && readNodeLabels == FALSE);
  
       
  if (! addElementLen(fp, tr, p, readBranches, readNodeLabels, &lcount))                 
    assert(0);
  if (! treeNeedCh(fp, ',', "in"))                
    assert(0);
  if (! addElementLen(fp, tr, p->next, readBranches, readNodeLabels, &lcount))
    assert(0);
  if (! tr->rooted) 
    {
      if ((ch = treeGetCh(fp)) == ',') 
	{ 
	  if (! addElementLen(fp, tr, p->next->next, readBranches, readNodeLabels, &lcount))
	    assert(0);	    
	}
      else 
	{                                    /*  A rooted format */
	  tr->rooted = TRUE;
	  if (ch != EOF)  (void) ungetc(ch, fp);
	}	
    }
  else 
    {      
      p->next->next->back = (nodeptr) NULL;
    }
  if (! treeNeedCh(fp, ')', "in"))                
    assert(0);

  if(topologyOnly)
    assert(!(tr->rooted && readNodeLabels));

  (void) treeFlushLabel(fp);
  
  if (! treeFlushLen(fp))                         
    assert(0);
 
  if (! treeNeedCh(fp, ';', "at end of"))       
    assert(0);
  
  if (tr->rooted) 
    {     
      assert(!readNodeLabels);

      p->next->next->back = (nodeptr) NULL;      
      tr->start = uprootTree(tr, p->next->next, FALSE, FALSE);      
      if (! tr->start)                              
	{
	  printf("FATAL ERROR UPROOTING TREE\n");
	  assert(0);
	}    
    }
  else    
    tr->start = findAnyTip(p, tr->mxtips);    
  
  
 
  assert(tr->ntips == tr->mxtips);
  
 
   
  
  return lcount;
}