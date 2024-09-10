void bruteforce_helper(HittingSetData &data, int setNum, int level, vector<int> &set_antenna)
{
	//make copies for recursive calls
	vector<int> b1(data.antennas.at(setNum)), b2, a1(set_antenna), a2(set_antenna), n1(data.antennas.at(setNum)), n2, dc1, dc2;
	int nn1 = data.antennas.at(setNum).size(), nn2 = 0;
	a1.at(level) = setNum;
	
	cout << "brute force called 1"  << endl;
	bruteforce(data, setNum+1, level+1, a1, b1, n1, dc1, nn1);
	
	cout << "brute force called 2 " << endl;
	bruteforce(data, setNum+2, level+1, a2, b2, n2, dc2, nn2);
	
  //select which one did better
  //TODO: check this logic
	if(nn1 > nn2)
  {
    set_antenna.swap(a1);
  }
	else
  {
    set_antenna.swap(a2);
  }

	return;
}