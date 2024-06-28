// filesystem experimental header

// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once
#ifndef _EXPERIMENTAL_FILESYSTEM_
#define _EXPERIMENTAL_FILESYSTEM_
#include <yvals_core.h>
#if _STL_COMPILER_PREPROCESSOR

#include <__msvc_chrono.hpp> // for chrono::time_point
#include <algorithm> // for replace
#include <codecvt> // for codecvt_utf8_*
#include <list> // for recursive_directory_iterator stack
#include <locale> // for wstring_convert
#include <memory> // for shared_ptr
#include <vector> // for canonical's .. handling

#pragma pack(push, _CRT_PACKING)
#pragma warning(push, _STL_WARNING_LEVEL)
#pragma warning(disable : _STL_DISABLED_WARNINGS)
_STL_DISABLE_CLANG_WARNINGS
#pragma push_macro("new")
#undef new

#ifndef _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#error The <experimental/filesystem> header providing std::experimental::filesystem is deprecated by Microsoft \
and will be REMOVED. It is superseded by the C++17 <filesystem> header providing std::filesystem. \
You can define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING to acknowledge that you have received this warning.
#endif // _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#pragma warning(disable : 4365) // conversion from 'type_1' to 'type_2', signed/unsigned mismatch (/Wall)

#ifndef _FS_DLL
#define _FS_DLL extern "C" _CRTIMP2_PURE
#endif // _FS_DLL

#define _MAX_FILESYS_NAME 260 // longest Windows or Posix filename + 1

#define _FS_BEGIN              \
    _STD_BEGIN                 \
    namespace experimental {   \
        namespace filesystem { \
            inline namespace v1 {
#define _FS_END \
    }           \
    }           \
    }           \
    _STD_END
#define _FSPFX _STD experimental::filesystem::v1::

_FS_BEGIN
using _Pchar = wchar_t; // UTF16
#define _FS_ISSEP(x) ((x) == L'/' || (x) == L'\\')
#define _FS_PREF     L'\\'

#define _FS_COLON  L':'
#define _FS_PERIOD L'.'
#define _FS_SLASH  L'/'
#define _FS_BSLASH L'\\'

struct _Char8_t; // flag for UTF8

enum class file_type { // names for file types
    not_found = -1,
    none,
    regular,
    directory,
    symlink,
    block,
    character,
    fifo,
    socket,
    unknown
};

enum class copy_options { // names for copy options
    none                                  = 0,
    skip_existing                         = 1,
    overwrite_existing                    = 2,
    update_existing                       = 4,
    recursive                             = 8,
    copy_symlinks                         = 16,
    skip_symlinks                         = 32,
    directories_only                      = 64,
    create_symlinks                       = 128,
    create_hard_links                     = 256,
    _Unspecified_recursion_prevention_tag = 512
};

_BITMASK_OPS(copy_options)

enum class directory_options { // names for directory options
    none = 0,
    follow_directory_symlink
};

enum class perms { // names for permissions
    none             = 0,
    owner_read       = 0400, // S_IRUSR
    owner_write      = 0200, // S_IWUSR
    owner_exec       = 0100, // S_IXUSR
    owner_all        = 0700, // S_IRWXU
    group_read       = 040, // S_IRGRP
    group_write      = 020, // S_IWGRP
    group_exec       = 010, // S_IXGRP
    group_all        = 070, // S_IRWXG
    others_read      = 04, // S_IROTH
    others_write     = 02, // S_IWOTH
    others_exec      = 01, // S_IXOTH
    others_all       = 07, // S_IRWXO
    all              = 0777,
    set_uid          = 04000, // S_ISUID
    set_gid          = 02000, // S_ISGID
    sticky_bit       = 01000, // S_ISVTX
    mask             = 07777,
    unknown          = 0xFFFF,
    add_perms        = 0x10000,
    remove_perms     = 0x20000,
    resolve_symlinks = 0x40000
};

_BITMASK_OPS(perms)

class file_status { // stores file status
public:
    explicit file_status(file_type _Ftype = file_type::none, perms _Prms = perms::unknown) noexcept
        : _Myftype(_Ftype), _Myperms(_Prms) {}

    file_status(const file_status&) noexcept = default;
    file_status& operator=(const file_status&) noexcept = default;

    file_status(file_status&&) = default;
    file_status& operator=(file_status&&) = default;

    _NODISCARD file_type type() const noexcept {
        return _Myftype;
    }

    _NODISCARD perms permissions() const noexcept {
        return _Myperms;
    }

    void type(file_type _Ftype) noexcept {
        _Myftype = _Ftype;
    }

    void permissions(perms _Prms) noexcept {
        _Myperms = _Prms;
    }

private:
    file_type _Myftype;
    perms _Myperms;
};

struct space_info { // space information for a file
    uintmax_t capacity;
    uintmax_t free;
    uintmax_t available;
};

// wide filenames
_FS_DLL void* __CLRCALL_PURE_OR_CDECL _Open_dir(wchar_t (&)[_MAX_FILESYS_NAME], const wchar_t*, int&, file_type&);
_FS_DLL wchar_t* __CLRCALL_PURE_OR_CDECL _Read_dir(wchar_t (&)[_MAX_FILESYS_NAME], void*, file_type&);
_FS_DLL void __CLRCALL_PURE_OR_CDECL _Close_dir(void*);
_FS_DLL bool __CLRCALL_PURE_OR_CDECL _Current_get(wchar_t (&)[_MAX_FILESYS_NAME]);
_FS_DLL bool __CLRCALL_PURE_OR_CDECL _Current_set(const wchar_t*);
_FS_DLL wchar_t* __CLRCALL_PURE_OR_CDECL _Symlink_get(wchar_t (&)[_MAX_FILESYS_NAME], const wchar_t*);
_FS_DLL wchar_t* __CLRCALL_PURE_OR_CDECL _Temp_get(wchar_t (&)[_MAX_FILESYS_NAME]);

_FS_DLL int __CLRCALL_PURE_OR_CDECL _Make_dir(const wchar_t*, const wchar_t*);
_FS_DLL bool __CLRCALL_PURE_OR_CDECL _Remove_dir(const wchar_t*);

_FS_DLL file_type __CLRCALL_PURE_OR_CDECL _Stat(const wchar_t*, perms*);
_FS_DLL file_type __CLRCALL_PURE_OR_CDECL _Lstat(const wchar_t*, perms*);
_FS_DLL uintmax_t __CLRCALL_PURE_OR_CDECL _File_size(const wchar_t*);
_FS_DLL uintmax_t __CLRCALL_PURE_OR_CDECL _Hard_links(const wchar_t*);
_FS_DLL int64_t __CLRCALL_PURE_OR_CDECL _Last_write_time(const wchar_t*);
_FS_DLL int __CLRCALL_PURE_OR_CDECL _Set_last_write_time(const wchar_t*, int64_t);
_FS_DLL space_info __CLRCALL_PURE_OR_CDECL _Statvfs(const wchar_t*);
_FS_DLL int __CLRCALL_PURE_OR_CDECL _Equivalent(const wchar_t*, const wchar_t*);

_FS_DLL int __CLRCALL_PURE_OR_CDECL _Link(const wchar_t*, const wchar_t*);
_FS_DLL int __CLRCALL_PURE_OR_CDECL _Symlink(const wchar_t*, const wchar_t*);
_FS_DLL int __CLRCALL_PURE_OR_CDECL _Rename(const wchar_t*, const wchar_t*);
_FS_DLL int __CLRCALL_PURE_OR_CDECL _Resize(const wchar_t*, uintmax_t);
_FS_DLL int __CLRCALL_PURE_OR_CDECL _Unlink(const wchar_t*);
_FS_DLL int __CLRCALL_PURE_OR_CDECL _Copy_file(const wchar_t*, const wchar_t*);
_FS_DLL int __CLRCALL_PURE_OR_CDECL _Chmod(const wchar_t*, perms);

template <class _Inchar, class _Outchar, class _Outtraits = char_traits<_Outchar>,
    class _Outalloc = allocator<_Outchar>>
struct _Path_cvt { // converts among {char, wchar_t, UTF8, char16_t, char32_t} paths
    using _Outstr = basic_string<_Outchar, _Outtraits, _Outalloc>;
    static _Outstr&& _Cvt(_Outstr& _Str, const _Inchar* _First, size_t _Size,
        _Unused_parameter = {}) { // convert _Inchar sequence to _Outchar one-to-one
        for (; 0 < _Size; --_Size, ++_First) {
            _Str.push_back(static_cast<_Outchar>(*_First));
        }

        return _STD move(_Str);
    }
};

template <class _Outchar, class _Outtraits, class _Outalloc>
struct _Path_cvt<_Outchar, _Outchar, _Outtraits,
    _Outalloc> { // converts among {char, wchar_t, UTF8, char16_t, char32_t} paths
    using _Outstr = basic_string<_Outchar, _Outtraits, _Outalloc>;
    static _Outstr&& _Cvt(_Outstr& _Str, const _Outchar* _First, size_t _Size,
        _Unused_parameter = {}) { // copy _Outchar sequence to _Outchar one-to-one
        return _STD move(_Str.append(_First, _First + _Size));
    }
};

_STL_DISABLE_DEPRECATED_WARNING
template <class _Outtraits, class _Outalloc>
struct _Path_cvt<char, char16_t, _Outtraits,
    _Outalloc> { // converts among {char, wchar_t, UTF8, char16_t, char32_t} paths
    using _Inchar  = char;
    using _Outchar = char16_t;
    using _Outstr  = basic_string<_Outchar, _Outtraits, _Outalloc>;
    static _Outstr&& _Cvt(_Outstr& _Str, const _Inchar* _First, size_t _Size,
        _Unused_parameter = {}) { // convert char sequence to char16_t string
        wstring_convert<codecvt_utf8_utf16<_Outchar>, _Outchar> _Wcvt;
        return _STD move(_Str.append(_Wcvt.from_bytes(_First, _First + _Size)));
    }
};

template <class _Outtraits, class _Outalloc>
struct _Path_cvt<char16_t, char, _Outtraits,
    _Outalloc> { // converts among {char, wchar_t, UTF8, char16_t, char32_t} paths
    using _Inchar  = char16_t;
    using _Outchar = char;
    using _Outstr  = basic_string<_Outchar, _Outtraits, _Outalloc>;
    static _Outstr&& _Cvt(_Outstr& _Str, const _Inchar* _First, size_t _Size,
        _Unused_parameter = {}) { // convert char16_t sequence to char string
        wstring_convert<codecvt_utf8_utf16<_Inchar>, _Inchar> _Wcvt;
        return _STD move(_Str.append(_Wcvt.to_bytes(_First, _First + _Size)));
    }
};

template <class _Outtraits, class _Outalloc>
struct _Path_cvt<char, char32_t, _Outtraits,
    _Outalloc> { // converts among {char, wchar_t, UTF8, char16_t, char32_t} paths
    using _Inchar  = char;
    using _Outchar = char32_t;
    using _Outstr  = basic_string<_Outchar, _Outtraits, _Outalloc>;
    static _Outstr&& _Cvt(_Outstr& _Str, const _Inchar* _First, size_t _Size,
        _Unused_parameter = {}) { // convert char sequence to char32_t string
        wstring_convert<codecvt_utf8<_Outchar>, _Outchar> _Wcvt;
        return _STD move(_Str.append(_Wcvt.from_bytes(_First, _First + _Size)));
    }
};

template <class _Outtraits, class _Outalloc>
struct _Path_cvt<char32_t, char, _Outtraits,
    _Outalloc> { // converts among {char, wchar_t, UTF8, char16_t, char32_t} paths
    using _Inchar  = char32_t;
    using _Outchar = char;
    using _Outstr  = basic_string<_Outchar, _Outtraits, _Outalloc>;
    static _Outstr&& _Cvt(_Outstr& _Str, const _Inchar* _First, size_t _Size,
        _Unused_parameter = {}) { // convert char32_t sequence to char string
        wstring_convert<codecvt_utf8<_Inchar>, _Inchar> _Wcvt;
        return _STD move(_Str.append(_Wcvt.to_bytes(_First, _First + _Size)));
    }
};

_FS_DLL int __CLRCALL_PURE_OR_CDECL _To_byte(const wchar_t*, char*);
_FS_DLL int __CLRCALL_PURE_OR_CDECL _To_wide(const char*, wchar_t*);

template <class _Outtraits, class _Outalloc>
struct _Path_cvt<char, wchar_t, _Outtraits,
    _Outalloc> { // converts among {char, wchar_t, UTF8, char16_t, char32_t} paths
    using _Inchar  = char;
    using _Outchar = wchar_t;
    using _Outstr  = basic_string<_Outchar, _Outtraits, _Outalloc>;
    static _Outstr&& _Cvt(_Outstr& _Str, const _Inchar* _First,
        size_t) { // convert char sequence to wchar_t string -- Windows
        _Outchar _Fname_wide[_MAX_FILESYS_NAME];
        if (_To_wide(_First, _Fname_wide) == 0) {
            _Xinvalid_argument("invalid char filename argument");
        }

        return _STD move(_Str.append(&_Fname_wide[0]));
    }

    static _Outstr&& _Cvt(_Outstr& _Str, const _Inchar* _First, size_t _Size,
        const locale& _Loc) { // convert char sequence to wchar_t string, locale -- Windows
        using _Mycvt = codecvt<_Outchar, _Inchar, _Mbstatet>;
        wstring_convert<_Mycvt> _Wcvt(&_STD use_facet<_Mycvt>(_Loc));
        return _STD move(_Str.append(_Wcvt.from_bytes(_First, _First + _Size)));
    }
};

template <class _Outtraits, class _Outalloc>
struct _Path_cvt<wchar_t, char, _Outtraits,
    _Outalloc> { // converts among {char, wchar_t, UTF8, char16_t, char32_t} paths
    using _Inchar  = wchar_t;
    using _Outchar = char;
    using _Outstr  = basic_string<_Outchar, _Outtraits, _Outalloc>;
    static _Outstr&& _Cvt(_Outstr& _Str, const _Inchar* _First,
        size_t) { // convert wchar_t sequence to char string -- Windows
        _Outchar _Fname_byte[_MAX_FILESYS_NAME];
        if (_To_byte(_First, _Fname_byte) == 0) {
            _Xinvalid_argument("invalid wchar_t filename argument");
        }

        return _STD move(_Str.append(&_Fname_byte[0]));
    }

    static _Outstr&& _Cvt(_Outstr& _Str, const _Inchar* _First, size_t _Size,
        const locale& _Loc) { // convert wchar_t sequence to char string, locale -- Windows
        using _Mycvt = codecvt<_Inchar, _Outchar, _Mbstatet>;
        wstring_convert<_Mycvt> _Wcvt(&_STD use_facet<_Mycvt>(_Loc));
        return _STD move(_Str.append(_Wcvt.to_bytes(_First, _First + _Size)));
    }
};

template <>
struct _Path_cvt<char, _Char8_t, char_traits<char>,
    allocator<char>> { // converts among {char, wchar_t, UTF8, char16_t, char32_t} paths
    using _Inchar    = char;
    using _Outchar   = char;
    using _Outtraits = char_traits<_Outchar>;
    using _Outalloc  = allocator<_Outchar>;
    using _Outstr    = basic_string<_Outchar, _Outtraits, _Outalloc>;
    static _Outstr&& _Cvt(_Outstr& _Str, const _Inchar* _First, size_t,
        _Unused_parameter = {}) { // convert char sequence to UTF8 string -- Windows
        wchar_t _Fname_wide[_MAX_FILESYS_NAME];
        if (_To_wide(_First, _Fname_wide) == 0) {
            _Xinvalid_argument("invalid char filename argument");
        }

        wstring_convert<codecvt_utf8<wchar_t>, wchar_t> _Wcvt;
        wchar_t* _Last1 = &_Fname_wide[0];
        while (*_Last1 != L'\0') {
            ++_Last1;
        }

        return _STD move(_Str.append(_Wcvt.to_bytes(&_Fname_wide[0], _Last1)));
    }
};

template <class _Outtraits, class _Outalloc>
struct _Path_cvt<_Char8_t, char, _Outtraits,
    _Outalloc> { // converts among {char, wchar_t, UTF8, char16_t, char32_t} paths
    using _Inchar  = char;
    using _Outchar = char;
    using _Outstr  = basic_string<_Outchar, _Outtraits, _Outalloc>;
    static _Outstr&& _Cvt(_Outstr& _Str, const _Inchar* _First, size_t _Size,
        _Unused_parameter = {}) { // convert UTF8 sequence to char string -- Windows
        wstring_convert<codecvt_utf8_utf16<wchar_t>, wchar_t> _Wcvt;
        wstring _Str0(_Wcvt.from_bytes(_First, _First + _Size));

        _Outchar _Fname_byte[_MAX_FILESYS_NAME];
        if (_To_byte(_Str0.c_str(), _Fname_byte) == 0) {
            _Xinvalid_argument("invalid UTF8 filename argument");
        }

        return _STD move(_Str.append(&_Fname_byte[0]));
    }
};

template <>
struct _Path_cvt<wchar_t, _Char8_t, char_traits<char>,
    allocator<char>> { // converts among {char, wchar_t, UTF8, char16_t, char32_t} paths
    using _Inchar    = wchar_t;
    using _Outchar   = char;
    using _Outtraits = char_traits<_Outchar>;
    using _Outalloc  = allocator<_Outchar>;
    using _Outstr    = basic_string<_Outchar, _Outtraits, _Outalloc>;
    static _Outstr&& _Cvt(_Outstr& _Str, const _Inchar* _First, size_t _Size,
        _Unused_parameter = {}) { // convert wchar_t sequence to UTF8 string -- Windows
        wstring_convert<codecvt_utf8<_Inchar>, _Inchar> _Wcvt;
        return _STD move(_Str.append(_Wcvt.to_bytes(_First, _First + _Size)));
    }
};

template <class _Outtraits, class _Outalloc>
struct _Path_cvt<_Char8_t, wchar_t, _Outtraits,
    _Outalloc> { // converts among {char, wchar_t, UTF8, char16_t, char32_t} paths
    using _Inchar  = char;
    using _Outchar = wchar_t;
    using _Outstr  = basic_string<_Outchar, _Outtraits, _Outalloc>;
    static _Outstr&& _Cvt(_Outstr& _Str, const _Inchar* _First, size_t _Size,
        _Unused_parameter = {}) { // convert UTF8 sequence to wchar_t string -- Windows
        wstring_convert<codecvt_utf8<_Outchar>, _Outchar> _Wcvt;
        return _STD move(_Str.append(_Wcvt.from_bytes(_First, _First + _Size)));
    }
};

// struct _Path_cvt<wchar_t, char16_t, _Outtraits, _Outalloc> Windows (copy)
// struct _Path_cvt<char16_t, wchar_t, _Outtraits, _Outalloc> Windows (copy)

template <class _Outtraits, class _Outalloc>
struct _Path_cvt<wchar_t, char32_t, _Outtraits,
    _Outalloc> { // converts among {char, wchar_t, UTF8, char16_t, char32_t} paths
    using _Inchar  = wchar_t;
    using _Outchar = char32_t;
    using _Outstr  = basic_string<_Outchar, _Outtraits, _Outalloc>;
    static _Outstr&& _Cvt(_Outstr& _Str, const _Inchar* _First, size_t _Size,
        _Unused_parameter = {}) { // convert wchar_t sequence to char32_t string -- Windows
        wstring_convert<codecvt_utf8_utf16<_Inchar>, _Inchar> _Wcvt0;
        _STD string _Str0(_Wcvt0.to_bytes(_First, _First + _Size));

        wstring_convert<codecvt_utf8<_Outchar>, _Outchar> _Wcvt;
        return _STD move(_Str.append(_Wcvt.from_bytes(_Str0)));
    }
};

template <class _Outtraits, class _Outalloc>
struct _Path_cvt<char32_t, wchar_t, _Outtraits,
    _Outalloc> { // converts among {char, wchar_t, UTF8, char16_t, char32_t} paths
    using _Inchar  = char32_t;
    using _Outchar = wchar_t;
    using _Outstr  = basic_string<_Outchar, _Outtraits, _Outalloc>;
    static _Outstr&& _Cvt(_Outstr& _Str, const _Inchar* _First, size_t _Size,
        _Unused_parameter = {}) { // convert char32_t sequence to wchar_t string -- Windows
        wstring_convert<codecvt_utf8<_Inchar>, _Inchar> _Wcvt0;
        _STD string _Str0(_Wcvt0.to_bytes(_First, _First + _Size));

        wstring_convert<codecvt_utf8_utf16<_Outchar>, _Outchar> _Wcvt;
        return _STD move(_Str.append(_Wcvt.from_bytes(_Str0)));
    }
};
_STL_RESTORE_DEPRECATED_WARNING

class path;
path operator/(const path&, const path&);

path _Absolute(const path&, const path&, error_code&);
// path absolute(const path&, const path& = current_path());

void _Canonicalize_string_only(path&, const path&);
// path canonical(const path&, const path& _Base = current_path());
path canonical(const path&, error_code&);
path canonical(const path&, const path&, error_code&);

void copy(const path&, const path&);
void copy(const path&, const path&, error_code&) noexcept;
void copy(const path&, const path&, copy_options);
void copy(const path&, const path&, copy_options, error_code&) noexcept;

bool copy_file(const path&, const path&, copy_options = copy_options::none);
bool copy_file(const path&, const path&, error_code&) noexcept;
bool copy_file(const path&, const path&, copy_options, error_code&) noexcept;

void copy_symlink(const path&, const path&);
void copy_symlink(const path&, const path&, error_code&) noexcept;

bool create_directories(const path&);
bool create_directories(const path&, error_code&) noexcept;

bool create_directory(const path&);
bool create_directory(const path&, error_code&) noexcept;
bool create_directory(const path&, const path&);
bool create_directory(const path&, const path&, error_code&) noexcept;

void create_directory_symlink(const path&, const path&);
void create_directory_symlink(const path&, const path&, error_code&) noexcept;

void create_hard_link(const path&, const path&);
void create_hard_link(const path&, const path&, error_code&) noexcept;

void create_symlink(const path&, const path&);
void create_symlink(const path&, const path&, error_code&) noexcept;

path current_path();
path current_path(error_code&);
void current_path(const path&);
void current_path(const path&, error_code&) noexcept;

bool equivalent(const path&, const path&);
bool equivalent(const path&, const path&, error_code&) noexcept;

bool exists(file_status) noexcept;
bool exists(const path&);
bool exists(const path&, error_code&) noexcept;

uintmax_t file_size(const path&);
uintmax_t file_size(const path&, error_code&) noexcept;

uintmax_t hard_link_count(const path&);
uintmax_t hard_link_count(const path&, error_code&) noexcept;

bool is_block_file(file_status) noexcept;
bool is_block_file(const path&);
bool is_block_file(const path&, error_code&) noexcept;

bool is_character_file(file_status) noexcept;
bool is_character_file(const path&);
bool is_character_file(const path&, error_code&) noexcept;

bool is_directory(file_status) noexcept;
bool is_directory(const path&);
bool is_directory(const path&, error_code&) noexcept;

bool is_empty(const path&);
bool is_empty(const path&, error_code&) noexcept;

bool is_fifo(file_status) noexcept;
bool is_fifo(const path&);
bool is_fifo(const path&, error_code&) noexcept;

bool is_other(file_status) noexcept;
bool is_other(const path&);
bool is_other(const path&, error_code&) noexcept;

bool is_regular_file(file_status) noexcept;
bool is_regular_file(const path&);
bool is_regular_file(const path&, error_code&) noexcept;

bool is_socket(file_status) noexcept;
bool is_socket(const path&);
bool is_socket(const path&, error_code&) noexcept;

bool is_symlink(file_status) noexcept;
bool is_symlink(const path&);
bool is_symlink(const path&, error_code&) noexcept;

using file_time_type = chrono::system_clock::time_point;

file_time_type last_write_time(const path&, error_code&) noexcept;
file_time_type last_write_time(const path&);
void last_write_time(const path&, file_time_type, error_code&) noexcept;
void last_write_time(const path&, file_time_type);

void permissions(const path&, perms);
void permissions(const path&, perms, error_code&);

path read_symlink(const path&);
path read_symlink(const path&, error_code&);

bool remove(const path&);
bool remove(const path&, error_code&) noexcept;

uintmax_t remove_all(const path&);
uintmax_t remove_all(const path&, error_code&) noexcept;

void rename(const path&, const path&);
void rename(const path&, const path&, error_code&) noexcept;

void resize_file(const path&, uintmax_t);
void resize_file(const path&, uintmax_t, error_code&) noexcept;

space_info space(const path&);
space_info space(const path&, error_code&) noexcept;

file_status status(const path&);
file_status status(const path&, error_code&) noexcept;

bool status_known(file_status) noexcept;

file_status symlink_status(const path&);
file_status symlink_status(const path&, error_code&) noexcept;

path system_complete(const path&);
path system_complete(const path&, error_code&);

path temp_directory_path();
path temp_directory_path(error_code&);

template <class _Path_type>
class _Path_iterator {
public:
    using path_type   = _Path_type;
    using string_type = typename _Path_type::string_type;

    using iterator_category = bidirectional_iterator_tag;
    using value_type        = path_type;
    using difference_type   = ptrdiff_t;
    using pointer           = const value_type*;
    using reference         = const value_type&;

    _Path_iterator() : _Myptr(nullptr), _Myoff(0) {}

    _Path_iterator(const path_type& _Path, size_t _Off) : _Myptr(&_Path), _Myoff(_Off) {
        _Getval();
    }

    _Path_iterator(const _Path_iterator& _Right)
        : _Myptr(_Right._Myptr), _Myelem(_Right._Myelem), _Myoff(_Right._Myoff) {}

    _Path_iterator& operator=(const _Path_iterator& _Right) {
        _Myptr  = _Right._Myptr;
        _Myelem = _Right._Myelem;
        _Myoff  = _Right._Myoff;
        return *this;
    }

    _Path_iterator(_Path_iterator&& _Right) noexcept
        : _Myptr(_Right._Myptr), _Myelem(_STD move(_Right._Myelem)), _Myoff(_Right._Myoff) {}

    _Path_iterator& operator=(_Path_iterator&& _Right) noexcept {
        _Myptr  = _Right._Myptr;
        _Myelem = _STD move(_Right._Myelem);
        _Myoff  = _Right._Myoff;
        return *this;
    }

    _NODISCARD reference operator*() const {
        return _Myelem;
    }

    _NODISCARD pointer operator->() const {
        return pointer_traits<pointer>::pointer_to(**this);
    }

    _Path_iterator& operator++() {
#if _ITERATOR_DEBUG_LEVEL != 0
        _STL_VERIFY(_Myptr && _Myoff < _Myptr->_Mystr.size(), "path::iterator is not incrementable");
#endif // _ITERATOR_DEBUG_LEVEL != 0

        const size_t _Pend = _Myptr->_Prefix_end();
        const size_t _Size = _Myptr->_Mystr.size();

        if (_Myoff < _Pend) {
            _Myoff = _Pend; // point past "x:"
        } else if (_Myoff == _Pend && _Pend < _Size
                   && _FS_ISSEP(_Myptr->_Mystr[_Pend])) { // point past root "/" and following slashes
            for (++_Myoff; _Myoff < _Size; ++_Myoff) {
                if (!_FS_ISSEP(_Myptr->_Mystr[_Myoff])) {
                    break;
                }
            }
        } else { // point past slashes followed by stuff
            for (; _Myoff < _Size; ++_Myoff) {
                if (!_FS_ISSEP(_Myptr->_Mystr[_Myoff])) {
                    break;
                }
            }
            for (; _Myoff < _Size; ++_Myoff) {
                if (_FS_ISSEP(_Myptr->_Mystr[_Myoff])) {
                    break;
                }
            }
        }
        _Getval();
        return *this;
    }

    _Path_iterator operator++(int) {
        _Path_iterator _Tmp = *this;
        ++*this;
        return _Tmp;
    }

    _Path_iterator& operator--() {
#if _ITERATOR_DEBUG_LEVEL != 0
        _STL_VERIFY(_Myptr && _Myoff != 0, "path::iterator is not decrementable");
#endif // _ITERATOR_DEBUG_LEVEL != 0

        const size_t _Myoff_sav = _Myoff;
        size_t _Off_back        = 0;
        _Myoff                  = 0;
        do { // scan down to previous
            _Off_back = _Myoff;
            ++*this;
        } while (_Myoff < _Myoff_sav);
        _Myoff = _Off_back;
        _Getval();
        return *this;
    }

    _Path_iterator operator--(int) {
        _Path_iterator _Tmp = *this;
        --*this;
        return _Tmp;
    }

    _NODISCARD bool operator==(const _Path_iterator& _Right) const {
        return _Myptr == _Right._Myptr && _Myoff == _Right._Myoff;
    }

    _NODISCARD bool operator!=(const _Path_iterator& _Right) const {
        return !(*this == _Right);
    }

private:
    void _Getval() { // determine _Myelem
        string_type _Str;
        const size_t _Pend = _Myptr->_Prefix_end();
        const size_t _Size = _Myptr->_Mystr.size();

        if (_Size > _Myoff) {
            if (_Myoff < _Pend) {
                _Str = _Myptr->_Mystr.substr(0, _Pend); // get "x:"
            } else if (_Myoff == _Pend && _Pend < _Size && _FS_ISSEP(_Myptr->_Mystr[_Pend])) {
                _Str = _FS_PREF; // get "/"
            } else { // determine next field as slashes followed by stuff
                size_t _Nslash = 0;
                size_t _Nstuff = 0;

                for (; _Myoff + _Nslash < _Size; ++_Nslash) {
                    if (!_FS_ISSEP(_Myptr->_Mystr[_Myoff + _Nslash])) {
                        break;
                    }
                }

                for (; _Myoff + _Nslash + _Nstuff < _Size; ++_Nstuff) {
                    if (_FS_ISSEP(_Myptr->_Mystr[_Myoff + _Nslash + _Nstuff])) {
                        break;
                    }
                }

                if (0 < _Nstuff) {
                    _Str = _Myptr->_Mystr.substr(_Myoff + _Nslash, _Nstuff); // get "stuff"
                } else if (0 < _Nslash) {
                    _Str = _FS_PERIOD; // get "."
                }
            }
        }

        _Myelem = _Str;
    }

    const path_type* _Myptr; // pointer to full path
    path_type _Myelem; // current element subpath
    size_t _Myoff; // current offset in full path
};

class path { // stores a pathname
public:
    using value_type  = _Pchar;
    using string_type = basic_string<value_type>;

    static constexpr value_type preferred_separator = _FS_PREF;

    path() {}

    path(const path& _Right) : _Mystr(_Right._Mystr) {}

    template <class _InIt, enable_if_t<_Is_iterator_v<_InIt>, int> = 0>
    path(_InIt _First, _InIt _Last) {
        using _Valty = _Iter_value_t<_InIt>;
        basic_string<_Valty> _Str(_First, _Last);
        string_type _Str_out;
        *this /= _Path_cvt<_Valty, value_type>::_Cvt(_Str_out, _Str.c_str(), _Str.size());
    }

    template <class _InIt, enable_if_t<conjunction_v<negation<is_same<_InIt, path>>, _Is_iterator<_InIt>>, int> = 0>
    path(_InIt _First) {
        using _Valty = _Iter_value_t<_InIt>;
        basic_string<_Valty> _Str;
        for (; *_First != _Valty(0); ++_First) {
            _Str += *_First;
        }

        string_type _Str_out;
        *this /= _Path_cvt<_Valty, value_type>::_Cvt(_Str_out, _Str.c_str(), _Str.size());
    }

    template <class _Elem, class _Traits, class _Alloc>
    path(const basic_string<_Elem, _Traits, _Alloc>& _Str) {
        string_type _Str_out;
        *this /= _Path_cvt<_Elem, value_type>::_Cvt(_Str_out, _Str.c_str(), _Str.size());
    }

    template <class _InIt, enable_if_t<_Is_iterator_v<_InIt>, int> = 0>
    path(_InIt _First, _InIt _Last, const locale& _Loc) {
        using _Valty = _Iter_value_t<_InIt>;
        basic_string<_Valty> _Str(_First, _Last);
        string_type _Str_out;
        *this /= _Path_cvt<_Valty, value_type>::_Cvt(_Str_out, _Str.c_str(), _Str.size(), _Loc);
    }

    template <class _InIt, enable_if_t<_Is_iterator_v<_InIt>, int> = 0>
    path(_InIt _First, const locale& _Loc) {
        using _Valty = _Iter_value_t<_InIt>;
        basic_string<_Valty> _Str;
        for (; *_First != _Valty(0); ++_First) {
            _Str += *_First;
        }

        string_type _Str_out;
        *this /= _Path_cvt<_Valty, value_type>::_Cvt(_Str_out, _Str.c_str(), _Str.size(), _Loc);
    }

    template <class _Elem, class _Traits, class _Alloc>
    path(const basic_string<_Elem, _Traits, _Alloc>& _Str, const locale& _Loc) {
        string_type _Str_out;
        *this /= _Path_cvt<_Elem, value_type>::_Cvt(_Str_out, _Str.c_str(), _Str.size(), _Loc);
    }

    path(path&& _Right) noexcept : _Mystr(_STD move(_Right._Mystr)) {}

    path& operator=(path&& _Right) noexcept {
        _Mystr = _STD move(_Right._Mystr);
        return *this;
    }

    ~path() noexcept {}

    path& operator=(const path& _Right) {
        _Mystr = _Right._Mystr;
        return *this;
    }

    template <class _InIt>
    path& operator=(_InIt _First) {
        return *this = path(_First);
    }

    template <class _Elem, class _Traits, class _Alloc>
    path& operator=(const basic_string<_Elem, _Traits, _Alloc>& _Str) {
        return *this = path(_Str);
    }

    template <class _InIt>
    path& assign(_InIt _First, _InIt _Last) {
        return *this = path(_First, _Last);
    }

    template <class _InIt>
    path& assign(_InIt _First) {
        return *this = path(_First);
    }

    template <class _Elem, class _Traits, class _Alloc>
    path& assign(const basic_string<_Elem, _Traits, _Alloc>& _Str) {
        return *this = path(_Str);
    }

    path& operator/=(const path& _Path) { // append copy
        return append(_Path._Mystr);
    }

    template <class _InIt>
    path& operator/=(_InIt _First) { // append NTCTS, given iterator
        return append(path(_First)._Mystr);
    }

    template <class _Elem, class _Traits, class _Alloc>
    path& operator/=(const basic_string<_Elem, _Traits, _Alloc>& _Str) { // append arbitrary source string
        return append(_Str);
    }

    template <class _InIt>
    path& append(_InIt _First, _InIt _Last) { // append NTCTS
        return append(path(_First, _Last)._Mystr);
    }

    template <class _InIt>
    path& append(_InIt _First) { // append NTCTS
        return append(path(_First)._Mystr);
    }

    template <class _Elem, class _Traits, class _Alloc>
    path& append(const basic_string<_Elem, _Traits, _Alloc>& _Str0) { // append arbitrary source string
        string_type _Str(_Str0.size(), L'\0');
        // convert _Elem and '/' to '\'
        _STD transform(_Str0.begin(), _Str0.end(), _Str.begin(), [](const _Elem _Ch) {
            auto _Wch = static_cast<wchar_t>(_Ch);
            if (_Wch == _FS_SLASH) {
                _Wch = _FS_PREF;
            }

            return _Wch;
        });

        if (0 < _Mystr.size() && 0 < _Str.size() && _Mystr.back() != _FS_COLON && !_FS_ISSEP(_Mystr.back())
            && !_FS_ISSEP(_Str[0])) {
            _Mystr.push_back(_FS_PREF); // add needed separator
        }

        _Mystr.append(_Str);
        return *this;
    }

    path& operator+=(const path& _Path) { // concatenate copy
        return concat(_Path._Mystr);
    }

    template <class _Ty>
    path& operator+=(_Ty _Val) { // concatenate NTCTS, given iterator/element
        return concat(_Val);
    }

    template <class _Elem, class _Traits, class _Alloc>
    path& operator+=(const basic_string<_Elem, _Traits, _Alloc>& _Str) { // concatenate arbitrary source string
        return concat(_Str);
    }

    template <class _Elem>
    path& operator+=(const _Elem* _Ptr) { // concatenate arbitrary NTCTS
        return concat(basic_string<_Elem>(_Ptr));
    }

    template <class _InIt>
    path& concat(_InIt _First, _InIt _Last) { // concatenate NTCTS
        return concat(path(_First, _Last)._Mystr);
    }

    template <class _Elem>
    path& concat(const _Elem* _Ptr) { // concatenate arbitrary NTCTS
        return concat(basic_string<_Elem>(_Ptr));
    }

    template <class _InIt, enable_if_t<_Is_iterator_v<_InIt>, int> = 0>
    path& concat(_InIt _First) { // concatenate NTCTS
        return concat(path(_First)._Mystr);
    }

    template <class _Elem, enable_if_t<!_Is_iterator_v<_Elem>, int> = 0>
    path& concat(_Elem _Val) { // concatenate element
        return concat(path(basic_string<_Elem>(1, _Val))._Mystr);
    }

    template <class _Elem, class _Traits, class _Alloc>
    path& concat(const basic_string<_Elem, _Traits, _Alloc>& _Str) { // concatenate arbitrary source string
        for (const auto& _Ch : _Str) {
            _Mystr.push_back(static_cast<wchar_t>(_Ch));
        }

        return *this;
    }

    void clear() noexcept { // clear the stored string
        _Mystr.clear();
    }

    path& make_preferred() { // convert any '/' to '\'
        _STD replace(_Mystr.begin(), _Mystr.end(), _FS_SLASH, _FS_BSLASH);
        return *this;
    }

    path& remove_filename() { // remove filename (leaf)
        if (!empty() && begin() != --end()) { // leaf to remove, back up over it
            const size_t _Rend = _Root_end();
            size_t _Idx        = _Mystr.size();

            for (; _Rend < _Idx; --_Idx) {
                if (_FS_ISSEP(_Mystr[_Idx - 1])) {
                    break; // back up over stuff at end
                }
            }

            for (; _Rend < _Idx; --_Idx) {
                if (!_FS_ISSEP(_Mystr[_Idx - 1])) {
                    break; // back up over trailing non-root slashes
                }
            }

            _Mystr.erase(_Idx);
        }
        return *this;
    }

    path& replace_filename(const path& _Path) { // replace filename
        remove_filename();
        *this /= _Path;
        return *this;
    }

    path& replace_extension(const path& _Newext = {}) { // replace extension with _Newext
        if (_Newext.empty() || _Newext.c_str()[0] == _FS_PERIOD) {
            *this = parent_path() / path((stem().native() + _Newext.native()));
        } else {
            *this = parent_path() / path((stem().native() + _FS_PERIOD + _Newext.native()));
        }

        return *this;
    }

    void swap(path& _Right) noexcept {
        _Mystr.swap(_Right._Mystr);
    }

    _NODISCARD const string_type& native() const noexcept {
        return _Mystr;
    }

    _NODISCARD _Ret_z_ const value_type* c_str() const noexcept {
        return _Mystr.c_str();
    }

    operator string_type() const {
        return _Mystr;
    }

    template <class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>>
    _NODISCARD basic_string<_Elem, _Traits, _Alloc> string(
        const _Alloc& _Al = _Alloc()) const { // return path as basic_string<_Elem, _Traits, _Alloc>
        basic_string<_Elem, _Traits, _Alloc> _Str(_Al);
        return _Path_cvt<value_type, _Elem>::_Cvt(_Str, _Mystr.c_str(), _Mystr.size());
    }

    _NODISCARD _STD string string() const { // return path as basic_string<char> native
        _STD string _Str;
        return _Path_cvt<value_type, char>::_Cvt(_Str, _Mystr.c_str(), _Mystr.size());
    }

    _NODISCARD _STD wstring wstring() const { // return path as basic_string<wchar_t> native
        _STD wstring _Str;
        return _Path_cvt<value_type, wchar_t>::_Cvt(_Str, _Mystr.c_str(), _Mystr.size());
    }

    _NODISCARD _STD string u8string() const { // return path as basic_string<char> UTF8
        _STD string _Str;
        return _Path_cvt<value_type, _Char8_t, char_traits<char>, allocator<char>>::_Cvt(
            _Str, _Mystr.c_str(), _Mystr.size());
    }

    _NODISCARD _STD u16string u16string() const { // return path as basic_string<char16_t> UTF16
        _STD u16string _Str;
        return _Path_cvt<value_type, char16_t>::_Cvt(_Str, _Mystr.c_str(), _Mystr.size());
    }

    _STD u32string u32string() const = delete; // TRANSITION, ABI
#if 0
                { // return path as basic_string<char32_t> UTF32
                    _STD u32string _Str;
                    return _Path_cvt<value_type, char32_t>::_Cvt(_Str, _Mystr.c_str(), _Mystr.size());
                }
#endif // 0

    string_type _Make_generic() const { // copy and convert any '\' to '/'
        string_type _Str = _Mystr;
        _STD replace(_Str.begin(), _Str.end(), _FS_BSLASH, _FS_SLASH);
        return _Str;
    }

    template <class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>>
    _NODISCARD basic_string<_Elem, _Traits, _Alloc> generic_string(
        const _Alloc& _Al = _Alloc()) const { // return path as basic_string<_Elem, _Traits, _Alloc>
        basic_string<_Elem, _Traits, _Alloc> _Str(_Al);
        const string_type _Genstr = _Make_generic();
        return _Path_cvt<value_type, _Elem>::_Cvt(_Str, _Genstr.c_str(), _Genstr.size());
    }

    _NODISCARD _STD string generic_string() const { // return path as basic_string<char> native
        _STD string _Str;
        const string_type _Genstr = _Make_generic();
        return _Path_cvt<value_type, char>::_Cvt(_Str, _Genstr.c_str(), _Genstr.size());
    }

    _NODISCARD _STD wstring generic_wstring() const { // return path as basic_string<wchar_t> native
        _STD wstring _Str;
        const string_type _Genstr = _Make_generic();
        return _Path_cvt<value_type, wchar_t>::_Cvt(_Str, _Genstr.c_str(), _Genstr.size());
    }

    _NODISCARD _STD string generic_u8string() const { // return path as basic_string<char> UTF8
        _STD string _Str;
        const string_type _Genstr = _Make_generic();
        return _Path_cvt<value_type, _Char8_t, char_traits<char>, allocator<char>>::_Cvt(
            _Str, _Genstr.c_str(), _Genstr.size());
    }

    _NODISCARD _STD u16string generic_u16string() const { // return path as basic_string<char16_t> UTF16
        _STD u16string _Str;
        const string_type _Genstr = _Make_generic();
        return _Path_cvt<value_type, char16_t>::_Cvt(_Str, _Genstr.c_str(), _Genstr.size());
    }

    _STD u32string generic_u32string() const = delete; // TRANSITION, ABI
#if 0
                { // return path as basic_string<char32_t> UTF32
                    _STD u32string _Str;
                    const string_type _Genstr = _Make_generic();
                    return _Path_cvt<value_type, char32_t>::_Cvt(_Str, _Genstr.c_str(), _Genstr.size());
                }
#endif // 0

    _NODISCARD int compare(const path& _Path) const noexcept { // compare native() to _Path.native()
        return _Mystr.compare(_Path._Mystr);
    }

    _NODISCARD int compare(const string_type& _Str) const { // compare native() to string
        return _Mystr.compare(_Str);
    }

    _NODISCARD int compare(const value_type* _Ptr) const { // compare native() to NTCS
        return _Mystr.compare(_Ptr);
    }

    _NODISCARD path root_name() const {
        return path(_Mystr.substr(0, _Prefix_end()));
    }

    _NODISCARD path root_directory() const {
        const size_t _Idx = _Prefix_end();
        if (_Idx < _Mystr.size() && _FS_ISSEP(_Mystr[_Idx])) {
            return path(string_type(1, _FS_PREF));
        } else {
            return {};
        }
    }

    _NODISCARD path root_path() const {
        return path(_Mystr.c_str(), _Mystr.c_str() + _Root_end());
    }

    _NODISCARD path relative_path() const {
        size_t _Idx = _Root_end();
        while (_Idx < _Mystr.size() && _FS_ISSEP(_Mystr[_Idx])) {
            ++_Idx; // skip extra '/' after root
        }

        return path(_Mystr.substr(_Idx));
    }

    _NODISCARD path parent_path() const {
        path _Ans;
        if (!empty()) { // append all but last element
            iterator _End = --end();
            for (iterator _Next = begin(); _Next != _End; ++_Next) {
                _Ans /= *_Next;
            }
        }
        return _Ans;
    }

    _NODISCARD path filename() const {
        return empty() ? path{} : path(*--end());
    }

    _NODISCARD path stem() const { // pick off stem (basename) in filename (leaf) before dot
        string_type _Str0 = filename().native();
        string_type _Str1 = extension().native();
        _Str0.resize(_Str0.size() - _Str1.size());
        return path(_Str0);
    }

    _NODISCARD path extension() const { // pick off .extension in filename (leaf), including dot
        string_type _Str  = filename().native();
        const size_t _Idx = _Str.rfind(_FS_PERIOD);
        return _Idx == string_type::npos // no .
                    || _Str.size() == 1 // only .
                    || (_Str.size() == 2 && _Str[0] == _FS_PERIOD && _Str[1] == _FS_PERIOD) // only ..
                 ? path{}
                 : path(_Str.substr(_Idx));
    }

    _NODISCARD bool empty() const noexcept {
        return _Mystr.empty();
    }

    _NODISCARD bool has_root_name() const {
        return !root_name().empty();
    }

    _NODISCARD bool has_root_directory() const {
        return !root_directory().empty();
    }

    _NODISCARD bool has_root_path() const {
        return !root_path().empty();
    }

    _NODISCARD bool has_relative_path() const {
        return !relative_path().empty();
    }

    _NODISCARD bool has_parent_path() const {
        return !parent_path().empty();
    }

    _NODISCARD bool has_filename() const {
        return !filename().empty();
    }

    _NODISCARD bool has_stem() const {
        return !stem().empty();
    }

    _NODISCARD bool has_extension() const {
        return !extension().empty();
    }

    _NODISCARD bool is_absolute() const {
        return has_root_name() && has_root_directory();
    }

    _NODISCARD bool is_relative() const {
        return !is_absolute();
    }

    using iterator       = _Path_iterator<path>;
    using const_iterator = iterator;

    _NODISCARD iterator begin() const {
        return iterator(*this, 0);
    }

    _NODISCARD iterator end() const {
        return iterator(*this, _Mystr.size());
    }

    size_t _Prefix_end() const {
        if (2 < _Mystr.size() && _FS_ISSEP(_Mystr[0]) && _FS_ISSEP(_Mystr[1])
            && !_FS_ISSEP(_Mystr[2])) { // network name, pick off \\name
            size_t _Idx = 3;
            while (_Idx < _Mystr.size() && !_FS_ISSEP(_Mystr[_Idx])) {
                ++_Idx;
            }

            return _Idx;
        } else { // no network name, pick off drive:
            size_t _Idx = _Mystr.find(_FS_COLON, 0);
            if (_Idx == _Mystr.npos) {
                _Idx = 0;
            } else {
                ++_Idx;
            }

            return _Idx;
        }
    }

    size_t _Root_end() const {
        size_t _Idx = _Prefix_end();
        if (_Idx < _Mystr.size() && _FS_ISSEP(_Mystr[_Idx])) {
            ++_Idx;
        }

        return _Idx;
    }

    string_type _Mystr;
};

inline void swap(path& _Left, path& _Right) noexcept {
    _Left.swap(_Right);
}

_NODISCARD inline size_t hash_value(const path& _Path) noexcept {
    return hash<path::string_type>()(_Path.native());
}

_NODISCARD inline bool operator==(const path& _Left, const path& _Right) noexcept {
    return _Left.native() == _Right.native();
}

_NODISCARD inline bool operator!=(const path& _Left, const path& _Right) noexcept {
    return !(_Left == _Right);
}

_NODISCARD inline bool operator<(const path& _Left, const path& _Right) noexcept {
    return _Left.native() < _Right.native();
}

_NODISCARD inline bool operator<=(const path& _Left, const path& _Right) noexcept {
    return !(_Right < _Left);
}

_NODISCARD inline bool operator>(const path& _Left, const path& _Right) noexcept {
    return _Right < _Left;
}

_NODISCARD inline bool operator>=(const path& _Left, const path& _Right) noexcept {
    return !(_Left < _Right);
}

_NODISCARD inline path operator/(const path& _Left, const path& _Right) { // concatenate paths
    path _Ans = _Left;
    return _Ans /= _Right;
}

template <class _Elem, class _Traits>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr, const path& _Path) { // insert a path
    return _Ostr << _Path.string<_Elem, _Traits, allocator<_Elem>>();
}

template <class _Elem, class _Traits>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr, path& _Path) { // extract a path
    basic_string<_Elem, _Traits> _Str;
    _Istr >> _Str;
    _Path = _Str;
    return _Istr;
}

template <class _InIt, enable_if_t<_Is_iterator_v<_InIt>, int> = 0>
_NODISCARD path u8path(_InIt _First, _InIt _Last) { // make path from [_First, _Last) UTF8, given iterators
    string _Str(_First, _Last);
    path::string_type _Str_out;
    return path(_Path_cvt<_Char8_t, _Pchar>::_Cvt(_Str_out, _Str.c_str(), _Str.size()));
}

template <class _InIt, enable_if_t<_Is_iterator_v<_InIt>, int> = 0>
_NODISCARD path u8path(_InIt _First) { // make path from NTBS UTF8, given iterator
    string _Str;
    for (; *_First != '\0'; ++_First) {
        _Str += *_First;
    }

    path::string_type _Str_out;
    return path(_Path_cvt<_Char8_t, _Pchar>::_Cvt(_Str_out, _Str.c_str(), _Str.size()));
}

template <class _Traits, class _Alloc>
_NODISCARD path u8path(const basic_string<char, _Traits, _Alloc>& _Str) { // make path from arbitrary char string UTF8
    path::string_type _Str_out;
    return path(_Path_cvt<_Char8_t, _Pchar>::_Cvt(_Str_out, _Str.c_str(), _Str.size()));
}

class filesystem_error : public system_error { // base of all filesystem-error exceptions
public:
    explicit filesystem_error(
        const string& _Message, error_code _Errcode = make_error_code(errc::operation_not_permitted))
        : system_error(_Errcode, _Message) {}

    filesystem_error(const string& _Message, const path& _Path1, error_code _Errcode)
        : system_error(_Errcode, _Message), _Mypval1(_Path1) {}

    filesystem_error(const string& _Message, const path& _Path1, const path& _Path2, error_code _Errcode)
        : system_error(_Errcode, _Message), _Mypval1(_Path1), _Mypval2(_Path2) {}

    virtual __CLR_OR_THIS_CALL ~filesystem_error() noexcept {}

    filesystem_error(filesystem_error&& _Right) noexcept
        : system_error(_Right.code(), _Right.what()), _Mypval1(_STD move(_Right._Mypval1)),
          _Mypval2(_STD move(_Right._Mypval2)) {}

    filesystem_error& operator=(filesystem_error&& _Right) noexcept {
        static_cast<system_error&>(*this) = _Right;
        _Mypval1                          = _STD move(_Right._Mypval1);
        _Mypval2                          = _STD move(_Right._Mypval2);
        return *this;
    }

    _NODISCARD const path& path1() const noexcept {
        return _Mypval1;
    }

    _NODISCARD const path& path2() const noexcept {
        return _Mypval2;
    }

    filesystem_error(const filesystem_error&) = default;
    filesystem_error& operator=(const filesystem_error&) = default;

private:
    path _Mypval1;
    path _Mypval2;

#if !_HAS_EXCEPTIONS
protected:
    virtual __CLR_OR_THIS_CALL void _Doraise() const override { // perform class-specific exception handling
        _RAISE(*this);
    }
#endif // !_HAS_EXCEPTIONS
};

[[noreturn]] inline void _Throw_filesystem_error(const char* const _Message) {
    _THROW(filesystem_error{_Message}); // centralize construction of temporary string
}

class directory_entry { // represents a directory entry
public:
    using string_type = _FSPFX path::string_type;

    directory_entry() : _Mystat(), _Mysymstat() {}

    directory_entry(const directory_entry&) = default;
    directory_entry& operator=(const directory_entry&) = default;

    directory_entry(directory_entry&&) = default;
    directory_entry& operator=(directory_entry&&) = default;

    explicit directory_entry(
        const _FSPFX path& _Path, file_status _Statarg = file_status{}, file_status _Symstatarg = file_status{})
        : _Mypval(_Path), _Mystat(_Statarg), _Mysymstat(_Symstatarg) {}

    void assign(
        const _FSPFX path& _Path, file_status _Statarg = file_status{}, file_status _Symstatarg = file_status{}) {
        _Mypval    = _Path;
        _Mystat    = _Statarg;
        _Mysymstat = _Symstatarg;
    }

    void replace_filename(const _FSPFX path& _Path, file_status _Statarg = file_status{},
        file_status _Symstatarg = file_status{}) { // replace filename and assign status
        _Mypval    = _Mypval.parent_path() / _Path;
        _Mystat    = _Statarg;
        _Mysymstat = _Symstatarg;
    }

    operator const _FSPFX path&() const noexcept {
        return _Mypval;
    }

    _NODISCARD const _FSPFX path& path() const noexcept {
        return _Mypval;
    }

    _NODISCARD file_status status() const {
        error_code _Code;
        return status(_Code);
    }

    _NODISCARD file_status status(error_code& _Code) const noexcept {
        _Code.clear();
        if (!status_known(_Mystat)) {
            if (status_known(_Mysymstat) && !is_symlink(_Mysymstat)) {
                _Mystat = _Mysymstat;
            } else {
                _Mystat = _FSPFX status(_Mypval, _Code);
            }
        }

        return _Mystat;
    }

    _NODISCARD file_status symlink_status() const {
        error_code _Code;
        return symlink_status(_Code);
    }

    _NODISCARD file_status symlink_status(error_code& _Code) const noexcept {
        _Code.clear();
        if (!status_known(_Mysymstat)) {
            _Mysymstat = _FSPFX symlink_status(_Mypval, _Code);
        }

        return _Mysymstat;
    }

    _NODISCARD bool operator==(const directory_entry& _Right) const noexcept {
        return _Mypval == _Right._Mypval;
    }

    _NODISCARD bool operator!=(const directory_entry& _Right) const noexcept {
        return !(*this == _Right);
    }

    _NODISCARD bool operator<(const directory_entry& _Right) const noexcept {
        return _Mypval < _Right._Mypval;
    }

    _NODISCARD bool operator>(const directory_entry& _Right) const noexcept {
        return _Right < *this;
    }
    _NODISCARD bool operator<=(const directory_entry& _Right) const noexcept {
        return !(_Right < *this);
    }

    _NODISCARD bool operator>=(const directory_entry& _Right) const noexcept {
        return !(*this < _Right);
    }

private:
    _FSPFX path _Mypval;
    mutable file_status _Mystat;
    mutable file_status _Mysymstat;
};

template <class _Prefix_directory>
class _Directory_iterator {
public:
    using string_type = path::string_type;

    using iterator_category = input_iterator_tag;
    using value_type        = directory_entry;
    using difference_type   = ptrdiff_t;
    using pointer           = const value_type*;
    using reference         = const value_type&;

    _Directory_iterator() noexcept : _Mypdir(new void*(nullptr), &_Delptr) {}

    explicit _Directory_iterator(const path& _Path) : _Mypdir(new void*(nullptr), &_Delptr), _Mydirpath(_Path) {
        typename string_type::value_type _Dest[_MAX_FILESYS_NAME];
        int _Errno = 0;
        file_type _Ftype;

        *_Mypdir = _Open_dir(_Dest, _Path.c_str(), _Errno, _Ftype);
        if (*_Mypdir) {
            _Form_name(_Dest, _Ftype, _Prefix_directory());
        }
    }

    _Directory_iterator(const path& _Path, error_code& _Code) noexcept
        : _Mypdir(new void*(nullptr), &_Delptr), _Mydirpath(_Path) {
        typename string_type::value_type _Dest[_MAX_FILESYS_NAME];
        int _Errno = 0;
        file_type _Ftype;

        *_Mypdir = _Open_dir(_Dest, _Path.c_str(), _Errno, _Ftype);
        if (*_Mypdir) {
            _Form_name(_Dest, _Ftype, _Prefix_directory());
        }

        _Code = error_code(_Errno, _STD system_category());
    }

    _Directory_iterator(const _Directory_iterator&) = default;
    _Directory_iterator& operator=(const _Directory_iterator&) = default;

    _Directory_iterator(_Directory_iterator&&) = default;
    _Directory_iterator& operator=(_Directory_iterator&&) = default;

    _NODISCARD const value_type& operator*() const {
#if _ITERATOR_DEBUG_LEVEL != 0
        _STL_VERIFY(*_Mypdir, "directory_iterator is not dereferenceable");
#endif // _ITERATOR_DEBUG_LEVEL != 0

        return _Myentry;
    }

    _NODISCARD pointer operator->() const {
        return pointer_traits<pointer>::pointer_to(**this);
    }

    _Directory_iterator& operator++() {
#if _ITERATOR_DEBUG_LEVEL != 0
        _STL_VERIFY(*_Mypdir, "directory_iterator is not incrementable");
#endif // _ITERATOR_DEBUG_LEVEL != 0

        _Get();
        return *this;
    }

    _Directory_iterator& increment(error_code& _Code) noexcept {
        _Code.clear();
        if (_Mypdir && *_Mypdir) {
            _Get();
        } else {
            _Code = make_error_code(errc::operation_not_permitted);
        }

        return *this;
    }

    _Directory_iterator operator++(int) {
        _Directory_iterator _Tmp = *this;
        ++*this;
        return _Tmp;
    }

    bool _Equal(const _Directory_iterator& _Right) const {
        if (_Mypdir.get() && _Right._Mypdir.get()) {
            return *_Mypdir == *_Right._Mypdir;
        }

        return !_Mypdir.get() && !_Right._Mypdir.get();
    }

private:
    static void _Delptr(void** _Ptr) { // close directory and delete pointer
        if (_Ptr && *_Ptr) {
            _Close_dir(*_Ptr);
        }

        delete _Ptr;
    }

    void _Get() { // peek at next input element
        if (*_Mypdir) { // read a directory entry
            typename string_type::value_type _Dest[_MAX_FILESYS_NAME];
            file_type _Ftype;
            if (_Read_dir(_Dest, *_Mypdir, _Ftype)[0] == 0) { // end of directory, close it
                _Close_dir(*_Mypdir);
                *_Mypdir = nullptr; // end of directory
            } else {
                _Form_name(_Dest, _Ftype, _Prefix_directory());
            }
        }
    }

    void _Form_name(typename string_type::value_type* _Filename, file_type _Ftype,
        true_type) { // set entry to _Mydirpath/_Filename
        _Myentry.assign(_Mydirpath / path(_Filename), file_status(_Ftype));
    }

    void _Form_name(typename string_type::value_type* _Filename, file_type _Ftype,
        false_type) { // set entry to _Filename
        _Myentry.assign(path(_Filename), file_status(_Ftype));
    }

    shared_ptr<void*> _Mypdir;
    path _Mydirpath;
    value_type _Myentry;
};

template <class _Prefix_directory>
_NODISCARD bool operator==(
    const _Directory_iterator<_Prefix_directory>& _Left, const _Directory_iterator<_Prefix_directory>& _Right) {
    return _Left._Equal(_Right);
}

template <class _Prefix_directory>
_NODISCARD bool operator!=(
    const _Directory_iterator<_Prefix_directory>& _Left, const _Directory_iterator<_Prefix_directory>& _Right) {
    return !(_Left == _Right);
}

using directory_iterator = _Directory_iterator<true_type>;

_NODISCARD inline const directory_iterator& begin(const directory_iterator& _Iter) noexcept {
    return _Iter;
}

_NODISCARD inline directory_iterator end(const directory_iterator&) noexcept {
    return {};
}

class recursive_directory_iterator {
public:
    using _Myiter     = _Directory_iterator<false_type>;
    using _Mypair     = pair<_Myiter, path>;
    using string_type = path::string_type;
    using char_type   = string_type::value_type;

    using iterator_category = input_iterator_tag;
    using value_type        = directory_entry;
    using difference_type   = ptrdiff_t;
    using pointer           = const value_type*;
    using reference         = const value_type&;

    recursive_directory_iterator() noexcept
        : _Mylist(1, _Mypair()), _Myentry(), _No_push(false), _Options(directory_options::none) {}

    explicit recursive_directory_iterator(const path& _Path, directory_options _Opts = directory_options::none)
        : _Mylist(1, _Mypair(_Myiter(_Path), _Path)), _Myentry(), _No_push(false), _Options(_Opts) {
        _Get();
    }

    recursive_directory_iterator(const path& _Path, directory_options _Opts, error_code& _Code) noexcept
        : _Mylist(1, _Mypair(_Myiter(_Path), _Path)), _Myentry(), _No_push(false), _Options(_Opts) {
        _Code.clear();
        _Get();
    }

    recursive_directory_iterator(const path& _Path, error_code& _Code) noexcept
        : _Mylist(1, _Mypair(_Myiter(_Path), _Path)), _Myentry(), _No_push(false), _Options(directory_options::none) {
        _Code.clear();
        _Get();
    }

    recursive_directory_iterator(const recursive_directory_iterator&) = default;
    recursive_directory_iterator& operator=(const recursive_directory_iterator&) = default;

    recursive_directory_iterator(recursive_directory_iterator&&) = default;
    recursive_directory_iterator& operator=(recursive_directory_iterator&&) = default;

    _NODISCARD directory_options options() const {
        return _Options;
    }

    _NODISCARD int depth() const {
        return static_cast<int>(_Mylist.size()) - 1;
    }

    _NODISCARD bool recursion_pending() const {
        return !_No_push;
    }

    void pop() { // pop a level
        if (1 < _Mylist.size()) {
            _Mylist.pop_front(); // something to pop, do it
        }
    }

    void disable_recursion_pending() { // disable directory recursion
        _No_push = true;
    }

    _NODISCARD const value_type& operator*() const {
#if _ITERATOR_DEBUG_LEVEL != 0
        _STL_VERIFY(_Mylist.front().first != _Myiter(), "recursive_directory_iterator is not dereferenceable");
#endif // _ITERATOR_DEBUG_LEVEL != 0

        return _Myentry;
    }

    _NODISCARD pointer operator->() const {
        return pointer_traits<pointer>::pointer_to(**this);
    }

    recursive_directory_iterator& operator++() {
#if _ITERATOR_DEBUG_LEVEL != 0
        _STL_VERIFY(_Mylist.front().first != _Myiter(), "recursive_directory_iterator is not incrementable");
#endif // _ITERATOR_DEBUG_LEVEL != 0

        if (_No_push || !is_directory(_Mylist.front().first->status())
            || (_Options != directory_options::follow_directory_symlink
                && is_symlink(_Mylist.front().first->status()))) {
            _No_push = false;
            ++_Mylist.front().first;
        } else { // push down a subdirectory
            path _Newpath = _Mylist.front().second / _Mylist.front().first->path();
            ++_Mylist.front().first;
            _Mylist.push_front(_Mypair(_Myiter(_Newpath), _Newpath));
        }
        while (1 < _Mylist.size() && _Mylist.front().first == _Myiter()) {
            pop();
        }

        _Get();
        return *this;
    }

    recursive_directory_iterator& increment(error_code& _Code) noexcept {
        _Code.clear();
        if (_Mylist.front().first == _Myiter()) {
            _Code = make_error_code(errc::operation_not_permitted);
        } else {
            ++*this;
        }

        return *this;
    }

    recursive_directory_iterator operator++(int) {
        recursive_directory_iterator _Tmp = *this;
        ++*this;
        return _Tmp;
    }

    bool _Equal(const recursive_directory_iterator& _Right) const {
        return _Mylist.front().first == _Right._Mylist.front().first;
    }

    void _Get() { // prime _Myentry for future gets
        if (_Mylist.front().first != _Myiter()) { // item present, get it
            value_type _Dentry = *_Mylist.front().first;
            _Myentry.assign(_Mylist.front().second / _Dentry.path(), _Dentry.status(), _Dentry.symlink_status());
        }
    }

private:
    list<_Mypair> _Mylist;
    value_type _Myentry;
    bool _No_push;
    directory_options _Options;
};

_NODISCARD inline bool operator==(
    const recursive_directory_iterator& _Left, const recursive_directory_iterator& _Right) {
    return _Left._Equal(_Right);
}

_NODISCARD inline bool operator!=(
    const recursive_directory_iterator& _Left, const recursive_directory_iterator& _Right) {
    return !(_Left == _Right);
}

_NODISCARD inline const recursive_directory_iterator& begin(const recursive_directory_iterator& _Iter) noexcept {
    return _Iter;
}

_NODISCARD inline recursive_directory_iterator end(const recursive_directory_iterator&) noexcept {
    return {};
}

inline path _Absolute(const path& _Path, const path& _Base,
    error_code& _Code) { // make absolute path from _Path and directory _Base; errors in _Code
    _Code.clear();
    const bool _Path_has_root_name      = _Path.has_root_name();
    const bool _Path_has_root_directory = _Path.has_root_directory();
    if (_Path_has_root_name && _Path_has_root_directory) {
        return _Path; // fine as is
    }

    path _Current = current_path(_Code);
    if (_Code) {
        return {};
    }

    path _Abs_base = _Absolute(_Base, _Current, _Code);
    if (_Code) {
        return {};
    }

    if (_Path_has_root_name) { // insert _Base
        return _Path.root_name() / _Abs_base.root_directory() / _Abs_base.relative_path() / _Path.relative_path();
    } else if (_Path_has_root_directory) {
        return _Abs_base.root_name() / _Path; // prepend root name of base
    } else {
        return _Abs_base / _Path; // prepend absolute name of base
    }
}

_NODISCARD inline path absolute(const path& _Path,
    const path& _Base = current_path()) { // make absolute path from _Path and directory _Base
    error_code _Code;
    path _Result = _Absolute(_Path, _Base, _Code);
    if (_Code) {
        _Throw_filesystem_error("absolute(p1, p2): current_path() couldn't get current working directory");
    }

    return _Result;
}

inline void _Canonicalize_string_only(
    path& _Canon_path, const path& _Abs_path) { // transform absolute path _Abs_path, removing .s, and ..s,
                                                // using string manipulations (rather than platform support)
    vector<path> _Components;
    path::const_iterator _Abs_path_next      = _Abs_path.begin();
    const path::const_iterator _Abs_path_end = _Abs_path.end();
    // This is safe because we have already made the path absolute
    _Canon_path /= *_Abs_path_next; // root_name
    ++_Abs_path_next;
    _Canon_path /= *_Abs_path_next; // root_directory
    ++_Abs_path_next;
    for (; _Abs_path_next != _Abs_path_end; ++_Abs_path_next) {
        const auto _Cstr = _Abs_path_next->c_str();
        if (_Cstr[0] == _FS_PERIOD) {
            if (_Cstr[1] == static_cast<path::value_type>(0)) {
                continue; // consume "."
            } else if (_Cstr[1] == _FS_PERIOD && _Cstr[2] == static_cast<path::value_type>(0)) {
                // If no parent is found to remove with .., ignore ..
                // (that is, C:\..\..\..\Meow canonicalizes to C:\Meow)
                if (!_Components.empty()) {
                    _Components.pop_back();
                }

                continue; // consume ".."
            }
        }

        _Components.push_back(*_Abs_path_next);
    }

    for (const auto& _Component : _Components) {
        _Canon_path /= _Component;
    }
}

_NODISCARD inline path canonical(const path& _Path,
    const path& _Base = current_path()) { // make absolute path from _Path, _Base with no ., .., or symlink
    error_code _Code;
    path _Ans = canonical(_Path, _Base, _Code);

    if (_Code) {
        _Throw_filesystem_error("canonical(p1, p2): invalid arguments");
    }

    return _Ans;
}

_NODISCARD inline path canonical(const path& _Path,
    error_code& _Code) { // make absolute path from _Path with no ., .., or symlink
    path _Current = current_path(_Code);
    if (_Code) {
        return {};
    }

    return canonical(_Path, _Current, _Code);
}

_NODISCARD inline path canonical(const path& _Path, const path& _Base,
    error_code& _Code) { // make absolute path from _Path, _Base with no ".", "..", symlink
    _Code.clear();
    path _Canon_path; // NRVO this variable
    path _Abs_path = _Absolute(_Path, _Base, _Code);
    if (_Code) {
        return _Canon_path;
    }

    if (_Abs_path.native().size() >= _MAX_FILESYS_NAME) {
        _Code = make_error_code(errc::filename_too_long);
        return _Canon_path;
    }

    _Canonicalize_string_only(_Canon_path, _Abs_path);
    return _Canon_path;
}

inline bool _Copy_options_indicate_recursive_copy(
    copy_options _Opts) { // Checks a copy_options for whether copy should call itself recursively
    if (_Opts == copy_options::none) {
        // This supports "copying a directory" as copying the directory and
        // files therein but not subdirectories.
        return true;
    }

    if ((_Opts & copy_options::recursive) != copy_options::none) {
        return true;
    }

    return false;
}

inline void copy(const path& _Oldpval, const path& _Newpval) { // copy _Oldpval to _Newpval, general
    error_code _Code;

    copy(_Oldpval, _Newpval, copy_options::none, _Code);
    if (_Code) {
        _Throw_filesystem_error("copy(p1, p2): invalid arguments");
    }
}

inline void copy(const path& _Oldpval, const path& _Newpval,
    error_code& _Code) noexcept { // copy _Oldpval to _Newpval, general
    copy(_Oldpval, _Newpval, copy_options::none, _Code);
}

inline void copy(const path& _Oldpval, const path& _Newpval,
    copy_options _Opts) { // copy _Oldpval to _Newpval, general
    error_code _Code;

    copy(_Oldpval, _Newpval, _Opts, _Code);
    if (_Code) {
        _Throw_filesystem_error("copy(p1, p2, options): invalid arguments");
    }
}

inline void copy(const path& _Oldpval, const path& _Newpval, copy_options _Opts,
    error_code& _Code) noexcept { // copy _Oldpval to _Newpval, general
    file_status _Oldstat;
    file_status _Newstat;
    error_code _Code2;

    _Code.clear();
    if ((_Opts & copy_options::create_symlinks) != copy_options::none
        || (_Opts & copy_options::skip_symlinks) != copy_options::none) { // get symlink status
        _Oldstat = symlink_status(_Oldpval);
        _Newstat = symlink_status(_Newpval);
    } else { // get file status
        _Oldstat = status(_Oldpval);
        _Newstat = status(_Newpval);
    }
    if (!exists(_Oldstat) || equivalent(_Oldpval, _Newpval, _Code2) || is_other(_Oldstat) || is_other(_Newstat)
        || (is_directory(_Oldstat) && is_regular_file(_Newstat))) {
        _Code = make_error_code(errc::operation_not_permitted);
    } else if (is_symlink(_Oldstat)) {
        if ((_Opts & copy_options::skip_symlinks) == copy_options::none) {
            if (exists(_Newstat) || (_Opts & copy_options::copy_symlinks) == copy_options::none) {
                _Code = make_error_code(errc::operation_not_permitted);
            } else {
                copy_symlink(_Oldpval, _Newpval, _Code);
            }
        }
    } else if (is_regular_file(_Oldstat)) {
        if ((_Opts & copy_options::directories_only) == copy_options::none) {
            if ((_Opts & copy_options::create_symlinks) != copy_options::none) {
                create_symlink(_Oldpval, _Newpval, _Code);
            } else if ((_Opts & copy_options::create_hard_links) != copy_options::none) {
                create_hard_link(_Oldpval, _Newpval, _Code);
            } else if (is_directory(_Newstat)) {
                copy_file(_Oldpval, _Newpval / _Oldpval.filename(), _Opts, _Code);
            } else {
                copy_file(_Oldpval, _Newpval, _Opts, _Code);
            }
        }
    } else if (is_directory(_Oldstat) && _Copy_options_indicate_recursive_copy(_Opts)) { // copy directory recursively
        if (!exists(_Newpval) && !create_directory(_Newpval, _Code) && !_Code) {
            _Code = make_error_code(errc::operation_not_permitted);
        }

        for (directory_iterator _Next(_Oldpval), _End; !_Code && _Next != _End; ++_Next) {
            copy(_Next->path(), _Newpval / _Next->path().filename(),
                _Opts | copy_options::_Unspecified_recursion_prevention_tag, _Code);
        }
    }
}

inline bool copy_file(const path& _Oldpval, const path& _Newpval,
    copy_options _Opt /* = copy_options::none */) { // copy _Oldpval to _Newpval
    error_code _Code;
    const bool _Ans = copy_file(_Oldpval, _Newpval, _Opt, _Code);
    if (_Code) {
        _Throw_filesystem_error("copy_file(p1, p2, options): invalid arguments");
    }

    return _Ans;
}

inline bool copy_file(const path& _Oldpval, const path& _Newpval,
    error_code& _Code) noexcept { // copy _Oldpval to _Newpval
    return copy_file(_Oldpval, _Newpval, copy_options::none, _Code);
}

inline bool copy_file(const path& _Oldpval, const path& _Newpval, copy_options _Opt,
    error_code& _Code) noexcept { // copy _Oldpval to _Newpval
    _Opt &= (copy_options::skip_existing | copy_options::overwrite_existing | copy_options::update_existing);
    const bool _Exists = exists(_Newpval);
    file_time_type _Oldtime;
    file_time_type _Newtime;

    _Code.clear();
    if (_Exists && (_Opt == copy_options::none || equivalent(_Oldpval, _Newpval, _Code))) {
        _Code = make_error_code(errc::file_exists);
        return false;
    }

    if (_Code) { // equivalent() failed, report error
        return false;
    }

    if (!_Exists || (_Opt & copy_options::overwrite_existing) != copy_options::none
        || ((_Opt & copy_options::update_existing) != copy_options::none
            && ((void) (_Oldtime = last_write_time(_Oldpval, _Code)), !_Code)
            && ((void) (_Newtime = last_write_time(_Newpval, _Code)), !_Code)
            && _Newtime < _Oldtime)) { // ok to overwrite, if necessary
        if (_Copy_file(_Oldpval.c_str(), _Newpval.c_str()) == 0) {
            return true;
        }

        _Code = make_error_code(errc::operation_not_permitted);
    }

    return false;
}

inline void copy_symlink(const path& _Oldpval, const path& _Newpval) { // copy symlink, file or directory
    error_code _Code;
    copy_symlink(_Oldpval, _Newpval, _Code);
    if (_Code) {
        _Throw_filesystem_error("copy_symlink(p1, p2): invalid arguments");
    }
}

inline void copy_symlink(const path& _Oldpval, const path& _Newpval,
    error_code& _Code) noexcept { // copy symlink, file or directory
    if (is_directory(_Oldpval)) {
        create_directory_symlink(_Oldpval, _Newpval, _Code);
    } else {
        create_symlink(_Oldpval, _Newpval, _Code);
    }
}

inline bool create_directories(const path& _Path) { // create directories chain
    error_code _Code;
    const bool _Ans = create_directories(_Path, _Code);
    if (_Code) {
        _Throw_filesystem_error("create_directories(p): invalid argument");
    }

    return _Ans;
}

inline bool create_directories(const path& _Path,
    error_code& _Code) noexcept { // create directory chain
    _Code.clear();
    if (_Path.empty()) {
        return false;
    } else if (!exists(_Path)) { // recursively create parent directories, then current
        create_directories(_Path.parent_path(), _Code);
        if (_Code) {
            return false; // report error
        }

        create_directory(_Path, _Code);
        if (_Code) {
            return false; // report error
        }

        return true;
    } else if (is_directory(_Path)) {
        return false; // directory already there
    } else { // report bad argument
        _Code = make_error_code(errc::operation_not_permitted);
        return false;
    }
}

inline bool create_directory(const path& _Path) { // create a directory
    error_code _Code;
    const bool _Ans = create_directory(_Path, _Code);

    if (_Code) {
        _Throw_filesystem_error("create_directory(p): invalid argument");
    }

    return _Ans;
}

inline bool create_directory(const path& _Path,
    error_code& _Code) noexcept { // create a directory
    const int _Ans = _Make_dir(_Path.c_str(), nullptr);

    _Code.clear();
    if (_Ans < 0) {
        _Code = make_error_code(errc::operation_not_permitted);
    }

    return 0 < _Ans;
}

inline bool create_directory(const path& _Path, const path& _Attrs) { // create a directory, copying attributes
    error_code _Code;
    const bool _Ans = create_directory(_Path, _Attrs, _Code);

    if (_Code) {
        _Throw_filesystem_error("create_directory(p1, p2): invalid arguments");
    }

    return _Ans;
}

inline bool create_directory(const path& _Path, const path& _Attrs,
    error_code& _Code) noexcept { // create a directory, copying attributes
    const int _Ans = _Make_dir(_Path.c_str(), _Attrs.c_str());

    _Code.clear();
    if (_Ans < 0) {
        _Code = make_error_code(errc::operation_not_permitted);
    }

    return 0 < _Ans;
}

inline void create_directory_symlink(const path& _Oldpval,
    const path& _Newpval) { // symlink directory _Newpval to _Oldpval
    error_code _Code;
    create_directory_symlink(_Oldpval, _Newpval, _Code);
    if (_Code) {
        _Throw_filesystem_error("create_directory_symlink(p1, p2): invalid arguments");
    }
}

inline void create_directory_symlink(const path& _Oldpval, const path& _Newpval,
    error_code& _Code) noexcept { // symlink directory_Newpval to _Oldpval (NB: SAME AS FILE)
    const int _Ans = _Symlink(_Oldpval.c_str(), _Newpval.c_str());

    _Code.clear();
    if (_Ans != 0) {
        _Code = error_code(_Ans, _STD system_category());
    }
}

inline void create_hard_link(const path& _Oldpval, const path& _Newpval) { // hard link _Newpval to _Oldpval
    error_code _Code;
    create_hard_link(_Oldpval, _Newpval, _Code);
    if (_Code) {
        _Throw_filesystem_error("create_hard_link(p1, p2): invalid arguments");
    }
}

inline void create_hard_link(const path& _Oldpval, const path& _Newpval,
    error_code& _Code) noexcept { // hard link _Newpval to _Oldpval
    const int _Ans = _Link(_Oldpval.c_str(), _Newpval.c_str());

    _Code.clear();
    if (_Ans != 0) {
        _Code = error_code(_Ans, _STD system_category());
    }
}

inline void create_symlink(const path& _Oldpval, const path& _Newpval) { // symlink _Newpval to _Oldpval
    error_code _Code;
    create_symlink(_Oldpval, _Newpval, _Code);
    if (_Code) {
        _Throw_filesystem_error("create_symlink(p1, p2): invalid arguments");
    }
}

inline void create_symlink(const path& _Oldpval, const path& _Newpval,
    error_code& _Code) noexcept { // symlink _Newpval to _Oldpval
    const int _Ans = _Symlink(_Oldpval.c_str(), _Newpval.c_str());

    _Code.clear();
    if (_Ans != 0) {
        _Code = error_code(_Ans, _STD system_category());
    }
}

_NODISCARD inline path current_path() {
    error_code _Code;
    path _Ans = current_path(_Code);
    if (_Code) {
        _Throw_filesystem_error("current_path(): can't get current working directory");
    }

    return _Ans;
}

_NODISCARD inline path current_path(error_code& _Code) {
    _Code.clear();
    _Pchar _Dest[_MAX_FILESYS_NAME];
    if (!_Current_get(_Dest)) { // report error
        _Code = make_error_code(errc::operation_not_permitted);
        return {};
    }
    return path(_Dest);
}

inline void current_path(const path& _Path) { // set current working directory
    if (!_Current_set(_Path.c_str())) {
        _Throw_filesystem_error("current_path(p): invalid argument");
    }
}

inline void current_path(const path& _Path,
    error_code& _Code) noexcept { // set current working directory
    _Code.clear();
    if (!_Current_set(_Path.c_str())) {
        _Code = make_error_code(errc::no_such_file_or_directory);
    }
}

_NODISCARD inline bool equivalent(const path& _Path1, const path& _Path2) {
    error_code _Code;
    const int _Ans = equivalent(_Path1, _Path2, _Code);

    if (_Code) {
        _Throw_filesystem_error("equivalent(p1, p2): invalid arguments");
    }

    return 0 < _Ans;
}

_NODISCARD inline bool equivalent(const path& _Path1, const path& _Path2, error_code& _Code) noexcept {
    const int _Ans = _Equivalent(_Path1.c_str(), _Path2.c_str());

    _Code.clear();
    if (_Ans < 0) {
        _Code = make_error_code(errc::operation_not_permitted);
    }

    return 0 < _Ans;
}

_NODISCARD inline bool exists(file_status _Stat) noexcept {
    return status_known(_Stat) && _Stat.type() != file_type::not_found;
}

_NODISCARD inline bool exists(const path& _Path) {
    return exists(status(_Path));
}

_NODISCARD inline bool exists(const path& _Path, error_code& _Code) noexcept {
    _Code.clear();
    return exists(status(_Path));
}

_NODISCARD inline uintmax_t file_size(const path& _Path) {
    error_code _Code;
    const uintmax_t _Ans = file_size(_Path, _Code);
    if (_Code) {
        _Throw_filesystem_error("file_size(p): invalid argument");
    }

    return _Ans;
}

_NODISCARD inline uintmax_t file_size(const path& _Path, error_code& _Code) noexcept {
    uintmax_t _Ans          = static_cast<uintmax_t>(-1);
    const file_status _Stat = status(_Path);

    _Code.clear();
    if (exists(_Stat) && is_regular_file(_Stat)) {
        _Ans = _File_size(_Path.c_str());
    }

    if (_Ans == static_cast<uintmax_t>(-1)) {
        _Code = make_error_code(errc::operation_not_permitted);
    }

    return _Ans;
}

_NODISCARD inline uintmax_t hard_link_count(const path& _Path) {
    error_code _Code;
    const uintmax_t _Ans = hard_link_count(_Path, _Code);
    if (_Code) {
        _Throw_filesystem_error("hard_link_count(p): invalid argument");
    }

    return _Ans;
}

_NODISCARD inline uintmax_t hard_link_count(const path& _Path, error_code& _Code) noexcept {
    _Code.clear();
    const uintmax_t _Ans = _Hard_links(_Path.c_str());
    if (_Ans == static_cast<uintmax_t>(-1)) {
        _Code = make_error_code(errc::operation_not_permitted);
    }

    return _Ans;
}

_NODISCARD inline bool is_block_file(file_status _Stat) noexcept {
    return _Stat.type() == file_type::block;
}

_NODISCARD inline bool is_block_file(const path& _Path) {
    return is_block_file(status(_Path));
}

_NODISCARD inline bool is_block_file(const path& _Path, error_code& _Code) noexcept {
    return is_block_file(status(_Path, _Code));
}

_NODISCARD inline bool is_character_file(file_status _Stat) noexcept {
    return _Stat.type() == file_type::character;
}

_NODISCARD inline bool is_character_file(const path& _Path) {
    return is_character_file(status(_Path));
}

_NODISCARD inline bool is_character_file(const path& _Path, error_code& _Code) noexcept {
    return is_character_file(status(_Path, _Code));
}

_NODISCARD inline bool is_directory(file_status _Stat) noexcept {
    return _Stat.type() == file_type::directory;
}

_NODISCARD inline bool is_directory(const path& _Path) {
    return is_directory(status(_Path));
}

_NODISCARD inline bool is_directory(const path& _Path, error_code& _Code) noexcept {
    return is_directory(status(_Path, _Code));
}

_NODISCARD inline bool is_empty(const path& _Path) {
    error_code _Code;
    const bool _Ans = _FSPFX is_empty(_Path, _Code);
    if (_Code) {
        _Throw_filesystem_error("is_empty(p): invalid argument");
    }

    return _Ans;
}

_NODISCARD inline bool is_empty(const path& _Path, error_code& _Code) noexcept {
    const file_status _Stat = status(_Path);

    _Code.clear();
    if (is_directory(_Stat)) {
        return directory_iterator(_Path) == directory_iterator();
    } else {
        return file_size(_Path, _Code) == 0;
    }
}

_NODISCARD inline bool is_fifo(file_status _Stat) noexcept {
    return _Stat.type() == file_type::fifo;
}

_NODISCARD inline bool is_fifo(const path& _Path) {
    return is_fifo(status(_Path));
}

_NODISCARD inline bool is_fifo(const path& _Path, error_code& _Code) noexcept {
    return is_fifo(status(_Path, _Code));
}

_NODISCARD inline bool is_other(file_status _Stat) noexcept {
    return exists(_Stat) && !is_regular_file(_Stat) && !is_directory(_Stat) && !is_symlink(_Stat);
}

_NODISCARD inline bool is_other(const path& _Path) {
    return is_other(status(_Path));
}

_NODISCARD inline bool is_other(const path& _Path, error_code& _Code) noexcept {
    return is_other(status(_Path, _Code));
}

_NODISCARD inline bool is_regular_file(file_status _Stat) noexcept {
    return _Stat.type() == file_type::regular;
}

_NODISCARD inline bool is_regular_file(const path& _Path) {
    return is_regular_file(status(_Path));
}

_NODISCARD inline bool is_regular_file(const path& _Path, error_code& _Code) noexcept {
    return is_regular_file(status(_Path, _Code));
}

_NODISCARD inline bool is_socket(file_status _Stat) noexcept {
    return _Stat.type() == file_type::socket;
}

_NODISCARD inline bool is_socket(const path& _Path) {
    return is_socket(status(_Path));
}

_NODISCARD inline bool is_socket(const path& _Path, error_code& _Code) noexcept {
    return is_socket(status(_Path, _Code));
}

_NODISCARD inline bool is_symlink(file_status _Stat) noexcept {
    return _Stat.type() == file_type::symlink;
}

_NODISCARD inline bool is_symlink(const path& _Path) {
    return is_symlink(status(_Path));
}

_NODISCARD inline bool is_symlink(const path& _Path, error_code& _Code) noexcept {
    return is_symlink(status(_Path, _Code));
}

_NODISCARD inline file_time_type last_write_time(const path& _Path) {
    error_code _Code;
    file_time_type _Ans = last_write_time(_Path, _Code);
    if (_Code) {
        _Throw_filesystem_error("last_write_time(p): invalid argument");
    }

    return _Ans;
}

_NODISCARD inline file_time_type last_write_time(const path& _Path, error_code& _Code) noexcept {
    const int64_t _Ticks = _Last_write_time(_Path.c_str());

    _Code.clear();
    if (_Ticks == -1) { // report error
        _Code = make_error_code(errc::operation_not_permitted);
        return (file_time_type::min)();
    }
    return file_time_type(chrono::system_clock::duration(_Ticks));
}

inline void last_write_time(const path& _Path, file_time_type _Newtime) { // set last write time
    error_code _Code;
    last_write_time(_Path, _Newtime, _Code);
    if (_Code) {
        _Throw_filesystem_error("last_write_time(p, new_time): invalid arguments");
    }
}

inline void last_write_time(const path& _Path, file_time_type _Newtime,
    error_code& _Code) noexcept { // set last write time
    _Code.clear();
    if (_Set_last_write_time(_Path.c_str(), _Newtime.time_since_epoch().count()) == 0) {
        _Code = make_error_code(errc::operation_not_permitted);
    }
}

inline void permissions(const path& _Path, perms _Mask) { // set access permissions
    error_code _Code;
    permissions(_Path, _Mask, _Code);
    if (_Code) {
        _Throw_filesystem_error("permissions(p, prms): can't set permissions");
    }
}

inline void permissions(const path& _Path, perms _Mask,
    error_code& _Code) { // set access permissions
    const perms _Todo = _Mask;
    _Mask             = _Mask & perms::mask;
    bool _Ok          = true;

    _Code.clear();
    if ((_Todo & perms::add_perms) == perms::none) {
        if ((_Todo & perms::remove_perms) != perms::none) {
            _Mask = status(_Path).permissions() & ~_Mask;
        }
    } else {
        if ((_Todo & perms::remove_perms) == perms::none) {
            _Mask = _Mask | status(_Path).permissions();
        } else {
            _Ok = false;
        }
    }

    if (!_Ok || _Chmod(_Path.c_str(), _Mask) != 0) {
        _Code = make_error_code(errc::operation_not_permitted);
    }
}

_NODISCARD inline path read_symlink(const path& _Path) { // read symbolic link
    error_code _Code;
    path _Sympath = read_symlink(_Path, _Code);
    if (_Code) {
        _Throw_filesystem_error("read_symlink(p): can't read symbolic link");
    }

    return _Sympath;
}

_NODISCARD inline path read_symlink(const path& _Path,
    error_code& _Code) { // read symbolic link
    _Code.clear();
    if (!is_symlink(_Path)) { // report error
        _Code = make_error_code(errc::no_such_file_or_directory);
        return {};
    }
    _Pchar _Dest[_MAX_FILESYS_NAME];
    return path(_Symlink_get(_Dest, _Path.c_str()));
}

inline bool remove(const path& _Path) { // remove a file
    error_code _Code;
    const bool _Ans = remove(_Path, _Code);

    if (_Code) {
        _Throw_filesystem_error("remove(p): invalid argument");
    }

    return _Ans;
}

inline bool remove(const path& _Path,
    error_code& _Code) noexcept { // remove a file
    _Code.clear();
    if (!exists(symlink_status(_Path))) {
        return false;
    } else if (is_directory(_Path, _Code)) {
        if (_Remove_dir(_Path.c_str())) {
            return true;
        } else { // couldn't remove emptied directory, report it
            _Code = make_error_code(errc::operation_not_permitted);
            return false;
        }
    } else { // file exists, try to remove it
        const bool _Ans = _Unlink(_Path.c_str()) == 0;
        if (!_Ans) {
            _Code = make_error_code(errc::operation_not_permitted);
        }

        return _Ans;
    }
}

inline bool _Remove_all(const path& _Path, uintmax_t& _Ans,
    error_code& _Code) noexcept { // recursively remove a file or directory, count removed files
    _Code.clear();
    if (is_directory(_Path)) { // empty and remove a directory
        using _Myit = _Directory_iterator<false_type>;
        _Myit _Last;

        for (;;) { // remove a directory entry
            _Myit _First(_Path);
            if (_First == _Last) {
                break;
            }

            if (!_Remove_all(_Path / _First->path(), _Ans, _Code)) {
                return false;
            }
        }
        if (_Remove_dir(_Path.c_str())) {
            return true;
        } else { // couldn't remove emptied directory, report it
            _Code = make_error_code(errc::operation_not_permitted);
            return false;
        }
    } else if (!remove(_Path, _Code)) {
        return false;
    } else { // file remove succeeded, count it
        ++_Ans;
        return true;
    }
}

inline uintmax_t remove_all(const path& _Path) { // recursively remove a directory
    error_code _Code;
    const uintmax_t _Ans = remove_all(_Path, _Code);
    if (_Code) {
        _Throw_filesystem_error("remove_all(p): invalid argument");
    }

    return _Ans;
}

inline uintmax_t remove_all(const path& _Path,
    error_code& _Code) noexcept { // recursively remove a directory
    uintmax_t _Ans = 0;
    _Remove_all(_Path, _Ans, _Code);
    if (_Code) {
        return static_cast<uintmax_t>(-1);
    }

    return _Ans;
}

inline void rename(const path& _Oldpval, const path& _Newpval) { // rename _Oldpval as _Newpval
    error_code _Code;
    rename(_Oldpval, _Newpval, _Code);
    if (_Code) {
        _Throw_filesystem_error("rename(p1, p2): invalid arguments");
    }
}

inline void rename(const path& _Oldpval, const path& _Newpval,
    error_code& _Code) noexcept { // rename _Oldpval as _Newpval
    _Code.clear();

    if (!exists(_Oldpval)) { // fail immediately without modifying the filesystem
        _Code = make_error_code(errc::operation_not_permitted);
        return;
    }

    if (exists(_Newpval)) { // both exist; there can be only one
        if (equivalent(_Oldpval, _Newpval, _Code) || _Code) {
            return; // successful no-op, or report equivalent() failure
        }

        if (!remove(_Newpval, _Code)) {
            return; // report remove() failure
        }
    }

    if (_Rename(_Oldpval.c_str(), _Newpval.c_str()) != 0) {
        _Code = make_error_code(errc::operation_not_permitted);
    }
}

inline void resize_file(const path& _Path, uintmax_t _Newsize) { // change file size
    error_code _Code;
    resize_file(_Path, _Newsize, _Code);
    if (_Code) {
        _Throw_filesystem_error("resize_file(p, n): invalid arguments");
    }
};

inline void resize_file(const path& _Path, uintmax_t _Newsize,
    error_code& _Code) noexcept { // change file size
    const int _Errno = _Resize(_Path.c_str(), _Newsize);

    _Code.clear();
    if (_Errno != 0) {
        _Code = error_code(_Errno, _STD system_category());
    }
}

_NODISCARD inline space_info space(const path& _Path) {
    return _Statvfs(_Path.c_str());
}

_NODISCARD inline space_info space(const path& _Path, error_code& _Code) noexcept {
    _Code.clear();
    return _Statvfs(_Path.c_str());
}

_NODISCARD inline file_status status(const path& _Path) {
    error_code _Code;
    return status(_Path, _Code);
}

_NODISCARD inline file_status status(const path& _Path, error_code& _Code) noexcept {
    _Code.clear();
    perms _Mode;
    const file_type _Ftype = _Stat(_Path.c_str(), &_Mode);
    return file_status(_Ftype, _Mode);
}

_NODISCARD inline bool status_known(file_status _Stat) noexcept {
    return _Stat.type() != file_type::unknown;
}

_NODISCARD inline file_status symlink_status(const path& _Path) {
    error_code _Code;
    return symlink_status(_Path, _Code);
}

_NODISCARD inline file_status symlink_status(const path& _Path, error_code& _Code) noexcept {
    perms _Mode;
    const file_type _Ftype = _Lstat(_Path.c_str(), &_Mode);

    _Code.clear();
    return file_status(_Ftype, _Mode);
}

_NODISCARD inline path system_complete(const path& _Path) {
    if (_Path.is_absolute()) {
        return _Path;
    }

    path _Curpath = current_path();
    if (!_Path.has_root_name() || _Path.root_name() == _Curpath.root_name()) {
        return absolute(_Path);
    }

    current_path(_Path.root_name()); // switch to new device
    path _Altpath = current_path(); // get its full current path
    current_path(_Curpath); // revert to original current path
    return _Altpath / _Path.relative_path();
}

_NODISCARD inline path system_complete(const path& _Path, error_code& _Code) {
    _Code.clear();

    path _Ans;

    _TRY_BEGIN
    _Ans = system_complete(_Path);
    _CATCH_ALL
    _Code = make_error_code(errc::operation_not_permitted);
    return {};
    _CATCH_END

    return _Ans;
}

_NODISCARD inline path temp_directory_path() {
    error_code _Code;
    path _Ans = temp_directory_path(_Code);
    if (_Code) {
        _Throw_filesystem_error("temp_directory_path(): can't find temp directory");
    }

    return _Ans;
}

_NODISCARD inline path temp_directory_path(error_code& _Code) {
    _Pchar _Dest[_MAX_FILESYS_NAME];
    _Temp_get(_Dest);
    path _Ans(_Dest);

    _Code.clear();
    if (!exists(_Ans) || !is_directory(_Ans)) { // report error
        _Code = make_error_code(errc::no_such_file_or_directory);
        return {};
    }
    return _Ans;
}
_FS_END

#pragma pop_macro("new")
_STL_RESTORE_CLANG_WARNINGS
#pragma warning(pop)
#pragma pack(pop)

#endif // _STL_COMPILER_PREPROCESSOR
#endif // _EXPERIMENTAL_FILESYSTEM_