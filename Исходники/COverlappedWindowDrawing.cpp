void COverlappedWindow::drawEdges(HDC paintDC, const RECT& rect) {
	if (isGameStarted) {
		for (Edge e : game.getEdges()) {
			drawEdge(paintDC, rect, e);
		}
	}
}