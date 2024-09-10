bool CFrmSettings::loadGraph(MdiChild * m)
{
    if (graph) {
	agclose(graph);
	graph = NULL;
    }
    graphData.clear();
    graphData.append(m->toPlainText());
    setActiveWindow(m);
    return true;

}