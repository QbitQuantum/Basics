//**********************************************************************************
bool CJpegHandler::Decompress(
//Load a JPEG from disk and uncompress it into a byte buffer.
//
//Returns: true if successful
//
//Params:
	const WCHAR *wszName,   //(in)   Full path+name to the JPEG image
	BYTE* &imageBuffer, UINT &wWidth, UINT &wHeight)   //(out) image data
{
/*
	DECOMPRESSION Outline:
	Allocate and initialize a JPEG decompression object
	Specify the source of the compressed data (eg, a file)
	Call jpeg_read_header() to obtain image info
	Set parameters for decompression
	jpeg_start_decompress(...);
	while (scan lines remain to be read)
		jpeg_read_scanlines(...);
	jpeg_finish_decompress(...);
	Release the JPEG decompression object
*/
	//Reading the JPEG file into a buffer and decompressing it there will result
	//in many fewer disk I/O accesses, so we'll do it that way.
	CFiles f;
	CStretchyBuffer buffer;
	if (!f.ReadFileIntoBuffer(wszName, buffer,true))
		return false;
	return Decompress((BYTE*)buffer, buffer.Size(), imageBuffer, wWidth, wHeight);
}