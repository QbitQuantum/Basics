//for only world
void UITextBox::setFace(vector3 right, vector3 down){
	right.normalize();
	down.normalize();

	direction = right;
	this->down = down;
}