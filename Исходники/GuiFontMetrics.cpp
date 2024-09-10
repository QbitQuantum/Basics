int GuiFontMetrics::smallcapsWidth(char_type c) const
{
	// FIXME: Optimisation probably needed: we don't use the width cache.
	if (is_utf16(c)) {
		QChar const qc = ucs4_to_qchar(c);
		QChar const uc = qc.toUpper();
		if (qc != uc)
			return smallcaps_metrics_.width(uc);
		else
			return metrics_.width(qc);
	} else {
		QString const s = toqstr(docstring(1, c));
		QString const us = s.toUpper();
		if (s != us)
			return smallcaps_metrics_.width(us);
		else
			return metrics_.width(s);
	}
}