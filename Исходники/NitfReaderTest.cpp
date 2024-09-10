TEST(NitfReaderTest, optionSrs)
{
    StageFactory f;

    Options nitfOpts;
    nitfOpts.add("filename", Support::datapath("nitf/autzen-utm10.ntf"));

    std::string sr = "PROJCS[\"NAD83 / UTM zone 11N\",GEOGCS[\"NAD83\",DATUM[\"North_American_Datum_1983\",SPHEROID[\"GRS 1980\",6378137,298.257222101,AUTHORITY[\"EPSG\",\"7019\"]],TOWGS84[0,0,0,0,0,0,0],AUTHORITY[\"EPSG\",\"6269\"]],PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]],UNIT[\"degree\",0.0174532925199433,AUTHORITY[\"EPSG\",\"9122\"]],AUTHORITY[\"EPSG\",\"4269\"]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",-123],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"metre\",1,AUTHORITY[\"EPSG\",\"9001\"]],AXIS[\"Easting\",EAST],AXIS[\"Northing\",NORTH],AUTHORITY[\"EPSG\",\"26910\"]]";

    nitfOpts.add("spatialreference", sr);

    PointContext ctx;

    ReaderPtr nitfReader(f.createReader("readers.nitf"));
    EXPECT_TRUE(nitfReader.get());
    nitfReader->setOptions(nitfOpts);

    Options lasOpts;
    lasOpts.add("filename", "/dev/null");

    WriterPtr lasWriter(f.createWriter("writers.las"));
    EXPECT_TRUE(lasWriter.get());
    lasWriter->setInput(nitfReader.get());
    lasWriter->setOptions(lasOpts);;

    lasWriter->prepare(ctx);
    PointBufferSet pbSet = lasWriter->execute(ctx);

    EXPECT_EQ(sr, nitfReader->getSpatialReference().getWKT());
    EXPECT_EQ("", lasWriter->getSpatialReference().getWKT());
    EXPECT_EQ(sr, ctx.spatialRef().getWKT());
}