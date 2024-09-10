/**
 * @brief TEST_F SdkTestTransfers
 *
 * It performs different operations related to transfers in both directions: up and down.
 *
 * - Starts an upload transfer and cancel it
 * - Starts an upload transfer, pause it, resume it and complete it
 * - Get node by fingerprint
 * - Get size of a node
 * - Download a file
 */
TEST_F(SdkTest, SdkTestTransfers)
{
    MegaNode *rootnode = megaApi->getRootNode();
    string filename1 = UPFILE;
    createFile(filename1);


    // --- Cancel a transfer ---

    transfersCancelled = false;
    megaApi->startUpload(filename1.data(), rootnode);
    megaApi->cancelTransfers(MegaTransfer::TYPE_UPLOAD);
    waitForResponse(&transfersCancelled);

    EXPECT_EQ(MegaError::API_OK, lastError) << "Transfer cancellation failed (error: " << lastError << ")";


    // --- Upload a file (part 1) ---

    uploadFinished = false;
    megaApi->startUpload(filename1.data(), rootnode);
    // do not wait yet for completion


    // --- Pause a transfer ---

    transfersPaused = false;
    megaApi->pauseTransfers(true, MegaTransfer::TYPE_UPLOAD);
    waitForResponse(&transfersPaused);

    EXPECT_EQ(MegaError::API_OK, lastError) << "Cannot pause transfer (error: " << lastError << ")";
    EXPECT_TRUE(megaApi->areTransfersPaused(MegaTransfer::TYPE_UPLOAD)) << "Upload transfer not paused";


    // --- Resume a transfer ---

    transfersPaused = false;
    megaApi->pauseTransfers(false, MegaTransfer::TYPE_UPLOAD);
    waitForResponse(&transfersPaused);

    EXPECT_EQ(MegaError::API_OK, lastError) << "Cannot resume transfer (error: " << lastError << ")";
    EXPECT_FALSE(megaApi->areTransfersPaused(MegaTransfer::TYPE_UPLOAD)) << "Upload transfer not resumed";


    // --- Upload a file (part 2) ---

    waitForResponse(&uploadFinished);

    ASSERT_EQ(MegaError::API_OK, lastError) << "Cannot upload file (error: " << lastError << ")";

    MegaNode *n1 = megaApi->getNodeByHandle(h);
    bool null_pointer = (n1 == NULL);

    ASSERT_FALSE(null_pointer) << "Cannot upload file (error: " << lastError << ")";
    ASSERT_STREQ(filename1.data(), n1->getName()) << "Uploaded file with wrong name (error: " << lastError << ")";


    // --- Get node by fingerprint (needs to be a file, not a folder) ---

    char *fingerprint = megaApi->getFingerprint(n1);
    MegaNode *n2 = megaApi->getNodeByFingerprint(fingerprint);

    null_pointer = (n2 == NULL);
    EXPECT_FALSE(null_pointer) << "Node by fingerprint not found";
//    ASSERT_EQ(n2->getHandle(), n4->getHandle());  This test may fail due to multiple nodes with the same name

    delete fingerprint;


    // --- Get the size of a file ---

    int filesize = getFilesize(filename1);
    int nodesize = megaApi->getSize(n2);
    EXPECT_EQ(filesize, nodesize) << "Wrong size of uploaded file";


    // --- Download a file ---

    string filename2 = "./" + DOWNFILE;

    downloadFinished = false;
    megaApi->startDownload(n2, filename2.c_str());
    waitForResponse(&downloadFinished);

    ASSERT_EQ(MegaError::API_OK, lastError) << "Cannot download the file (error: " << lastError << ")";

    MegaNode *n3 = megaApi->getNodeByHandle(h);
    null_pointer = (n3 == NULL);

    ASSERT_FALSE(null_pointer) << "Cannot download node";
    ASSERT_EQ(n2->getHandle(), n3->getHandle()) << "Cannot download node (error: " << lastError << ")";

    delete rootnode;
    delete n1;
    delete n2;
    delete n3;
}