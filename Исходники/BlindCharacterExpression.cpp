bool BlindCharacterExpression::interpret(
	Context& context,
	SceneManager* smgr,
	AdventureScene* scene) {

	if (context.isEnd()) { return false; }

    // キーの取得
	m_key = context.getToken();
	context.next();
	m_position = context.getToken();
	context.next();

    // オプションの取得
	m_option = context.getToken();

	return setAdventureTask(smgr, scene);
}