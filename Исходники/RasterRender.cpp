AVPixelFormat RasterRenderPrivate::getFormat(QString &chroma)
{
	static QHash<QString, AVPixelFormat> f;
	if (f.isEmpty()){
		f.insert("RV32", AV_PIX_FMT_RGB32);
		f.insert("RV24", AV_PIX_FMT_RGB24);
		f.insert("RGB8", AV_PIX_FMT_RGB8);
		f.insert("RV12", AV_PIX_FMT_RGB444);
		f.insert("RV15", AV_PIX_FMT_RGB555);
		f.insert("RV16", AV_PIX_FMT_RGB565);
		f.insert("RGBA", AV_PIX_FMT_RGBA);
		f.insert("ARGB", AV_PIX_FMT_ARGB);
		f.insert("BGRA", AV_PIX_FMT_BGRA);
		f.insert("I410", AV_PIX_FMT_YUV410P);
		f.insert("I411", AV_PIX_FMT_YUV411P);
		f.insert("I420", AV_PIX_FMT_YUV420P);
		f.insert("IYUV", AV_PIX_FMT_YUV420P);
		f.insert("I422", AV_PIX_FMT_YUV422P);
		f.insert("I440", AV_PIX_FMT_YUV440P);
		f.insert("I444", AV_PIX_FMT_YUV444P);
		f.insert("J420", AV_PIX_FMT_YUVJ420P);
		f.insert("J422", AV_PIX_FMT_YUVJ422P);
		f.insert("J440", AV_PIX_FMT_YUVJ440P);
		f.insert("J444", AV_PIX_FMT_YUVJ444P);
		f.insert("I40A", AV_PIX_FMT_YUVA420P);
		f.insert("I42A", AV_PIX_FMT_YUVA422P);
		f.insert("YUVA", AV_PIX_FMT_YUVA444P);
		f.insert("YA0L", AV_PIX_FMT_YUVA444P10LE);
		f.insert("YA0B", AV_PIX_FMT_YUVA444P10BE);
		f.insert("NV12", AV_PIX_FMT_NV12);
		f.insert("NV21", AV_PIX_FMT_NV21);
		f.insert("I09L", AV_PIX_FMT_YUV420P9LE);
		f.insert("I09B", AV_PIX_FMT_YUV420P9BE);
		f.insert("I29L", AV_PIX_FMT_YUV422P9LE);
		f.insert("I29B", AV_PIX_FMT_YUV422P9BE);
		f.insert("I49L", AV_PIX_FMT_YUV444P9LE);
		f.insert("I49B", AV_PIX_FMT_YUV444P9BE);
		f.insert("I0AL", AV_PIX_FMT_YUV420P10LE);
		f.insert("I0AB", AV_PIX_FMT_YUV420P10BE);
		f.insert("I2AL", AV_PIX_FMT_YUV422P10LE);
		f.insert("I2AB", AV_PIX_FMT_YUV422P10BE);
		f.insert("I4AL", AV_PIX_FMT_YUV444P10LE);
		f.insert("I4AB", AV_PIX_FMT_YUV444P10BE);
		f.insert("UYVY", AV_PIX_FMT_UYVY422);
		f.insert("YUYV", AV_PIX_FMT_YUYV422);
		f.insert("YUY2", AV_PIX_FMT_YUYV422);
	}
	chroma = chroma.toUpper();
	if (f.contains(chroma)){
	}
	else if (chroma == "YV12"){
		chroma = "I420";
	}
	else if (chroma == "NV16"){
		chroma = "NV12";
	}
	else if (chroma == "NV61"){
		chroma = "NV21";
	}
	else if (chroma == "VYUY" ||
		chroma == "YVYU" ||
		chroma == "V422" ||
		chroma == "CYUV"){
		chroma = "UYVY";
	}
	else if (chroma == "V210"){
		chroma = "I0AL";
	}
	else{
		chroma = "I420";
	}
	return f[chroma];
}