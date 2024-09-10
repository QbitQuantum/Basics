int CERT_SIGS::write(MIOFILE &f) {
    if (this->signatures.size()==0) return true;
    f.printf("<signatures>\n");
    for(unsigned int i=0;i < this->signatures.size(); i++) {
        f.printf("  <entry>\n");
        f.printf("    <signature>\n%s\n", this->signatures.at(i).signature);
        f.printf("    </signature>\n");
        f.printf("    <subject>%s</subject>\n", this->signatures.at(i).subject);    
        f.printf("    <type>%s</type>\n", (this->signatures.at(i).type == MD5_HASH) ? "md5" : "sha1");
        f.printf("    <hash>%s</hash>\n", this->signatures.at(i).hash);
        f.printf("  </entry>\n");
    }
    f.printf("</signatures>\n");
    return true;
}