CapitalisationAlgorithms::CapitalisationAlgorithms()
{
    add({ "Upper", "Capitalisation",
        [](std::string input, std::vector<std::string> /*params*/, bool /*ignoreCase*/, bool /*reverseOutput*/) -> std::string
        {
            return boost::locale::to_upper(input);
        }
    });

    add({ "Lower", "Capitalisation",
        [](std::string input, std::vector<std::string> /*params*/, bool /*ignoreCase*/, bool /*reverseOutput*/) -> std::string
        {
            return boost::locale::to_lower(input);
        }
    });

    add({ "Title", "Capitalisation",
        [](std::string input, std::vector<std::string> /*params*/, bool /*ignoreCase*/, bool /*reverseOutput*/) -> std::string
        {
            return boost::locale::to_title(input);
        }
    });

    add({ "Toggle", "Capitalisation",
        [](std::string input, std::vector<std::string> /*params*/, bool /*ignoreCase*/, bool /*reverseOutput*/) -> std::string
        {
            std::stringstream stream;

            boost::locale::boundary::ssegment_index segmentIndex(boost::locale::boundary::character, std::begin(input), std::end(input));

            for (const auto& segment : segmentIndex)
            {
                stream << (isUpper(segment.str()) ? boost::locale::to_lower(segment.str()) : boost::locale::to_upper(segment.str()));

            }

            return stream.str();
        }
    });
}