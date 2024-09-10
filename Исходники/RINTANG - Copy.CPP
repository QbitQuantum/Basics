		//METHOD
		void draw(){
			if(type == 0){//BOX
				if(y<=10){
					
					Matrix3x3 ms;//SCALE
					Matrix3x3 mt;//TRANSLASI
					
					//TITIK PENGGAMBARAN
					int drawx1;//X1 SETELAH DITRANSFORMASI
					int drawy1;//Y1 SETELAH DITRANSFORMASI
					int drawx2;//X2 SETELAH DITRANSFORMASI
					int drawy2;//Y2 SETELAH DITRANSFORMASI
					int drawfx;//X UNTUK FILL
					int drawfy;//Y UNTUK FILL
					
					scale2(0.1*y,0.1*y,x*213+112,mobilY-10,ms);
					
					translate2(-(x-1)*(213)*(10-y)/10,-(mobilY-40-(maxy+1)/8-1)*(10-y)/10,mt);
					
					transformPoints2(ms,x*213+82,&drawx1,mobilY+20,&drawy1);
					transformPoints2(ms,x*213+142,&drawx2,mobilY+20,&drawy2);
					transformPoints2(mt,drawx1,&drawx1,drawy1,&drawy1);
					transformPoints2(mt,drawx2,&drawx2,drawy2,&drawy2);
					lineDDA(drawx1, drawy1, drawx2, drawy2); //BAWAH LUAR
					
					transformPoints2(ms,x*213+82,&drawx1,mobilY-40,&drawy1);
					transformPoints2(ms,x*213+142,&drawx2,mobilY-40,&drawy2);
					transformPoints2(mt,drawx1,&drawx1,drawy1,&drawy1);
					transformPoints2(mt,drawx2,&drawx2,drawy2,&drawy2);
					lineDDA(drawx1, drawy1, drawx2, drawy2);//ATAS LUAR
					
					transformPoints2(ms,x*213+82,&drawx1,mobilY+20,&drawy1);
					transformPoints2(ms,x*213+82,&drawx2,mobilY-40,&drawy2);
					transformPoints2(mt,drawx1,&drawx1,drawy1,&drawy1);
					transformPoints2(mt,drawx2,&drawx2,drawy2,&drawy2);
					lineDDA(drawx1, drawy1, drawx2, drawy2); //KIRI LUAR
					
					transformPoints2(ms,x*213+142,&drawx1,mobilY+20,&drawy1);
					transformPoints2(ms,x*213+142,&drawx2,mobilY-40,&drawy2);
					transformPoints2(mt,drawx1,&drawx1,drawy1,&drawy1);
					transformPoints2(mt,drawx2,&drawx2,drawy2,&drawy2);
					lineDDA(drawx1, drawy1, drawx2, drawy2); //KANAN LUAR
					
					//AREA FILLNYA
					if(y>0){//KALO Y 0 JADI TITIK, GA AMAN BUAT FILL
						transformPoints2(ms,x*213+82,&drawfx,mobilY-40,&drawfy);
						transformPoints2(mt,drawfx,&drawfx,drawfy,&drawfy);
						boundaryFill4(drawfx+2,drawfy+1,BLUE,WHITE);
					}
					// lineDDA(x*213+82, yFactor()*(mobilY+20), x*213+142, yFactor()*(mobilY+20)); //BAWAH LUAR
					// lineDDA(x*213+88, yFactor()*(mobilY+15), x*213+137, yFactor()*(mobilY+15)); //BAWAH DALAM
					// lineDDA(x*213+82, yFactor()*(mobilY-40),x*213+142, yFactor()*(mobilY-40));//ATAS LUAR
					// lineDDA(x*213+87, yFactor()*(mobilY-35), x*213+137, yFactor()*(mobilY-35)); //ATAS DALAM
					// lineDDA(x*213+82, yFactor()*(mobilY+20), x*213+82, yFactor()*(mobilY-40)); //KIRI LUAR
					// lineDDA(x*213+87, yFactor()*(mobilY+15), x*213+87, yFactor()*(mobilY-35)); //KIRI DALAM
					// lineDDA(x*213+142, yFactor()*(mobilY+20), x*213+142, yFactor()*(mobilY-40)); //KANAN LUAR
					// lineDDA(x*213+137, yFactor()*(mobilY+15), x*213+137, yFactor()*(mobilY-35)); //KANAN DALAM
					// lineDDA(x*213+92, yFactor()*(mobilY+15), x*213+137, yFactor()*(mobilY-30));
					// lineDDA(x*213+87, yFactor()*(mobilY+10), x*213+132, yFactor()*(mobilY-35));
					// lineDDA(x*213+132, yFactor()*(mobilY+15), x*213+87, yFactor()*(mobilY-30));
					// lineDDA(x*213+137, yFactor()*(mobilY+10), x*213+92, yFactor()*(mobilY-35));
				}else{

					Matrix3x3 mr;//ROTASI
					Matrix3x3 mt;//TRANSLASI
				
					//TITIK PENGGAMBARAN
					int drawx1;//X1 SETELAH DITRANSFORMASI
					int drawy1;//Y1 SETELAH DITRANSFORMASI
					int drawx2;//X2 SETELAH DITRANSFORMASI
					int drawy2;//Y2 SETELAH DITRANSFORMASI
					int drawfx;//X UNTUK FILL
					int drawfy;//Y UNTUK FILL
					
					// cout << "kiri " << x*213+82 << "\n";
					// cout << "kanan " << x*213+142 << "\n";
					// cout << "atas " << 70+(mobilY-40) << "\n";
					// cout << "bawah " << 70+(mobilY+20) << "\n";
					// cout << "Tengah " << x*213+112 << " " << 70+(mobilY-10) <<"\n";
					
					
					rotate2(22.5*(y-11),x*213+112,70+(mobilY-10),mr);
					translate2((y-11)*(maxx-(x*213))/8,0,mt);
					
					transformPoints2(mr,x*213+82,&drawx1,70+(mobilY+20),&drawy1);
					transformPoints2(mr,x*213+142,&drawx2,70+(mobilY+20),&drawy2);
					transformPoints2(mt,drawx1,&drawx1,drawy1,&drawy1);
					transformPoints2(mt,drawx2,&drawx2,drawy2,&drawy2);
					lineDDA(drawx1, drawy1, drawx2, drawy2); //BAWAH LUAR

					transformPoints2(mr,x*213+82,&drawx1,70+(mobilY-40),&drawy1);
					transformPoints2(mr,x*213+142,&drawx2,70+(mobilY-40),&drawy2);
					transformPoints2(mt,drawx1,&drawx1,drawy1,&drawy1);
					transformPoints2(mt,drawx2,&drawx2,drawy2,&drawy2);
					lineDDA(drawx1, drawy1, drawx2, drawy2);//ATAS LUAR
					
					transformPoints2(mr,x*213+82,&drawx1,70+(mobilY+20),&drawy1);
					transformPoints2(mr,x*213+82,&drawx2,70+(mobilY-40),&drawy2);
					transformPoints2(mt,drawx1,&drawx1,drawy1,&drawy1);
					transformPoints2(mt,drawx2,&drawx2,drawy2,&drawy2);
					lineDDA(drawx1, drawy1, drawx2, drawy2); //KIRI LUAR
					
					transformPoints2(mr,x*213+142,&drawx1,70+(mobilY+20),&drawy1);
					transformPoints2(mr,x*213+142,&drawx2,70+(mobilY-40),&drawy2);
					transformPoints2(mt,drawx1,&drawx1,drawy1,&drawy1);
					transformPoints2(mt,drawx2,&drawx2,drawy2,&drawy2);
					lineDDA(drawx1, drawy1, drawx2, drawy2); //KANAN LUAR
	
					//AREA FILLNYA
					transformPoints2(mr,x*213+82+5,&drawfx,70+(mobilY-37),&drawfy);
					transformPoints2(mt,drawfx,&drawfx,drawfy,&drawfy);
					boundaryFill4(drawfx,drawfy,BLUE,WHITE);
	
					// lineDDA(x*213+82, 70+(mobilY+20), x*213+142, 70+(mobilY+20)); //BAWAH LUAR
					// lineDDA(x*213+88, 70+(mobilY+15), x*213+137, 70+(mobilY+15)); //BAWAH DALAM
					// lineDDA(x*213+82, 70+(mobilY-40),x*213+142, 70+(mobilY-40));//ATAS LUAR
					// lineDDA(x*213+87, 70+(mobilY+-35), x*213+137, 70+(mobilY-35)); //ATAS DALAM
					// lineDDA(x*213+82, 70+(mobilY+20), x*213+82, 70+(mobilY-40)); //KIRI LUAR
					// lineDDA(x*213+87, 70+(mobilY+15), x*213+87, 70+(mobilY-35)); //KIRI DALAM
					// lineDDA(x*213+142, 70+(mobilY+20), x*213+142, 70+(mobilY-40)); //KANAN LUAR
					//lineDDA(x*213+137, 70+(mobilY+15), x*213+137, 70+(mobilY-35)); //KANAN DALAM
					//lineDDA(x*213+92, 70+(mobilY+15), x*213+137, 70+(mobilY-30));
					//lineDDA(x*213+87, 70+(mobilY+10), x*213+132, 70+(mobilY-35));
					//lineDDA(x*213+132, 70+(mobilY+15), x*213+87, 70+(mobilY-30));
					//lineDDA(x*213+137, 70+(mobilY+10), x*213+92, 70+(mobilY-35));
				}
			}else if(type == 1){//STONE
				lineDDA(40, 80, 90, 80);
				lineDDA(40, 80, 50, 60);
				lineDDA(50, 60, 55, 55);
				lineDDA(55, 55, 75, 65);
				lineDDA(75, 65, 90, 80);
			}
		}