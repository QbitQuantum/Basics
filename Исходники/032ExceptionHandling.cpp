	void main1()
	{
		set_terminate(Release);
		cout << "Resources alloted in main" << endl;
		throw 100;
		cout << "Resources released in main" << endl;
	}