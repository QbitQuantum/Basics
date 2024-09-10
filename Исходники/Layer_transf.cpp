void Layer::move() {
    if (INPUT->again(Qt::RightButton)) {
        posi = INPUT->getPixel();
        posf = getPosition();
    }

    if (INPUT->pressed(Qt::RightButton)) {
        sf::Vector2f move;
        if (INPUT->pressed(Qt::Key_Control)) {
            sf::Vector2f pos_mouse = Fonction::selecPointRect(VECTOR2F(posi), VECTOR2F(INPUT->getDeltaPixel())).distance;
            pos_mouse = CALL_VECTOR2F(pos_mouse, floor);
            move = pos_mouse + posf;
            setPosition(move);
        }
        else
            translate(VECTOR2F(INPUT->getDeltaPixel()));
    }
    else if (INPUT->released(Qt::RightButton))
        if (getPosition() != posf)
            UNDO->push(*new LayerMoved(this, getPosition()));
}