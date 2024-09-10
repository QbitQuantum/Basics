int main() {
    int major,
        minor;
    wxOperatingSystemId os = wxGetOsVersion(&major, &minor);
    if (os == wxOS_WINDOWS_NT) {
        DirName = wxT("C:\\Users\\Roberto\\sample_php_project");
    } else {
        DirName = wxT("/home/roberto/workspace/sample_php_project");
    }
    ProfileFindInFilesExactMode();
    ProfileFindInFilesCodeMode();

    // calling cleanup here so that we can run this binary through a memory leak detector
    // ICU will cache many things and that will cause the detector to output "possible leaks"
    u_cleanup();
    return 0;
}