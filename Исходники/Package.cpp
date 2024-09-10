/*
 * Process a regular file, adding it to the archive if appropriate.
 *
 * If we're in "update" mode, and the file already exists in the archive,
 * delete the existing entry before adding the new one.
 */
bool processFile(Bundle* bundle, ZipFile* zip,
                 String8 storageName, const sp<const AaptFile>& file)
{
    const bool hasData = file->hasData();

    ZipEntry* entry;
    bool fromGzip = false;
    status_t result;

    /*
     * See if the filename ends in ".EXCLUDE".  We can't use
     * String8::getPathExtension() because the length of what it considers
     * to be an extension is capped.
     *
     * The Asset Manager doesn't check for ".EXCLUDE" in Zip archives,
     * so there's no value in adding them (and it makes life easier on
     * the AssetManager lib if we don't).
     *
     * NOTE: this restriction has been removed.  If you're in this code, you
     * should clean this up, but I'm in here getting rid of Path Name, and I
     * don't want to make other potentially breaking changes --joeo
     */
    int fileNameLen = storageName.length();
    int excludeExtensionLen = strlen(kExcludeExtension);
    if (fileNameLen > excludeExtensionLen
            && (0 == strcmp(storageName.string() + (fileNameLen - excludeExtensionLen),
                            kExcludeExtension))) {
        fprintf(stderr, "warning: '%s' not added to Zip\n", storageName.string());
        return true;
    }

    if (strcasecmp(storageName.getPathExtension().string(), ".gz") == 0) {
        fromGzip = true;
        storageName = storageName.getBasePath();
    }

    if (bundle->getUpdate()) {
        entry = zip->getEntryByName(storageName.string());
        if (entry != NULL) {
            /* file already exists in archive; there can be only one */
            if (entry->getMarked()) {
                fprintf(stderr,
                        "ERROR: '%s' exists twice (check for with & w/o '.gz'?)\n",
                        file->getPrintableSource().string());
                return false;
            }
            if (!hasData) {
                const String8& srcName = file->getSourceFile();
                time_t fileModWhen;
                fileModWhen = getFileModDate(srcName.string());
                if (fileModWhen == (time_t) -1) { // file existence tested earlier,
                    return false;                 //  not expecting an error here
                }
    
                if (fileModWhen > entry->getModWhen()) {
                    // mark as deleted so add() will succeed
                    if (bundle->getVerbose()) {
                        printf("      (removing old '%s')\n", storageName.string());
                    }
    
                    zip->remove(entry);
                } else {
                    // version in archive is newer
                    if (bundle->getVerbose()) {
                        printf("      (not updating '%s')\n", storageName.string());
                    }
                    entry->setMarked(true);
                    return true;
                }
            } else {
                // Generated files are always replaced.
                zip->remove(entry);
            }
        }
    }

    //android_setMinPriority(NULL, ANDROID_LOG_VERBOSE);

    if (fromGzip) {
        result = zip->addGzip(file->getSourceFile().string(), storageName.string(), &entry);
    } else if (!hasData) {
        /* don't compress certain files, e.g. PNGs */
        int compressionMethod = bundle->getCompressionMethod();
        if (!okayToCompress(bundle, storageName)) {
            compressionMethod = ZipEntry::kCompressStored;
        }
        result = zip->add(file->getSourceFile().string(), storageName.string(), compressionMethod,
                            &entry);
    } else {
        result = zip->add(file->getData(), file->getSize(), storageName.string(),
                           file->getCompressionMethod(), &entry);
    }
    if (result == NO_ERROR) {
        if (bundle->getVerbose()) {
            printf("      '%s'%s", storageName.string(), fromGzip ? " (from .gz)" : "");
            if (entry->getCompressionMethod() == ZipEntry::kCompressStored) {
                printf(" (not compressed)\n");
            } else {
                printf(" (compressed %d%%)\n", calcPercent(entry->getUncompressedLen(),
                            entry->getCompressedLen()));
            }
        }
        entry->setMarked(true);
    } else {
        if (result == ALREADY_EXISTS) {
            fprintf(stderr, "      Unable to add '%s': file already in archive (try '-u'?)\n",
                    file->getPrintableSource().string());
        } else {
            fprintf(stderr, "      Unable to add '%s': Zip add failed (%d)\n",
                    file->getPrintableSource().string(), result);
        }
        return false;
    }

    return true;
}