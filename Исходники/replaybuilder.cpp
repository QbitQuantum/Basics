// Format of saved replay file:
// | replay version
// | stage name length | stage name | stage width | stage height
// | num walls | <walls>
// | num zones | <zones>
// | num ships | <ship properties>
// | num ship adds | <ship adds>
// | num ship removes | <ship removes>
// | num ship show names | <show names>
// | num ship hide names | <hide names>
// | num ship show energys | <show energys>
// | num ship hide energys | <hide energys>
// | num ship ticks | <ship ticks>
// | num laser starts | <laser starts>
// | num laser ends | <laser ends>
// | num laser sparks | <laser sparks>
// | num torpedo starts | <torpedo starts>
// | num torpedo ends | <torpedo ends>
// | num torpedo blasts | <torpedo blasts>
// | num torpedo debris | <torpedo debris>
// | num ship destroys | <ship destroys>
// | num texts | <texts>
// | num log entries | <log entries>
// | num results | <results>
void ReplayBuilder::saveReplay(const char *dir, const char *filename) {
  // TODO: throw exceptions for failing to save replay, don't silently fail

  FileManager fileManager;
  char *replayTemplate = 0;
  char *templatePath = getResourcePath(REPLAY_TEMPLATE);
  if (templatePath != 0) {
    try {
      replayTemplate = fileManager.readFile(templatePath);
    } catch (FileNotFoundException *e) {
      delete e;
    }
    delete templatePath;
  }

  if (replayTemplate != 0) {
    copyReplayResource(KINETIC_JS, dir);
    copyReplayResource(BBREPLAY_JS, dir);

    std::string replayHtml(replayTemplate);
    std::string title = htmlTitle();
    size_t i;
    size_t len = strlen(REPLAY_TITLE_PLACEHOLDER);
    i = replayHtml.find(REPLAY_TITLE_PLACEHOLDER, 0);
    if (i != std::string::npos) {
      replayHtml.replace(i, len, htmlTitle());
    }

    len = strlen(REPLAY_DATA_PLACEHOLDER);
    i = replayHtml.find(REPLAY_DATA_PLACEHOLDER, 0);
    if (i != std::string::npos) {
      replayHtml.replace(i, len, buildReplayDataString());
    }

    len = strlen(EXTRA_JS_PLACEHOLDER);
    i = replayHtml.find(EXTRA_JS_PLACEHOLDER, 0);
    if (i != std::string::npos) {
      replayHtml.replace(i, len, extraJavascript_ == 0 ? "" : extraJavascript_);
    }

    char *filePath = fileManager.getFilePath(dir, filename);
    char *absFilename = fileManager.getAbsFilePath(filePath);
    delete filePath;
    fileManager.writeFile(absFilename, replayHtml.c_str());
    delete absFilename;
    delete replayTemplate;
  }
}