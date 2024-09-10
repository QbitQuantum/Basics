void FileSystemDevice::complete_getFileUpdateTime(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFileSystem::CmpFileTimeExt,GetFileUpdateTimeExt> packet=packet_;

  auto ext=packet.getExt();
  auto ext2=packet.getDeepExt<1>();

  if( ext->isOk() )
    {
     ext2->setFileTime(ext->file_time);
    }
  else
    {
     ext2->setError(MakeError(ext,FileError_OpFault));
    }

  packet.popExt().complete();
 }