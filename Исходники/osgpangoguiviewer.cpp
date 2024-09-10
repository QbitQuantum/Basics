	void _finalizeCorner(
		float x,
		float y,
		const osgWidget::Color& lc,
		const osgWidget::Color& fc
	) {
		setSourceRGBA(lc);
		strokePreserve();
		setSourceRGBA(fc);
		lineTo(x, y);
		fill();
	}