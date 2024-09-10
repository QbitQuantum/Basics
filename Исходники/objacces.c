static int GetPolygon(LWOBInfo *object, LWPolygon *poly)
{
   unsigned short pntcnt;
   unsigned short pointval;
   unsigned short junk;
   unsigned short detail;
   short surface;
   int k,x;


   fsetpos(object->fp,&object->polPosCur);
   if (object->polSizeCur<object->polSize){


      fread(&pntcnt,2,1,object->fp);


      BSWAP_W(pntcnt)   ;


      object->polSizeCur = object->polSizeCur + 2;


      poly->npoints = pntcnt;


      for(x=0;x<pntcnt;x++){
         fread(&pointval,2,1,object->fp);
         BSWAP_W(pointval);


         object->polSizeCur = object->polSizeCur + 2;
         poly->plist[x]=pointval;
         }


      fread(&surface,2,1,object->fp);
      BSWAP_W(surface);


      object->polSizeCur = object->polSizeCur + 2;


      if (surface<0)
      {
         fread(&detail,2,1,object->fp);
         BSWAP_W(detail);
         object->polSizeCur = object->polSizeCur + 2;


         for(k=0;k<detail;k++)
         {
            fread(&junk,2,1,object->fp);
            BSWAP_W(junk);


            fseek(object->fp,(junk+1)*2,SEEK_CUR);
            object->polSizeCur = object->polSizeCur + ((junk+2)*2);
         }
         poly->surface = abs(surface);
      }
      else
         poly->surface=surface;


      fgetpos(object->fp,&object->polPosCur);
      }
   else
      return(0);


   return(1);
}