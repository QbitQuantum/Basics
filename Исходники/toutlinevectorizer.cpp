void OutlineVectorizer::createOutlineStrokes()
{
	m_vimage->enableRegionComputing(true, false);
	int j;

	for (j = 0; j < (int)m_nodes.size(); j++) {
		Node *node = m_nodes[j];
		if (node->m_pixel == 0 || node->m_visited)
			continue;
		traceOutline(node);
	}

#ifdef DEBUG
	for (j = 0; j < (int)m_nodes.size(); j++) {
		Node *node = m_nodes[j];
		if (node->m_pixel == 0 || node->m_flag)
			continue;
		outputNodes(node);
	}
#endif

	std::list<std::vector<TThickPoint>>::iterator it_outlines = m_protoOutlines.begin();
	for (it_outlines; it_outlines != m_protoOutlines.end(); it_outlines++) {
		if (it_outlines->size() > 3) {
			std::vector<TThickPoint> points;
			std::vector<TThickPoint>::iterator it;

			if (it_outlines->size() > 10) {
				it = it_outlines->begin() + 1;
				for (;;) {
					//Baco: Ricontrolla l'if seguente - in alcuni casi va fuori bounds...
					if ((int)it_outlines->size() <= m_configuration.m_smoothness + 1)
						break;
					if (it >= it_outlines->end() - (m_configuration.m_smoothness + 1))
						break;
					for (j = 0; j < m_configuration.m_smoothness; j++)
						it = it_outlines->erase(it);
					++it;
				}
			}

			points.push_back(it_outlines->front());
			it = it_outlines->begin();
			TThickPoint old = *it;
			++it;
			for (; it != it_outlines->end(); ++it) {
				TThickPoint point((1 / 2.0) * (*it + old));
				points.push_back(point);
				old = *it;
			}

			points.push_back(it_outlines->back());
			points.push_back(it_outlines->front());

			TStroke *stroke = TStroke::interpolate(points, m_configuration.m_interpolationError);
			stroke->setStyle(m_configuration.m_strokeStyleId);
			stroke->setSelfLoop();
			m_vimage->addStroke(stroke);
		}
	}
}