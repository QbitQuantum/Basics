CubeMap * SceneParser::parseCubeMap()
{
	char token[MAX_PARSER_TOKEN_LENGTH];
	getToken(token);
	return new CubeMap(token);
}