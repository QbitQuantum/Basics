void __fastcall TCDirectoryOutline::WalkTree(const AnsiString& Dest)
{
    AnsiString Path = ForceCase(Dest);
    long Item = RootIndex;  // start at root


    // remove drive component of Path

    int Colon = Path.Pos(":");
    if (Colon > 0) {
        int Offset = (Path[Colon + 1] == '\\') ? 2 : 1;
        if ((Colon + Offset) >= Path.Length())
           Path = "";
        else
           Path = Path.SubString(Colon + Offset, Path.Length() - (Colon + Offset) +1);
    }

    // do the walk
    for (int SlashPos = GetPos(Path, "\\"); Path.Length() > 0;
            SlashPos = GetPos(Path, "\\")) {
        AnsiString Dir = Path;

        if (SlashPos > 0) {
            // splice out the first directory
            Dir = Path.SubString(1, SlashPos - 1);
            Path = Path.SubString(SlashPos + 1, Path.Length() - (SlashPos + 1) + 1);
        }
        else {
            Dir = Path;
            Path = "";
        }

        Item = GetChildNamed(Dir, Item);
    }

    SelectedItem = Item;
}