void PlayingState::draw(HDC& hdc)
{
	_snake.draw(hdc);
	Rectangle(hdc, _food.x, _food.y, _food.x + BLOCK_WIDTH, _food.y + BLOCK_WIDTH);
}