void Renamer::renameMovies(QList<Movie*> movies, const QString &filePattern, const QString &filePatternMulti,
                           const QString &directoryPattern, const bool &renameFiles, const bool &renameDirectories, const bool &dryRun)
{
    if ((renameFiles && filePattern.isEmpty()) || (renameDirectories && directoryPattern.isEmpty()))
        return;

    foreach (Movie *movie, movies) {
        if (movie->files().isEmpty() || (movie->files().count() > 1 && filePatternMulti.isEmpty()) || movie->hasChanged())
            continue;

        qApp->processEvents();
        QFileInfo fi(movie->files().first());
        QString fiCanonicalPath = fi.canonicalPath();
        QDir dir(fi.canonicalPath());
        QString newFolderName = directoryPattern;
        QString newFileName;
        QString nfo = Manager::instance()->mediaCenterInterface()->nfoFilePath(movie);
        QString poster = Manager::instance()->mediaCenterInterface()->imageFileName(movie, ImageType::MoviePoster);
        QString fanart = Manager::instance()->mediaCenterInterface()->imageFileName(movie, ImageType::MovieBackdrop);
        QString banner = Manager::instance()->mediaCenterInterface()->imageFileName(movie, ImageType::MovieBanner);
        QString thumb = Manager::instance()->mediaCenterInterface()->imageFileName(movie, ImageType::MovieThumb);
        QString logo = Manager::instance()->mediaCenterInterface()->imageFileName(movie, ImageType::MovieLogo);
        QString clearArt = Manager::instance()->mediaCenterInterface()->imageFileName(movie, ImageType::MovieClearArt);
        QString cdArt = Manager::instance()->mediaCenterInterface()->imageFileName(movie, ImageType::MovieCdArt);

        QDir chkDir(fi.canonicalPath());
        chkDir.cdUp();

        bool isBluRay = Helper::instance()->isBluRay(chkDir.path());
        bool isDvd = Helper::instance()->isDvd(chkDir.path());

        if (isBluRay || isDvd)
            dir.cdUp();

        if (!isBluRay && !isDvd && renameFiles) {
            int partNo = 0;
            foreach (const QString &file, movie->files()) {
                newFileName = (movie->files().count() == 1) ? filePattern : filePatternMulti;
                QFileInfo fi(file);
                QString baseName = fi.completeBaseName();
                QDir currentDir = fi.dir();
                Renamer::replace(newFileName, "title", movie->name());
                Renamer::replace(newFileName, "originalTitle", movie->originalName());
                Renamer::replace(newFileName, "sortTitle", movie->sortTitle());
                Renamer::replace(newFileName, "year", movie->released().toString("yyyy"));
                Renamer::replace(newFileName, "extension", fi.suffix());
                Renamer::replace(newFileName, "partNo", QString::number(++partNo));
                Renamer::replace(newFileName, "resolution", Helper::instance()->matchResolution(movie->streamDetails()->videoDetails().value("width").toInt(),
                                                                                                movie->streamDetails()->videoDetails().value("height").toInt()));
                Renamer::replaceCondition(newFileName, "imdbId", movie->id());
                Renamer::replaceCondition(newFileName, "movieset", movie->set());
                Renamer::replaceCondition(newFileName, "3D", movie->streamDetails()->videoDetails().value("stereomode") != "");
                Helper::instance()->sanitizeFileName(newFileName);
                if (fi.fileName() != newFileName) {
                    ui->results->append(tr("<b>Rename File</b> \"%1\" to \"%2\"").arg(fi.fileName()).arg(newFileName));
                    if (!dryRun) {
                        if (!rename(file, fi.canonicalPath() + "/" + newFileName))
                            ui->results->append("&nbsp;&nbsp;<span style=\"color:#ff0000;\"><b>" + tr("Failed") + "</b></span>");
                    }

                    foreach (const QString &trailerFile, currentDir.entryList(QStringList() << fi.completeBaseName() + "-trailer.*", QDir::Files | QDir::NoDotAndDotDot)) {
                        QFileInfo trailer(fi.canonicalPath() + "/" + trailerFile);
                        QString newTrailerFileName = newFileName;
                        newTrailerFileName = newTrailerFileName.left(newTrailerFileName.lastIndexOf(".")) + "-trailer." + trailer.suffix();
                        if (trailer.fileName() != newTrailerFileName) {
                            ui->results->append(tr("<b>Rename File</b> \"%1\" to \"%2\"").arg(trailer.fileName()).arg(newTrailerFileName));
                            if (!dryRun) {
                                if (!rename(fi.canonicalPath() + "/" + trailerFile, fi.canonicalPath() + "/" + newTrailerFileName))
                                    ui->results->append("&nbsp;&nbsp;<span style=\"color:#ff0000;\"><b>" + tr("Failed") + "</b></span>");
                            }
                        }
                    }

                    QStringList filters;
                    foreach (const QString &extra, m_extraFiles)
                        filters << baseName + extra;
                    foreach (const QString &subFileName, currentDir.entryList(filters, QDir::Files | QDir::NoDotAndDotDot)) {
                        QString subSuffix = subFileName.mid(baseName.length());
                        QString newBaseName = newFileName.left(newFileName.lastIndexOf("."));
                        QString newSubName = newBaseName + subSuffix;
                        ui->results->append(tr("<b>Rename File</b> \"%1\" to \"%2\"").arg(subFileName).arg(newSubName));
                        if (!dryRun) {
                            if (!rename(currentDir.canonicalPath() + "/" + subFileName, currentDir.canonicalPath() + "/" + newSubName))
                                ui->results->append("&nbsp;&nbsp;<span style=\"color:#ff0000;\"><b>" + tr("Failed") + "</b></span>");
                        }
                    }
                }
            }

            // Rename nfo
            if (!nfo.isEmpty()) {
                QString nfoFileName = QFileInfo(nfo).fileName();
                QList<DataFile> nfoFiles = Settings::instance()->dataFiles(DataFileType::MovieNfo);
                if (!nfoFiles.isEmpty()) {
                    QString newNfoFileName = nfoFiles.first().saveFileName(newFileName, -1, movie->files().count() > 1);
                    Helper::instance()->sanitizeFileName(newNfoFileName);
                    if (newNfoFileName != nfoFileName) {
                        ui->results->append(tr("<b>Rename NFO</b> \"%1\" to \"%2\"").arg(nfoFileName).arg(newNfoFileName));
                        if (!dryRun) {
                            if (!rename(nfo, fiCanonicalPath + "/" + newNfoFileName))
                                ui->results->append("&nbsp;&nbsp;<span style=\"color:#ff0000;\"><b>" + tr("Failed") + "</b></span>");
                        }
                    }
                }
            }

            // Rename Poster
            if (!poster.isEmpty()) {
                QString posterFileName = QFileInfo(poster).fileName();
                QList<DataFile> posterFiles = Settings::instance()->dataFiles(DataFileType::MoviePoster);
                if (!posterFiles.isEmpty()) {
                    QString newPosterFileName = posterFiles.first().saveFileName(newFileName, -1, movie->files().count() > 1);
                    Helper::instance()->sanitizeFileName(newPosterFileName);
                    if (newPosterFileName != posterFileName) {
                        ui->results->append(tr("<b>Rename Poster</b> \"%1\" to \"%2\"").arg(posterFileName).arg(newPosterFileName));
                        if (!dryRun) {
                            if (!rename(poster, fiCanonicalPath + "/" + newPosterFileName))
                                ui->results->append("&nbsp;&nbsp;<span style=\"color:#ff0000;\"><b>" + tr("Failed") + "</b></span>");
                        }
                    }
                }
            }

            // Rename Fanart
            if (!fanart.isEmpty()) {
                QString fanartFileName = QFileInfo(fanart).fileName();
                QList<DataFile> fanartFiles = Settings::instance()->dataFiles(DataFileType::MovieBackdrop);
                if (!fanartFiles.isEmpty()) {
                    QString newFanartFileName = fanartFiles.first().saveFileName(newFileName, -1, movie->files().count() > 1);
                    Helper::instance()->sanitizeFileName(newFanartFileName);
                    if (newFanartFileName != fanartFileName) {
                        ui->results->append(tr("<b>Rename Fanart</b> \"%1\" to \"%2\"").arg(fanartFileName).arg(newFanartFileName));
                        if (!dryRun) {
                            if (!rename(fanart, fiCanonicalPath + "/" + newFanartFileName))
                                ui->results->append("&nbsp;&nbsp;<span style=\"color:#ff0000;\"><b>" + tr("Failed") + "</b></span>");
                        }
                    }
                }
            }

            // Rename Banner
            if (!banner.isEmpty()) {
                QString bannerFileName = QFileInfo(banner).fileName();
                QList<DataFile> bannerFiles = Settings::instance()->dataFiles(DataFileType::MovieBanner);
                if (!bannerFiles.isEmpty()) {
                    QString newBannerFileName = bannerFiles.first().saveFileName(newFileName, -1, movie->files().count() > 1);
                    Helper::instance()->sanitizeFileName(newBannerFileName);
                    if (newBannerFileName != bannerFileName) {
                        ui->results->append(tr("<b>Rename Banner</b> \"%1\" to \"%2\"").arg(bannerFileName).arg(newBannerFileName));
                        if (!dryRun) {
                            if (!rename(banner, fiCanonicalPath + "/" + newBannerFileName))
                                ui->results->append("&nbsp;&nbsp;<span style=\"color:#ff0000;\"><b>" + tr("Failed") + "</b></span>");
                        }
                    }
                }
            }

            // Rename Thumb
            if (!thumb.isEmpty()) {
                QString thumbFileName = QFileInfo(thumb).fileName();
                QList<DataFile> thumbFiles = Settings::instance()->dataFiles(DataFileType::MovieThumb);
                if (!thumbFiles.isEmpty()) {
                    QString newThumbFileName = thumbFiles.first().saveFileName(newFileName, -1, movie->files().count() > 1);
                    Helper::instance()->sanitizeFileName(newThumbFileName);
                    if (newThumbFileName != thumbFileName) {
                        ui->results->append(tr("<b>Rename Thumb</b> \"%1\" to \"%2\"").arg(thumbFileName).arg(newThumbFileName));
                        if (!dryRun) {
                            if (!rename(thumb, fiCanonicalPath + "/" + newThumbFileName))
                                ui->results->append("&nbsp;&nbsp;<span style=\"color:#ff0000;\"><b>" + tr("Failed") + "</b></span>");
                        }
                    }
                }
            }

            // Rename Logo
            if (!logo.isEmpty()) {
                QString logoFileName = QFileInfo(logo).fileName();
                QList<DataFile> logoFiles = Settings::instance()->dataFiles(DataFileType::MovieLogo);
                if (!logoFiles.isEmpty()) {
                    QString newLogoFileName = logoFiles.first().saveFileName(newFileName, -1, movie->files().count() > 1);
                    Helper::instance()->sanitizeFileName(newLogoFileName);
                    if (newLogoFileName != logoFileName) {
                        ui->results->append(tr("<b>Rename Logo</b> \"%1\" to \"%2\"").arg(logoFileName).arg(newLogoFileName));
                        if (!dryRun) {
                            if (!rename(logo, fiCanonicalPath + "/" + newLogoFileName))
                                ui->results->append("&nbsp;&nbsp;<span style=\"color:#ff0000;\"><b>" + tr("Failed") + "</b></span>");
                        }
                    }
                }
            }

            // Rename ClearArt
            if (!clearArt.isEmpty()) {
                QString clearArtFileName = QFileInfo(clearArt).fileName();
                QList<DataFile> clearArtFiles = Settings::instance()->dataFiles(DataFileType::MovieClearArt);
                if (!clearArtFiles.isEmpty()) {
                    QString newClearArtFileName = clearArtFiles.first().saveFileName(newFileName, -1, movie->files().count() > 1);
                    Helper::instance()->sanitizeFileName(newClearArtFileName);
                    if (newClearArtFileName != clearArtFileName) {
                        ui->results->append(tr("<b>Rename Clear Art</b> \"%1\" to \"%2\"").arg(clearArtFileName).arg(newClearArtFileName));
                        if (!dryRun) {
                            if (!rename(clearArt, fiCanonicalPath + "/" + newClearArtFileName))
                                ui->results->append("&nbsp;&nbsp;<span style=\"color:#ff0000;\"><b>" + tr("Failed") + "</b></span>");
                        }
                    }
                }
            }

            // Rename CdArt
            if (!cdArt.isEmpty()) {
                QString cdArtFileName = QFileInfo(cdArt).fileName();
                QList<DataFile> cdArtFiles = Settings::instance()->dataFiles(DataFileType::MovieCdArt);
                if (!cdArtFiles.isEmpty()) {
                    QString newCdArtFileName = cdArtFiles.first().saveFileName(newFileName, -1, movie->files().count() > 1);
                    Helper::instance()->sanitizeFileName(newCdArtFileName);
                    if (newCdArtFileName != cdArtFileName) {
                        ui->results->append(tr("<b>Rename CD Art</b> \"%1\" to \"%2\"").arg(cdArtFileName).arg(newCdArtFileName));
                        if (!dryRun) {
                            if (!rename(cdArt, fiCanonicalPath + "/" + newCdArtFileName))
                                ui->results->append("&nbsp;&nbsp;<span style=\"color:#ff0000;\"><b>" + tr("Failed") + "</b></span>");
                        }
                    }
                }
            }
        }