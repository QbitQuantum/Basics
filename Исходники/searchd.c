void getpath(int start,struct searchd_nodent *cur)
{
  if(cur->pare!=-1){
    getpath(start,list+start+cur->pare);
    strcat(buf,"/");    strcat(buf2,"/");
    strcat(buf,cur->name);  strcat(buf2,cur->ori_name);
  }
}