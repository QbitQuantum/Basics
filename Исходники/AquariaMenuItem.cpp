void AquariaMenuItem::destroy()
{
	setFocus(false);
	Quad::destroy();
	AquariaGuiElement::clean();
}