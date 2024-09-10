bst128 TAES_DECRYPT(bst128 in,u32* rkd,bst128 counter){
     bst128 out;
	 int i;
	 u32 tempcounter;
	 /*apply the inverse matrix mult to counter */
	 
	 for(i=0;i<4;i++){
		tempcounter=INVERT(counter.t[i]);
	 /*set rkeys 1,5,9 using the backups*/
		rkd[4+i]=rkd[44+i]^tempcounter;
		rkd[20+i]=rkd[48+i]^tempcounter;
		rkd[36+i]=rkd[52+i]^tempcounter;
	}
	
 rijndaelDecrypt(rkd,in.b,out.b);

 return out;
}