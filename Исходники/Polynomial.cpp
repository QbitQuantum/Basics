std::vector<double> Polynomial::solveQuartic(){
	double firstRoot = this->newtonRaphson(1.0);
	Polynomial cubic = this->syntheticDiv(firstRoot);
	std::vector<double> temp = cubic.solveCubic();
	std::vector<double> retVal;
	retVal.push_back(temp[0]);
	retVal.push_back(temp[1]);
	retVal.push_back(temp[2]);
	retVal.push_back(firstRoot);
	return retVal;
}