void LayerSelect::serializeBody(QIODevice& data) const {
	data.putChar(_user);
	data.putChar(_layer);
}