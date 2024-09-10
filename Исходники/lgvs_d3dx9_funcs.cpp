bool D3dx9Funcs::initialize()
{
    uninitialize();

    std::wstring dll_file_path;

    dll_file_path = System::combine_paths(
        System::get_system_dir(), L"d3dx9_43.dll");

    library_ = ::LoadLibraryW(dll_file_path.c_str());

    if (library_ == nullptr)
        return false;

    create_font_ = reinterpret_cast<FP_D3DXCREATEFONT>(
        ::GetProcAddress(library_, "D3DXCreateFontW"));

    create_sprite_ = reinterpret_cast<FP_D3DXCREATESPRITE>(
        ::GetProcAddress(library_, "D3DXCreateSprite"));

    if (create_font_ != nullptr && create_sprite_ != nullptr)
        is_initialized_ = true;
    else
        uninitialize();

    return is_initialized_;
}