void GridFrame::update() {
    float tmp = (float)15/19;

    currentTetrimono->fall(25);
    repaint();
    if(!hasLost)
        setTimer(1000*tmp/(currentGame->getLevel() + tmp));
    else
        setTimer(75);
    if (currentTetrimono->isOnFloor()) {
        if (currentTetrimono->getUpperBound() <= 0) {
            hasLost = true;
            return;
        }
        currentGame->scoreManage();
        delete currentTetrimono; // on désaloue la mémoire  du tétrimono sur le sol
        currentTetrimono = new Tetrimono(nextTetrimonoNumber, grid);
        int i = rand() % 7;
        nextTetrimonoNumber = i;
        emit updateNextBlock(i);
    }
    QWidget::update();
}