void OsmAnd::ObfPoiSectionReader_P::readAmenities(
    const ObfReader_P& reader, const std::shared_ptr<const ObfPoiSectionInfo>& section,
    QSet<uint32_t>* desiredCategories,
    QList< std::shared_ptr<const Amenity> >* amenitiesOut,
    const ZoomLevel zoom, uint32_t zoomDepth, const AreaI* bbox31,
    std::function<bool (std::shared_ptr<const Amenity>)> visitor,
    const IQueryController* const controller)
{
    const auto cis = reader.getCodedInputStream().get();
    QList< std::shared_ptr<Tile> > tiles;
    for(;;)
    {
        const auto tag = cis->ReadTag();
        switch(gpb::internal::WireFormatLite::GetTagFieldNumber(tag))
        {
        case 0:
            if (!ObfReaderUtilities::reachedDataEnd(cis))
                return;

            return;
        case OBF::OsmAndPoiIndex::kBoxesFieldNumber:
            {
                const auto length = ObfReaderUtilities::readBigEndianInt(cis);
                const auto offset = cis->CurrentPosition();
                const auto oldLimit = cis->PushLimit(length);

                readTile(reader, section, tiles, nullptr, desiredCategories, zoom, zoomDepth, bbox31, controller, nullptr);

                ObfReaderUtilities::ensureAllDataWasRead(cis);
                cis->PopLimit(oldLimit);
                if (controller && controller->isAborted())
                    return;
            }
            break;
        case OBF::OsmAndPoiIndex::kPoiDataFieldNumber:
            {
                // Sort tiles byte data offset, to all cache-friendly with I/O system
                qSort(tiles.begin(), tiles.end(), [](const std::shared_ptr<Tile>& l, const std::shared_ptr<Tile>& r) -> bool
                {
                    return l->_hash < r->_hash;
                });

                for(const auto& tile : constOf(tiles))
                {
                    cis->Seek(section->_offset + tile->_offset);
                    const auto length = ObfReaderUtilities::readBigEndianInt(cis);
                    const auto offset = cis->CurrentPosition();
                    const auto oldLimit = cis->PushLimit(length);

                    readAmenitiesFromTile(reader, section, tile.get(), desiredCategories, amenitiesOut, zoom, zoomDepth, bbox31, visitor, controller, nullptr);

                    ObfReaderUtilities::ensureAllDataWasRead(cis);
                    cis->PopLimit(oldLimit);
                    if (controller && controller->isAborted())
                        return;
                }
                cis->Skip(cis->BytesUntilLimit());
            }
            return;
        default:
            ObfReaderUtilities::skipUnknownField(cis, tag);
            break;
        }
    }
}