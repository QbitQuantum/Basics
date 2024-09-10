void DrawMap(void)
{

  char buff[512];
	
  /*------------------------------------------------------------------------------
  //Begin Input Ctrl & View Matrix Setup
  ------------------------------------------------------------------------------*/
  static float angle = 0.0f;
  static float view = -240.0f;
  //view = -view;
  D3DXMATRIX matWorld;
  D3DXMATRIX matWorld2;
  D3DXMatrixTranslation(&matWorld2,0.0f,0.0f,angle/1500.0f);
  //D3DXMatrixRotationX(&matWorld, DEGtoRAD(angle/1.0069));
  //DXMatrixRotationY(&matWorld, DEGtoRAD(angle));
  D3DXMatrixRotationYawPitchRoll(&matWorld,DEGtoRAD(angle/20.0f),DEGtoRAD(angle/15.0f),DEGtoRAD(angle/10.0f));
  matWorld*=matWorld2;
  angle += 1.0f;
  //g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

  D3DXMATRIX matView;
  static float mawari = 0.0f;
  float delta;
  delta = 0.02f;
  if( GetKeyState(VK_CONTROL)&0x8000 ){ delta = 0.1f; };
  if( GetKeyState(VK_RIGHT) & 0x8000 ) mawari-=delta;
  if( GetKeyState(VK_LEFT)  & 0x8000 ) mawari+=delta;
  static D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);
  delta = 2.0f;
  if( GetKeyState(VK_CONTROL)&0x8000 ){ delta = 5.0f; };
  if( GetKeyState(VK_UP)    & 0x8000 ){ pos.x+=cos(mawari)*delta; pos.z+=sin(mawari)*delta; }
  if( GetKeyState(VK_DOWN)  & 0x8000 ){ pos.x+=cos(mawari+3.1415926f)*delta; pos.z+=sin(mawari+3.1415926f)*delta; }
  if( GetKeyState(VK_PRIOR) & 0x8000 ){ pos.y+=delta; }
  if( GetKeyState(VK_NEXT)  & 0x8000 ){ pos.y-=delta; }
  if( GetKeyState(VK_HOME)  & 0x8000 ){ mawari=pos.x=pos.y=pos.z=0.0f; }
  D3DXVECTOR3 pnt(pos.x+cos(mawari), pos.y+0.0f, pos.z+sin(mawari));
  D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
  D3DXMatrixLookAtRH(&matView, &pos, &pnt, &up);
  g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView); 

  D3DXMATRIX matProj;
  D3DXMatrixPerspectiveFovRH(&matProj, DEGtoRAD(45.0f), 4.0f / 3.0f, 1.0f, 500.0f);
  g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);


   if( GetAsyncKeyState(VK_RETURN)  & 0x1 ){ AutoMakeMMB=TRUE;}


  /*------------------------------------------------------------------------------
  //End Input Ctrl & View Matrix Setup
  ------------------------------------------------------------------------------*/

  /*------------------------------------------------------------------------------
  //Begin RenderState
  ------------------------------------------------------------------------------*/
  //g_pD3DDevice->SetRenderState( D3DRS_CULLMODE,   D3DCULL_CW/*/D3DCULL_NONE*/  );
  g_pD3DDevice->SetRenderState( D3DRS_CULLMODE,   D3DCULL_CCW/*/D3DCULL_NONE*/  );
  g_pD3DDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
  //g_pD3DDevice->SetLight(0,&light);
  //g_pD3DDevice->LightEnable(0,TRUE);
  g_pD3DDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
  //g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0xF0F0F0F0);
  g_pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD );

  g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
  g_pD3DDevice->SetRenderState( D3DRS_STENCILENABLE, TRUE );
  g_pD3DDevice->SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );
  g_pD3DDevice->SetRenderState( D3DRS_ALPHAREF , 0x80 );
  g_pD3DDevice->SetRenderState( D3DRS_ALPHAFUNC  , D3DCMP_GREATER );
  //g_pD3DDevice->SetRenderState(D3DRS_EDGEANTIALIAS,TRUE);
  /*------------------------------------------------------------------------------
  //End RenderState
  ------------------------------------------------------------------------------*/

  //地图是在TheDesertWorld.cpp里画的
  //g_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,128), 1.0f, 0L );



  if( flgFirst ) logprintf("MZB:%d",noj);
  pory = 0;
  for( int i=0; i< noj; i++ )
  {
    //if(i>=50) break;
    D3DXMATRIX matWorld;
    D3DXMATRIX matWorld2;
    D3DXMATRIX matWorld3;
    D3DXMATRIX matWorld4;
    D3DXMATRIX matWorldR4;
    D3DXMATRIX matWorldR5;
    D3DXMATRIX matWorldR6;
    ZeroMemory(&matWorld,sizeof(D3DXMATRIX));
    D3DXMatrixScaling(&matWorld3,oj[i].fScaleX,oj[i].fScaleY,oj[i].fScaleZ); 
    D3DXMatrixTranslation(&matWorld,oj[i].fTransX,oj[i].fTransY,oj[i].fTransZ);
    D3DXMatrixRotationX(&matWorldR4,oj[i].fRotX);
    D3DXMatrixRotationY(&matWorldR5,oj[i].fRotY);
    D3DXMatrixRotationZ(&matWorldR6,oj[i].fRotZ);
    matWorld2 = matWorldR4 * matWorldR5 * matWorldR6;
    matWorld=((matWorld3*matWorld2)/**matWorld4*/)*matWorld;
    g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
    if( oj[i].fScaleX*oj[i].fScaleY*oj[i].fScaleZ < 0.0f )
	{ 
      g_pD3DDevice->SetRenderState( D3DRS_CULLMODE,   D3DCULL_CW );
    }
	else
	{
      g_pD3DDevice->SetRenderState( D3DRS_CULLMODE,   D3DCULL_CCW );
    }
    if(0)
	{
       float pp[]={-20,0,0,20,0,0, 0,-20,0,0,20,0, 0,0,-20,0,0,20};
       //float pp[]={-10,0,0,10,0,0, 0,-10,0,0,10,0, 0,0,-10,0,0,10};
       g_pD3DDevice->SetFVF(D3DFVF_XYZ);
       g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,3,pp,12);
    }



	//Draw MzbLists Hint
	{
    RECT rc={5,91,600,128};

	  //自动输出
	  i = haha; //这个会打乱文件名和文件内容的正确配对吗?
	  if (AutoMakeMMB == TRUE) {haha+=1;};
      if (haha == (noj -1)) {haha = 0;AutoMakeMMB == false;};

    sprintf(buff,"-----MZBList:%d/%d",i,noj);
    pDxFont->DrawTextA(NULL,buff,lstrlen(buff),&rc, DT_LEFT,  D3DCOLOR_XRGB(0,0,255)); 
	}


    for( int j=0; j< NumMMB; j++ )
	{
      if( memcmp(MMBlist[j]+16,oj[i].id,16) ) continue;

	//Draw Mmb Hint
	{
    RECT rc={5,134,600,160};
    sprintf(buff,"------- Draw MMB:%s",sstr(oj[i].id,16));
    pDxFont->DrawTextA(NULL,buff,lstrlen(buff),&rc, DT_LEFT,  D3DCOLOR_XRGB(0,0,255)); 
	}

    /*------------------------------------------------------------------------------
    //Begin MapObj Files Output
    ------------------------------------------------------------------------------*/
    char opname[16];  //要输出的文件名
    CopyMemory(opname,MMBlist[j]+16,16);
    ChangeSpaceToNull(opname);
	lstrcat(opname,".MapObj");


    if (DoesFileExist(opname)) { logprintf("发现有文件重复将自动复盖,这些文件是%s",opname);}
    HANDLE hFile = CreateFile(opname,GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL );
    //ReadFile(hFile,pdat,dwSize,&dmy,NULL);	  

    if( hFile!=INVALID_HANDLE_VALUE && hFile!=NULL )
	{
    DWORD dmy;
    //SetFilePointer(hFile,0,NULL,FILE_END);

	LPSTR ReadLocate = MMBlist[j+1]-16;

	int size = (int)(((*(DWORD*)&ReadLocate[4])>>3)&0x007ffff0);

    WriteFile(hFile,&ReadLocate[0],size,&dmy,NULL);
    CloseHandle(hFile);
	}
   /*------------------------------------------------------------------------------
   //End MapObj Files Output
   ------------------------------------------------------------------------------*/

    DrawMMB(MMBlist[j]);

    //信息输出1
	{
    RECT rc={5,5,600,64};
    sprintf(buff,"正在绘制Index数=%d\nLookAt:X=%02.2f Y=%02.2f Z=%02.2f",pory,pos.x,pos.y,pos.z);
    pDxFont->DrawTextA(NULL,buff,lstrlen(buff),&rc, DT_LEFT,  D3DCOLOR_XRGB(196,196,0)); 
	}
    //信息输出2
	{
    RECT rc={5,48,600,96};
    sprintf(buff,"%sMZB=%d MMB=%d\n当前第%d个MMB",oj?"总共":"第",noj,NumMMB,j);
    pDxFont->DrawTextA(NULL,buff,lstrlen(buff),&rc, DT_LEFT,  D3DCOLOR_XRGB(196,196,0)); 
	}

	break;
	}//End For MumMMB

  break;
  }//End For Noj