void HuffmanCodec::buildEncodeCodes()
{
	long long freqTable[256];

	memset(freqTable, 0, sizeof(freqTable));

	while (!reader->atEnd())
	{
		byte next;
		reader->readByte(next);
		freqTable[next]++;
	}

	priority_queue<pll> pq;

	for (int i = 0; i < 256; i++)
	{
		nodes[i].c = i;
		pq.push(pll(-freqTable[i], i));
	}

	int nodesCount = 256;

	for (int i = 0; i < 255; i++)
	{
		pll top = pq.top();
		pq.pop();
		pll top2 = pq.top();
		pq.pop();
		int nextNodeIndex = nodesCount++;

		int left = top.second, right = top2.second;
		if (left > right)
			swap(left, right);

		nodes[nextNodeIndex].leftChildIndex = left;
		nodes[nextNodeIndex].rightChildIndex = right;
		nodes[top.second].parentIndex = nextNodeIndex;
		nodes[top2.second].parentIndex = nextNodeIndex;

		pq.push(pll(top.first + top2.first, nextNodeIndex));
	}

	rootIndex = nodesCount - 1;
	nodes[rootIndex].parentIndex = -1;

	for (int i = 0; i < 256; i++)
	{
		codeLengths[i] = 0;
		int ci = i;
		int &cLen = codeLengths[i];
		while (true)
		{
			HuffmanTreeNode &cur = nodes[ci];
			if (cur.parentIndex == -1)
				break;
			int curCode = 1;
			if (nodes[cur.parentIndex].leftChildIndex == ci)
				curCode = 0;
			codes[i][cLen++] = curCode;
			ci = cur.parentIndex;
		}
		reverse(codes[i], codes[i] + cLen);
	}

	fwprintf(stderr, L"Table was built\n");
}