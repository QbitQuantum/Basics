bool StopSEExpression::interpret(
	Context& context,
	SceneManager* smgr,
	AdventureScene* scene) {

	if (context.isEnd()) { return false; }

    // リソースファイルへのkeyを取得
	m_key = context.getToken();

	return setAdventureTask(smgr, scene);
}