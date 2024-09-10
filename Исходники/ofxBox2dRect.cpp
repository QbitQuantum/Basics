// Temporary fix until OF 0.8.0
static void rectangle(ofPath & path, const ofRectangle & r){
	path.moveTo(r.getTopLeft());
	path.lineTo(r.getTopRight());
	path.lineTo(r.getBottomRight());
	path.lineTo(r.getBottomLeft());
	path.close();
}