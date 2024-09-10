void MapLayer::cull(sf::FloatRect bounds){
	if (m_type == MapLayerType::TileLayer){
		int tilePatchCount = m_tilePatches.size();
		for (int i = 0; i < tilePatchCount; i++){
			if (bounds.intersects(m_tilePatches[i].aabb))
				m_tilePatches[i].visible = true;
			else
				m_tilePatches[i].visible = false;
		}
		sf::RectangleShape test;
		test.setSize(sf::Vector2f(bounds.width, bounds.height));
		test.setFillColor(sf::Color(255, 0,0, 25));
		test.setOutlineColor(sf::Color::Magenta);
		test.setOutlineThickness(8.f);
		test.setPosition(bounds.left, bounds.top);
		testShapes.back() = test;
	}
}