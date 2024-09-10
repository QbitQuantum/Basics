/**
 * Returns a suitable epsFilename build from a file or directory name and
 * histogram name.
 *
 * @param fileOrDirectoryName
 *                            name of the file or directory
 * @param histogramNamw
 *                            name of the histogram
 * @return
 *                            a suitable epsFilename
 */
TString
epsFilename(const TString& fileOrDirectoryName, const TString& histogramName)
{
// {{{
    TString s = fileOrDirectoryName;
    if (s.EndsWith("/")) s.Remove(s.Length()-1);
    s = gSystem->BaseName(s);
    s.ReplaceAll(".root", "");
    s.Append(".").Append(histogramName);
    s.ReplaceAll(".", "_");
    return s;
// }}}
};