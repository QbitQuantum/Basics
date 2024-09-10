void ServiceMessagePainter::paint(Painter &p, const HistoryService *message, const PaintContext &context, int height) {
	int left = 0, width = 0;
	message->countPositionAndSize(left, width);
	if (width < 1) return;

	uint64 fullAnimMs = App::main() ? App::main()->animActiveTimeStart(message) : 0;
	if (fullAnimMs > 0 && fullAnimMs <= context.ms) {
		int animms = context.ms - fullAnimMs;
		if (animms > st::activeFadeInDuration + st::activeFadeOutDuration) {
			App::main()->stopAnimActive();
		} else {
			int skiph = st::msgServiceMargin.top() - st::msgServiceMargin.bottom();

			textstyleSet(&st::inTextStyle);
			float64 dt = (animms > st::activeFadeInDuration) ? (1 - (animms - st::activeFadeInDuration) / float64(st::activeFadeOutDuration)) : (animms / float64(st::activeFadeInDuration));
			float64 o = p.opacity();
			p.setOpacity(o * dt);
			p.fillRect(0, skiph, message->history()->width, message->height() - skiph, textstyleCurrent()->selectOverlay->b);
			p.setOpacity(o);
		}
	}

	textstyleSet(&st::serviceTextStyle);

	if (auto media = message->getMedia()) {
		height -= st::msgServiceMargin.top() + media->height();
		int32 left = st::msgServiceMargin.left() + (width - media->maxWidth()) / 2, top = st::msgServiceMargin.top() + height + st::msgServiceMargin.top();
		p.translate(left, top);
		media->draw(p, context.clip.translated(-left, -top), message->toMediaSelection(context.selection), context.ms);
		p.translate(-left, -top);
	}

	QRect trect(QRect(left, st::msgServiceMargin.top(), width, height).marginsAdded(-st::msgServicePadding));

	paintBubble(p, left, width, message->_text, trect);

	if (width > message->maxWidth()) {
		left += (width - message->maxWidth()) / 2;
		width = message->maxWidth();
	}

	p.setBrush(Qt::NoBrush);
	p.setPen(st::msgServiceColor);
	p.setFont(st::msgServiceFont);
	message->_text.draw(p, trect.x(), trect.y(), trect.width(), Qt::AlignCenter, 0, -1, context.selection, false);

	textstyleRestore();
}