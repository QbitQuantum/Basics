 bool TestCase::hasTag( std::string const& tag ) const {
     return tags.find( toLower( tag ) ) != tags.end();
 }