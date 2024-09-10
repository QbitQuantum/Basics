///<summary>
///保存先のファイルパスを生成（OpenCV用としてマルチバイトキャラ専用）
///</summary>
void CImageProcessor::GetNewFilePath(LPSTR lpSrc, LPSTR lpFile, LPSTR lpDest)
{
	LPCSTR lpFileName = PathFindFileNameA(lpSrc);
	wsprintfA(lpDest, "%s.%s", lpFileName, lpFile);
}