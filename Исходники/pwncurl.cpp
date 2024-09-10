static cell AMX_NATIVE_CALL n_SetPixelRGBA( AMX* amx, cell* params ){
	amx_StrParam(amx,params[1],tmp);
	BMP Image;
	posx = params[2];
	posy = params[3];
	Image.ReadFromFile(tmp);
	RGBApixel value;
	
	value.Red = (ebmpBYTE)params[4];
	value.Green = (ebmpBYTE)params[5];
	value.Blue = (ebmpBYTE)params[6];
	value.Alpha = (ebmpBYTE)params[7];
	
	Image.SetBitDepth(24);
	Image.GetPixel(posx,posy);
	Image.SetPixel(posx,posy,value);
	return Image.WriteToFile(tmp);
}