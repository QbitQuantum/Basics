FILE *
File::Open (/*[in]*/ const PathName &	path,
	    /*[in]*/ FileMode		mode,
	    /*[in]*/ FileAccess		access,
	    /*[in]*/ bool		isTextFile,
	    /*[in]*/ FileShare		share)
{
  UNUSED_ALWAYS (isTextFile);
  UNUSED_ALWAYS (share);

  SessionImpl::theSession->trace_files->WriteFormattedLine
    ("core",
     T_("opening file %s (%d 0x%x %d %d)"),
     Q_(path),
     static_cast<int>(mode.Get()),
     static_cast<int>(access.Get()),
     static_cast<int>(share.Get()),
     static_cast<int>(isTextFile));

  int flags = 0;
  string strFlags;

  if (mode == FileMode::Create)
    {
      flags |= O_CREAT;
    }
  else if (mode == FileMode::Append)
    {
      flags |= O_APPEND;
    }

  if (access == FileAccess::ReadWrite)
    {
      flags |= O_RDWR;
      if (mode == FileMode::Append)
	{
	  strFlags += "a+";
	}
      else
	{
	  strFlags += "r+";
	}
    }
  else if (access == FileAccess::Read)
    {
      flags |= O_RDONLY;
      strFlags += "r";
    }
  else if (access == FileAccess::Write)
    {
      flags |= O_WRONLY;
      if (mode == FileMode::Append)
	{
	  strFlags += "a";
	}
      else
	{
	  flags |= O_TRUNC;
	  strFlags += "w";
	}
    }

  if (mode == FileMode::Create)
    {
      PathName dir (path);
      dir.MakeAbsolute ();
      dir.RemoveFileSpec();
      if (! Directory::Exists(dir))
	{
	  Directory::Create (dir);
	}
    }

  int fd;

  fd =
    open(path.Get(),
	 flags,
	 (((flags & O_CREAT) == 0)
	  ? 0
	  : (0
	     | S_IRUSR | S_IWUSR
	     | S_IRGRP
	     | S_IROTH
	     | 0)));

  if (fd < 0)
    {
      FATAL_CRT_ERROR ("open", path.Get());
    }

  try
    {
      return (FdOpen(fd, strFlags.c_str()));
    }
  catch (const exception &)
    {
      close (fd);
      throw;
    }
}