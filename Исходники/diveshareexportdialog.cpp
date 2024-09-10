static QByteArray generate_html_list(const QByteArray &data)
{
	QList<QByteArray> dives = data.split('\n');
	QByteArray html;
	html.append("<html><body><table>");
	for (int i = 0; i < dives.length(); i++ ) {
		html.append("<tr>");
		QList<QByteArray> dive_details = dives[i].split(',');
		if (dive_details.length() < 3)
			continue;

		QByteArray dive_id = dive_details[0];
		QByteArray dive_delete = dive_details[1];

		html.append("<td>");
		html.append("<a href=\"" DIVESHARE_BASE_URI "/dive/" + dive_id + "\">");

		//Title gets separated too, this puts it back together
		const char *sep = "";
		for (int t = 2; t < dive_details.length(); t++) {
			html.append(sep);
			html.append(dive_details[t]);
			sep = ",";
		}

		html.append("</a>");
		html.append("</td>");
		html.append("<td>");
		html.append("<a href=\"" DIVESHARE_BASE_URI "/delete/dive/" + dive_delete + "\">Delete dive</a>");
		html.append("</td>"  );

		html.append("</tr>");
	}

	html.append("</table></body></html>");
	return html;
}