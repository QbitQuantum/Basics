		//function
		void Draw(){
			switch(Jenis){
				case 0 :  //garis
					lineDDA(x1,y1,x2,y2);
					break;
				case 1 : //kotak
					DrawKotak1(x1, y1, x2, y2, x3, y3,x4,y4);
					break;
				case 3: //fill :v
					boundaryFill4(x1,y1,KodeWarna, WHITE);
					break;
			}
		}