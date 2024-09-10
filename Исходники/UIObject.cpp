void UIObject::SetText(const wchar_t* pText) {
	text = pText;

	XMVECTOR xmSize = font->MeasureString(text);
	XMFLOAT2 size;
	XMStoreFloat2(&size, xmSize);
	textWidth = size.x;
	textHeight = size.y;

	textPos = XMFLOAT2(position.x + (material->getTexWidth() - size.x) / 2, position.y + (material->getTexHeight() - size.y) / 2);
}