bool PlayBGMExpression::interpret(
	Context& context,
	SceneManager* smgr,
	AdventureScene* scene) {

	if (context.isEnd()) { return false; }

    // リソースファイルへのkeyを取得
	m_key = context.getToken();

    // ボリュームを取得
	context.next();
    // todo: error処理
	m_volume = std::stoi(context.getToken());

	context.next();
	m_option = context.getToken();

	return setAdventureTask(smgr, scene);
}