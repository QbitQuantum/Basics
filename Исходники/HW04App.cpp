void HW04App::setup()
{
	//Initialize random number generator
	srand(time(NULL));

	vector<Entry> entries;
	ifstream in = ifstream("..\\resources\\Starbucks_2006.csv", fstream::in );
	if(!in.is_open())
	{
		console() << "Error opening file" << endl;
		exit(1);
	}
	while(in.good())
	{
		string line;
		getline(in, line, '\r');
		//Find locations of the commas
		int comma1 = line.find(',');
		int comma2 = line.find(',', comma1 + 1);
		if(comma1 == line.npos || comma2 == line.npos)
		{
			console() << "Error: Malformed file, line " << entries.size() << endl;
			exit(2);
		}
		string str1 = line.substr(0,comma1),
			str2 = line.substr(comma1 + 1, comma2 - comma1 - 1),
			str3 = line.substr(comma2 + 1);
		Entry* e = new Entry;
		e->identifier = str1;
		e->x = atof(str2.c_str());
		e->y = atof(str3.c_str());
		entries.push_back(*e);
	}
	
	//Vector of entries is built, convert to array and call dadoskbmStarbucks.build()

	Entry* arr = new Entry[entries.size()];
	for(unsigned int i = 0; i < entries.size(); i++)
		arr[i] = entries[i];

	starbucks = new dadoskbmStarbucks();
	starbucks->build(arr, entries.size());

	/*
	//DEBUG CODE:
	Entry* entry = starbucks->getNearest(0.167744693,0.3479477);
		
	console() << "Your nearest Starbucks:" << endl
		<< entry->identifier << endl << entry->x << endl << entry->y << endl;
	*/

	//DRAWING SETUP
	lastHighlighted = Vec2i(-1, -1);
	bg = loadImage("..\\resources\\usa.jpg");
	clone = bg.clone();
	
	for(unsigned int i = 0; i < entries.size(); i++)
	{
		Entry entry = entries[i];
		Vec2i coords = coord2Img(entry.x, entry.y);
		clone.setPixel(coords, Color8u(0xff,0x00,0x00));
	}
	
}