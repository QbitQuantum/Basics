/* Version for Zoo species */
boolean convertCoordinatesZoo(FILE *goodOut, FILE *badOut, 
			void (*goodResult)(FILE *out, struct coordConvRep *report),
			void (*badResult)(FILE *out, struct coordConvRep *report)) 
/* tries to convert coordinates and prints report 
 depending on function pointers provided. In generial
 goodResult and badResult either generate html or tesxt
 if we are in cgi or testing mode respectively. */
{
struct blatServerTable *serve = NULL;
struct coordConvRep *ccr = createCoordConvRep_mod();
struct dbDb *newDbRec = NULL, *oldDbRec = NULL;
struct sqlConnection *conn = sqlConnect(origGenome);
struct linkedFeatures *lfList = NULL, *lf;
struct sqlResult *sr = NULL;

boolean success = FALSE;

/* Keeps track if we're in an inverted match or not */
boolean inversion = FALSE;

/* Two possible reasons two fail */
boolean incoherent = FALSE;
boolean max_apart= FALSE;

char track[256];
char success_message[256];
char **row;
int rowOffset;
int conv_total=0;
int iteration = 0;

/* These two distances check how different the distance is between the converted and unconverted coordinates.  
   In this case if the distance between a converted versus unconverted block is more than 10 times
   and greater than 10 000 bases, set up a warning... */

int ref_end=0,ref_start,comp_end=0,comp_start=0;

/* Load info from databases into ccr */
oldDbRec = loadDbInformation_mod(origGenome);
ccr->from->chrom = cloneString(chrom);
ccr->from->chromStart = chromStart;
ccr->from->chromEnd = chromEnd;
ccr->from->version = cloneString(oldDbRec->name);
ccr->from->date = cloneString(oldDbRec->description);
ccr->from->nibDir = cloneString(oldDbRec->nibPath);
ccr->seqSize=1000;
newDbRec = loadDbInformation_mod(newGenome);
ccr->to->version = cloneString(newDbRec->name);
ccr->to->date = cloneString(newDbRec->description);
ccr->to->nibDir = cloneString(newDbRec->nibPath);
ccr->good=FALSE;

/* Create the correct track name...  Will have to be changed when multiple versions? */

sprintf(track,"%s_%s",origGenome,newGenome);

/* Get the information from loading the track. */
/* Double check we are not using a track connecting 1 and 2 */

if(!(strstr(track,"2") && strstr(track,"1")))
    {
    sr = hRangeQuery(conn, track, chrom, chromStart, chromEnd, NULL, &rowOffset);
    }

while ((row = sqlNextRow(sr)) != NULL)
    {
    /* Find the correponding track */
    struct psl *psl = pslLoad(row+rowOffset);
    
    /* If first time through... */
    if(iteration==0)
	{
	/* Fill in stuff if first time through... */
	ccr->to->chrom=cloneString(psl->qName);
	ccr->to->chromStart=psl->qStart;
	
	/* Actual point of conversion of coordinates */
	ccr->from->next->chromStart=psl->tStart;      
	ccr->good=TRUE;
	
	success=TRUE;
	}
    
    /* check for erroneous conversion if not first time through */
    /* Check for inversions, massive insertions... */
    
    /* Check for inversion (old start is "bigger" than new start)*/	
    
    if(iteration > 0)
	{
	if((comp_start> psl->qStart))
	    {
	    /* If not currently in an inversion state */
	    if(!inversion )
		/* If not the second time through (first time inversion could be detected) */
		if(iteration > 2)
		    incoherent=TRUE;
	    
	    /* Reset variables used for measuring distance... */
	    
	    /* Set inversion state variable to true */
	    inversion = TRUE;
	    
	    
	    /* Check to see if there are too great distances ... */
	    
	    if( ((comp_start - psl->qEnd)>(10 * (psl->tStart - ref_end))) && ((comp_start - psl->qEnd) > 10000))
		max_apart=TRUE;
	    }
	else 
	    /* No inversion */
	    {
	    /* Check if previous state was an inversion (then flip flop)...*/
	    if(inversion)
		incoherent = TRUE;
	    else
		{
		/* Check to see if the mapping is too far apart */
		if( ((psl->qStart - comp_end) > (10 * (psl->tStart - ref_end))) && ((psl->qStart - comp_end) > 10000))
		    max_apart=TRUE;
		}
	    }
	}
    
    if(inversion)
	{
	if(iteration == 1)
	    ccr->to->chromEnd=comp_end;
	
	ccr->to->chromStart=psl->qStart;
	}
    else
	ccr->to->chromEnd=psl->qEnd;
    
    ccr->from->next->chromEnd=psl->tEnd;
    
    if(max_apart || incoherent)
	{
	success=FALSE;
	break;
	}
    
    if(psl->tStart > ref_end)
	conv_total+=(psl->tEnd - psl->tStart);
    else
	conv_total+=(psl->tEnd - ref_end);
    
    ref_end=psl->tEnd;
    comp_end=psl->qEnd;
    ref_start=psl->tStart;
    comp_start=psl->qStart;
        
    iteration++;
    pslFree(&psl);
    }
		    
if(!success)
    {
    /* Check to see if using version two of zoo.  Not integrated into the database at this stage... */
    if((strstr(origGenome,"2") && strstr(newGenome,"1"))|| (strstr(newGenome,"2") && strstr(origGenome,"1")))
	sprintf(success_message,"Couldn't convert between these two genomes since the cross conversion between the two zoo dataset hasn't been fully integrated into the database");
    else if (max_apart)
	sprintf(success_message, "Coordinates couldn't reliably be converted between the two species.  Try using a smaller window. ");
    else if (incoherent)
	sprintf(success_message, "Coordinates couldn't be converted due to inconsistent inversions.");
    else
	sprintf(success_message,"Couldn't find a corresponding region for the original genome to the new genome.");
    
    ccr->msg=cloneString(success_message);
    badResult(badOut,ccr);
    }
else
    {
    sprintf(success_message,"Successfully converted (%3.1f%% of the original region was converted.)",((float)(conv_total * 100))/(float)(chromEnd-chromStart));
    ccr->msg=cloneString(success_message);
    goodResult(goodOut,ccr);
    }

dbDbFree(&oldDbRec);
dbDbFree(&newDbRec);
coordConvRepFreeList(&ccr); 
return success;
}