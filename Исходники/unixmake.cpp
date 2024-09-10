QT_BEGIN_NAMESPACE

void
UnixMakefileGenerator::init()
{
    ProStringList &configs = project->values("CONFIG");
    if(project->isEmpty("ICON") && !project->isEmpty("RC_FILE"))
        project->values("ICON") = project->values("RC_FILE");
    if(project->isEmpty("QMAKE_EXTENSION_PLUGIN"))
        project->values("QMAKE_EXTENSION_PLUGIN").append(project->first("QMAKE_EXTENSION_SHLIB"));

    project->values("QMAKE_ORIG_TARGET") = project->values("TARGET");

    //version handling
    if (project->isEmpty("VERSION")) {
        project->values("VERSION").append(
            "1.0." + (project->isEmpty("VER_PAT") ? QString("0") : project->first("VER_PAT")));
    }
    QStringList l = project->first("VERSION").toQString().split('.');
    l << "0" << "0"; //make sure there are three
    project->values("VER_MAJ").append(l[0]);
    project->values("VER_MIN").append(l[1]);
    project->values("VER_PAT").append(l[2]);

    QString sroot = project->sourceRoot();
    foreach (const ProString &iif, project->values("QMAKE_INTERNAL_INCLUDED_FILES")) {
        if (iif == project->cacheFile())
            continue;
        if (iif.startsWith(sroot) && iif.at(sroot.length()) == QLatin1Char('/'))
            project->values("DISTFILES") += fileFixify(iif.toQString(), FileFixifyRelative);
    }

    /* this should probably not be here, but I'm using it to wrap the .t files */
    if(project->first("TEMPLATE") == "app")
        project->values("QMAKE_APP_FLAG").append("1");
    else if(project->first("TEMPLATE") == "lib")
        project->values("QMAKE_LIB_FLAG").append("1");
    else if(project->first("TEMPLATE") == "subdirs") {
        MakefileGenerator::init();
        if(project->isEmpty("MAKEFILE"))
            project->values("MAKEFILE").append("Makefile");
        return; /* subdirs is done */
    }

    project->values("QMAKE_ORIG_DESTDIR") = project->values("DESTDIR");
    project->values("QMAKE_LIBS") += project->values("LIBS");
    project->values("QMAKE_LIBS_PRIVATE") += project->values("LIBS_PRIVATE");
    if((!project->isEmpty("QMAKE_LIB_FLAG") && !project->isActiveConfig("staticlib")) ||
       (project->isActiveConfig("qt") &&  project->isActiveConfig("plugin"))) {
        if(configs.indexOf("dll") == -1) configs.append("dll");
    } else if(!project->isEmpty("QMAKE_APP_FLAG") || project->isActiveConfig("dll")) {
        configs.removeAll("staticlib");
    }
    if(!project->isEmpty("QMAKE_INCREMENTAL"))
        project->values("QMAKE_LFLAGS") += project->values("QMAKE_LFLAGS_INCREMENTAL");
    else if(!project->isEmpty("QMAKE_LFLAGS_PREBIND") &&
            !project->values("QMAKE_LIB_FLAG").isEmpty() &&
            project->isActiveConfig("dll"))
        project->values("QMAKE_LFLAGS") += project->values("QMAKE_LFLAGS_PREBIND");
    if(!project->isEmpty("QMAKE_INCDIR"))
        project->values("INCLUDEPATH") += project->values("QMAKE_INCDIR");
    ProStringList ldadd;
    if(!project->isEmpty("QMAKE_LIBDIR")) {
        const ProStringList &libdirs = project->values("QMAKE_LIBDIR");
        for(int i = 0; i < libdirs.size(); ++i) {
            if(!project->isEmpty("QMAKE_LFLAGS_RPATH") && project->isActiveConfig("rpath_libdirs"))
                project->values("QMAKE_LFLAGS") += var("QMAKE_LFLAGS_RPATH") + libdirs[i];
            project->values("QMAKE_LIBDIR_FLAGS") += "-L" + escapeFilePath(libdirs[i]);
        }
    }
    ldadd += project->values("QMAKE_LIBDIR_FLAGS");
    if (project->isActiveConfig("mac")) {
        if (!project->isEmpty("QMAKE_FRAMEWORKPATH")) {
            const ProStringList &fwdirs = project->values("QMAKE_FRAMEWORKPATH");
            for (int i = 0; i < fwdirs.size(); ++i)
                project->values("QMAKE_FRAMEWORKPATH_FLAGS") += "-F" + escapeFilePath(fwdirs[i]);
        }
        ldadd += project->values("QMAKE_FRAMEWORKPATH_FLAGS");
    }
    ProStringList &qmklibs = project->values("QMAKE_LIBS");
    qmklibs = ldadd + qmklibs;
    if (!project->isEmpty("QMAKE_RPATHDIR") && !project->isEmpty("QMAKE_LFLAGS_RPATH")) {
        const ProStringList &rpathdirs = project->values("QMAKE_RPATHDIR");
        for (int i = 0; i < rpathdirs.size(); ++i) {
            QString rpathdir = rpathdirs[i].toQString();
            if (rpathdir.length() > 1 && rpathdir.at(0) == '$' && rpathdir.at(1) != '(') {
                rpathdir.replace(0, 1, "\\$$");  // Escape from make and the shell
            } else if (!rpathdir.startsWith('@') && fileInfo(rpathdir).isRelative()) {
                QString rpathbase = project->first("QMAKE_REL_RPATH_BASE").toQString();
                if (rpathbase.isEmpty()) {
                    fprintf(stderr, "Error: This platform does not support relative paths in QMAKE_RPATHDIR (%s)\n",
                                    rpathdir.toLatin1().constData());
                    continue;
                }
                if (rpathbase.startsWith('$'))
                    rpathbase.replace(0, 1, "\\$$");  // Escape from make and the shell
                if (rpathdir == ".")
                    rpathdir = rpathbase;
                else
                    rpathdir.prepend(rpathbase + '/');
                project->values("QMAKE_LFLAGS").insertUnique(project->values("QMAKE_LFLAGS_REL_RPATH"));
            }
            project->values("QMAKE_LFLAGS") += var("QMAKE_LFLAGS_RPATH") + escapeFilePath(rpathdir);
        }
    }
    if (!project->isEmpty("QMAKE_RPATHLINKDIR")) {
        const ProStringList &rpathdirs = project->values("QMAKE_RPATHLINKDIR");
        for (int i = 0; i < rpathdirs.size(); ++i) {
            if (!project->isEmpty("QMAKE_LFLAGS_RPATHLINK"))
                project->values("QMAKE_LFLAGS") += var("QMAKE_LFLAGS_RPATHLINK") + escapeFilePath(QFileInfo(rpathdirs[i].toQString()).absoluteFilePath());
        }
    }

    if(project->isActiveConfig("GNUmake") && !project->isEmpty("QMAKE_CFLAGS_DEPS"))
        include_deps = true; //do not generate deps

    MakefileGenerator::init();

    if (project->isActiveConfig("objective_c"))
        project->values("QMAKE_BUILTIN_COMPILERS") << "OBJC" << "OBJCXX";

    foreach (const ProString &compiler, project->values("QMAKE_BUILTIN_COMPILERS")) {
        QString compile_flag = var("QMAKE_COMPILE_FLAG");
        if(compile_flag.isEmpty())
            compile_flag = "-c";

        if(doPrecompiledHeaders() && !project->isEmpty("PRECOMPILED_HEADER")) {
            QString pchFlags = var(ProKey("QMAKE_" + compiler + "FLAGS_USE_PRECOMPILE"));

            QString pchBaseName;
            if(!project->isEmpty("PRECOMPILED_DIR")) {
                pchBaseName = Option::fixPathToTargetOS(project->first("PRECOMPILED_DIR").toQString());
                if(!pchBaseName.endsWith(Option::dir_sep))
                    pchBaseName += Option::dir_sep;
            }
            pchBaseName += project->first("QMAKE_ORIG_TARGET").toQString();

            // replace place holders
            pchFlags.replace(QLatin1String("${QMAKE_PCH_INPUT}"),
                             escapeFilePath(project->first("PRECOMPILED_HEADER").toQString()));
            pchFlags.replace(QLatin1String("${QMAKE_PCH_OUTPUT_BASE}"), escapeFilePath(pchBaseName));
            if (project->isActiveConfig("icc_pch_style")) {
                // icc style
                pchFlags.replace(QLatin1String("${QMAKE_PCH_OUTPUT}"),
                                 escapeFilePath(pchBaseName + project->first("QMAKE_PCH_OUTPUT_EXT")));
            } else {
                // gcc style (including clang_pch_style)
                QString headerSuffix;
                if (project->isActiveConfig("clang_pch_style"))
                    headerSuffix = project->first("QMAKE_PCH_OUTPUT_EXT").toQString();
                else
                    pchBaseName += project->first("QMAKE_PCH_OUTPUT_EXT").toQString();

                pchBaseName += Option::dir_sep;

                ProString language = project->first(ProKey("QMAKE_LANGUAGE_" + compiler));
                if (!language.isEmpty()) {
                    pchFlags.replace(QLatin1String("${QMAKE_PCH_OUTPUT}"),
                                     escapeFilePath(pchBaseName + language + headerSuffix));
                }
            }

            if (!pchFlags.isEmpty())
                compile_flag += " " + pchFlags;
        }

        QString compilerExecutable;
        if (compiler == "C" || compiler == "OBJC") {
            compilerExecutable = "$(CC)";
            compile_flag += " $(CFLAGS)";
        } else {
            compilerExecutable = "$(CXX)";
            compile_flag += " $(CXXFLAGS)";
        }

        compile_flag += " $(INCPATH)";

        ProString compilerVariable = compiler;
        if (compilerVariable == "C")
            compilerVariable = ProString("CC");

        const ProKey runComp("QMAKE_RUN_" + compilerVariable);
        if(project->isEmpty(runComp))
            project->values(runComp).append(compilerExecutable + " " + compile_flag + " " + var("QMAKE_CC_O_FLAG") + "$obj $src");
        const ProKey runCompImp("QMAKE_RUN_" + compilerVariable + "_IMP");
        if(project->isEmpty(runCompImp))
            project->values(runCompImp).append(compilerExecutable + " " + compile_flag + " " + var("QMAKE_CC_O_FLAG") + "\"$@\" \"$<\"");
    }

    if (project->isActiveConfig("mac") && !project->isEmpty("TARGET") &&
       ((project->isActiveConfig("build_pass") || project->isEmpty("BUILDS")))) {
        ProString bundle;
        if(project->isActiveConfig("bundle") && !project->isEmpty("QMAKE_BUNDLE_EXTENSION")) {
            bundle = project->first("TARGET");
            if(!project->isEmpty("QMAKE_BUNDLE_NAME"))
                bundle = project->first("QMAKE_BUNDLE_NAME");
            if(!bundle.endsWith(project->first("QMAKE_BUNDLE_EXTENSION")))
                bundle += project->first("QMAKE_BUNDLE_EXTENSION");
        } else if(project->first("TEMPLATE") == "app" && project->isActiveConfig("app_bundle")) {
            bundle = project->first("TARGET");
            if(!project->isEmpty("QMAKE_APPLICATION_BUNDLE_NAME"))
                bundle = project->first("QMAKE_APPLICATION_BUNDLE_NAME");
            if(!bundle.endsWith(".app"))
                bundle += ".app";
            if(project->isEmpty("QMAKE_BUNDLE_LOCATION"))
                project->values("QMAKE_BUNDLE_LOCATION").append("Contents/MacOS");
            project->values("QMAKE_PKGINFO").append(project->first("DESTDIR") + bundle + "/Contents/PkgInfo");
            project->values("QMAKE_BUNDLE_RESOURCE_FILE").append(project->first("DESTDIR") + bundle + "/Contents/Resources/empty.lproj");
        } else if(project->first("TEMPLATE") == "lib" && !project->isActiveConfig("staticlib") &&
                  ((!project->isActiveConfig("plugin") && project->isActiveConfig("lib_bundle")) ||
                   (project->isActiveConfig("plugin") && project->isActiveConfig("plugin_bundle")))) {
            bundle = project->first("TARGET");
            if(project->isActiveConfig("plugin")) {
                if(!project->isEmpty("QMAKE_PLUGIN_BUNDLE_NAME"))
                    bundle = project->first("QMAKE_PLUGIN_BUNDLE_NAME");
                if (project->isEmpty("QMAKE_BUNDLE_EXTENSION"))
                    project->values("QMAKE_BUNDLE_EXTENSION").append(".plugin");
                if (!bundle.endsWith(project->first("QMAKE_BUNDLE_EXTENSION")))
                    bundle += project->first("QMAKE_BUNDLE_EXTENSION");
                if(project->isEmpty("QMAKE_BUNDLE_LOCATION"))
                    project->values("QMAKE_BUNDLE_LOCATION").append("Contents/MacOS");
            } else {
                if(!project->isEmpty("QMAKE_FRAMEWORK_BUNDLE_NAME"))
                    bundle = project->first("QMAKE_FRAMEWORK_BUNDLE_NAME");
                if (project->isEmpty("QMAKE_BUNDLE_EXTENSION"))
                    project->values("QMAKE_BUNDLE_EXTENSION").append(".framework");
                if (!bundle.endsWith(project->first("QMAKE_BUNDLE_EXTENSION")))
                    bundle += project->first("QMAKE_BUNDLE_EXTENSION");
            }
        }
        if(!bundle.isEmpty()) {
            project->values("QMAKE_BUNDLE") = ProStringList(bundle);
        } else {
            project->values("QMAKE_BUNDLE").clear();
            project->values("QMAKE_BUNDLE_LOCATION").clear();
        }
    } else { //no bundling here
        project->values("QMAKE_BUNDLE").clear();
        project->values("QMAKE_BUNDLE_LOCATION").clear();
    }

    init2();
    project->values("QMAKE_INTERNAL_PRL_LIBS") << "QMAKE_LIBS";
    ProString target = project->first("TARGET");
    int slsh = target.lastIndexOf(Option::dir_sep);
    if (slsh != -1)
        target.chopFront(slsh + 1);
    project->values("LIB_TARGET").prepend(target);
    if(!project->isEmpty("QMAKE_MAX_FILES_PER_AR")) {
        bool ok;
        int max_files = project->first("QMAKE_MAX_FILES_PER_AR").toInt(&ok);
        ProStringList ar_sublibs, objs = project->values("OBJECTS");
        if(ok && max_files > 5 && max_files < (int)objs.count()) {
            QString lib;
            for(int i = 0, obj_cnt = 0, lib_cnt = 0; i != objs.size(); ++i) {
                if((++obj_cnt) >= max_files) {
                    if(lib_cnt) {
                        lib.sprintf("lib%s-tmp%d.a",
                                    project->first("QMAKE_ORIG_TARGET").toLatin1().constData(), lib_cnt);
                        ar_sublibs << lib;
                        obj_cnt = 0;
                    }
                    lib_cnt++;
                }
            }
        }
        if(!ar_sublibs.isEmpty()) {
            project->values("QMAKE_AR_SUBLIBS") = ar_sublibs;
            project->values("QMAKE_INTERNAL_PRL_LIBS") << "QMAKE_AR_SUBLIBS";
        }
    }
}