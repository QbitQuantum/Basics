S3Status listBucketCallback(int isTruncated, const char *nextMarker,
                                   int contentsCount,
                                   const S3ListBucketContent *contents,
                                   int commonPrefixesCount,
                                   const char **commonPrefixes,
                                   void *callbackData)
{
    list_bucket_callback_data *data =
        (list_bucket_callback_data *) callbackData;

    data->isTruncated = isTruncated;
    // This is tricky.  S3 doesn't return the NextMarker if there is no
    // delimiter.  Why, I don't know, since it's still useful for paging
    // through results.  We want NextMarker to be the last content in the
    // list, so set it to that if necessary.
    if ((!nextMarker || !nextMarker[0]) && contentsCount) {
        nextMarker = contents[contentsCount - 1].key;
    }
    if (nextMarker) {
        snprintf(data->nextMarker, sizeof(data->nextMarker), "%s",
                 nextMarker);
    }
    else {
        data->nextMarker[0] = 0;
    }

//    if (contentsCount && !data->keyCount) {
//        printListBucketHeader(data->allDetails);
//    }

    int i;
    for (i = 0; i < contentsCount; i++) {
        const S3ListBucketContent *content = &(contents[i]);
        char timebuf[256];
        time_t t = (time_t) content->lastModified;
        strftime(timebuf, sizeof(timebuf), "%Y-%m-%dT%H:%M:%SZ",
                 gmtime(&t));
        char sizebuf[16];
        if (content->size < 100000) {
            sprintf(sizebuf, "%5llu", (unsigned long long) content->size);
        }
        else if (content->size < (1024 * 1024)) {
            sprintf(sizebuf, "%4lluK",
                    ((unsigned long long) content->size) / 1024ULL);
        }
        else if (content->size < (10 * 1024 * 1024)) {
            float f = content->size;
            f /= (1024 * 1024);
            sprintf(sizebuf, "%1.2fM", f);
        }
        else if (content->size < (1024 * 1024 * 1024)) {
            sprintf(sizebuf, "%4lluM",
                    ((unsigned long long) content->size) /
                    (1024ULL * 1024ULL));
        }
        else {
            float f = (content->size / 1024);
            f /= (1024 * 1024);
            sprintf(sizebuf, "%1.2fG", f);
        }
        savedContents.append(*content);
        savedKeys.append(content->key);
    }

    data->keyCount += contentsCount;

    for (i = 0; i < commonPrefixesCount; i++) {
        savedCommonPrefixes.append(commonPrefixes[i]);
    }

    return S3StatusOK;
}