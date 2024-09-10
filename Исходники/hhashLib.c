/**************************************************************
*
*  hashCreate - Creates an empty hash table
*
*
*  This routine creates am empty hash table of size <size> 
*  and initializes it. Memory for the buffer is allocated from 
*  the system memory partition.
*
*
* RETURNS:
* ID of the hash table , or NULL if memory cannot be allocated.
*
*	Author Greg Brissey 8/5/93
*/
HASH_ID hashCreate(int size,PFL hashf, PFI cmpf, char* idstr)
/* int size;  size of hash table */
/* PFL hashf;  pointer to user defined hashing function */
/* PFI cmpf;   pointer to user defined comparison function */
/* char* idstr;   Identifing string for user */
{
  HASH_ID pHashTbl;
  HASH_ENTRY *pHashAry;
  register long i;
  char tmpstr[80];

  pHashTbl = (HASH_ID) malloc(sizeof(HASH_TABLE));  /* create structure */

  if (pHashTbl == NULL) 
     return (NULL);
 

  if (idstr == NULL) 
  {
     sprintf(tmpstr,"%s %d\n",HashIDStr,++HIdCnt);
     pHashTbl->pHashIdStr = (char *) malloc(strlen(tmpstr)+2);
  }
  else
  {
     pHashTbl->pHashIdStr = (char *) malloc(strlen(idstr)+2);
  }

  if (pHashTbl->pHashIdStr == NULL)
  {
     free(pHashTbl);
     return(NULL);
  }

  if (idstr == NULL) 
  {
     strcpy(pHashTbl->pHashIdStr,tmpstr);
  }
  else
  {
     strcpy(pHashTbl->pHashIdStr,idstr);
  }

  /* create space for all table entries  */
  pHashTbl->pHashEntries = (HASH_ENTRY *) malloc( (size * sizeof(HASH_ENTRY)) );  

  if (pHashTbl->pHashEntries == NULL) 
  {
     free(pHashTbl->pHashIdStr);
     free(pHashTbl);
     return (NULL);
  }

  pHashTbl->numEntries =(long) 0;
  pHashTbl->maxEntries = size;
  pHashTbl->collisions = (long) 0;

  if (hashf == NULL)
     pHashTbl->pHashFunc = strhash; /* if users func is NULL use default hash */
  else
     pHashTbl->pHashFunc = hashf; /* set up users hash function */

  if (cmpf == NULL)
     pHashTbl->pCmpFunc = cmpstrs;  /* if users func is NULL use default hash */
  else
     pHashTbl->pCmpFunc = cmpf; 	  /* set up users hash function */

  pHashAry = pHashTbl->pHashEntries;
  /* initialize hash table */
  for(i=0;i<size;i++)
  {
    pHashAry[i].hashKey = NULL;
    pHashAry[i].refAddr= NULL;
  }
   
  return( pHashTbl );
}