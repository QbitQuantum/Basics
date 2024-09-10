void CSurfaceView::OnDraw(CDC* pDC) 
{
//	return;
	// TODO: Add your specialized code here and/or call the base class
//	if(!CGeneral::RaftArray.size())	return;
	if(CGeneral::step == 0) return;
	CGeneral::is_draw_finished = false;

	clock_t startd, find;
	double	duration = 0;
	startd = clock();
	//yellow, cremovi
	static 	COLORREF colors[255*255*255];
	for(int r=0; r<255 ; r++)	{
		for(int g=0; g<255 ; g++)	{
			for(int b=0; b<255 ; b++)	{
				colors[r+g+b]= RGB( 255-r, 255-g, 255-b);
			}
		}
	}


	static 	COLORREF col[16] = { RGB( 255, 0, 0 ), RGB( 0, 255, 0 ), //krasnii-0, zelyonii-1
		RGB( 0, 0, 255), RGB( 0, 255, 255 ), //sinii-2, goluboiCian-3
		RGB( 255, 0, 255), RGB( 255, 255, 0 ), //malinovii-4, jyoltii-5
		RGB( 192, 192, 192), RGB( 80, 0, 80 ), //serii-6, t-malinovii-7
		RGB( 255, 255, 255), RGB( 80, 80, 0 ), //serii-8, t-jyoltii-9, 
		RGB( 80, 80, 0 ), RGB( 0, 0, 80 ), //4yornii-10, tyomn. golub - 11 
		RGB( 250, 166, 70 ), RGB( 207, 10, 243 ), //orange-12, tyomn. fioletovii - 13 
		RGB( 128, 128, 0 ), RGB( 0, 0, 0 )}; // seri 15

	GetClientRect(m_ClientRect );
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	
	static int key = 1;

	DrawSize = (m_ClientRect.Width( ) < m_ClientRect.Height( ) )
		? m_ClientRect.Width( ) : m_ClientRect.Height( ) ;
	if(DrawSize > GRID_SIZE)  DrawSize = GRID_SIZE;
	else
	{	
		minZoom = (GRID_SIZE-1)/DrawSize + 1 ;
		if(m_PartGrid < minZoom)
		{
			m_PartGrid = minZoom;
		}
	}
	DrawSize = GRID_SIZE/m_PartGrid;
	m_OptionDlg->SetZoom(m_PartGrid, GRID_SIZE/m_PartGrid,num);
	int xp = (m_PartGridNum - 1)%m_PartGrid ;
	int yp = (m_PartGridNum - 1) / m_PartGrid ;
	X = 0 + DrawSize * xp;
	Y = 0 + DrawSize * yp;
	X1 = X + DrawSize; 
	Y1 = Y + DrawSize;


//-----------------------------------------------------------------		
	CDC * myDc;
	CDC memdc;
	CBitmap bmp, *poldbmp;
	isMemDc = IsMemDc && !( CGeneral::DrawRaftIndexes 
		|| CGeneral::DrawRecIndexes
		|| CGeneral::DrawSigMolInd || CGeneral::DrawSigMolNames
		|| CGeneral::DrawRecNames);

	if(isMemDc)
	{
		// Create a compatible memory DC
		memdc.CreateCompatibleDC( pDC);
		bmp.CreateCompatibleBitmap (pDC, m_ClientRect.Height(), m_ClientRect.Height()); 
		//bmp.CreateCompatibleBitmap (pDC, DrawSize, DrawSize); 
		// Select the new bitmap object into the memory device context. 
		poldbmp = memdc.SelectObject( &bmp );

		memdc.BitBlt( 0,0,m_ClientRect.Height(), m_ClientRect.Height(),&memdc, 0, 0, WHITENESS );  
		myDc = &memdc;
	}
	else myDc = pDC;
	myDc->SetMapMode(MM_ISOTROPIC);
	SetWindowExtEx(*myDc,DrawSize,DrawSize,NULL);
	SetViewportExtEx(*myDc,m_ClientRect.right, -m_ClientRect.bottom,NULL);
	SetViewportOrgEx(*myDc,0,m_ClientRect.bottom,NULL);	
//-----------------------------------------------------------------		





	double sd = sqrt(DrawSize /27.) ;

	if( CGeneral::DrawSigMol ){

		double sd_sm = sd-1;
		if(sd_sm < 1) sd_sm = 1; //   ?????????????????

		CBrush br;
		br.CreateSolidBrush(col[1]);

		for(int in=0; in<GRID_SIZE ; in++)
		{
			for(int in1=0; in1<GRID_SIZE ; in1++)
			{
				CBrush br1;
				double IFN_prot_conc = CGeneral::grid.m_Grid[in1][in].array[SM];
				if(IFN_prot_conc == 0){
					continue;
				}
				int normalized_IFN_prot_conc = floor(IFN_prot_conc);
				br1.CreateSolidBrush(colors[normalized_IFN_prot_conc]);
				CBrush* pSMBr = myDc->SelectObject( &br1 );

	//			myDc->Rectangle(in - X, in1 -Y,	in + sd_sm -X, in1 + sd_sm - Y); 
				CRect rect(in - X, in1 -Y, in + sd_sm -X, in1 + sd_sm - Y);
				myDc->FillRect(&rect ,&br1); 

				if(CGeneral::DrawSigMolNames)
				{
					char buf[30] = "IFNprot: ";
					char buf5[10];
					itoa(IFN_prot_conc,buf5,10);
					strncat(buf, buf5, 10);//add coma
					myDc->TextOut(in - X, in1 -Y, buf, strlen(buf));
				}	

			}
		}

	}



	/////////////////// begin drawing rafts //////////////////////////////////
	if( CGeneral::DrawRafts )
	{
		CBrush gray_hatch_br, red_br, grey_br;
		gray_hatch_br.CreateHatchBrush(HS_BDIAGONAL, col[15]);
		grey_br.CreateSolidBrush(col[15]);
		red_br.CreateSolidBrush(col[1]);


		CBrush* pOldBr = myDc->SelectObject( &gray_hatch_br );

		std::vector<CCell>::iterator raft_iter;
		raft_iter = CGeneral::CellArray.begin();
		CCell * p_Raft = raft_iter;
		for(; raft_iter  != CGeneral::CellArray.end(); raft_iter++)
		{
			p_Raft = raft_iter;



			double rigI_rna_conc = p_Raft->GetRIGI_rna_conc();
//			double normalized_rigI_rna_conc = rigI_rna_conc/CGeneral::RIGI_rna_maxLevel;
			double IFN_prot_conc = p_Raft->GetIFN_prot_conc();
//			double normalized_IFN_prot_conc = IFN_prot_conc/CGeneral::IFN_prot_maxLevel;

			if( p_Raft->IsActivated() )
			{
				CBrush br;
 				double RIGI_rna_conc = p_Raft->GetRIGI_rna_conc();
				int val=0;
				if(CGeneral::DrawAgs)
					double rigI_rna_conc = p_Raft->GetRIGI_rna_conc();
				else
					double rigI_rna_conc = p_Raft->GetRIGI_rna_conc();


				if( !p_Raft->IsInfected() )//not infected
				{
					br.CreateHatchBrush(HS_BDIAGONAL, RGB( 128, 128, 128 ));
					CBrush* pSMBr = myDc->SelectObject( &br );
					myDc->Ellipse(p_Raft->Location.x - X, p_Raft->Location.y -Y,
								p_Raft->Location.x  -X, p_Raft->Location.y - Y); 

				} 	           
				else// infected
				{
					if( CGeneral::step != 1)
					{
						CBrush* pSMBr = myDc->SelectObject( &red_br );
						myDc->Ellipse(p_Raft->Location.x - X, p_Raft->Location.y -Y,
									p_Raft->Location.x  -X, p_Raft->Location.y  - Y); 
					}
					if(p_Raft->m_blinking_counter == p_Raft->m_blinking_const)
					{
						p_Raft->m_blinking_counter = 0;
						p_Raft->m_justChangedStatus = !p_Raft->m_justChangedStatus;
					}
					else{p_Raft->m_blinking_counter++;}

					br.CreateSolidBrush(RGB( 128, 128, 128 ));
					CBrush* pSMBr = myDc->SelectObject( &br );
					myDc->Ellipse(p_Raft->Location.x - X, p_Raft->Location.y -Y,
								p_Raft->Location.x -X, p_Raft->Location.y - Y); 
					if(p_Raft->m_blinking_counter == p_Raft->m_blinking_const)
					{
						p_Raft->m_blinking_counter = 0;
						p_Raft->m_justChangedStatus = !p_Raft->m_justChangedStatus;
					}
					else{p_Raft->m_blinking_counter++;}
				}

			} // if	                 
			else // not activated
			{
				CBrush brt,brt1;
				int val_msg;
				int val_prot;
				if(!CGeneral::DrawAgs) {//DDX58
//					if(CGeneral::DrawAgIndexes)//msg
						val_msg = p_Raft->GetRIGI_rna_conc();
//					else //prot
						val_prot = p_Raft->GetRIGI_prot_conc();
				}
				else {//IFNB1
//					if(CGeneral::DrawAgIndexes)//IFNB1
						val_msg = p_Raft->GetIFN_rna_conc();
//					else   //prot
						val_prot = p_Raft->GetIFN_prot_conc();
				}

				if( p_Raft->IsInfected() )//NOT UNFECTED		
				{
					brt.CreateSolidBrush(colors[val_prot]);
					CBrush* pSMBr = myDc->SelectObject( &brt );
					myDc->Ellipse(p_Raft->Location.x - X-1, p_Raft->Location.y -Y-1,
								p_Raft->Location.x -X+sd+1, p_Raft->Location.y  - Y+sd+1); 

					brt1.CreateSolidBrush(colors[val_msg]);
					pSMBr = myDc->SelectObject( &brt1 );
					myDc->Ellipse(p_Raft->Location.x - X, p_Raft->Location.y -Y,
								p_Raft->Location.x -X+sd, p_Raft->Location.y  - Y+sd); 

/*					myDc->SetTextColor(col[0]); 
					char buf[30] = "*";
					myDc->TextOut(p_Raft->Location.x - X+1, p_Raft->Location.y -Y+1, 
						buf, strlen(buf));
						*/

				} // if	  
				else//not infected
				{	
//					brt.CreateSolidBrush(colors[col[2]]);
					brt.CreateHatchBrush(HS_BDIAGONAL, colors[val_prot]);
					CBrush* pSMBr = myDc->SelectObject( &brt );
					myDc->Ellipse(p_Raft->Location.x - X-1, p_Raft->Location.y -Y-1,
								p_Raft->Location.x -X+sd+1, p_Raft->Location.y  - Y+sd+1); 

					brt1.CreateHatchBrush(HS_FDIAGONAL, colors[val_prot]);
					pSMBr = myDc->SelectObject( &brt1 );
					myDc->Ellipse(p_Raft->Location.x - X, p_Raft->Location.y -Y,
								p_Raft->Location.x -X+sd, p_Raft->Location.y  - Y+sd); 
				}
				
			}
			myDc->SetTextColor(col[0]); 
			int boundTypeIR = p_Raft->Get_boundTypeIR();
			if(boundTypeIR)	{
				char buf1[3] = "|";
				char buf2[3] = "--";
				char buf3[3]="";
				char buf[30] = "";
				char buf5[10];
				if((boundTypeIR%2)){
					strncat(buf3, buf1, 3);//add coma					
				}else{
					strncat(buf3, buf2, 3);//add coma					
				}
				myDc->TextOut(p_Raft->Location.x - X+1, p_Raft->Location.y -Y+1, 
					buf3, strlen(buf3));
			}
			myDc->SetTextColor(RGB(0,0,0)); 

			if( !p_Raft->IsInfected() ) {//not infected
			

			} 	           
			else {// infected
			
			}

			/*

			double rigI_rna_conc = p_Raft->GetRIGI_rna_conc();
			double normalized_rigI_rna_conc = rigI_rna_conc/CGeneral::RIGI_rna_maxLevel;
			double IFN_rna_conc = p_Raft->GetIFN_rna_conc();
			double normalized_IFN_rna_conc = IFN_rna_conc/CGeneral::IFN_rna_maxLevel;

			int sd_rna = sd+3;
			int val;
			if(CGeneral::DrawAgs)
				val = 255 - normalized_rigI_rna_conc * 255;
			else
				val = 255 - normalized_IFN_rna_conc * 255;
			CBrush br_rna;
			br_rna.CreateSolidBrush(RGB( val, val, val ));
			CBrush* pSMBr = myDc->SelectObject( &br_rna );
//			myDc->Ellipse(p_Raft->m_shape.Centroid().x - X, p_Raft->m_shape.Centroid().y -Y,
//				p_Raft->m_shape.Centroid().x + sd_rna -X, p_Raft->m_shape.Centroid().y + sd_rna - Y); 

*/



			if(CGeneral::DrawRaftIndexes)
			{
				char buf[30]="";
				char buf5[10]="";
				if(!CGeneral::DrawAgs){
//					if(CGeneral::DrawAgIndexes)	{
						strncat(buf, "DDX58: ", 10);//add coma
						itoa(p_Raft->GetRIGI_rna_conc(),buf5,10);
						strncat(buf, buf5, 10);//add coma
						myDc->TextOut(p_Raft->Location.x - X, p_Raft->Location.y -Y, 
							buf, strlen(buf));
//					}
//					else{
						strncat(buf, ", RIGI: ", 10);//add coma
						itoa(p_Raft->GetRIGI_prot_conc(),buf5,10);
						strncat(buf, buf5, 10);//add coma
						myDc->TextOut(p_Raft->Location.x - X, p_Raft->Location.y -Y, 
							buf, strlen(buf));
//					}
				}
				else{
//					if(CGeneral::DrawAgIndexes)	{
						strncat(buf, "IFNB:", 10);//add coma
//						buf = "IFNB: ";
						itoa(p_Raft->GetIFN_rna_conc(),buf5,10);
						strncat(buf, buf5, 10);//add coma
						myDc->TextOut(p_Raft->Location.x - X, p_Raft->Location.y -Y, 
							buf, strlen(buf));
//					}
//					else{
/*						strncat(buf, ", IFNb:", 10);//add coma
						itoa(p_Raft->GetIFN_prot_conc(),buf5,10);
						strncat(buf, buf5, 10);//add coma
						myDc->TextOut(p_Raft->Location.x - X, p_Raft->Location.y -Y, 
							buf, strlen(buf));*/
//					}

				}
			}

		}
		myDc->SelectObject( pOldBr);
		num++;
		myDc->SetBkMode(oldBkMode);
	}
//------------------------ end drawing rafts ---------------------------//

	
	if(isMemDc)
	{
		pDC->StretchBlt( 0,0,m_ClientRect.Height( ) ,m_ClientRect.Height( ),&memdc, 0, 0,
			DrawSize, DrawSize, SRCCOPY); 
		//pDC->BitBlt( 0,0,DrawSize, DrawSize,&memdc, 0, 0, SRCCOPY ); 
		bmp.DeleteObject();
		memdc.DeleteDC();
	}
	pDC->SetBkMode(oldBkMode);

	CGeneral::is_draw_finished = true;
	if(stepGl == 10 || stepGl == 1000 || stepGl == 10000
		|| stepGl == 100000 || stepGl == 300000 || stepGl == 2000000)
	{
		find = clock();
		duration = (double)(find - startd) / CLOCKS_PER_SEC;	
//		CGeneral::out << "\n Draw duration " << duration << " step " << stepGl << endl;
	}
}