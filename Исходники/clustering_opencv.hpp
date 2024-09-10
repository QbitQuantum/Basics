	virtual double DistTo(ClusterablePoint* other) {
		ClusterablePoint_OpenCV* b = dynamic_cast<ClusterablePoint_OpenCV*>(other);
		return pow(GetPixel()[0]-b->GetPixel()[0],2.0) + pow(GetPixel()[1]-b->GetPixel()[1],2.0) + pow(GetPixel()[2]-b->GetPixel()[2],2.0);
	}