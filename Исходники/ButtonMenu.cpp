void ButtonMenu::mouseOver(sf::IntRect rect){

	for(int i = 0; i < m_buttons.size(); i++){
		if(rect.intersects(m_buttons[i]->getButtonRect())){
			m_buttons[i]->setColor(sf::Color::Magenta);
		}else{
			m_buttons[i]->setColor(sf::Color::Blue);
		}
	}
}