void CreateNeighbours(EERIE_3DOBJ * obj)
{
	if (obj->ndata == NULL)
	{
		obj->ndata = (NEIGHBOURS_DATA *)malloc(sizeof(NEIGHBOURS_DATA) * obj->vertexlist.size());
	}
	else memset(obj->ndata, 0, sizeof(NEIGHBOURS_DATA)*obj->vertexlist.size());

	for (size_t i = 0; i < obj->vertexlist.size(); i++)
	{
		obj->ndata[i].Nvertex = NULL;
		obj->ndata[i].Nfaces = NULL;
		obj->ndata[i].nb_Nfaces = 0;
		obj->ndata[i].nb_Nvertex = 0;

		for (size_t j = 0; j < obj->facelist.size(); j++)
		{
			if ((obj->facelist[j].vid[0] == i) ||
			        (obj->facelist[j].vid[1] == i) ||
			        (obj->facelist[j].vid[2] == i))
			{
				AddNeighBoringVertex(obj, i, obj->facelist[j].vid[0]);
				AddNeighBoringVertex(obj, i, obj->facelist[j].vid[1]);
				AddNeighBoringVertex(obj, i, obj->facelist[j].vid[2]);
				AddNeighBoringFace(obj, i, j);
			}
		}
	}

}