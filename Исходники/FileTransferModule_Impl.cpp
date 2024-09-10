BOOL FileTransferModule_Impl::sendFile(IN const CString& sFilePath, IN const std::string& sSendToSID,IN BOOL bOnlineMode)
{
    if (TransferFileEntityManager::getInstance()->checkIfIsSending(sFilePath))
    {
        return FALSE;
    }
    TransferFileEntity fileEntity;

    //获取文件大小
    struct __stat64 buffer;
    _wstat64(sFilePath, &buffer);
    fileEntity.nFileSize = (UInt32)buffer.st_size;
    if (0 != fileEntity.nFileSize)
    {
        CString strFileName = sFilePath;
        strFileName.Replace(_T("\\"), _T("/"));//mac上对于路径字符“\”需要做特殊处理，windows上则可以识别
        fileEntity.sFileName = util::cStringToString(strFileName);
        fileEntity.sFromID = module::getSysConfigModule()->userID();
        fileEntity.sToID = sSendToSID;
        uint32_t transMode = 0;
        transMode = bOnlineMode ? IM::BaseDefine::FileType::FILE_TYPE_ONLINE : IM::BaseDefine::FileType::FILE_TYPE_OFFLINE;

        LOG__(DEBG,_T("FileTransferSevice_Impl::sendFile sTaskID = %s"), util::stringToCString(fileEntity.sTaskID));

        imcore::IMLibCoreStartOperationWithLambda(
            [=]()
        {
            IM::File::IMFileReq imFileReq;
            LOG__(APP, _T("imFileReq,name=%s,size=%d,toId=%s"),util::stringToCString(fileEntity.sFileName)
                  ,fileEntity.nFileSize,util::stringToCString(fileEntity.sToID));
            imFileReq.set_from_user_id(util::stringToInt32(fileEntity.sFromID));
            imFileReq.set_to_user_id(util::stringToInt32(fileEntity.sToID));
            imFileReq.set_file_name(fileEntity.sFileName);
            imFileReq.set_file_size(fileEntity.nFileSize);
            imFileReq.set_trans_mode(static_cast<IM::BaseDefine::FileType>(transMode));

            module::getTcpClientModule()->sendPacket(IM::BaseDefine::ServiceID::DFFX_SID_FILE
                    , IM::BaseDefine::FileCmdID::DFFX_CID_FILE_REQUEST
                    , &imFileReq);
        });

        return TRUE;
    }
    LOG__(ERR, _T("fileEntity FileSize error,size = %d"), fileEntity.nFileSize);
    return FALSE;
}