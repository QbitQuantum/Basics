bool echoscu(const QString &peerTitle, const QString &ourTitle,
             const QString &hostname, int port,
             QString &msg)
{
    T_ASC_Network *net;
    T_ASC_Parameters *params;
    T_ASC_Association *assoc;
    OFString temp_str;
    bool ret = false;

#ifdef HAVE_WINSOCK_H
    WSAData winSockData;
    /* we need at least version 1.1 */
    WORD winSockVersionNeeded = MAKEWORD( 1, 1 );
    WSAStartup(winSockVersionNeeded, &winSockData);
#endif

    /* initialize network, i.e. create an instance of T_ASC_Network*. */
    OFCondition cond = ASC_initializeNetwork(NET_REQUESTOR, 0, 6, &net);
    if (cond.bad()) {
        DimseCondition::dump(temp_str, cond);
        msg = QString::fromLatin1(temp_str.c_str());
        goto cleanup;
    }

    /* initialize asscociation parameters, i.e. create an instance of T_ASC_Parameters*. */
    cond = ASC_createAssociationParameters(&params, ASC_DEFAULTMAXPDU);
    if (cond.bad()) {
        DimseCondition::dump(temp_str, cond);
        msg = QString::fromLatin1(temp_str.c_str());
        goto cleanup;
    }

    ASC_setAPTitles(params, ourTitle.toLocal8Bit().data(), peerTitle.toLocal8Bit().data(), NULL);

    /* Set the transport layer type (type of network connection) in the params */
    /* strucutre. The default is an insecure connection; where OpenSSL is  */
    /* available the user is able to request an encrypted,secure connection. */
    cond = ASC_setTransportLayerType(params, OFFalse);
    if (cond.bad()) {
        DimseCondition::dump(temp_str, cond);
        msg = QString::fromLatin1(temp_str.c_str());
        goto cleanup;
    }

    /* Figure out the presentation addresses and copy the */
    /* corresponding values into the association parameters.*/
    DIC_NODENAME localHost;
    DIC_NODENAME peerHost;
    gethostname(localHost, sizeof(localHost) - 1);
    sprintf(peerHost, "%s:%d", hostname.toLocal8Bit().data(), port);

    ASC_setPresentationAddresses(params, localHost, peerHost);

    /* Set the presentation contexts which will be negotiated */
    /* when the network connection will be established */
    int presentationContextID = 1; /* odd byte value 1, 3, 5, .. 255 */
    for (unsigned long ii=0; ii<1; ii++)
    {
        cond = ASC_addPresentationContext(params, presentationContextID, UID_VerificationSOPClass,
                 transferSyntaxes, 3);
        presentationContextID += 2;
        if (cond.bad())
        {
            DimseCondition::dump(temp_str, cond);
            msg = QString::fromLatin1(temp_str.c_str());
            goto cleanup;
        }
    }

    /* create association, i.e. try to establish a network connection to another */
    /* DICOM application. This call creates an instance of T_ASC_Association*. */
    cond = ASC_requestAssociation(net, params, &assoc);
    if (cond.bad()) {
        if (cond == DUL_ASSOCIATIONREJECTED)
        {
            T_ASC_RejectParameters rej;

            ASC_getRejectParameters(params, &rej);
            ASC_printRejectParameters(temp_str, &rej);
            msg = QString("Association Rejected: %1").arg(temp_str.c_str());
            goto cleanup;
        } else {
            DimseCondition::dump(temp_str, cond);
            msg = QString("Association Request Failed: %1").arg(temp_str.c_str());
            goto cleanup;
        }
    }

    /* count the presentation contexts which have been accepted by the SCP */
    /* If there are none, finish the execution */
    if (ASC_countAcceptedPresentationContexts(params) == 0) {
        msg = QString("No Acceptable Presentation Contexts");
        goto cleanup;
    }

    /* do the real work, i.e. send a number of C-ECHO-RQ messages to the DICOM application */
    /* this application is connected with and handle corresponding C-ECHO-RSP messages. */
    DIC_US msgId = assoc->nextMsgID++;
    DIC_US status;
    DcmDataset *statusDetail = NULL;

    /* send C-ECHO-RQ and handle response */
    cond = DIMSE_echoUser(assoc, msgId, DIMSE_BLOCKING, 0, &status, &statusDetail);

    /* check for status detail information, there should never be any */
    if (statusDetail != NULL) {
        delete statusDetail;
    }

    /* tear down association, i.e. terminate network connection to SCP */
    if (cond == EC_Normal)
    {
        cond = ASC_releaseAssociation(assoc);
        ret = true;
    }
    else if (cond == DUL_PEERABORTEDASSOCIATION)
    {

    }
    else
    {
        DimseCondition::dump(temp_str, cond);
        msg = QString::fromLatin1(temp_str.c_str());
        cond = ASC_abortAssociation(assoc);
    }

cleanup:
    /* destroy the association, i.e. free memory of T_ASC_Association* structure. This */
    /* call is the counterpart of ASC_requestAssociation(...) which was called above. */
    cond = ASC_destroyAssociation(&assoc);

    /* drop the network, i.e. free memory of T_ASC_Network* structure. This call */
    /* is the counterpart of ASC_initializeNetwork(...) which was called above. */
    cond = ASC_dropNetwork(&net);

#ifdef HAVE_WINSOCK_H
    WSACleanup();
#endif

    return ret;
}