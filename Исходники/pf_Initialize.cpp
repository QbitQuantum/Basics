//HeadFile作成
int Initialize_stdin()
{
  // -i "filepath" -pipe が同時に指定されていた。
  if (NumLoadedFiles != 1)
    return 1;

  //HeadFile
  //  標準入力の先頭部をファイルに書き出す。
  //  ファイルにすることでseekに対応
  _setmode(_fileno(stdin), _O_BINARY);
  fdStdin = _fileno(stdin);

  //WindowsのTempフォルダにDGI_temp_0000000_2を作成
  {
    DWORD pid = GetCurrentProcessId();
    std::random_device rnd;
    std::mt19937 mt(rnd());
    UINT32 rnd_num = mt() % (1000 * 1000);
    std::string tmp_path;
    tmp_path = "DGI_temp_" + std::to_string(pid) + std::to_string(rnd_num) + "_";
    tmp_path = std::string(_tempnam(NULL, tmp_path.c_str()));
    HeadFilePath = tmp_path;
  }
  fdHeadFile = _open(HeadFilePath.c_str(), _O_CREAT | _O_RDWR | _O_BINARY, _S_IREAD | _S_IWRITE);
  if (fdHeadFile == -1)
    return 1;
  int head_size;
  {
    const double mini_MB = 6.0;
    double size = HeadFileSize_CmdLine;
    size = mini_MB < size ? size : mini_MB;
    head_size = (int)(size * 1024 * 1024);
  }


  //標準入力からデータ取得、HeadFile書込
  const int buff_size = 1024 * 32;
  std::vector<BYTE> buff(buff_size);
  int cur_size = 0;                  //HeadFileに書込済サイズ

  while (cur_size < head_size)
  {
    int read = _read(fdStdin, &buff.front(), buff_size);
    if (read == -1)
    {
      Sleep(30);
      continue;//fail to connect. wait.
    }
    else if (read == 0)
      break;//end of stream.

    int written = _write(fdHeadFile, &buff.front(), read);
    if (written != read)
      return 1;
    cur_size += written;
  }
  if (head_size <= cur_size)
    head_size = cur_size;
  else
    return 1;//fail to read. too short stream.


  //Infileにセット
  strcpy(Infilename[0], HeadFilePath.c_str());
  Infile[0] = fdHeadFile;
  _lseeki64(Infile[0], 0, SEEK_SET);

  return 0;
}