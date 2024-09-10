void load_YUAN_config_file(char filename[])       //读取YUAN配置文件
{

 

 FILE *fp;
 errno_t err;//检测文件问题

 int n;
 float f;
 int end=0;

 if((err = fopen_s(&fp,filename,"r")) !=0 )
    {
     AfxMessageBox("config/YUAN.txt没有找到!");

    }

 //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   /*61 =*/
 }

 fscanf_s(fp,"%d",&n);

 A_time_max=n;  //元激活持续总时间

 //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   /*61 =*/
 }

 fscanf_s(fp,"%d",&n);

 Wait_Start_Time_MAX=n;  //元等待激活时间

 //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   /*61 =*/
 }

 fscanf_s(fp,"%f",&f);

 LE=f;  //连接强度的增加值,学习效率

 //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   /*61 =*/
 }

 fscanf_s(fp,"%f",&f);

 WL=f;  //连接强度上增加的  元F值的比率

  //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   //61
 }

 fscanf_s(fp,"%f",&f);

 fag_add=f;  //元疲劳值增加的数值

 //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   //61
 }

 fscanf_s(fp,"%f",&f);

 fag_minus=f;  //元疲劳值减少的数值

 //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   //61
 }

 fscanf_s(fp,"%f",&f);

 E_minus=f;  // 反应强度衰减值

 //------------------




 while(1)
 {
  if(fgetc(fp)==61)break;   /*61 =*/
 }

 fscanf_s(fp,"%d",&n);

 Learn_Ready_Time_MAX=n;   //运行学习

 //------------------



 while(1)
 {
  if(fgetc(fp)==61)break;   /*61 =*/
 }

 fscanf_s(fp,"%f",&f);

 Forgot_Weight=f;   //遗忘量
 //------------------


 fclose(fp);

}