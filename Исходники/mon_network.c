void MonNetworkGatherData(double *cf_this)
{
FILE *pp;
char local[CF_BUFSIZE],remote[CF_BUFSIZE],comm[CF_BUFSIZE];
struct Item *in[ATTR],*out[ATTR];
char *sp;
int i;
char vbuff[CF_BUFSIZE];

Debug("GatherSocketData()\n");

for (i = 0; i < ATTR; i++)
   {
   in[i] = out[i] = NULL;
   }

if (ALL_INCOMING != NULL)
   {
   DeleteItemList(ALL_INCOMING);
   ALL_INCOMING = NULL;
   }

if (ALL_OUTGOING != NULL)
   {
   DeleteItemList(ALL_OUTGOING);
   ALL_OUTGOING = NULL;
   }

sscanf(VNETSTAT[VSYSTEMHARDCLASS],"%s",comm);

strcat(comm," -n");

if ((pp = cf_popen(comm,"r")) == NULL)
   {
   return;
   }

while (!feof(pp))
   {
   memset(local,0,CF_BUFSIZE);
   memset(remote,0,CF_BUFSIZE);

   CfReadLine(vbuff,CF_BUFSIZE,pp);

   if (strstr(vbuff,"UNIX"))
      {
      break;
      }

   if (!strstr(vbuff,"."))
      {
      continue;
      }

   /* Different formats here ... ugh.. */

   if (strncmp(vbuff,"tcp",3) == 0)
      {
      sscanf(vbuff,"%*s %*s %*s %s %s",local,remote); /* linux-like */
      }
   else
      {
      sscanf(vbuff,"%s %s",local,remote);             /* solaris-like */
      }

   if (strlen(local) == 0)
      {
      continue;
      }

   for (sp = local+strlen(local); (*sp != '.') && (sp > local); sp--)
      {
      }

   sp++;

   if ((strlen(sp) < 5) &&!IsItemIn(ALL_INCOMING,sp))
      {
      PrependItem(&ALL_INCOMING,sp,NULL);
      }

   for (sp = remote+strlen(remote); (sp >= remote) && !isdigit((int)*sp); sp--)
      {
      }

   sp++;

   if ((strlen(sp) < 5) && !IsItemIn(ALL_OUTGOING,sp))
      {
      PrependItem(&ALL_OUTGOING,sp,NULL);
      }

   for (i = 0; i < ATTR; i++)
      {
      char *spend;

      for (spend = local+strlen(local)-1; isdigit((int)*spend); spend--)
         {
         }

      spend++;

      if (strcmp(spend,ECGSOCKS[i].portnr) == 0)
         {
         cf_this[ECGSOCKS[i].in]++;
         AppendItem(&in[i],vbuff,"");
         }

      for (spend = remote+strlen(remote)-1; (sp >= remote) && isdigit((int)*spend); spend--)
         {
         }

      spend++;

      if (strcmp(spend,ECGSOCKS[i].portnr) == 0)
         {
         cf_this[ECGSOCKS[i].out]++;
         AppendItem(&out[i],vbuff,"");
         }
      }
   }

cf_pclose(pp);

/* Now save the state for ShowState() cf2 version alert function IFF
   the state is not smaller than the last or at least 40 minutes
   older. This mirrors the persistence of the maxima classes */


for (i = 0; i < ATTR; i++)
   {
   struct stat statbuf;
   time_t now = time(NULL);

   Debug("save incoming %s\n",ECGSOCKS[i].name);
   snprintf(vbuff,CF_MAXVARSIZE,"%s/state/cf_incoming.%s",CFWORKDIR,ECGSOCKS[i].name);
   if (cfstat(vbuff,&statbuf) != -1)
      {
      if ((ByteSizeList(in[i]) < statbuf.st_size) && (now < statbuf.st_mtime+40*60))
         {
         CfOut(cf_verbose,"","New state %s is smaller, retaining old for 40 mins longer\n",ECGSOCKS[i].name);
         DeleteItemList(in[i]);
         continue;
         }
      }

   SetNetworkEntropyClasses(ECGSOCKS[i].name,"in",in[i]);
   RawSaveItemList(in[i],vbuff);
   DeleteItemList(in[i]);
   Debug("Saved in netstat data in %s\n",vbuff);
   }

for (i = 0; i < ATTR; i++)
   {
   struct stat statbuf;
   time_t now = time(NULL);

   Debug("save outgoing %s\n",ECGSOCKS[i].name);
   snprintf(vbuff,CF_MAXVARSIZE,"%s/state/cf_outgoing.%s",CFWORKDIR,ECGSOCKS[i].name);

   if (cfstat(vbuff,&statbuf) != -1)
      {
      if ((ByteSizeList(out[i]) < statbuf.st_size) && (now < statbuf.st_mtime+40*60))
         {
         CfOut(cf_verbose,"","New state %s is smaller, retaining old for 40 mins longer\n",ECGSOCKS[i].name);
         DeleteItemList(out[i]);
         continue;
         }
      }

   SetNetworkEntropyClasses(ECGSOCKS[i].name,"out",out[i]);
   RawSaveItemList(out[i],vbuff);
   Debug("Saved out netstat data in %s\n",vbuff);
   DeleteItemList(out[i]);
   }
}