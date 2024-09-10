/**
 * takes a richtext string and heuristically adds links for uris of common protocols
 * @return a richtext string with link markup added
 */
QString TextUtil::linkify(const QString &in)
{
	QString out = in;
	int x1, x2;
	bool isUrl, isAtStyle;
	QString linked, link, href;

	for(int n = 0; n < (int)out.length(); ++n) {
		isUrl = false;
		isAtStyle = false;
		x1 = n;

		if(linkify_pmatch(out, n, "xmpp:")) {
			n += 5;
			isUrl = true;
			href = "";
		}
		else if(linkify_pmatch(out, n, "mailto:")) {
			n += 7;
			isUrl = true;
			href = "";
		}
		else if(linkify_pmatch(out, n, "http://")) {
			n += 7;
			isUrl = true;
			href = "";
		}
		else if(linkify_pmatch(out, n, "https://")) {
			n += 8;
			isUrl = true;
			href = "";
		}
		else if(linkify_pmatch(out, n, "ftp://")) {
			n += 6;
			isUrl = true;
			href = "";
		}
		else if(linkify_pmatch(out, n, "news://")) {
			n += 7;
			isUrl = true;
			href = "";
		}
		else if (linkify_pmatch(out, n, "ed2k://")) {
			n += 7;
			isUrl = true;
			href = "";
		}
		else if (linkify_pmatch(out, n, "magnet:")) {
			n += 7;
			isUrl = true;
			href = "";
		}
		else if(linkify_pmatch(out, n, "www.")) {
			isUrl = true;
			href = "http://";
		}
		else if(linkify_pmatch(out, n, "ftp.")) {
			isUrl = true;
			href = "ftp://";
		}
		else if(linkify_pmatch(out, n, "@")) {
			isAtStyle = true;
			href = "x-psi-atstyle:";
		}

		if(isUrl) {
			// make sure the previous char is not alphanumeric
			if(x1 > 0 && out.at(x1-1).isLetterOrNumber())
				continue;

			// find whitespace (or end)
			QMap<QChar, int> brackets;
			brackets['('] = brackets[')'] = brackets['['] = brackets[']'] = brackets['{'] = brackets['}'] = 0;
			QMap<QChar, QChar> openingBracket;
			openingBracket[')'] = '(';
			openingBracket[']'] = '[';
			openingBracket['}'] = '{';
			for(x2 = n; x2 < (int)out.length(); ++x2) {
				if(out.at(x2).isSpace() || linkify_isOneOf(out.at(x2), "\"\'`<>")
					|| linkify_pmatch(out, x2, "&quot;")  || linkify_pmatch(out, x2, "&apos;")
					|| linkify_pmatch(out, x2, "&gt;") || linkify_pmatch(out, x2, "&lt;") ) {
					break;
				}
				if(brackets.keys().contains(out.at(x2))) {
					++brackets[out.at(x2)];
				}
			}
			int len = x2-x1;
			QString pre = resolveEntities(out.mid(x1, x2-x1));

			// go backward hacking off unwanted punctuation
			int cutoff;
			for(cutoff = pre.length()-1; cutoff >= 0; --cutoff) {
				if(!linkify_isOneOf(pre.at(cutoff), "!?,.()[]{}<>\""))
					break;
				if(linkify_isOneOf(pre.at(cutoff), ")]}")
					&& brackets[pre.at(cutoff)] - brackets[openingBracket[pre.at(cutoff)]] <= 0 ) {
					break;	// in theory, there could be == above, but these are urls, not math ;)
				}
				if(brackets.keys().contains(pre.at(cutoff))) {
					--brackets[pre.at(cutoff)];
				}

			}
			++cutoff;
			//++x2;

			link = pre.mid(0, cutoff);
			if(!linkify_okUrl(link)) {
				n = x1 + link.length();
				continue;
			}
			href += link;
			// attributes need to be encoded too.
			href = escape(href);
			href = linkify_htmlsafe(href);
			//printf("link: [%s], href=[%s]\n", link.latin1(), href.latin1());
			QColor lcolor=PsiOptions::instance()->getOption("options.ui.look.colors.chat.link-color").toString();
			linked = QString("<a href=\"%1\" style=\"color:"+lcolor.name()+"\">").arg(href) + escape(link) + "</a>" + escape(pre.mid(cutoff));
			out.replace(x1, len, linked);
			n = x1 + linked.length() - 1;
		}
		else if(isAtStyle) {
			// go backward till we find the beginning
			if(x1 == 0)
				continue;
			--x1;
			for(; x1 >= 0; --x1) {
				if(!linkify_isOneOf(out.at(x1), "_.-+") && !out.at(x1).isLetterOrNumber())
					break;
			}
			++x1;

			// go forward till we find the end
			x2 = n + 1;
			for(; x2 < (int)out.length(); ++x2) {
				if(!linkify_isOneOf(out.at(x2), "_.-+") && !out.at(x2).isLetterOrNumber())
					break;
			}

			int len = x2-x1;
			link = out.mid(x1, len);
			//link = resolveEntities(link);

			if(!linkify_okEmail(link)) {
				n = x1 + link.length();
				continue;
			}

			href += link;
			//printf("link: [%s], href=[%s]\n", link.latin1(), href.latin1());
			QColor mcolor=PsiOptions::instance()->getOption("options.ui.look.colors.chat.mailto-color").toString();
			linked = QString("<a href=\"%1\" style=\"color:"+mcolor.name()+"\">").arg(href) + link + "</a>";
			out.replace(x1, len, linked);
			n = x1 + linked.length() - 1;
		}
	}

	return out;
}