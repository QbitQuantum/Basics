// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.IOUtils.pas' rev: 34.00 (iOS)

#ifndef System_IoutilsHPP
#define System_IoutilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.SysTypes.hpp>
#include <Posix.Errno.hpp>
#include <Posix.Unistd.hpp>
#include <iOSapi.Foundation.hpp>
#include <System.RTLConsts.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.Masks.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Ioutils
{
//-- forward type declarations -----------------------------------------------
struct TDirectory;
struct TPath;
struct TFile;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TSearchOption : unsigned char { soTopDirectoryOnly, soAllDirectories };

enum class DECLSPEC_DENUM TFileAttribute : unsigned char { faNamedPipe, faCharacterDevice, faDirectory, faBlockDevice, faNormal, faSymLink, faSocket, faWhiteout, faOwnerRead, faOwnerWrite, faOwnerExecute, faGroupRead, faGroupWrite, faGroupExecute, faOthersRead, faOthersWrite, faOthersExecute, faUserIDExecution, faGroupIDExecution, faStickyBit };

typedef System::Set<TFileAttribute, _DELPHI_SET_ENUMERATOR(TFileAttribute::faNamedPipe), _DELPHI_SET_ENUMERATOR(TFileAttribute::faStickyBit)> TFileAttributes;

enum class DECLSPEC_DENUM TFileMode : unsigned char { fmCreateNew, fmCreate, fmOpen, fmOpenOrCreate, fmTruncate, fmAppend };

enum class DECLSPEC_DENUM TFileAccess : unsigned char { faRead, faWrite, faReadWrite };

enum class DECLSPEC_DENUM TFileShare : unsigned char { fsNone, fsRead, fsWrite, fsReadWrite };

struct DECLSPEC_DRECORD TDirectory
{
	
public:
	__interface DELPHIINTERFACE TFilterPredicate;
	typedef System::DelphiInterface<TFilterPredicate> _di_TFilterPredicate;
	__interface TFilterPredicate  : public System::IInterface 
	{
		virtual bool __fastcall Invoke(const System::UnicodeString Path, const System::Sysutils::TSearchRec &SearchRec) = 0 ;
	};
	
	
private:
	__interface DELPHIINTERFACE TDirectoryWalkProc;
	typedef System::DelphiInterface<TDirectoryWalkProc> _di_TDirectoryWalkProc;
	__interface TDirectoryWalkProc  : public System::IInterface 
	{
		virtual bool __fastcall Invoke(const System::UnicodeString Path, const System::Sysutils::TSearchRec &FileInfo) = 0 ;
	};
	
	
private:
	static void __fastcall InternalCheckDirPathParam(const System::UnicodeString Path, const bool ExistsCheck);
	static void __fastcall CheckCreateDirectoryParameters(const System::UnicodeString Path);
	static void __fastcall CheckCopyParameters(System::UnicodeString SourceDirName, System::UnicodeString DestDirName);
	static void __fastcall CheckDeleteParameters(const System::UnicodeString Path, const bool Recursive);
	static void __fastcall CheckGetAttributesParameters(const System::UnicodeString Path);
	static void __fastcall CheckGetDirectoriesParameters(const System::UnicodeString Path, const System::UnicodeString SearchPattern);
	static void __fastcall CheckGetDirectoryRootParameters(const System::UnicodeString Path);
	static void __fastcall CheckGetFilesParameters(System::UnicodeString Path, const System::UnicodeString SearchPattern);
	static void __fastcall CheckGetFileSystemEntriesParameters(System::UnicodeString Path, const System::UnicodeString SearchPattern);
	static void __fastcall CheckGetCreationTimeParameters(const System::UnicodeString Path);
	static void __fastcall CheckGetCreationTimeUtcParameters(const System::UnicodeString Path);
	static void __fastcall CheckGetLastAccessTimeParameters(const System::UnicodeString Path);
	static void __fastcall CheckGetLastAccessTimeUtcParameters(const System::UnicodeString Path);
	static void __fastcall CheckGetLastWriteTimeParameters(const System::UnicodeString Path);
	static void __fastcall CheckGetLastWriteTimeUtcParameters(const System::UnicodeString Path);
	static void __fastcall CheckGetParentParameters(const System::UnicodeString Path);
	static void __fastcall CheckMoveParameters(System::UnicodeString SourceDirName, System::UnicodeString DestDirName);
	static void __fastcall CheckSetAttributesParameters(const System::UnicodeString Path);
	static void __fastcall CheckSetCurrentDirectoryParameters(const System::UnicodeString Path);
	static void __fastcall CheckSetCreationTimeParameters(const System::UnicodeString Path);
	static void __fastcall CheckSetCreationTimeUtcParameters(const System::UnicodeString Path);
	static void __fastcall CheckSetLastAccessTimeParameters(const System::UnicodeString Path);
	static void __fastcall CheckSetLastAccessTimeUtcParameters(const System::UnicodeString Path);
	static void __fastcall CheckSetLastWriteTimeParameters(const System::UnicodeString Path);
	static void __fastcall CheckSetLastWriteTimeUtcParameters(const System::UnicodeString Path);
	static void __fastcall GetDateTimeInfo(const System::UnicodeString Path, /* out */ System::TDateTime &CreationTime, /* out */ System::TDateTime &LastAccessTime, /* out */ System::TDateTime &LastWriteTime, const bool UseLocalTimeZone);
	static void __fastcall SetDateTimeInfo(const System::UnicodeString Path, const System::PDateTime CreationTime, const System::PDateTime LastAccessTime, const System::PDateTime LastWriteTime, const bool UseLocalTimeZone);
	static long __fastcall ConvertDateTimeToFileTime(const System::TDateTime DateTime, const bool UseLocalTimeZone);
	static System::TDateTime __fastcall DoGetCreationTime(const System::UnicodeString Path);
	static System::TDateTime __fastcall DoGetCreationTimeUtc(const System::UnicodeString Path);
	static System::TDateTime __fastcall DoGetLastAccessTime(const System::UnicodeString Path);
	static System::TDateTime __fastcall DoGetLastAccessTimeUtc(const System::UnicodeString Path);
	static System::TDateTime __fastcall DoGetLastWriteTime(const System::UnicodeString Path);
	static System::TDateTime __fastcall DoGetLastWriteTimeUtc(const System::UnicodeString Path);
	static void __fastcall DoSetCreationTime(const System::UnicodeString Path, const System::TDateTime CreationTime);
	static void __fastcall DoSetCreationTimeUtc(const System::UnicodeString Path, const System::TDateTime CreationTime);
	static void __fastcall DoSetLastAccessTime(const System::UnicodeString Path, const System::TDateTime LastAccessTime);
	static void __fastcall DoSetLastAccessTimeUtc(const System::UnicodeString Path, const System::TDateTime LastAccessTime);
	static void __fastcall DoSetLastWriteTime(const System::UnicodeString Path, const System::TDateTime LastWriteTime);
	static void __fastcall DoSetLastWriteTimeUtc(const System::UnicodeString Path, const System::TDateTime LastWriteTime);
	static System::TArray__1<System::UnicodeString> __fastcall DoGetFiles(const System::UnicodeString Path, const System::UnicodeString SearchPattern, const TSearchOption SearchOption, const _di_TFilterPredicate Predicate);
	static System::TArray__1<System::UnicodeString> __fastcall DoGetDirectories(const System::UnicodeString Path, const System::UnicodeString SearchPattern, const TSearchOption SearchOption, const _di_TFilterPredicate Predicate);
	static System::TArray__1<System::UnicodeString> __fastcall DoGetFileSystemEntries(const System::UnicodeString Path, const System::UnicodeString SearchPattern, const TSearchOption SearchOption, const _di_TFilterPredicate Predicate)/* overload */;
	static void __fastcall WalkThroughDirectory(const System::UnicodeString Path, const System::UnicodeString Pattern, const _di_TDirectoryWalkProc PreCallback, const _di_TDirectoryWalkProc PostCallback, const bool Recursive);
	
public:
	static void __fastcall Copy(const System::UnicodeString SourceDirName, const System::UnicodeString DestDirName);
	static void __fastcall CreateDirectory(const System::UnicodeString Path);
	static void __fastcall Delete(const System::UnicodeString Path)/* overload */;
	static void __fastcall Delete(const System::UnicodeString Path, const bool Recursive)/* overload */;
	static bool __fastcall Exists(const System::UnicodeString Path, bool FollowLink = true);
	static TFileAttributes __fastcall GetAttributes(const System::UnicodeString Path, bool FollowLink = true);
	static System::UnicodeString __fastcall GetCurrentDirectory();
	static void __fastcall SetCurrentDirectory(const System::UnicodeString Path);
	static System::TArray__1<System::UnicodeString> __fastcall GetLogicalDrives();
	static System::TDateTime __fastcall GetCreationTime(const System::UnicodeString Path);
	static System::TDateTime __fastcall GetCreationTimeUtc(const System::UnicodeString Path);
	static System::TDateTime __fastcall GetLastAccessTime(const System::UnicodeString Path);
	static System::TDateTime __fastcall GetLastAccessTimeUtc(const System::UnicodeString Path);
	static System::TDateTime __fastcall GetLastWriteTime(const System::UnicodeString Path);
	static System::TDateTime __fastcall GetLastWriteTimeUtc(const System::UnicodeString Path);
	static void __fastcall SetAttributes(const System::UnicodeString Path, const TFileAttributes Attributes);
	static void __fastcall SetCreationTime(const System::UnicodeString Path, const System::TDateTime CreationTime);
	static void __fastcall SetCreationTimeUtc(const System::UnicodeString Path, const System::TDateTime CreationTime);
	static void __fastcall SetLastAccessTime(const System::UnicodeString Path, const System::TDateTime LastAccessTime);
	static void __fastcall SetLastAccessTimeUtc(const System::UnicodeString Path, const System::TDateTime LastAccessTime);
	static void __fastcall SetLastWriteTime(const System::UnicodeString Path, const System::TDateTime LastWriteTime);
	static void __fastcall SetLastWriteTimeUtc(const System::UnicodeString Path, const System::TDateTime LastWriteTime);
	static System::UnicodeString __fastcall GetParent(const System::UnicodeString Path);
	static System::TArray__1<System::UnicodeString> __fastcall GetDirectories(const System::UnicodeString Path)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall GetDirectories(const System::UnicodeString Path, const _di_TFilterPredicate Predicate)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall GetDirectories(const System::UnicodeString Path, const System::UnicodeString SearchPattern)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall GetDirectories(const System::UnicodeString Path, const System::UnicodeString SearchPattern, const _di_TFilterPredicate Predicate)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall GetDirectories(const System::UnicodeString Path, const System::UnicodeString SearchPattern, const TSearchOption SearchOption)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall GetDirectories(const System::UnicodeString Path, const System::UnicodeString SearchPattern, const TSearchOption SearchOption, const _di_TFilterPredicate Predicate)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall GetDirectories(const System::UnicodeString Path, const TSearchOption SearchOption, const _di_TFilterPredicate Predicate)/* overload */;
	static System::UnicodeString __fastcall GetDirectoryRoot(const System::UnicodeString Path);
	static System::TArray__1<System::UnicodeString> __fastcall GetFiles(const System::UnicodeString Path)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall GetFiles(const System::UnicodeString Path, const _di_TFilterPredicate Predicate)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall GetFiles(const System::UnicodeString Path, const System::UnicodeString SearchPattern)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall GetFiles(const System::UnicodeString Path, const System::UnicodeString SearchPattern, const _di_TFilterPredicate Predicate)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall GetFiles(const System::UnicodeString Path, const System::UnicodeString SearchPattern, const TSearchOption SearchOption)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall GetFiles(const System::UnicodeString Path, const System::UnicodeString SearchPattern, const TSearchOption SearchOption, const _di_TFilterPredicate Predicate)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall GetFiles(const System::UnicodeString Path, const TSearchOption SearchOption, const _di_TFilterPredicate Predicate)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall GetFileSystemEntries(const System::UnicodeString Path)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall GetFileSystemEntries(const System::UnicodeString Path, const _di_TFilterPredicate Predicate)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall GetFileSystemEntries(const System::UnicodeString Path, const System::UnicodeString SearchPattern)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall GetFileSystemEntries(const System::UnicodeString Path, const System::UnicodeString SearchPattern, const _di_TFilterPredicate Predicate)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall GetFileSystemEntries(const System::UnicodeString Path, const TSearchOption SearchOption, const _di_TFilterPredicate Predicate)/* overload */;
	static bool __fastcall IsEmpty(const System::UnicodeString Path);
	static bool __fastcall IsRelativePath(const System::UnicodeString Path);
	static void __fastcall Move(const System::UnicodeString SourceDirName, const System::UnicodeString DestDirName);
};


enum class DECLSPEC_DENUM TPathPrefixType : unsigned char { pptNoPrefix, pptExtended, pptExtendedUNC };

struct DECLSPEC_DRECORD TPath
{
private:
	static System::UnicodeString FCCurrentDir;
	static System::UnicodeString FCParentDir;
	static System::UnicodeString FCExtendedPrefix;
	static System::UnicodeString FCExtendedUNCPrefix;
	static System::WideChar FAltDirectorySeparatorChar;
	static System::WideChar FDirectorySeparatorChar;
	static System::WideChar FPathSeparator;
	static System::WideChar FVolumeSeparatorChar;
	static System::WideChar FExtensionSeparatorChar;
	static System::TArray__1<System::WideChar> FInvalidPathChars;
	static System::TArray__1<System::WideChar> FInvalidFileNameChars;
	static System::TArray__1<System::WideChar> FPathWildcardChars;
	static System::TArray__1<System::WideChar> FFileNameWildCardChars;
	static void __fastcall CheckPathLength(const System::UnicodeString Path, const int MaxLength);
	static int __fastcall GetExtensionSeparatorPos(const System::UnicodeString FileName);
	static void __fastcall InternalCheckPathParam(const System::UnicodeString Path, const bool ExistsCheck);
	static bool __fastcall IsCharInOrderedArray(const System::WideChar AChar, const System::TArray__1<System::WideChar> AnArray);
	static bool __fastcall IsPathWildcardChar(const System::WideChar AChar);
	static bool __fastcall IsPathSeparator(const System::WideChar AChar);
	static bool __fastcall IsFileNameWildcardChar(const System::WideChar AChar);
	static System::UnicodeString __fastcall DoCombine(const System::UnicodeString Path1, const System::UnicodeString Path2, const bool ValidateParams);
	static System::UnicodeString __fastcall DoGetDirectoryName(System::UnicodeString FileName);
	static System::UnicodeString __fastcall DoGetFileName(const System::UnicodeString FileName, const bool ValidateParam);
	static System::UnicodeString __fastcall DoGetFullPath(const System::UnicodeString Path);
	static System::UnicodeString __fastcall DoGetPathRoot(const System::UnicodeString Path);
	static bool __fastcall DoIsPathRooted(const System::UnicodeString Path, const bool ValidateParam);
	static bool __fastcall DoMatchesPattern(const System::UnicodeString FileName, const System::UnicodeString Pattern);
	static System::UnicodeString __fastcall InternalGetMACOSPath(const unsigned long SearchedPath, const unsigned long SearchMask);
	
private:
	// __classmethod void __fastcall Create@();
	
public:
	static bool __fastcall IsValidPathChar(const System::WideChar AChar);
	static bool __fastcall IsValidFileNameChar(const System::WideChar AChar);
	static bool __fastcall HasValidPathChars(const System::UnicodeString Path, const bool UseWildcards);
	static bool __fastcall HasValidFileNameChars(const System::UnicodeString FileName, const bool UseWildcards);
	static TPathPrefixType __fastcall GetExtendedPrefix(const System::UnicodeString Path);
	static bool __fastcall IsDriveRooted(const System::UnicodeString Path);
	static bool __fastcall IsExtendedPrefixed(const System::UnicodeString Path);
	static bool __fastcall IsRelativePath(const System::UnicodeString Path);
	static bool __fastcall IsUNCPath(const System::UnicodeString Path);
	static bool __fastcall IsUNCRooted(const System::UnicodeString Path);
	static System::UnicodeString __fastcall GetGUIDFileName(const bool UseSeparator = false);
	static bool __fastcall DriveExists(const System::UnicodeString Path);
	static bool __fastcall MatchesPattern(const System::UnicodeString FileName, const System::UnicodeString Pattern, const bool CaseSensitive);
	static System::UnicodeString __fastcall ChangeExtension(const System::UnicodeString Path, const System::UnicodeString Extension);
	static System::UnicodeString __fastcall Combine(const System::UnicodeString Path1, const System::UnicodeString Path2);
	static System::UnicodeString __fastcall GetDirectoryName(System::UnicodeString FileName);
	static System::UnicodeString __fastcall GetExtension(const System::UnicodeString FileName);
	static System::UnicodeString __fastcall GetFileName(const System::UnicodeString FileName);
	static System::UnicodeString __fastcall GetFileNameWithoutExtension(const System::UnicodeString FileName);
	static System::UnicodeString __fastcall GetFullPath(const System::UnicodeString Path);
	static System::TArray__1<System::WideChar> __fastcall GetInvalidFileNameChars();
	static System::TArray__1<System::WideChar> __fastcall GetInvalidPathChars();
	static System::UnicodeString __fastcall GetPathRoot(const System::UnicodeString Path);
	static System::UnicodeString __fastcall GetRandomFileName();
	static System::UnicodeString __fastcall GetTempFileName();
	static System::UnicodeString __fastcall GetTempPath();
	static System::UnicodeString __fastcall GetHomePath();
	static System::UnicodeString __fastcall GetDocumentsPath();
	static System::UnicodeString __fastcall GetSharedDocumentsPath();
	static System::UnicodeString __fastcall GetLibraryPath();
	static System::UnicodeString __fastcall GetCachePath();
	static System::UnicodeString __fastcall GetPublicPath();
	static System::UnicodeString __fastcall GetPicturesPath();
	static System::UnicodeString __fastcall GetSharedPicturesPath();
	static System::UnicodeString __fastcall GetCameraPath();
	static System::UnicodeString __fastcall GetSharedCameraPath();
	static System::UnicodeString __fastcall GetMusicPath();
	static System::UnicodeString __fastcall GetSharedMusicPath();
	static System::UnicodeString __fastcall GetMoviesPath();
	static System::UnicodeString __fastcall GetSharedMoviesPath();
	static System::UnicodeString __fastcall GetAlarmsPath();
	static System::UnicodeString __fastcall GetSharedAlarmsPath();
	static System::UnicodeString __fastcall GetDownloadsPath();
	static System::UnicodeString __fastcall GetSharedDownloadsPath();
	static System::UnicodeString __fastcall GetRingtonesPath();
	static System::UnicodeString __fastcall GetSharedRingtonesPath();
	static TFileAttributes __fastcall GetAttributes(const System::UnicodeString Path, bool FollowLink = true);
	static void __fastcall SetAttributes(const System::UnicodeString Path, const TFileAttributes Attributes);
	static bool __fastcall HasExtension(const System::UnicodeString Path);
	static bool __fastcall IsPathRooted(const System::UnicodeString Path);
	/* static */ __property System::WideChar ExtensionSeparatorChar = {read=FExtensionSeparatorChar};
	/* static */ __property System::WideChar AltDirectorySeparatorChar = {read=FAltDirectorySeparatorChar};
	/* static */ __property System::WideChar DirectorySeparatorChar = {read=FDirectorySeparatorChar};
	/* static */ __property System::WideChar PathSeparator = {read=FPathSeparator};
	/* static */ __property System::WideChar VolumeSeparatorChar = {read=FVolumeSeparatorChar};
	
private:
	// __classmethod void __fastcall Destroy@();
};


struct DECLSPEC_DRECORD TFile
{
private:
	static constexpr System::Int8 FCMinFileNameLen = System::Int8(0xc);
	
	static void __fastcall InternalCheckFilePathParam(const System::UnicodeString Path, const bool FileExistsCheck);
	static void __fastcall CheckAppendAllTextParameters(const System::UnicodeString Path, System::Sysutils::TEncoding* const Encoding, const bool NeedEncoding);
	static void __fastcall CheckAppendTextParameters(const System::UnicodeString Path);
	static void __fastcall CheckCopyParameters(const System::UnicodeString SourceFileName, const System::UnicodeString DestFileName, const bool Overwrite);
	static void __fastcall CheckCreateParameters(const System::UnicodeString Path);
	static void __fastcall CheckCreateTextParameters(const System::UnicodeString Path);
	static void __fastcall CheckDeleteParameters(const System::UnicodeString Path);
	static void __fastcall CheckGetAttributesParameters(const System::UnicodeString Path);
	static void __fastcall CheckGetCreationTimeParameters(const System::UnicodeString Path);
	static void __fastcall CheckGetCreationTimeUtcParameters(const System::UnicodeString Path);
	static void __fastcall CheckGetLastAccessTimeParameters(const System::UnicodeString Path);
	static void __fastcall CheckGetLastAccessTimeUtcParameters(const System::UnicodeString Path);
	static void __fastcall CheckGetLastWriteTimeParameters(const System::UnicodeString Path);
	static void __fastcall CheckGetLastWriteTimeUtcParameters(const System::UnicodeString Path);
	static void __fastcall CheckMoveParameters(const System::UnicodeString SourceFileName, const System::UnicodeString DestFileName);
	static void __fastcall CheckOpenParameters(const System::UnicodeString Path);
	static void __fastcall CheckOpenReadParameters(const System::UnicodeString Path);
	static void __fastcall CheckOpenTextParameters(const System::UnicodeString Path);
	static void __fastcall CheckOpenWriteParameters(const System::UnicodeString Path);
	static void __fastcall CheckReadAllBytesParameters(const System::UnicodeString Path);
	static void __fastcall CheckReadAllLinesParameters(const System::UnicodeString Path, System::Sysutils::TEncoding* const Encoding, const bool NeedEncoding);
	static void __fastcall CheckReadAllTextParameters(const System::UnicodeString Path, System::Sysutils::TEncoding* const Encoding, const bool NeedEncoding);
	static void __fastcall CheckSetAttributesParameters(const System::UnicodeString Path);
	static void __fastcall CheckSetCreationTimeParameters(const System::UnicodeString Path);
	static void __fastcall CheckSetCreationTimeUtcParameters(const System::UnicodeString Path);
	static void __fastcall CheckSetLastAccessTimeParameters(const System::UnicodeString Path);
	static void __fastcall CheckSetLastAccessTimeUtcParameters(const System::UnicodeString Path);
	static void __fastcall CheckSetLastWriteTimeParameters(const System::UnicodeString Path);
	static void __fastcall CheckSetLastWriteTimeUtcParameters(const System::UnicodeString Path);
	static void __fastcall CheckWriteAllBytesParameters(const System::UnicodeString Path);
	static void __fastcall CheckWriteAllLinesParameters(const System::UnicodeString Path, System::Sysutils::TEncoding* const Encoding, const bool NeedEncoding);
	static void __fastcall CheckWriteAllTextParameters(const System::UnicodeString Path, System::Sysutils::TEncoding* const Encoding, const bool NeedEncoding);
	static System::Sysutils::TEncoding* __fastcall GetEncoding(System::Classes::TStream* const Stream);
	static System::TArray__1<System::UnicodeString> __fastcall GetStringArrayFromText(const System::UnicodeString Text);
	static System::Classes::TStringList* __fastcall GetStringListFromArray(const System::TArray__1<System::UnicodeString> AnArray);
	static System::Classes::TFileStream* __fastcall DoCreateOpenFile(const System::UnicodeString Path);
	static bool __fastcall DoCopy(const System::UnicodeString SourceFileName, const System::UnicodeString DestFileName, const bool Overwrite);
	static TFileAttributes __fastcall DoGetAttributes(const System::UnicodeString Path, bool FollowLink = true);
	static System::TArray__1<System::Byte> __fastcall DoReadAllBytes(const System::UnicodeString Path);
	static System::UnicodeString __fastcall DoReadAllText(const System::UnicodeString Path)/* overload */;
	static System::UnicodeString __fastcall DoReadAllText(const System::UnicodeString Path, System::Sysutils::TEncoding* const Encoding)/* overload */;
	static void __fastcall DoSetAttributes(const System::UnicodeString Path, const TFileAttributes Attributes);
	static void __fastcall DoWriteAllText(const System::UnicodeString Path, const System::UnicodeString Contents, System::Sysutils::TEncoding* const Encoding, const bool WriteBOM);
	static void __fastcall DoWriteAllLines(const System::UnicodeString Path, const System::TArray__1<System::UnicodeString> Contents, System::Sysutils::TEncoding* const Encoding, const bool WriteBOM);
	
public:
	static TFileAttributes __fastcall IntegerToFileAttributes(const int Attributes);
	static int __fastcall FileAttributesToInteger(const TFileAttributes Attributes);
	static System::Classes::TFileStream* __fastcall Create(const System::UnicodeString Path)/* overload */;
	static System::Classes::TFileStream* __fastcall Create(const System::UnicodeString Path, const int BufferSize)/* overload */;
	static void __fastcall AppendAllText(const System::UnicodeString Path, const System::UnicodeString Contents)/* overload */;
	static void __fastcall AppendAllText(const System::UnicodeString Path, const System::UnicodeString Contents, System::Sysutils::TEncoding* const Encoding)/* overload */;
	static System::Classes::TStreamWriter* __fastcall AppendText(const System::UnicodeString Path);
	static void __fastcall Copy(const System::UnicodeString SourceFileName, const System::UnicodeString DestFileName)/* overload */;
	static void __fastcall Copy(const System::UnicodeString SourceFileName, const System::UnicodeString DestFileName, const bool Overwrite)/* overload */;
	static bool __fastcall CreateSymLink(const System::UnicodeString Link, const System::UnicodeString Target);
	static System::Classes::TStreamWriter* __fastcall CreateText(const System::UnicodeString Path);
	static void __fastcall Delete(const System::UnicodeString Path);
	static bool __fastcall Exists(const System::UnicodeString Path, bool FollowLink = true);
	static TFileAttributes __fastcall GetAttributes(const System::UnicodeString Path, bool FollowLink = true);
	static System::TDateTime __fastcall GetCreationTime(const System::UnicodeString Path);
	static System::TDateTime __fastcall GetCreationTimeUtc(const System::UnicodeString Path);
	static System::TDateTime __fastcall GetLastAccessTime(const System::UnicodeString Path);
	static System::TDateTime __fastcall GetLastAccessTimeUtc(const System::UnicodeString Path);
	static System::TDateTime __fastcall GetLastWriteTime(const System::UnicodeString Path);
	static System::TDateTime __fastcall GetLastWriteTimeUtc(const System::UnicodeString Path);
	static bool __fastcall GetSymLinkTarget(const System::UnicodeString FileName, System::Sysutils::TSymLinkRec &SymLinkRec)/* overload */;
	static bool __fastcall GetSymLinkTarget(const System::UnicodeString FileName, System::UnicodeString &TargetName)/* overload */;
	static void __fastcall Move(System::UnicodeString SourceFileName, System::UnicodeString DestFileName);
	static System::Classes::TFileStream* __fastcall Open(const System::UnicodeString Path, const TFileMode Mode)/* overload */;
	static System::Classes::TFileStream* __fastcall Open(const System::UnicodeString Path, const TFileMode Mode, const TFileAccess Access)/* overload */;
	static System::Classes::TFileStream* __fastcall Open(const System::UnicodeString Path, const TFileMode Mode, const TFileAccess Access, const TFileShare Share)/* overload */;
	static System::Classes::TFileStream* __fastcall OpenRead(const System::UnicodeString Path);
	static System::Classes::TStreamReader* __fastcall OpenText(const System::UnicodeString Path);
	static System::Classes::TFileStream* __fastcall OpenWrite(const System::UnicodeString Path);
	static System::TArray__1<System::Byte> __fastcall ReadAllBytes(const System::UnicodeString Path);
	static System::TArray__1<System::UnicodeString> __fastcall ReadAllLines(const System::UnicodeString Path)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall ReadAllLines(const System::UnicodeString Path, System::Sysutils::TEncoding* const Encoding)/* overload */;
	static System::UnicodeString __fastcall ReadAllText(const System::UnicodeString Path)/* overload */;
	static System::UnicodeString __fastcall ReadAllText(const System::UnicodeString Path, System::Sysutils::TEncoding* const Encoding)/* overload */;
	static void __fastcall Replace(const System::UnicodeString SourceFileName, const System::UnicodeString DestinationFileName, const System::UnicodeString DestinationBackupFileName)/* overload */;
	static void __fastcall SetAttributes(const System::UnicodeString Path, const TFileAttributes Attributes);
	static void __fastcall SetCreationTime(const System::UnicodeString Path, const System::TDateTime CreationTime);
	static void __fastcall SetCreationTimeUtc(const System::UnicodeString Path, const System::TDateTime CreationTime);
	static void __fastcall SetLastAccessTime(const System::UnicodeString Path, const System::TDateTime LastAccessTime);
	static void __fastcall SetLastAccessTimeUtc(const System::UnicodeString Path, const System::TDateTime LastAccessTime);
	static void __fastcall SetLastWriteTime(const System::UnicodeString Path, const System::TDateTime LastWriteTime);
	static void __fastcall SetLastWriteTimeUtc(const System::UnicodeString Path, const System::TDateTime LastWriteTime);
	static void __fastcall WriteAllBytes(const System::UnicodeString Path, const System::TArray__1<System::Byte> Bytes);
	static void __fastcall WriteAllLines(const System::UnicodeString Path, const System::TArray__1<System::UnicodeString> Contents)/* overload */;
	static void __fastcall WriteAllLines(const System::UnicodeString Path, const System::TArray__1<System::UnicodeString> Contents, System::Sysutils::TEncoding* const Encoding)/* overload */;
	static void __fastcall WriteAllText(const System::UnicodeString Path, const System::UnicodeString Contents)/* overload */;
	static void __fastcall WriteAllText(const System::UnicodeString Path, const System::UnicodeString Contents, System::Sysutils::TEncoding* const Encoding)/* overload */;
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ioutils */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_IOUTILS)
using namespace System::Ioutils;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_IoutilsHPP
