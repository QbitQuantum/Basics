void CdHardware::OnSelchangeCcd() 
{
	int detecttype;

	detecttype = ((CComboBox*)GetDlgItem(IDC_CCD))->GetCurSel();
	switch (detecttype)
		{
		case 0:					// EEV 256x1024 3-phase
			ccdtype = EEV_256x1024_3ph;
			break;
		case 1:					// EEV 576x384 3-phase
			ccdtype = EEV_576x384_3ph;
			break;
		case 2:					// EEV 1152x298 3-phase
			ccdtype = EEV_1152x298_3ph;
			break;
		case 3:					// EEV 1152x1242
			ccdtype = EEV_1152x1242_3ph;
			break;
		case 4:					// EEV 256x1024 6-phase
			ccdtype = EEV_256x1024_6ph;
			break;
		case 5:					// EEV 1024x512 FT
			ccdtype = EEV_1024x512_FT;
			break;
		case 6:					// EEV 576x384 6-phase
			ccdtype = EEV_576x384_6ph;
			break;
		case 7:					// EEV 1152x298 6-phase
			ccdtype = EEV_1152x298_6ph;
			break;
		case 8:					// EEV 1152x1242 6-phase
			ccdtype = EEV_1152x1242_6ph;
			break;
		case 9:					// EEV 256x1024 8-phase
			ccdtype = EEV_256x1024_8ph;
			break;
		case 10:				// EEV 1152x770 3-phase
			ccdtype = EEV_1152x770_3ph;
			break;
		case 11:				// EEV 1152x770 6-phase
			ccdtype = EEV_1152x770_6ph;
			break;
		case 12:				// EEV 256x1024 6-phase CCD30
			ccdtype = EEV_256x1024_6ph_CCD30;
			break;
		case 13:				// EEV 1024x1024 CCD47-10
			ccdtype = EEV_1024x1024_CCD47_10;
			break;
		case 14:				// HAMMA 64x1024
			ccdtype = HAM_64x1024;
			break;
		case 15:				// HAMMA 128x1024
			ccdtype = HAM_128x1024;
			break;
		case 16:				// HAMMA 256x1024
			ccdtype = HAM_256x1024;
			break;
		case 17:				// KODAK 1024x1536
			ccdtype = KDK_1024x1536;
			break;
		case 18:				// KODAK 512x768
			ccdtype = KDK_512x768;
			break;
		case 19:				// KODAK 1035x1317
			ccdtype = KDK_1035x1317;
			break;
		case 20:				// KODAK 1024x1280
			ccdtype = KDK_1024x1280;
			break;
		case 21:				// KODAK 2044x2033
			ccdtype = KDK_2044x2033;
			break;
		case 22:				// KODAK 2048x3072
			ccdtype = KDK_2048x3072;
			break;
		case 23:				// PI 330x1100 8-phase (horz)
			ccdtype = PID_330x1100_8phH;
			break;
		case 24:				// PI 532x1752
			ccdtype = PID_532x1752;
			break;
		case 25:				// PI 330x1100 6-phase
			ccdtype = PID_330x1100_6phH;
			break;
		case 26:				// PI 240x330 HgCdTe
			ccdtype = PID_240x330_MCT;
			break;
		case 27:				// PI 64x1024
			ccdtype = PI_64x1024;
			break;
		case 28:				// PI 128x1024
			ccdtype = PI_128x1024;
			break;
		case 29:				// PI 256x1024
			ccdtype = PI_256x1024;
			break;
		case 30:				// RET 400x1200
			ccdtype = RET_400x1200;
			break;
		case 31:				// RET 512x512
			ccdtype = RET_512x512;
			break;
		case 32:				// RET 1024x1024
			ccdtype = RET_1024x1024;
			break;
		case 33:				// RET 2048x2048
			ccdtype = RET_2048x2048;
			break;
		case 34:				// SIT 800x2000 Back Illm
			ccdtype = SIT_800x2000_B;
			break;
		case 35:				// SIT 800x2000 Front Illm
			ccdtype = SIT_800x2000_F;
			break;
		case 36:				// SIT 800x1000 Back
			ccdtype = PI_800x1000_B;
			break;
		case 37:				// TEK 512x512B [100ns]
			ccdtype = TEK_512x512_B_100ns;
			break;
		case 38:				// TEK 512x512F [100ns]
			ccdtype = TEK_512x512_F_100ns;
			break;
		case 39:				// TEK 1024x1024B [100ns]
			ccdtype = TEK_1024x1024_B_100ns;
			break;
		case 40:				// TEK 1024x1024F [100ns]
			ccdtype = TEK_1024x1024_F_100ns;
			break;
		case 41:				// TEK 2048x2048
			ccdtype = TEK_2048x2048;
			break;
		case 42:				// TEK 1024x1024B Illm
			ccdtype = TEK_1024x1024_B_200ns;
			break;
		case 43:				// TEK 1024x1024F Illm
			ccdtype = TEK_1024x1024_F_200ns;
			break;
		case 44:				// TEK 512x512B [200ns]
			ccdtype = TEK_512x512_B_200ns;
			break;
		case 45:				// TEK 512x512F [200ns]
			ccdtype = TEK_512x512_F_200ns;
			break;
		case 46:				// TEK 512x512D Back Illm
			ccdtype = TEK_512x512D_B;
			break;
		case 47:				// TEK 512x512D Front Illm
			ccdtype = TEK_512x512D_F;
			break;
		case 48:				// TEK 1024x1024B Back Illm 42usV
			ccdtype = TEK_1024x1024_B_42usV;
			break;
		case 49:				// TEK 1024x1024D Back Illm
			ccdtype = TEK_1024x1024D_B;
			break;
		case 50:				// TEK 1024x1024D Front Illm
			ccdtype = TEK_1024x1024D_F;
			break;
		case 51:				// TEK 1024x1024D Back Illm T3
			ccdtype = TEK_1024x1024D_B_T3;
			break;
		case 52:				// TH 576x384
			ccdtype = THM_576x384;
			break;
		case 53:				// TH 512x512
			ccdtype = THM_512x512;
			break;
		case 54:				// TH 256x1024
			ccdtype = THM_256x1024;
			break;
		case 55:				// TH THM_2048x1024FT
			ccdtype = THM_2048x1024_FT;
			break;
		}	
	
}	