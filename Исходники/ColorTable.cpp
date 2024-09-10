// saveTable
//---------------------------------------------------------------------------
void ColorTable::saveTable(const char *filename) const
{
    WriteFile *file = FileSystem::openWrite(filename);

    if (file->write(&Palette::color, 768, 1) != 1
            || file->write(colorArray, colorCount, 1) != 1) {
        throw Exception("error while writing to file '%s' (disk full?)",
                        filename);
    }

    delete file;
} // end ColorTable::saveTable