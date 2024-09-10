void MBConnection::createPreparedStatements()
{
  this->_insPlayerRowStatement = mysql_stmt_init(this->_conn);
  this->_insWordRowStatement = mysql_stmt_init(this->_conn);
  this->_insConvRowStatement = mysql_stmt_init(this->_conn);
  this->_getRandomStartingWordStatement = mysql_stmt_init(this->_conn);
  this->_getRandomNextWordStatement = mysql_stmt_init(this->_conn);
  this->_getProperCaseStatement = mysql_stmt_init(this->_conn);
  this->_getBigramCountStatement = mysql_stmt_init(this->_conn);  
  this->_getPlayerLineCountStatement = mysql_stmt_init(this->_conn);
  this->_getPlayerNameStatement = mysql_stmt_init(this->_conn);
  this->_insTextRowStatement = mysql_stmt_init(this->_conn);
  this->_getRandomChatMessageStatement = mysql_stmt_init(this->_conn);

  if (!this->_insPlayerRowStatement || 
    !this->_insWordRowStatement || 
    !this->_insConvRowStatement ||
    !this->_getRandomStartingWordStatement ||
    !this->_getRandomNextWordStatement ||
    !this->_getProperCaseStatement ||
    !this->_getBigramCountStatement ||
    !this->_getPlayerLineCountStatement ||
    !this->_getPlayerNameStatement ||
    !this->_insTextRowStatement ||
    !this->_getRandomChatMessageStatement)
  {
    std::cout << "Initializating prepared statements failed" << std::endl;
    throw 0;
  }

  static const std::string INSERT_PLAYER_ROW_SQL("INSERT INTO markovsbot.player_names (id,name) VALUES (?,?)");
  static const std::string INSERT_WORD_ROW_SQL("INSERT INTO markovsbot.words (id,word) VALUES (?,?)");
  static const std::string INSERT_CONV_ROW_SQL("INSERT INTO markovsbot.conversations (name_id, word_a, word_b, is_starting) VALUES (?,?,?,?)");

  static const std::string GET_RANDOM_STARTING_WORD_SQL("SELECT markovsbot.words.id, markovsbot.words.word FROM ("
    "(SELECT markovsbot.conversations.word_a FROM markovsbot.player_names INNER JOIN markovsbot.conversations "
      "ON markovsbot.player_names.id=markovsbot.conversations.name_id "
      "WHERE markovsbot.player_names.name=? AND markovsbot.conversations.is_starting=1) "
    "AS t1) "
    "INNER JOIN markovsbot.words ON markovsbot.words.id=t1.word_a ORDER BY RAND() LIMIT 1");

  static const std::string GET_RANDOM_NEXT_WORD_SQL("SELECT markovsbot.words.id, markovsbot.words.word FROM ("
    "(SELECT markovsbot.conversations.word_b FROM markovsbot.player_names INNER JOIN markovsbot.conversations "
      "ON markovsbot.player_names.id=markovsbot.conversations.name_id "
      "WHERE markovsbot.player_names.name=? AND markovsbot.conversations.word_a=?) "
    "AS t1) "
    "INNER JOIN markovsbot.words ON markovsbot.words.id=t1.word_b ORDER BY RAND() LIMIT 1");

  static const std::string GET_PROPER_CASE_SQL("SELECT markovsbot.player_names.name FROM markovsbot.player_names WHERE name=? LIMIT 1");
  static const std::string GET_BIGRAM_COUNT_SQL("SELECT name_id, COUNT(*) AS c FROM ("
      "SELECT * FROM markovsbot.words WHERE word=?"
    ") AS t1, ("
      "SELECT * FROM markovsbot.words WHERE word=?"
    ") AS t2 INNER JOIN markovsbot.conversations WHERE markovsbot.conversations.word_a=t1.id AND "
    "markovsbot.conversations.word_b=t2.id GROUP BY markovsbot.conversations.name_id ORDER BY c DESC LIMIT 20");
  static const std::string GET_PLAYER_LINE_COUNT_SQL("SELECT COUNT(*) FROM markovsbot.conversations WHERE name_id=? GROUP BY name_id");
  static const std::string GET_PLAYER_NAME_SQL("SELECT name FROM markovsbot.player_names WHERE id=?");
  static const std::string INSERT_TEXT_SQL("INSERT INTO markovsbot.fulltext_log (name, `text`) VALUES (?, ?)");
  static const std::string GET_RANDOM_CHAT_MESSAGE_SQL("SELECT `name`,`text` FROM markovsbot.fulltext_log WHERE MATCH(`text`) AGAINST (CONCAT('\"', ?, '\"') IN BOOLEAN MODE) ORDER BY RAND() DESC LIMIT 1");

  int r1 = mysql_stmt_prepare(this->_insPlayerRowStatement, INSERT_PLAYER_ROW_SQL.c_str(), INSERT_PLAYER_ROW_SQL.length());
  int r2 = mysql_stmt_prepare(this->_insWordRowStatement, INSERT_WORD_ROW_SQL.c_str(), INSERT_WORD_ROW_SQL.length());
  int r3 = mysql_stmt_prepare(this->_insConvRowStatement, INSERT_CONV_ROW_SQL.c_str(), INSERT_CONV_ROW_SQL.length());

  int r4 = mysql_stmt_prepare(this->_getRandomStartingWordStatement, GET_RANDOM_STARTING_WORD_SQL.c_str(), GET_RANDOM_STARTING_WORD_SQL.length());
  int r5 = mysql_stmt_prepare(this->_getRandomNextWordStatement, GET_RANDOM_NEXT_WORD_SQL.c_str(), GET_RANDOM_NEXT_WORD_SQL.length());

  int r6 = mysql_stmt_prepare(this->_getProperCaseStatement, GET_PROPER_CASE_SQL.c_str(), GET_PROPER_CASE_SQL.length());
  int r7 = mysql_stmt_prepare(this->_getBigramCountStatement, GET_BIGRAM_COUNT_SQL.c_str(), GET_BIGRAM_COUNT_SQL.length());
  int r8 = mysql_stmt_prepare(this->_getPlayerLineCountStatement, GET_PLAYER_LINE_COUNT_SQL.c_str(), GET_PLAYER_LINE_COUNT_SQL.length());
  int r9 = mysql_stmt_prepare(this->_getPlayerNameStatement, GET_PLAYER_NAME_SQL.c_str(), GET_PLAYER_NAME_SQL.length());

  int r10 = mysql_stmt_prepare(this->_insTextRowStatement, INSERT_TEXT_SQL.c_str(), INSERT_TEXT_SQL.length());
  int r11 = mysql_stmt_prepare(this->_getRandomChatMessageStatement, GET_RANDOM_CHAT_MESSAGE_SQL.c_str(), GET_RANDOM_CHAT_MESSAGE_SQL.length());

  if (r1 || r2 || r3 || r4 || r5 || r6 || r7 || r8 || r9 || r10 || r11)
  {
    std::cout << "Creating prepared statements failed" << std::endl;
    throw 0;
  }
}