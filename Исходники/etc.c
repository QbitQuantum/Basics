/*
 * Returns the system information obtained by uname system call.
 *
 * The return value is a hash which has 5 keys at least:
 *   :sysname, :nodename, :release, :version, :machine
 *
 * Example:
 *
 *   require 'etc'
 *   require 'pp'
 *
 *   pp Etc.uname
 *   #=> {:sysname=>"Linux",
 *   #    :nodename=>"boron",
 *   #    :release=>"2.6.18-6-xen-686",
 *   #    :version=>"#1 SMP Thu Nov 5 19:54:42 UTC 2009",
 *   #    :machine=>"i686"}
 *
 */
static VALUE
etc_uname(VALUE obj)
{
#ifdef _WIN32
    OSVERSIONINFOW v;
    SYSTEM_INFO s;
    const char *sysname, *mach;
    VALUE result, release, version;
    VALUE vbuf, nodename = Qnil;
    DWORD len = 0;
    WCHAR *buf;

    v.dwOSVersionInfoSize = sizeof(v);
    if (!GetVersionExW(&v))
        rb_sys_fail("GetVersionEx");

    result = rb_hash_new();
    switch (v.dwPlatformId) {
      case VER_PLATFORM_WIN32s:
	sysname = "Win32s";
	break;
      case VER_PLATFORM_WIN32_NT:
	sysname = "Windows_NT";
	break;
      case VER_PLATFORM_WIN32_WINDOWS:
      default:
	sysname = "Windows";
	break;
    }
    rb_hash_aset(result, ID2SYM(rb_intern("sysname")), rb_str_new_cstr(sysname));
    release = rb_sprintf("%lu.%lu.%lu", v.dwMajorVersion, v.dwMinorVersion, v.dwBuildNumber);
    rb_hash_aset(result, ID2SYM(rb_intern("release")), release);
    version = rb_sprintf("%s Version %"PRIsVALUE": %"PRIsVALUE, sysname, release,
			 rb_w32_conv_from_wchar(v.szCSDVersion, rb_utf8_encoding()));
    rb_hash_aset(result, ID2SYM(rb_intern("version")), version);

# if defined _MSC_VER && _MSC_VER < 1300
#   define GET_COMPUTER_NAME(ptr, plen) GetComputerNameW(ptr, plen)
# else
#   define GET_COMPUTER_NAME(ptr, plen) GetComputerNameExW(ComputerNameDnsFullyQualified, ptr, plen)
# endif
    GET_COMPUTER_NAME(NULL, &len);
    buf = ALLOCV_N(WCHAR, vbuf, len);
    if (GET_COMPUTER_NAME(buf, &len)) {
	nodename = rb_w32_conv_from_wchar(buf, rb_utf8_encoding());
    }
    ALLOCV_END(vbuf);
    if (NIL_P(nodename)) nodename = rb_str_new(0, 0);
    rb_hash_aset(result, ID2SYM(rb_intern("nodename")), nodename);

# ifndef PROCESSOR_ARCHITECTURE_AMD64
#   define PROCESSOR_ARCHITECTURE_AMD64 9
# endif
# ifndef PROCESSOR_ARCHITECTURE_IA64
#   define PROCESSOR_ARCHITECTURE_IA64 6
# endif
# ifndef PROCESSOR_ARCHITECTURE_INTEL
#   define PROCESSOR_ARCHITECTURE_INTEL 0
# endif
    GetSystemInfo(&s);
    switch (s.wProcessorArchitecture) {
      case PROCESSOR_ARCHITECTURE_AMD64:
	mach = "x64";
	break;
      case PROCESSOR_ARCHITECTURE_ARM:
	mach = "ARM";
	break;
      case PROCESSOR_ARCHITECTURE_IA64:
	mach = "IA64";
	break;
      case PROCESSOR_ARCHITECTURE_INTEL:
	mach = "x86";
	break;
      default:
	mach = "unknown";
	break;
    }

    rb_hash_aset(result, ID2SYM(rb_intern("machine")), rb_str_new_cstr(mach));
#else
    struct utsname u;
    int ret;
    VALUE result;

    ret = uname(&u);
    if (ret == -1)
        rb_sys_fail("uname");

    result = rb_hash_new();
    rb_hash_aset(result, ID2SYM(rb_intern("sysname")), rb_str_new_cstr(u.sysname));
    rb_hash_aset(result, ID2SYM(rb_intern("nodename")), rb_str_new_cstr(u.nodename));
    rb_hash_aset(result, ID2SYM(rb_intern("release")), rb_str_new_cstr(u.release));
    rb_hash_aset(result, ID2SYM(rb_intern("version")), rb_str_new_cstr(u.version));
    rb_hash_aset(result, ID2SYM(rb_intern("machine")), rb_str_new_cstr(u.machine));
#endif

    return result;
}