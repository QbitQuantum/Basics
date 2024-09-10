 hndop()
 {
  char *str;
  int sign,ndig,dec;
  float inte;
  if(temp[j][i+1]=='^')
  {
   if(temp[j][i+2]>='1'&&temp[j][i+2]<='9')
   {
	inte=atoi(&stack[0])*atoi(&temp[j][i+2]);
	str=ecvt(inte,2,&dec,&sign);
	ans[l++]=str[0];
	ans[l++]=str[1];
	ans[l++]=ch;
	ans[l++]='^';
	printf("%d",atoi(&stack[0])*atoi(&temp[j][i+2]));
	ans[l++]=temp[j][i+2]-1;
   }
  }
  if(temp[j][i+1]=='\0')
 {
  ans[l++]=ch;
 }

 ans[l]=0;
printf("\n%s",ans);

 }