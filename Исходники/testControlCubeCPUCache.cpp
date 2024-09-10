int main(int argc, char ** argv)
{
	int nLevels = 10;
	int levelCube = 8;
	vmml::vector<3,int> offset(0,0,0);

	lunchbox::Clock clock;

	std::vector<std::string> parameters;
	parameters.push_back(std::string(argv[1]));
	parameters.push_back(std::string(argv[2]));

	if (argc == 4)
	{
		std::string n(argv[3]);
		mO = boost::lexical_cast<double>(n);
	}

	hdf5File.init(parameters);

	if (!ccc.initParameter(parameters, mO))
	{
		std::cerr<<"Error init control cube cpu cache"<<std::endl;
	}

	vmml::vector<3, int> dim = hdf5File.getRealDimension();

	std::cout<<"Checking errors........."<<std::endl;

	bool error = false;
	for(int i=0; i<10 && !error; i++)
	{
		vmml::vector<3,int> s;
		vmml::vector<3,int> e;
		int nLevels = 0;
		int dimA = 0;
		int dimV = 0;
		do
		{
			s.set(rand() % dim.x(), 0, rand() % dim.z());
			do
			{
				e.set(rand() % (dim.x() - s.x()) + s.x(), rand() % (dim.y() - s.y()) + s.y(), rand() % (dim.z() - s.z()) + s.z());
			}
			while(s.x() >= e.x() || s.y() >= e.y() || s.z() >= e.z());
			 
			/* Calcular dimension del árbol*/
			dimA = fmin(e.x()-s.x(), fmin(e.y() - s.y(), e.z() - s.z()));
			float aux = logf(dimA)/logf(2.0);
			float aux2 = aux - floorf(aux);
			nLevels = aux2>0.0 ? aux+1 : aux;
			dimV = exp2(nLevels);
		}
		while(nLevels <= 1 || s.x()+dimV >= dim.x() || s.y()+dimV >= dim.y() || s.z()+dimV >= dim.z());

		int levelCube = rand() % (nLevels - 1) + 1;

		std::cout<<"Test "<<i<<" nLevels "<<nLevels<<" levelCube "<<levelCube<<" dimension "<<exp2(nLevels - levelCube)<<" offset "<<s<<" : "<<std::endl;

		error = test(nLevels, levelCube, s);
		if (error)
			std::cout<<"Test Fail!"<<std::endl;
		else
		{
			std::cout<<"Test OK"<<std::endl;
		}
	}

	std::cout<<"Checking performance........."<<std::endl;

	for(int i=0; i<10 && !error; i++)
	{
		vmml::vector<3,int> s;
		vmml::vector<3,int> e;
		int nLevels = 0;
		int dimA = 0;
		int dimV = 0;
		do
		{
			s.set(rand() % dim.x(), 0, rand() % dim.z());
			do
			{
				e.set(rand() % (dim.x() - s.x()) + s.x(), rand() % (dim.y() - s.y()) + s.y(), rand() % (dim.z() - s.z()) + s.z());
			}
			while(s.x() >= e.x() || s.y() >= e.y() || s.z() >= e.z());
			 
			dimA = fmin(e.x()-s.x(), fmin(e.y() - s.y(), e.z() - s.z()));;
			/* Calcular dimension del árbol*/
			float aux = logf(dimA)/logf(2.0);
			float aux2 = aux - floorf(aux);
			nLevels = aux2>0.0 ? aux+1 : aux;
			dimV = exp2(nLevels);
		}
		while(nLevels <= 1 || s.x()+dimV >= dim.x() || s.y()+dimV >= dim.y() || s.z()+dimV >= dim.z());

		int levelCube = rand() % (nLevels - 1) + 1;

		std::cout<<"Test "<<i<<" nLevels "<<nLevels<<" levelCube "<<levelCube<<" dimension "<<exp2(nLevels - levelCube)<<" offset "<<s<<" : "<<std::endl;

		double time = 0.0;
		clock.reset();
		testPerf(nLevels, levelCube, s);
		time = clock.getTimed()/1000.0;
		double bw = ((((dimV-s.x())*(dimV-s.y())*(dimV-s.z()))*sizeof(float))/1204.0/1024.0)/time;

		std::cout<<"Test "<<s<<" "<<e<<": "<<time<<" seconds ~ "<<bw<<" MB/s"<<std::endl;
	}

	if (!error)
	{
		int dimA = fmax(dim.x(), fmaxf(dim.y(), dim.z()));
		nLevels = 0;
		/* Calcular dimension del árbol*/
		float aux = logf(dimA)/logf(2.0);
		float aux2 = aux - floorf(aux);
		nLevels = aux2>0.0 ? aux+1 : aux;

		levelCube = rand() % (nLevels - 4) + 4;
		std::cout<<"Test reading complete volume"<<std::endl;
		if (test(nLevels, levelCube, vmml::vector<3,int>(0,0,0)))
		{
			std::cerr<<"Test Fail!!"<<std::endl;	
		}
		else
		{
			double time = 0.0;
			clock.reset();
			testPerf(nLevels, levelCube, vmml::vector<3,int>(0,0,0));
			time = clock.getTimed()/1000.0;
			double bw = (((dim.x()*dim.y()*dim.z())*sizeof(float))/1204.0/1024.0)/time;

			std::cout<<"Read complete volume "<<dim<<" : "<<time<<" seconds ~ "<<bw<<" MB/s"<<std::endl; 
		}
	}

	ccc.stopCache();
	hdf5File.close();

	return 0;
}