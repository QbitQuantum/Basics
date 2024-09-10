/* METAR examples
Berlin-Schoenefeld, Germany (EDDB) 52-23N 013-31E 50M
Sep 26, 2013 - 03:50 AM EDT / 2013.09.26 0750 UTC
Wind: from the NNE (020 degrees) at 13 MPH (11 KT):0
Visibility: 3 mile(s):0
Sky conditions: mostly cloudy
Weather: light drizzle
Temperature: 46 F (8 C)
Dew Point: 46 F (8 C)
Relative Humidity: 100%
Pressure (altimeter): 29.83 in. Hg (1010 hPa)
ob: EDDB 260750Z 02011KT 6000 -DZ SCT003 BKN006 08/08 Q1010 TEMPO BKN010
cycle: 8

Station name not available
Aug 18, 2013 - 09:30 PM EDT / 2013.08.19 0130 UTC
Sky conditions: partly cloudy
Temperature: 59 F (15 C)
Dew Point: 57 F (14 C)
Relative Humidity: 93%
Pressure (altimeter): 30.39 in. Hg (1029 hPa)
ob: OPSD 190130Z CALM 09KM P/CLOUDY FEW015ST SCT035 Q1029/30.41 15/14C RH 95 PERCENT A/V OH CLEAR
cycle: 1
*/
void PreFlightWeatherPage::slotNewWeaterReport( QString& file )
{
  QFile report(file);

  QString station = QFileInfo(file).baseName();

  if( file.contains("/weather/METAR/") )
    {
      if ( ! report.open( QIODevice::ReadOnly ) )
        {
          // could not open file ...
          qWarning() << "Cannot open file: " << report.fileName();
          return;
        }

      // METAR report received
      QTextStream stream( &report );
      QString line;

      QHash<QString, QString> reportItems;
      reportItems.insert( "icao", station );

      int lineNo = 0;

      int tempUnit = GeneralConfig::instance()->getUnitTemperature();
      int pressureUnit = GeneralConfig::instance()->getUnitAirPressure();

      while( !stream.atEnd() )
        {
          line = stream.readLine();
          lineNo++;

          // qDebug() << "line=" << line;

          if( line.trimmed().isEmpty() )
            {
              // ignore comment and empty lines
              continue;
            }

          if( lineNo == 1 )
            {
              // Line 1: station name
              // Berlin-Schoenefeld, Germany (EDDB) 52-23N 013-31E 50M
              // Station name not available
              if( line.startsWith( "Station name not available" ) )
                {
                  reportItems.insert( "station", tr("Station name not available") );
                  continue;
                }

              int idx = line.indexOf( "(" + station + ")" );

              if( idx > 0 )
                {
                  reportItems.insert( "station", line.left(idx - 1) );
                  continue;
                }

              reportItems.insert( "station", line );
              continue;
            }

          if( lineNo == 2 )
            {
              // Line 2: Date and time
              // Sep 26, 2013 - 11:50 AM EDT / 2013.09.26 1550 UTC
              if( line.endsWith(" UTC") )
                {
                  int idx = line.indexOf( " / " );

                  if( idx > 0 && line.size() > (idx + 3) )
                    {
                      QString date = line.mid(idx + 3, 13) + ":" +
                                     line.mid(idx + 3 + 13);

                      reportItems.insert( "date", date );
                      continue;
                    }
                }

              reportItems.insert( "date", line );
              continue;
            }

          if( line.startsWith( "Wind: ") )
            {
              // Wind: from the NW (310 degrees) at 5 MPH (4 KT):0
              // Wind: from the W (280 degrees) at 5 MPH (4 KT) (direction variable):0
              // Wind: from the ESE (120 degrees) at 20 MPH (17 KT) gusting to 32 MPH (28 KT) (direction variable):0
              line.replace( " degrees", QChar(Qt::Key_degree) );

              if( line.endsWith( ":0") )
                {
                  line.chop(2);
                }

              // Remove the line beginning.
              line = line.mid(6);
              int loop = 6;

              while( loop-- )
                {
                  QRegExp re = QRegExp("[0-9]+ MPH \\([0-9]+ KT\\)");

                  int idx1 = line.indexOf(re, 0);

                  if( idx1 == -1 )
                    {
                      // No speed value found.
                      break;
                    }

                  int idx2 = line.indexOf( "(", idx1 + 1 );
                  int idx3 = line.indexOf( " KT)", idx1 + 1 );

                  if( idx2 > 0 && idx2 < idx3 )
                    {
                      bool ok;
                      double ws = line.mid(idx2 + 1, idx3 - idx2 -1).toDouble(&ok);

                      if( ok )
                        {
                          Speed speed(0);
                          speed.setKnot( ws );

                          QString wsText = speed.getWindText( true, 0 );

                          line = line.left(idx1) + wsText + line.mid(idx3 + 4);
                        }
                    }
                }

              reportItems.insert( "wind", line );
              continue;
            }

          if( line.startsWith( "Visibility: ") )
            {
              // Visibility: greater than 7 mile(s):0
              // Visibility: less than 1 mile:0
              // Visibility: 3/4 mile(s):0
              if( line.contains( " mile") )
                {
                  int idx2  = line.lastIndexOf( " mile" );
                  int idx1  = line.lastIndexOf( " ", idx2 - 1 );

                  if( idx1 > 0 && idx1 < idx2 )
                    {
                      bool ok = false;
                      double visiDouble = 0.0;

                      QString visiText = line.mid(idx1 + 1, idx2 - idx1 -1);

                      if( visiText.contains("/") )
                        {
                          QStringList visiList = visiText.split("/");

                          if( visiList.size() == 2 )
                            {
                              double arg1 = visiList.at(0).toDouble(&ok);

                              if( ok )
                                {
                                  double arg2 = visiList.at(1).toDouble(&ok);

                                  if( ok && arg2 > 0.0 )
                                    {
                                      visiDouble = arg1 / arg2;
                                    }
                                }
                            }
                        }
                      else
                        {
                          visiDouble = visiText.toDouble( &ok );
                        }

                      if( ok )
                        {
                          Distance distance(0);
                          distance.setMiles( visiDouble );

                          QString visibility = line.mid( 12, idx1 - 11 );

                          if( distance.getKilometers() > 5 )
                            {
                              visibility += distance.getText( true, 0 );
                            }
                          else
                            {
                              visibility += distance.getText( true, 1 );
                            }

                          if( line.contains("mile(s)") )
                            {
                              // This must be tested as first to prevent wrong handling!
                              if( ! line.endsWith( "mile(s):0") )
                                {
                                  line.replace( ":0", "" );
                                  visibility += line.mid( line.indexOf( "mile(s)" ) + 7 );
                                }
                            }
                          else if( line.contains("mile") && ! line.endsWith( "mile:0") )
                            {
                              if( ! line.endsWith( "mile:0") )
                                {
                                  line.replace( ":0", "" );
                                  visibility += line.mid( line.indexOf( "mile" ) + 4 );
                                }
                            }

                          reportItems.insert( "visibility", visibility );
                          continue;
                        }
                    }
                }

              reportItems.insert( "visibility", line.mid(12) );
              continue;
            }

          if( line.startsWith( "Sky conditions: ") )
            {
              // Sky conditions: partly cloudy or mostly cloudy
              reportItems.insert( "sky", line.mid(16) );
              continue;
            }

          if( line.startsWith( "Weather: ") )
            {
              reportItems.insert( "weather", line.mid(9) );
              continue;
            }

          if( line.startsWith( "Temperature: ") )
            {
              // Temperature: 51 F (11 C)
              if( tempUnit == GeneralConfig::Fahrenheit )
                {
                  // Temperature in F
                  int idx = line.indexOf( " F (" );

                  if( idx > 0 )
                    {
                      reportItems.insert("temperature", line.mid(13, idx-13 ) + QChar(Qt::Key_degree) + "F");
                      continue;
                    }
                }
              else
                {
                  // Temperature in C
                  int idx2 = line.lastIndexOf( " C)" );
                  int idx1 = line.lastIndexOf( "(", idx2 -1 );

                  if( idx1 > 0 && idx1+1 < idx2 )
                    {
                      reportItems.insert("temperature", line.mid( idx1+1, idx2-idx1-1 ) + QChar(Qt::Key_degree) + "C");
                      continue;
                    }
                }

              reportItems.insert("temperature", line.mid( 13 ) );
              continue;
            }

          if( line.startsWith( "Dew Point: ") )
            {
              // Dew Point: 42 F (6 C)
              if( tempUnit == GeneralConfig::Fahrenheit )
                {
                  // Dew point in F
                  int idx = line.indexOf( " F (" );

                  if( idx > 0 )
                    {
                      reportItems.insert("dewPoint", line.mid(11, idx-11) + QChar(Qt::Key_degree) + "F");
                      continue;
                    }
                }
              else
                {
                  // Dew point in C
                  int idx2 = line.lastIndexOf( " C)" );
                  int idx1 = line.lastIndexOf( "(", idx2 - 1 );

                  if( idx1 > 0 && idx1+1 < idx2 )
                    {
                      reportItems.insert("dewPoint", line.mid( idx1+1, idx2-idx1-1 ) + QChar(Qt::Key_degree) + "C");
                      continue;
                    }
                }

              reportItems.insert("dewPoint", line.mid( 11 ) );
              continue;
            }

          if( line.startsWith( "Relative Humidity: ") )
            {
              // Relative Humidity: 71%
              reportItems.insert( "humidity", line.mid(19) );
              continue;
            }

          if( line.startsWith( "Pressure (altimeter): ") )
            {
              // Pressure (altimeter): 30.00 in. Hg (1016 hPa)
              if( pressureUnit == GeneralConfig::inHg )
                {
                  // QNH in inch Hg
                  int idx = line.lastIndexOf( " (" );

                  if( idx > 22 )
                    {
                      reportItems.insert("qnh", line.mid(22, idx - 22 ));
                      continue;
                    }
                }
              else
                {
                  // QHN in hPa
                  int idx2 = line.lastIndexOf( " hPa)" );
                  int idx1 = line.lastIndexOf( "(", idx2 - 1 );

                  if( idx1 > 0 && idx1+2 < idx2 )
                    {
                      reportItems.insert("qnh", line.mid( idx1 + 1, idx2 - idx1 + 3 ));
                      continue;
                    }
                }

              reportItems.insert("qnh", line.mid( 22 ));
              continue;
            }

          if( line.startsWith( "ob: ") )
            {
              // Extract the observation line from the report.
              // ob: EDDB 261550Z 31004KT 9999 FEW030 SCT056 11/06 Q1016 NOSIG
              reportItems.insert( "observation", line.mid(4) );
              continue;
            }
        }

      report.close();

      // qDebug() << "ReportItems:" << reportItems;

      m_metarReports.insert( station, reportItems );
      updateIcaoItem( station );
    }
  else if( file.contains("/weather/TAF/") )
    {
      /* TAF Example
      2013/09/26 12:29
      TAF EDDF 261100Z 2612/2718 32008KT 9999 SCT035
            BECMG 2617/2619 04005KT
      */

      // TAF report received. The whole report is stored in the hash as one string.
      if ( ! report.open( QIODevice::ReadOnly ) )
        {
          // could not open file ...
          qWarning() << "Cannot open file: " << report.fileName();
          return;
        }

      // TAF report received
      QTextStream stream( &report );
      QString line;
      QString tafReport;

      int lineNo = 0;

      while( !stream.atEnd() )
        {
          line = stream.readLine();
          lineNo++;

          if( line.trimmed().isEmpty() || lineNo == 1 )
            {
              // ignore comment and empty lines
              // ignore line 1, it contains the date and time
              continue;
            }

          if( tafReport.isEmpty() )
            {
              tafReport = line;
            }
          else
            {
              tafReport += "\n" + line;
            }
        }

      report.close();

      m_tafReports.insert( station, tafReport );

      // qDebug() << "TAFs:" << m_tafReports;
    }

  if( m_displayWidget->isVisible() )
    {
      if( m_list->topLevelItemCount() == 0 )
        {
          return;
        }

      IcaoItem *item = dynamic_cast<IcaoItem *>( m_list->currentItem() );

      if( item == 0 )
        {
          return;
        }

      if( item->getIcao() == station )
        {
          // The display widget is visible and must be updated too, if new
          // station data are available.
          slotDetails();
        }
    }
}