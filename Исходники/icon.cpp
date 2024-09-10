/* called by GUI */
Icon::Icon(User *user, void *d)
{
  char *infos = (char *) d;
  ifile = NULL;
  ofile = NULL;
  char *action = NULL;
  vref = NULL;
  char icon[URL_LEN];
  *icon = 0;

  /* parameters transmission */
  for (char *pt = strtok(infos, "&"); pt ; pt = strtok(NULL, "&")) {
    if (! stringcmp(pt, "<url=")) { pt = getParam(pt); strcpy(names.url, pt); taken = true; }
    else if (! stringcmp(pt, "<file=")) { pt = getParam(pt); ifile = strdup(pt); }
    else if (! stringcmp(pt, "<ofile=")) { pt = getParam(pt); strcpy(names.url, pt); }
    else if (! stringcmp(pt, "<name=")) { pt = getParam(pt); strcpy(names.named, pt); }
    else if (! stringcmp(pt, "<icon=")) { pt = getParam(pt); strcpy(icon, pt); }
    else if (! stringcmp(pt, "<action=")) { pt = getParam(pt); action = strdup(pt); }
    else if (! stringcmp(pt, "<vref=")) {
      pt = strchr(pt, '=');
      pt++;
      char *p2;
      if ((p2 = strchr(pt, '>'))) *p2 = 0;
      vref = strdup(pt);
    }
  }

  if (vref) {	// local saved document exists
    parser(vref);

    // get the last loaded texture
    int texid = Texture::getIdByUrl(names.url);
    Texture *tclast = Texture::getEntryById(texid);
    if (! tclast) {
      tex = new char[sizeof(ICO_DEF) + 1];
      strcpy(tex, ICO_DEF);	// default texture
    }
    else {
      tex = new char[strlen(tclast->url) + 1];
      strcpy(tex, tclast->url);
    }
    taken = false;
  }

  else {	// new document named interactively by hand
    /* position */
    float off = 0.4;
    pos.x = user->pos.x + off * Cos(user->pos.az);
    pos.y = user->pos.y + off * Sin(user->pos.az);
    pos.z = user->pos.z + 0.6;        // visible by eyes
    pos.az = user->pos.az + M_PI_2;

    /* texture */
    if (*icon) {
      tex = new char[strlen(icon) + 1];
      strcpy(tex, icon);
    }
    else {
      // default binding icon to document
      char ext[8] = "";
      memset(ext, 0, sizeof(ext));
      if (Format::getExt(names.url, ext)) {
        tex = new char[URL_LEN];
        Format::getImgByExt(ext, tex);
      }
      else {
        tex = new char[sizeof(ICO_DEF) + 1];
        strcpy(tex, ICO_DEF);
      }
    }

    if (ifile) {	// private local document
      if (*names.url) {
        // public url given by user
        Cache::download(ifile, ofile, "inout");
      }
      else {
        // build local ofile in ~/public_html/vreng/
        ofile = new char[URL_LEN];
        sprintf(ofile, "%s/public_html", getenv("HOME"));
        if (access(ofile, R_OK|W_OK|X_OK) == 0) {
          strcat(ofile, "/vreng/");
          if (access(ofile, R_OK|W_OK|X_OK) == -1)
            mkdir(ofile, 0755);
          strcat(ofile, ifile);
          FILE *fin, *fout;
          if ((fin = File::openFile(ifile, "r")) && (fout = File::openFile(ofile, "w"))) {
            char buf[2];
            while (fread(buf, 1, 1, fin))
              fwrite(buf, 1, 1, fout);
            File::closeFile(fin);
            File::closeFile(fout);
            chmod(ofile, 0644);

            //FIXME: define local http_server
            sprintf(names.url, "http://%s/~%s/vreng/%s", DEF_HTTP_SERVER, getenv("USER"), ifile);
          }
          else {
            error("can't open %s or %s: %s (%d)", ifile, ofile, strerror(errno), errno);
            free(ifile); ifile = NULL;
            delete[] ofile;
          }
        }
        else {
          error("can't access %s", ofile);
          free(ifile); ifile = NULL;
          delete[] ofile;
        }
      }
    }
    makeSolid();
  }

  // local creation
  defaults();

  enableBehavior(REMOVABLE);
  enableBehavior(NO_ELEMENTARY_MOVE);
  setRenderPrior(RENDER_HIGH);

  initializeMobileObject(1);
  ttl = (taken) ? MAXFLOAT : 0;
  initImposedMovement(ttl);
  disablePermanentMovement();

  // network creation
  createVolatileNetObject(PROPS);

  // document's owner
  setOwner();

  trace(DBG_WO, "Icon: url=%s icon=%s name=%s owner=%s", urlName(), tex, getInstance(), ownerName());

  if (action) {
    if      (! stringcmp(action, "pin")) pin(this, NULL, 0L, 0L);
    else if (! stringcmp(action, "push")) push(this, NULL, 0L, 0L);
    else if (! stringcmp(action, "carry")) carry(this, NULL, 0L, 0L);
  }
}