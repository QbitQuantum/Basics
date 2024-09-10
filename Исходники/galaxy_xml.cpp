void Galaxy::writeGalaxy(VSFile &f) const
{
  f.Fprintf ("<galaxy>\n<systems>\n");
  writeSector(f,1,"sector",planet_types);
  f.Fprintf ("</systems>\n");
  if (planet_types) {
    f.Fprintf("<planets>\n");
    planet_types->writeSector(f,1,"planet",NULL);
    f.Fprintf("</planets>\n");
  }
  f.Fprintf("</galaxy>\n");
}