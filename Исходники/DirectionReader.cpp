        void DirectionReader::parseWords( const core::DirectionType& directionType)
        {
            const auto& wordSet = directionType.getWordsSet();

            for( const auto& wordPtr : wordSet )
            {
                api::WordsData outWords;
                const auto& attr = *wordPtr->getAttributes();
                outWords.text = wordPtr->getValue().getValue();
                outWords.positionData = getPositionData( attr );
                outWords.colorData = getColor( attr );
                outWords.fontData = getFontData( attr );
                myOutDirectionData.words.emplace_back( std::move( outWords ) );
            }
        }