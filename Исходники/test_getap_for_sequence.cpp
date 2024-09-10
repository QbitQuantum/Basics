/**
 * @brief Programa para obtener el numero de APs que se descubriria dada una secuencia de canales
 * y sus respectivos temporizadores MinChannelTime y MaxChannelTime.
 * @param argc cantidad de argumentos del programa
 * @param argv lista de argumentos
 * @return
 *
 * Para ejecutar:
 * ./test_getap_for_sequence <DATABASE> <EXPERIMENT> <SEQUENCEFILE>
 *
 * DATABASE: base de datos de scanning
 * EXPERIMENT: tipo de experimento utilizado en la campaña de scanning
 * SEQUENCEFILE: ruta absoluta al archivo de texto que posee la secuencia
 *
 */
int main(int argc, char ** argv) {

  if (argc != 4) {
    std::cerr << argv[0] << " <DATABASE> <EXPERIMENT> <SEQUENCEFILE> " << std::endl;
    // std::cerr << argv[0] << " <DATABASE> <EXPERIMENT> <chan seq> <MinCT list> <MaxCT list>" << std::endl;
    return 1;
  }

  ScanningCampaing scan(argv[1], argv[2]);
  scan.init();

  scan.prepareIRD();

  // vector de canales de la secuencia
  std::vector<int> channelList;

  // vector de MinChannelTime de la secuencia
  std::vector<int> minChannelTimeList;

  // vector de MaxChannelTime de la secuencia
  std::vector<int> maxChannelTimeList;

  // linea de la secuencia
  std::string line;

  // archivo de la secuencia
  std::ifstream myfile (argv[3]);

  if (myfile.is_open()) {

      getline (myfile,line);
      std::cout << line << std::endl;

      std::vector<std::string> tokens;
      std::istringstream f(line);
      std::string s;
      while (getline(f, s, ',')) {
          //std::cout << s << std::endl;
          tokens.push_back(s);
      }
      printf("numero de parametros de la secuencia: %d \n", tokens.size());
      int sequenceLength = tokens.size()/3;
      printf("sequenceLength: %d \n", sequenceLength);

      for (int i=0; i<sequenceLength; i++) {

          //printf("canal: %d \n", stoi(tokens.at(i*3)));
          //printf("min: %d \n", stoi(tokens.at(i*3+1)));
          //printf("max: %d \n", stoi(tokens.at(i*3+2)));


          channelList.push_back(std::stoi(tokens.at(i*3)));
          minChannelTimeList.push_back(std::stoi(tokens.at(i*3+1)));
          maxChannelTimeList.push_back(std::stoi(tokens.at(i*3+2)));
      }


      printf("canales: ");
      for (int j=0; j<channelList.size(); j++) {
          printf("%d ", channelList.at(j));
      }
      printf("\n");

      printf("min: ");
      for (int j=0; j<minChannelTimeList.size(); j++) {
          printf("%d ", minChannelTimeList.at(j));
      }
      printf("\n");

      printf("max: ");
      for (int j=0; j<maxChannelTimeList.size(); j++) {
          printf("%d ", maxChannelTimeList.at(j));
      }
      printf("\n");


      int aps = scan.getAPsForSequence(channelList, minChannelTimeList, maxChannelTimeList);
      printf("numero de aps descubiertos por la cadena: %d \n", aps);

      printf("**************************************************\n");
/*
      aps = 0;
      int sum = 0;
      for (int j=0; j<30; j++) {
          aps = scan.getAPsForSequence(channelList, minChannelTimeList, maxChannelTimeList);
          printf("%d,", aps);
          sum = sum + aps;
      }
      printf("\npromedio de APs en 30 ejecuciones: %d \n", sum/30);
*/
      myfile.close();
  }
  else {
      std::cout << "Unable to open file with sequence\n";
      return 1;
  }

  return 0;
}