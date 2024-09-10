void CGPSSubcrible::OnRevGpsMsg(long ILongID,char strgps[],long lenth)
{
	  //获得字符数组
		char *pchar = new char[ lenth + 1];
		char *pdate = new char[5];
		
		memcpy(pchar,strgps,lenth);
		
		*(pchar + lenth) = '\0';

 		char *tok;
 		char *p[50] = {0};
 		char seps[] = ",";
 	    int i = 0;
 	    
		char *stopstr;
 		
 		//获得字符串数组
 	    tok = strtok(pchar,seps);
 		while( tok != NULL && i < 50)
 		{	
 			p[i] = new char[strlen(tok) + 1];
 		    strcpy(p[i],tok);
 	        tok = strtok( NULL,seps);
 			
 			i++;
 		}
 	    
 		if ( i < 10 )
 		{
 			//清除数组指针
 	       for(int j = 0; j<i; j++)
		   {
 	          delete p[j];
		   }
 	
 		   delete pchar;
 		   delete pdate;
		   
		    return;
 		}
 	
		GPS_Info info = {0};
//		const int TIGER_COORDINATE_UNIT = 1000000;

 		info.latidude = strtod(p[0],&stopstr);
//		info.latidude /= TIGER_COORDINATE_UNIT;
//		info.latidude -= 90;

 		info.longitude = strtod(p[1],&stopstr);
//		info.longitude /= TIGER_COORDINATE_UNIT;
//		info.longitude -= 180;

 		info.speed     = strtod(p[2],&stopstr);
 		info.height    = strtod(p[3],&stopstr);
 		info.angle     = strtod(p[4],&stopstr);
 	
 	     strncpy(pdate,p[5],4);
 	     *(pdate+4) = '\0';
 	     info.revTime.dwYear = strtol(pdate,&stopstr,10);
 	  
 	     strncpy(pdate,p[5]+4,2);
 	     *(pdate+2) = '\0';
 	     info.revTime.dwMonth = strtol(pdate,&stopstr,10);
 	   
 	     strncpy(pdate,p[5]+6,2);
 	     *(pdate+2) = '\0';
 	     info.revTime.dwDay = strtol(pdate,&stopstr,10);
 	      
 	
 	     strncpy(pdate,p[5]+8,2);
 	     *(pdate+2) = '\0';
 	     info.revTime.dwHour = strtol(pdate,&stopstr,10);
 	
 	     strncpy(pdate,p[5]+10,2);
 	     *(pdate+2) = '\0';
 	     info.revTime.dwMinute = strtol(pdate,&stopstr,10);
 	
 	     strncpy(pdate,p[5]+12,2);
 	     *(pdate+2) = '\0';
 	     info.revTime.dwSecond = strtol(pdate,&stopstr,10);
 	     
 	
 		 info.antennaState = (p[6][0] == '1');
 		 info.orientationState = (p[7][0] == '1');
 		 info.starCount = strtol(p[8],&stopstr,10);
 		 
		 //清除数组指针
 	     for(int j = 0; j<i; j++)
		 {
 	        delete p[j];
		 }
 	
 		 delete pchar;
 		 delete pdate;

 		 if(m_RecievCallBack != NULL)
 		 {
 			 m_RecievCallBack(ILongID,info,m_dwuserdata);
 		 }
 	
}