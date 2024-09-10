void stable_merge_y(vector<point_seg_pair>::iterator first, vector<point_seg_pair>::iterator middle, vector<point_seg_pair>::iterator last)
{
	vector<point_seg_pair> buffer(distance(first, last));

	auto in1 = first;
	auto in2 = middle;
	auto out = buffer.begin();

	while(in1 != middle && in2 != last)
	{
		if(in2->first.y < in1->first.y)
			*out++ = *in2++;
		else
			*out++ = *in1++;
	}

	copy(in1, middle, out);
	copy(in2, last, out);
	copy(buffer.begin(), buffer.end(), first);
}