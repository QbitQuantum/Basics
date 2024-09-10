String GetString(PasteClip& clip)
{
	GuiLock __;
	if(clip.Accept("wtext")) {
		String s = ~clip;
		return WString((const wchar *)~s, wstrlen((const wchar *)~s)).ToString();
	}
	if(clip.IsAvailable("text"))
		return ~clip;
	return Null;
}