int main(){	

	//https://github.com/SkullCrusher/ProjectMicheal

	//"Lol you can decrypt I see. try the rest."
	//Encrypted with Seed 23: "ct$D_p)INQa#)05Idv.N9Ynu|Ll$8Ss+5<\\pw.Dr"

	//"SkullCrusher: I hope this works right, I did not test alot."
	//Encrypted with Seed 43: "~-DR`EYp'18L(H3S]n\")I_it+Kdu+8Mm#.7AW%E0PVag)9J`\"8?Tj,/=Nd4"

	//http://i.imgur.com/4SBSgDo.jpg
	//Encrypted with Seed 50: "<RhzV'Va1<KTk!OTetEynRGP6Gu#5>"

	//"This was encrypted here is a url: http://i.imgur.com/OTz3RH1.gif"
	//Encrypted with Seed 42: "~*5Jj%(=]dty/J\\ry!AKRfm/:Oor4K_mIis+AS/^/:hs$-DX(->M|mc!TH2c3<GO"
	
	//An example encryption string.
	std::string Message = "http://www.cplusplus.com/doc/tutorial/variables/";
	
	Encrypt(Message, 17);
	Decrypt(Message, 17);

	return 0;
}