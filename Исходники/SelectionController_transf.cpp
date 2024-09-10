void SelectionController::move() {
	if (INPUT->again(Qt::RightButton)) {
		pos_init = INPUT->getPixel();
		pos_selec = getPosition();
	}

	if (INPUT->pressed(Qt::RightButton)) {
		sf::Vector2f final_pos;
		if (INPUT->pressed(Qt::Key_Control)) {
			sf::Vector2f pos_mouse = Fonction::selecPointRect(VECTOR2F(pos_init), VECTOR2F(INPUT->getPixel())).distance;
			pos_mouse.x = floor(pos_mouse.x);
			pos_mouse.y = floor(pos_mouse.y);
			final_pos.x = pos_mouse.x + pos_selec.x;
			final_pos.y = pos_mouse.y + pos_selec.y;
			setPosition(final_pos);
		}
		else
			translate(VECTOR2F(INPUT->getDeltaPixel()));
	}
	else if (INPUT->released(Qt::RightButton))
		if (getPosition() != pos_selec)
			UNDO->push(*new SelecMoved(this, getPosition()));
}