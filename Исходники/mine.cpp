void BoardDrawer::drawCovered(int row, int col) {
	m_ctx->fillRect(col * 10 + 1, row * 10 + 1, 8, 8);
}