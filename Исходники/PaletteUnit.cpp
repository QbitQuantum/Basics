void __fastcall TPaletteForm::DoPalette()
{
	 int PaperWidth  = 0;
	 int PaperHeight = 0;
	 int ImageWidth  = 0;
	 int ImageHeight = 0;
	 // получим размер бумаги
	 this->GetPaperSize(PaperWidth, PaperHeight);
	 // получим размер изображения
	 GetImageSize(PaperWidth, PaperHeight, ImageWidth, ImageHeight);

	 Graphics::TBitmap* bmp = new Graphics::TBitmap();
	 bmp->Width = ImageWidth;
	 bmp->Height = ImageHeight;
	 // отрисовка палитры.

	 TCanvas* cnv = bmp->Canvas;
	 cnv->Brush->Color = clBlack;
	 TRect r;r.init(0,0,bmp->Width, bmp->Height);
	 cnv->FillRect(r);
	 switch(ComboBox1->ItemIndex)
	 {
		case 0:
			 DrawPantone(cnv, ImageWidth, ImageHeight);
		break;
		case 1:
			DrawCube(cnv, ImageWidth, ImageHeight,1);
		break;
		case 2:
			DrawCube(cnv, ImageWidth, ImageHeight,2);
		break;
		case 3:
			DrawCube(cnv, ImageWidth, ImageHeight,3);
		break;
		case 4:
			DrawPantoneRandom(cnv, ImageWidth, ImageHeight);
		break;
		case 5:
			DrawCubeRandom(cnv, ImageWidth, ImageHeight);
		break;
		case 6:
			DrawPantoneCube(cnv, ImageWidth, ImageHeight,1);
		break;
		case 7:
			DrawPantone27Cube(cnv, ImageWidth, ImageHeight,1);
		break;

		case 8:
			DrawPantone8Polar(cnv, ImageWidth, ImageHeight,1);
		break;

		case 9:
			DrawPantone27Polar(cnv, ImageWidth, ImageHeight,1);
		break;

		case 10:
			DrawRGBPolar8(cnv, ImageWidth, ImageHeight,1);
		break;
		case 11:
			DrawRGBPolar27(cnv, ImageWidth, ImageHeight,1);
		break;
		default:
			DrawCube(cnv, ImageWidth, ImageHeight,1);
	 }

	 this->Image1->Picture->Assign(bmp);
	 delete bmp;

}