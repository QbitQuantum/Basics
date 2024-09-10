/*#define TOPARSE_DEBUG
#include <QtDebug>*/
toSQLParse::statement toSQLParse::parseStatement(tokenizer &tokens, bool declare, bool lst)
{
	statement ret(statement::Statement);

//	 toSyntaxAnalyzer &syntax = tokens.analyzer();

	QString first;
	QString realfirst;
	bool nokey = false;
	bool block = false;
	for (QString token = tokens.getToken(true, true);
			!token.isNull();
			token = tokens.getToken(true, true))
	{
		QString upp = token.toUpper();

		if (first.isNull() && !token.startsWith(("/*")) && !token.startsWith("--") && !token.startsWith("//"))
			realfirst = first = upp;

#ifdef TOPARSE_DEBUG
        printf("%s (%d)\n", (const char*)token.toUtf8(), tokens.line());
        printf("    %s - %s\n", (const char*)first.toUtf8(), (const char*)realfirst.toUtf8());
#endif

// SQLITEMAN
		 if (upp == ("PROCEDURE") ||
				 upp == ("FUNCTION") ||
				 upp == ("PACKAGE"))
         {
//              qDebug() << "PROCEDURE";
			 block = true;
         }

		 if (upp == ("SELF"))
         {
//              qDebug() << "SELF";
			 block = false;
         }

        if (upp == "BEGIN" && (first.isNull() || first == "BEGIN"))
        {
//             qDebug() << "plain BEGIN";
            ret.subTokens().insert(ret.subTokens().end(), statement(statement::Keyword, token, tokens.line()));
            nokey = false;            
        }
		else if (first != ("END") && ((first == ("IF") && upp == ("THEN")) ||
								  upp == ("LOOP") ||
								  upp == ("DO") ||
								  (/*syntax.declareBlock()*/true && upp == ("DECLARE")) ||
								  (block && upp == ("AS")) ||
								  (block && upp == ("IS")) ||
								  ((!declare || block) && upp == ("BEGIN"))))
		 {
//              qDebug() << "first != (\"END\") ";
			 block = false;
			 statement blk(statement::Block);
			 ret.subTokens().insert(ret.subTokens().end(), statement(statement::Keyword, token, tokens.line()));
			 blk.subTokens().insert(blk.subTokens().end(), ret);
			 statement cur(statement::Statement);
			 bool dcl = (upp == ("DECLARE") || upp == ("IS") || upp == ("AS"));
			 do
			 {
				 cur = parseStatement(tokens, dcl, false);
				 if (cur.Type == statement::List)
				 {
					 QMessageBox::warning(QApplication::activeWindow(), "Sqliteman",
										  "toSQLparse: Unbalanced parenthesis (Too many ')')");
				 }
				 blk.subTokens().insert(blk.subTokens().end(), cur);
				 if (cur.subTokens().begin() != cur.subTokens().end() &&
						 (*(cur.subTokens().begin())).String.toUpper() == ("BEGIN"))
					 dcl = false;
			 }
			 while (cur.subTokens().begin() != cur.subTokens().end() &&
					 (*cur.subTokens().begin()).String.toUpper() != ("END"));
			 return blk;
		 }
		 else if (((first == "IF" && upp == "THEN") ||
				   (first == "WHEN" && upp == "THEN") ||
				   (first == "ELSIF" && upp == "THEN") ||
				   upp == ("BEGIN") ||
				   upp == ("EXCEPTION") ||
				   first == ("ELSE")) && !lst)
		 {
//              qDebug() << "else if first==IF";
			 ret.subTokens().insert(ret.subTokens().end(), statement(statement::Keyword, token, tokens.line()));
			 return ret;
		 }
		 else if (first == ("ASSIGN") ||
				  first == ("SET") ||
				  first == ("PROMPT") ||
				  first == ("COLUMN") ||
				  first == ("SPOOL") ||
				  first == ("STORE") ||
				  first == ("REMARK") ||
				  first == ("REM"))
		 {
//              qDebug() << "ASSIGN";
			 ret.subTokens().insert(ret.subTokens().end(), statement(statement::Keyword, token, tokens.line()));
			 int line = tokens.line();
			 int offset = tokens.offset();
			 for (QString tmp = tokens.getToken(true, true);line == tokens.line();tmp = tokens.getToken(true, true))
				 ret.subTokens().insert(ret.subTokens().end(), statement(statement::Token, tmp, line));
			 tokens.setLine(line);
			 tokens.setOffset(offset);
			 tokens.remaining(true);
			 return ret;
		 }
		 else if (upp == (",") ||
// 		if (upp == (",") ||
//				  (syntax.reservedWord(upp) &&
				  (isKeyword(upp) &&
				  upp != ("NOT") &&
				  upp != ("IS") &&
				  upp != ("LIKE") &&
				  upp != ("IN") &&
				  upp != ("ELSE") &&
				  upp != ("ELSIF") &&
				  upp != ("END") &&
				  upp != ("BETWEEN") &&
				  upp != ("ASC") &&
				  upp != ("DESC") &&
				  upp != ("NULL")) && !nokey)
		{

		}
		else if (upp == ("("))
		{
//             qDebug() << "start (";
			ret.subTokens().insert(ret.subTokens().end(), statement(statement::Token, token, tokens.line()));
			statement lst = parseStatement(tokens, false, true);
			statement t = toPop(lst.subTokens());
			if (lst.Type != statement::List)
			{
				QMessageBox::warning(QApplication::activeWindow(), "Sqliteman",
									 "toSQLparse: Unbalanced parenthesis (Too many '(')");
			}
			nokey = false;
			if (first == ("CREATE") && !block)
			{
				statement end = parseStatement(tokens, false, true);
				statement blk(statement::Block);
				blk.subTokens().insert(blk.subTokens().end(), ret);
				blk.subTokens().insert(blk.subTokens().end(), lst);
				end.subTokens().insert(end.subTokens().begin(), t);
				blk.subTokens().insert(blk.subTokens().end(), end);
				return blk;
			}
			else
			{
				ret.subTokens().insert(ret.subTokens().end(), lst);
				ret.subTokens().insert(ret.subTokens().end(), t);
			}
		}
		else if (upp == (")"))
		{
//             qDebug() << "end )";
			ret.Type = statement::List;
			ret.subTokens().insert(ret.subTokens().end(), statement(statement::Token, token, tokens.line()));
			return ret;
		}
		else if (upp == (";"))
		{
//             qDebug() << "bodkociarka";
			ret.subTokens().insert(ret.subTokens().end(), statement(statement::Token, token, tokens.line()));
			return ret;
		}
		else if (upp.startsWith(("/*+")) || upp.startsWith(("--+")))
		{
//             qDebug() << "hint --+";
			QString com = token;
			if (com.startsWith(("--+")))
				com = ("/*+ ") + com.mid(3) + (" */");
			ret.subTokens().insert(ret.subTokens().end(), statement(statement::Token,
								   com.simplified(), tokens.line()));
		}
		else if (upp.startsWith(("/*")) || upp.startsWith(("--")) || upp.startsWith("//"))
		{
//             qDebug() << "comment";
			if ( ret.subTokens().empty() )
			{
				if (ret.Comment.isNull())
					ret.Comment = token;
				else
					ret.Comment += ("\n") + token;
			}
			else
			{
				QString &com = (*ret.subTokens().rbegin()).Comment;
				if (com.isEmpty())
					com = token;
				else
					com += ("\n") + token;
			}
		}
		else
		{
//             qDebug() << "plain else" <<token<< tokens.line();
			ret.subTokens().insert(ret.subTokens().end(), statement(statement::Token, token, tokens.line()));
			nokey = (token == ("."));
		}
		if (upp == ("AS") || upp == ("IS"))
        {
//             qDebug() << "setting first: " << upp;
			first = upp;
        }
		else if (first == ("IS") && upp == ("NULL"))
        {
//             qDebug() << "setting first (real): " << realfirst;
			first = realfirst;
        }
	}
	return ret;
}