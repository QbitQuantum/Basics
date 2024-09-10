static int parse_arguments_and_execute()
{
    enum
    {
        Argument_logical_sector = 0,
        Argument_file_name,
        Argument_help,
    };

    const std::vector<Parsing::Argument_descriptor> argument_map =
    {
        { Argument_logical_sector, u8"logical-sector", u8's', true,  u8"The logical block address (LBA) of the sector to read." },
        { Argument_file_name,      u8"file-name",      u8'f', true,  u8"The name of the file to hold the output. This file will be overwritten." },
        { Argument_help,           u8"help",           u8'?', false, nullptr },
    };
#ifndef NDEBUG
    Parsing::validate_argument_map(argument_map);
#endif

    const auto arguments = WindowsCommon::args_from_command_line();
    const auto options = Parsing::options_from_allowed_args(arguments, argument_map);

    int error_level = 0;
    if(options.count(Argument_help) == 0)
    {
        CHECK_EXCEPTION(options.count(Argument_logical_sector) > 0, u8"Missing a required argument: --" + std::string(argument_map[Argument_logical_sector].long_name));
        CHECK_EXCEPTION(options.count(Argument_file_name) > 0,      u8"Missing a required argument: --" + std::string(argument_map[Argument_file_name].long_name));

        // There is no _atoui64 function (and perhaps a private implementation is a good idea), but
        // reading an int64_t into a uint64_t will have no negative (ha!) consequences, as any sector
        // number is considered a valid sector to read.
        const uint64_t sector_number = _atoi64(options.at(Argument_logical_sector).c_str());
        GetSector::read_physical_drive_sector_to_file(0, sector_number, PortableRuntime::utf16_from_utf8(options.at(Argument_file_name)).c_str());
    }
    else
    {
        constexpr auto arg_program_name = 0;

        // Hold a reference to program_name_long for the duration of the output functions.
        const auto program_name_long = PortableRuntime::utf16_from_utf8(arguments[arg_program_name]);
        const auto program_name = PathFindFileNameW(program_name_long.c_str());

        std::fwprintf(stderr, L"Usage: %s [options]\nOptions:\n", program_name);
        std::fwprintf(stderr, PortableRuntime::utf16_from_utf8(Parsing::Options_help_text(argument_map)).c_str());
        std::fwprintf(stderr,
                      L"\nTo read the Master Boot Record:\n  %s -%c 1 -%c mbr.bin\n",
                      program_name,
                      argument_map[Argument_logical_sector].short_name,
                      argument_map[Argument_file_name].short_name);
        error_level = 1;
    }

    return error_level;
}