bool
Win32MakefileGenerator::findLibraries(const QString &where)
{
    QStringList &l = project->values(where);
    QList<QMakeLocalFileName> dirs;
    {
        QStringList &libpaths = project->values("QMAKE_LIBDIR");
        for(QStringList::Iterator libpathit = libpaths.begin();
            libpathit != libpaths.end(); ++libpathit)
            dirs.append(QMakeLocalFileName((*libpathit)));
    }
    for(QStringList::Iterator it = l.begin(); it != l.end();) {
        QChar quote;
        bool modified_opt = false, remove = false;
        QString opt = (*it).trimmed();
        if((opt[0] == '\'' || opt[0] == '"') && opt[(int)opt.length()-1] == opt[0]) {
            quote = opt[0];
            opt = opt.mid(1, opt.length()-2);
        }
        if(opt.startsWith("/LIBPATH:")) {
            dirs.append(QMakeLocalFileName(opt.mid(9)));
        } else if(opt.startsWith("-L") || opt.startsWith("/L")) {
            QString libpath = opt.mid(2);
            QMakeLocalFileName l(libpath);
            if(!dirs.contains(l)) {
                dirs.append(l);
                modified_opt = true;
                if (!quote.isNull()) {
                    libpath = quote + libpath + quote;
                    quote = QChar();
                }
                (*it) = "/LIBPATH:" + libpath;
            } else {
                remove = true;
            }
        } else if(opt.startsWith("-l") || opt.startsWith("/l")) {
            QString lib = opt.right(opt.length() - 2), out;
            if(!lib.isEmpty()) {
                QString suffix;
                if(!project->isEmpty("QMAKE_" + lib.toUpper() + "_SUFFIX"))
                    suffix = project->first("QMAKE_" + lib.toUpper() + "_SUFFIX");
                for(QList<QMakeLocalFileName>::Iterator it = dirs.begin();
                    it != dirs.end(); ++it) {
                    QString extension;
                    int ver = findHighestVersion((*it).local(), lib);
                    if(ver > 0)
                        extension += QString::number(ver);
                    extension += suffix;
                    extension += ".lib";
                    if(QMakeMetaInfo::libExists((*it).local() + Option::dir_sep + lib) ||
                       exists((*it).local() + Option::dir_sep + lib + extension)) {
                        out = (*it).real() + Option::dir_sep + lib + extension;
                        break;
                    }
                }
            }
            if(out.isEmpty())
                out = lib + ".lib";
            modified_opt = true;
            (*it) = out;
        } else if(!exists(Option::fixPathToLocalOS(opt))) {
            QList<QMakeLocalFileName> lib_dirs;
            QString file = opt;
            int slsh = file.lastIndexOf(Option::dir_sep);
            if(slsh != -1) {
                lib_dirs.append(QMakeLocalFileName(file.left(slsh+1)));
                file = file.right(file.length() - slsh - 1);
            } else {
                lib_dirs = dirs;
            }
            if(file.endsWith(".lib")) {
                file = file.left(file.length() - 4);
                if(!file.at(file.length()-1).isNumber()) {
                    QString suffix;
                    if(!project->isEmpty("QMAKE_" + file.section(Option::dir_sep, -1).toUpper() + "_SUFFIX"))
                        suffix = project->first("QMAKE_" + file.section(Option::dir_sep, -1).toUpper() + "_SUFFIX");
                    for(QList<QMakeLocalFileName>::Iterator dep_it = lib_dirs.begin(); dep_it != lib_dirs.end(); ++dep_it) {
                        QString lib_tmpl(file + "%1" + suffix + ".lib");
                        int ver = findHighestVersion((*dep_it).local(), file);
                        if(ver != -1) {
                            if(ver)
                                lib_tmpl = lib_tmpl.arg(ver);
                            else
                                lib_tmpl = lib_tmpl.arg("");
                            if(slsh != -1) {
                                QString dir = (*dep_it).real();
                                if(!dir.endsWith(Option::dir_sep))
                                    dir += Option::dir_sep;
                                lib_tmpl.prepend(dir);
                            }
                            modified_opt = true;
                            (*it) = lib_tmpl;
                            break;
                        }
                    }
                }
            }
        }
        if(remove) {
            it = l.erase(it);
        } else {
            if(!quote.isNull() && modified_opt)
                (*it) = quote + (*it) + quote;
            ++it;
        }
    }
    return true;
}