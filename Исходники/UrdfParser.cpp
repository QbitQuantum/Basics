static bool parseVector3(btVector3& vec3, const std::string& vector_str, ErrorLogger* logger, bool lastThree = false)
{
	vec3.setZero();
	btArray<std::string> pieces;
	btArray<float> rgba;
	urdfStringSplit(pieces, vector_str, urdfIsAnyOf(" "));
	for (int i = 0; i < pieces.size(); ++i)
	{
		if (!pieces[i].empty())
		{
			rgba.push_back(urdfLexicalCast<double>(pieces[i].c_str()));
		}
	}
	if (rgba.size() < 3)
	{
		logger->reportWarning("Couldn't parse vector3");
		return false;
	}
    if (lastThree) {
        vec3.setValue(rgba[rgba.size()-3], rgba[rgba.size()-2], rgba[rgba.size()-1]);
    }
    else
    {
        vec3.setValue(rgba[0],rgba[1],rgba[2]);

    }
	return true;
}