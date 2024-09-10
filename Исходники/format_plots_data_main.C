void SaveCanvas(TCanvas * c, string fileNameAndDir, string FileTypes){
/*
 Supply a canvas, a name you'd like the file to have (possibly prefixed by a directory), 
 and a string containing the names of file extensons.  The default is to save as .C, .root, .pdf, .jpg, .gif, .png, and .eps
 The filetype string is case insensitive. 
 
 For example 
 SaveCanvas(myCanvas, "plots/mycanvas") 
       saves canvas in dir plots as mycanvas.C, mycanvas.root, mycanvas.jpg 
       all types are saved.
 SaveCanvas(myCanvas, "mycanvas","jpgif")
       saves the canvas as mycanvas.jpg and mycanvas.gif
 */
	
	TString TFileTypes = FileTypes;
	TFileTypes.ToLower();
	string lc_types = TFileTypes.Data();
	if(lc_types.find("c")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".C").c_str());
	if(lc_types.find("root")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".root").c_str());
	if(lc_types.find("pdf")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".pdf").c_str());
	if(lc_types.find("jpg")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".jpg").c_str());
	if(lc_types.find("gif")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".gif").c_str());
	if(lc_types.find("png")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".png").c_str());
	if(lc_types.find("eps")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".eps").c_str());
}