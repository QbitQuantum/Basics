FontConverter::FontConverter(const Arguments& arguments): Platform::WindowlessApplication(arguments, nullptr) {
    args.addArgument("input").setHelp("input", "input font")
        .addArgument("output").setHelp("output", "output filename prefix")
        .addNamedArgument("font").setHelp("font", "font plugin")
        .addNamedArgument("converter").setHelp("converter", "font converter plugin")
        .addOption("plugin-dir", MAGNUM_PLUGINS_DIR).setHelpKey("plugin-dir", "DIR").setHelp("plugin-dir", "base plugin dir")
        .addOption("characters", "abcdefghijklmnopqrstuvwxyz"
                                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 "0123456789?!:;,. ").setHelp("characters", "characters to include in the output")
        .addOption("font-size", "128").setHelpKey("font-size", "N").setHelp("font-size", "input font size")
        .addOption("atlas-size", "2048 2048").setHelpKey("atlas-size", "\"X Y\"").setHelp("atlas-size", "glyph atlas size")
        .addOption("output-size", "256 256").setHelpKey("output-size", "\"X Y\"").setHelp("output-size", "output atlas size. If set to zero size, distance field computation will not be used.")
        .addOption("radius", "24").setHelpKey("radius", "N").setHelp("radius", "distance field computation radius")
        .setHelp("Converts font to raster one of given atlas size.")
        .parse(arguments.argc, arguments.argv);

    createContext();
}