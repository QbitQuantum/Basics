void SkLabel::setDefaultForegroundColor (const QColor &color)
{
	// TODO: this will use the parent's foreground color as this widget's
	// foreground color, which means that it will not be updated if the
	// style is changed.
	defaultForegroundColor=color;
	updateColors ();
}