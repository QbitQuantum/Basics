std::string Exporter::getBoneInfo() const
{
	std::string result;
	
	char number[20] = { 0 };
	_itoa(bones.size(), number, 10);
	std::string boneAmount = number;

	for(unsigned int i = 0; i < bones.size(); ++i)
	{
		_itoa(i+1, number, 10);
		result += "Bone (" + std::string(number) + "/" + boneAmount + ")\r\n";
		result += "\tName: " + bones[i].getName() + "\r\n";
		result += "\tParent: " + bones[i].getParentName() + "\r\n";
		_gcvt(bones[i].getRestLength(), 7, number);
		result += "\tRest length: " + std::string(number) + "\r\n";

		_gcvt(bones[i].getRadius(), 7, number);
		result += "\tBone radius: " + std::string(number) + "\r\n";
	}

	return result;
}