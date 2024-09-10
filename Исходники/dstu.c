err_t dstuCompressPoint(octet xpoint[], const dstu_params* params, 
	const octet point[])
{
	err_t code;
	// состояние
	ec_o* ec;
	word* x;
	word* y;
	void* stack;
	// старт
	code = _dstuCreateEc(&ec, params, _dstuCompressPoint_deep);
	ERR_CALL_CHECK(code);
	// проверить входные указатели
	if (!memIsValid(point, 2 * ec->f->no) || 
		!memIsValid(xpoint, ec->f->no))
	{
		_dstuCloseEc(ec);
		return ERR_BAD_INPUT;
	}
	// раскладка состояния
	x = objEnd(ec, word);
	y = x + ec->f->n;
	stack = y + ec->f->n;
	// загрузить точку
	if (!qrFrom(x, point, ec->f, stack) ||
		!qrFrom(y, point + ec->f->no, ec->f, stack))
	{
		_dstuCloseEc(ec);
		return ERR_BAD_POINT;
	}
	// x == 0?
	if (wwIsZero(x, ec->f->n))
	{
		_dstuCloseEc(ec);
		return ERR_OK;
	}
	// y <- y / x
	qrDiv(y, y, x, ec->f, stack);
	// xpoint <- x(point), xpoint_0 <- tr(y)
	memMove(xpoint, point, ec->f->no);
	xpoint[0] &= 0xFE;
	xpoint[0] |= gf2Tr(y, ec->f, stack);
	// завершение
	_dstuCloseEc(ec);
	return ERR_OK;
}