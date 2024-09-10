//test read
TEST_F(SqliteWrapTest, InsertData) {

	CreateTable();

	m_sqliteDriver->execute("insert into MyTable(name) values('aaa')");

	Statement stmt(*m_sqliteDriver, "select * from MyTable");

	if (stmt.executeStep())
	{
		ASSERT_STREQ(stmt.getColumn(1).getText(), "aaa");
	}

	TrunkTable();
}