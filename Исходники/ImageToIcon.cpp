int _tmain(int argc, _TCHAR* argv[])
{

	ENapi::Image img;
	if(ENapi::Image::ErrorCode::NONE != img.loadImage("alpha.ppm",ENapi::Image::FileType::PPM))
	{
		return 0;
	}
	ENapi::Image *fimg = new ENapi::Image();
	*fimg = img;
	bool outside  = true;
	int edgeTotal = 0;
	int r,g,b;
	nodeMap = new Node**[fimg->getImageHeight()];


	//make binary
	for(int i=0;i<img.getImageHeight(); ++i)
	{
		nodeMap[i] = new Node*[fimg->getImageWidth()];
		for(int j=0;j<img.getImageWidth(); ++j)
		{
			nodeMap[i][j] = NULL;
			img.getPixel(i,j,r,g,b);
			if(r > 100)
				img.setPixel(i,j,255,255,255);
			else
				img.setPixel(i,j,0,0,0);
		}
	}

	fimg->saveImage("alpha2_bin.ppm",ENapi::Image::FileType::PPM);


	for(int i=0;i<img.getImageHeight(); ++i)
	{
		outside = true;
		for(int j=0;j<img.getImageWidth(); ++j)
		{
			img.getPixel(i,j,r,g,b);
			if(outside && r == 255)
			{
				outside = false;
				fimg->setbPixel(i,j,255,255,255);
				Node *node = new Node(j,i,img.getImageWidth(), img.getImageHeight());
				nodeList.push_back(node);
				nodeMap[i][j] = node;
			}
			else if(!outside && j > 0 && r ==0)
			{
				outside = true;
				fimg->setbPixel(i,j-1,255,255,255);
				Node *node = new Node(j-1,i,img.getImageWidth(), img.getImageHeight());
				nodeList.push_back(node);
				nodeMap[i][j] = node;
				
			}
			else
			{
				if(r == 255 && allNeighborsWhite(&img,i,j,3))
					fimg->setbPixel(i,j,0,0,0);
				else if(r == 0)
					fimg->setbPixel(i,j,0,0,0);

				else
				{
					fimg->setbPixel(i,j,255,255,255);
					Node *node = new Node(j,i,img.getImageWidth(), img.getImageHeight());
					nodeList.push_back(node);
					nodeMap[i][j] = node;
				}

			}
			
			
		}
	}
	
	fimg->saveImage("alpha2.ppm",ENapi::Image::FileType::PPM);

	Path p(nodeList,fimg,3);
	p.run();
	p.render(fimg->getImageHeight() * 2, fimg->getImageWidth() * 2)->saveImage("alphaRendered.ppm", ENapi::Image::FileType::PPM);
	
	return 0;
}