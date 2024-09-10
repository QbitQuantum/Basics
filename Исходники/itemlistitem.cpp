	void layout() {
		rectCount = 0;
		minimum = 0;
		if (list.isEmpty())
			return;
		_Expand(rects, list.size()+4, 2.1);

		int fills = 0;
		qreal filled = 0;
		auto calculate = [&filled, &fills, this] (const ItemListAttached *attached) {
			filled += 2*O::padding(p, attached);
			if (attached->thickness() < 0) {
				if (length < 0)
					++fills;
				else
					filled += length;
			} else
				filled += attached->thickness();
		};
		runLayoutLoop(calculate);
		const auto fill = qMax((O::length(p) - filled)/fills, 0.0);
		auto it = rects.begin();
		qreal pos = 0;
		auto append = [&it, &pos, fill, this] (ItemListAttached *attached) {
			qreal total = 2*O::padding(p, attached);
			if (attached->thickness() < 0) {
				if (length < 0)
					total += fill;
				else
					total += length;
			} else
				total += attached->thickness();
			attached->fill(total);
			if (attached->isQmlItem()) {
				const auto vpad = pick(attached->verticalPadding(), this->vpad);
				const auto hpad = pick(attached->horizontalPadding(), this->hpad);
				const auto rect = O::itemRect(p, attached, pos, {hpad, vpad});
				auto qml = static_cast<QQuickItem*>(attached->attachee());
				qml->setPosition(rect.topLeft());
				qml->setSize(rect.size());
			}
			it->attached = attached;
			it->pos = pos;
			++it;
			pos += total;
		};
		runLayoutLoop(append);
		rectCount = std::distance(rects.begin(), it);
		if (_Change(minimum, filled))
			emit p->minimumLengthChanged();
		p->setGeometryDirty();
	}