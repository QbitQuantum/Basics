void CP1::main_do()
{
	

CClientDC dc(this);

//下面是图片路径    
zstringEx imgpath,zs;
imgpath.getCtlText(IDC_EDIT2,this->m_hWnd);
imgpath.trim();
if(imgpath.getStringLen()>0)
{
	if(imgpath[imgpath.getStringLen()-1]!='\\')imgpath+='\\';		
}
//上面是取得图片路径

	        


	//////////////////////////////////////////////按序选文件
	zs=imgpath.v();


	   
		zs+=  face_img_dir[cur_order].name;cur_order++;
		//zs.setCtlText(IDC_EDIT4);
		zs.replaceB(0,".jpg",".bmp");  //如果是JPG文件，暂换为BMP
		zs.replaceB(0,".JPG",".bmp");
		                                 //从按序从枚举数组中取出文件名
	
	
	

	////////////////////////////////////////////按序选文件





	//下面是把JPG转为BMP
	if( !zstringEx::is_file_exist(zs.v())  )
	{
		zs.replaceB(0,".bmp",".jpg");
		if(!zstringEx::is_file_exist(zs.v()))return;

		DRAWPIC.Destroy();
		DRAWPIC.Load(zs.v());
				
		zstringEx zs2;zs2.tools_GetCurDir();
		zs2+="\\jpg2bmp.bmp";  //统一转化为BMP来进行
		DRAWPIC.Save(zs2.v());
		zs=zs2.v();		
	}
	
    DRAWPIC.Destroy();
	DRAWPIC.Load(zs.v());


//if(DRAWPIC.GetWidth()>601)goto loopfor_only_320_small_pic; //大小限制，临时用的



	//下面是把BMP进行缩小，过大的
	if(DRAWPIC.GetWidth()>MY_IMAGE_MAX_WIDTH)
	{
		SMALLPIC.Create(MY_IMAGE_MAX_WIDTH,
			            DRAWPIC.GetHeight()/((float)DRAWPIC.GetWidth()/MY_IMAGE_MAX_WIDTH),
						24);

		HDC hdc=SMALLPIC.GetDC();

		::SetStretchBltMode(hdc,COLORONCOLOR);

		DRAWPIC.Draw(hdc,0,0,SMALLPIC.GetWidth(),SMALLPIC.GetHeight(),0,0,DRAWPIC.GetWidth(),DRAWPIC.GetHeight());
        

		zstringEx zs2;zs2.tools_GetCurDir();
		zs2+="\\cur_small.bmp";  //统一转化为BMP来进行
		SMALLPIC.Save(zs2.v());
        zs=zs2.v();

		SMALLPIC.ReleaseDC();
        SMALLPIC.Destroy();

         DRAWPIC.Destroy();
	     DRAWPIC.Load(zs.v());//重装入
	}



    //下面是把BMP进行缩小，过大的
	if(DRAWPIC.GetHeight()>MY_IMAGE_MAX_HEIGHT)
	{
		SMALLPIC.Create(DRAWPIC.GetWidth()/((float)DRAWPIC.GetHeight()/MY_IMAGE_MAX_HEIGHT),
			            MY_IMAGE_MAX_HEIGHT,
						24);

		HDC hdc=SMALLPIC.GetDC();
        ::SetStretchBltMode(hdc,COLORONCOLOR);
		DRAWPIC.Draw(hdc,0,0,SMALLPIC.GetWidth(),SMALLPIC.GetHeight(),0,0,DRAWPIC.GetWidth(),DRAWPIC.GetHeight());
        

		zstringEx zs2;zs2.tools_GetCurDir();
		zs2+="\\cur_small2.bmp";  //统一转化为BMP来进行
		SMALLPIC.Save(zs2.v());
        zs=zs2.v();

		SMALLPIC.ReleaseDC();
        SMALLPIC.Destroy();

        DRAWPIC.Destroy();
	    DRAWPIC.Load(zs.v());//重装入
	}


	this->RedrawWindow();//去掉原来的
    DRAWPIC.Draw(dc,0,0);//在窗口上画图




 

//1.人脸检测
long zret= zFaceLocate( OID,                     //第一个函数返回的人脸识别实例对象ID
						zs.v(),               //图像文件名，JPG,BMP
						cur_max_out_nums,            //用户要求的最大人脸输出数
						cur_sel_threshold,              //人脸置信度阀值，高于这个阀值才会被输出
						ofs); 
//2.报错信息    
if(zret<0)
{
	char er[256];
	zGetLastError(OID,er);
	AfxMessageBox(er);
}


	//CClientDC dc(this);
   POINT of;of.x=0;of.y=0;
   CString sbwh;
	for(int k=0;k<zret;k++)
	{   		
		//3.标记出选中的人脸
        zFlagFace(OID,(LONG)this->m_hWnd,k,0,0);

		sbwh.Format("E1_W: %d E1_H: %d E2_W: %d E2_H: %d",ofs[k].eye1_w,ofs[k].eye1_h,ofs[k].eye2_w,ofs[k].eye2_h);
        GetDlgItem(6677)->SetWindowText(sbwh);

		//dc.Rectangle(ofs[k].eye1_x-ofs[k].eye1_w/2,
		//	ofs[k].eye1_y-ofs[k].eye1_h/2,
		//	ofs[k].eye1_x+ofs[k].eye1_w/2,
		//	ofs[k].eye1_y+ofs[k].eye1_h/2) ;
		//dc.Rectangle(ofs[k].eye2_x-ofs[k].eye2_w/2,
		//	ofs[k].eye2_y-ofs[k].eye2_h/2,
		//	ofs[k].eye2_x+ofs[k].eye2_w/2,
		//	ofs[k].eye2_y+ofs[k].eye2_h/2) ;
	


		//4.在其下打分
		CString outdf;
		outdf.Format("%d: %0.2f",k+1,ofs[k].tally);
        dc.TextOut(ofs[k].left,ofs[k].bottom,outdf);
		
	}
	 
//5.回收人脸检测内存
    zFaceLocate_FreeMemory(OID);

}//end func