void exportTerrain::printLightData(const MFnLight& theLight){
	fout << "Color: " << theLight.intensity()*theLight.color() << endl;

	MVector dir = theLight.lightDirection( 0, MSpace::kWorld);
	dir.normalize();
	fout << "Direction: " << dir << endl;

}