void Highscores::saveToFile(const vector<Score>& scores, const FilePath& path) {
  CompressedOutput out(path.getPath());
  out.getArchive() << scores;
}