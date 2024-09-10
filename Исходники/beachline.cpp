void Voronoi::ParabolaNode::_move(std::unique_ptr<ParabolaNode> parabola)
{
	_leftSibling = parabola->_leftSibling;
	_rightSibling = parabola->_rightSibling;
	_leftChild = std::move(parabola->_leftChild);
	_rightChild = std::move(parabola->_rightChild);
	setSite(parabola->site());
	setEdge(parabola->edge());
	setEvent(parabola->event());
}