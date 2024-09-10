IGraphFile *newGraphFile()
{
   IGraphFile *graphfile = NULL;
   MetaGraph *graph = new MetaGraph();
   // REMINDER: fill in some more details here:
	pstring version = "Sala.dll version";
	char tmpbuf[9];
	pstring date = pstring(_strdate(tmpbuf));
   graph->setProperties(pstring("Name"),pstring("Organisation"),pstring(date),pstring(version));
	graphfile = new IGraphFile();
	graphfile->setData(graph);
   // ensure the graph is labelled for deletion after use
   ((IGraphOrganizer *)graphfile->m_data)->setDeleteFlag();
   return graphfile;
}