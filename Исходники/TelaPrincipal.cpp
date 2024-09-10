void TelaPrincipal::compilaCodigoFonte() {
    // Salva o que foi digitado para carregar as variáveis necessárias
    salvarArquivo();

    // Limpa a Lista de Tokens
    tokens.clear();

    // Joga o código fonte para uma variável temporária
    QByteArray dialogConteudo = conteudoDoArquivo.toLatin1();

    QList <char> token; // Armazena o valor do token em char
    int ref = 0; // Referência para percorrer cada char da variavel token
    while (dialogConteudo.size() > 0) { // Enquanto tiver código fonte faça
        QString dialog; // Variável que armazena o token em String
        token.insert(ref, dialogConteudo.at(0)); // Armazena o primeiro char do token
        if (token.at(ref) ==  39) { // O char atual é uma ' ?
            ref++;  // Se for incrementa a referência
            while (ref < (dialogConteudo.size())) { // Percorre todo o arquivo procurando a outra '
                if (dialogConteudo.at(ref) == 39) { // Se o char na posição ref for '
                    token.insert(ref,dialogConteudo.at(ref)); // Insere a aspas no token para poder ser corretamente identificado como alfa depois
                    break; // Para de percorrer o arquivo
                } else { // Se não for '
                    token.insert(ref,dialogConteudo.at(ref)); // Adiciona o char na posição ref no token
                    ref++; // Incrementa a referência
                }
            } // Só sai do loop quando pecorre todo o arquivo não encontrando a segunda ' ou quando encontrar a segunda '
            if(ref == dialogConteudo.size())
                ref--;
            for (int i=0; i <= ref; i++) { // Percorre o token formado para inserir na lista de tokens
                dialog += token.at(i); // Cria uma String com os char do Token
                dialogConteudo.remove(0,1); // Deleta sempre o char lido
            }
            if (dialog.size() > 0) // Só cria novo token se este tivar algum char
                tokens.insert(tokens.size(),new Token(dialog)); // Adiciona na lista de tokens o token formado
            ref = 0; // Zera a referência
            token.clear(); // Limpa a variável que cria o token temporariamente
        } else if (token.at(ref) ==  47) { // O char atual é uma / ?
            ref++;  // Se for incrementa a referência
            if (dialogConteudo.at(ref) == 47) { // Se o char na posição ref for /
                token.insert(ref,dialogConteudo.at(ref)); // Insere a segunda / no token para poder ser corretamente identificado como comentário depois
                ref++; // Incrementa a referência
                while ((dialogConteudo.at(ref) != '\n') || (ref == (dialogConteudo.size()-1))) { // Percorre o arquivo procurando pela quebra de linha
                    token.insert(ref,dialogConteudo.at(ref)); // Adiciona o char atual ao Token
                    ref++; // Incrementa a referência
                } // Sai do loop pois achou uma quebra de linha
                for (int i=0; i < ref; i++) { // Percorre o token formado para inserir na lista de tokens
                    dialog += token.at(i); // Cria uma String com os char do Token
                    dialogConteudo.remove(0,1); // Deleta sempre o char lido
                }
                if (dialog.size() > 0) // Só cria novo token se este tivar algum char
                    tokens.insert(tokens.size(),new Token(dialog)); // Adiciona na lista de tokens o token formado
                ref = 0; // Zera a referência
                token.clear(); // Limpa a variável que cria o token temporariamente
            } else if (dialogConteudo.at(ref) == 42) { // Se o char na posição ref for *
                token.insert(ref,dialogConteudo.at(ref)); // Insere o * no token para poder ser corretamente identificado como comentário depois
                ref++; // Incrementa a referência
                while (ref < (dialogConteudo.size()-1)) { // Percorre o arquivo procurando por * que indicia o inicio do fim do comentário ou até acabar o arquivo
                    token.insert(ref,dialogConteudo.at(ref)); // Adiciona o char atual ao Token
                    if (dialogConteudo.at(ref) == 42) {
                        ref++;
                        if (ref <= (dialogConteudo.size()-1)) {
                            if (dialogConteudo.at(ref) == 47) {
                                token.insert(ref,dialogConteudo.at(ref)); // Adiciona o char atual ao Token
                                ref++;
                                break;
                            } else {
                                ref--;
                            }
                        } else {
                            ref--;
                        }

                    }
                    ref++; // Incrementa a referência

                }

                for (int i=0; i < ref; i++) { // Percorre o token formado para inserir na lista de tokens
                    dialog += token.at(i); // Cria uma String com os char do Token
                    dialogConteudo.remove(0,1); // Deleta sempre o char lido
                }
                if (dialog.size() > 0) // Só cria novo token se este tivar algum char
                    tokens.insert(tokens.size(),new Token(dialog)); // Adiciona na lista de tokens o token formado
                ref = 0; // Zera a referência
                token.clear(); // Limpa a variável que cria o token temporariamente
            } else {
                dialogConteudo.remove(0,1); // Deleta sempre o char lido
            }

        } else if (token.at(ref) ==  ' ') { // O char atual é um espaço ?
            for (int i=0; i < ref; i++) // Se for, percorre da referência até a posição do espaço
                dialog += token.at(i); // Cria uma String com os char da referencia até o espaço
            if (dialog.size() > 0) // Só cria novo token se for identificado algum valor para o token (evita criar token para o enter)
                tokens.insert(tokens.size(),new Token(dialog)); // Adiciona na lista de tokens o token formado
            ref = 0; // Zera a referência
            token.clear();
            dialogConteudo.remove(0,1); // Deleta sempre o char lido
        } else if (token.at(ref) ==  '\n') { // O char atual é um Enter ?
            for (int i=0; i < ref; i++) // Se for, percorre da referência até a posição do Enter
                dialog += token.at(i); // Cria uma String com os char da referencia até o Enter
            if (dialog.size() > 0) // Só cria novo token se for identificado algum valor para o token (evita criar token para o enter)
                tokens.insert(tokens.size(),new Token(dialog)); // Adiciona na lista de tokens o token formado
            ref = 0; // Zera a referência
            token.clear();
            dialogConteudo.remove(0,1); // Deleta sempre o char lido
        } else { // Se o char atual não é um espaço
            ref++; // Incrementa a referência
            dialogConteudo.remove(0,1); // Deleta sempre o char lido
        }

    }

    QString tokensIdentificados = "Tokens Identificados na analise Lexica \n";
    QString tokensNaoIdentificados = "Tokens que geraram erro na analise lexica \n";
    for (int i=0; i < tokens.size(); i++) {
        Token * dialog = tokens.at(i);
        if (dialog->getTipoDeToken() != "NAO")
            tokensIdentificados += dialog->getToken() + " = " + dialog->getTipoToken() + " \n";
        if (dialog->getTipoDeToken() == "NAO")
            tokensNaoIdentificados += " Erro de sintaxe no token "+dialog->getToken() +" \n";
    }
    ui->textEditCodigoIntermediario->clear();
    ui->textEditCodigoIntermediario->setText(tokensIdentificados+"\n" + tokensNaoIdentificados);

    // Realiza a análise Sintática
    QString tokensLinha = "";
    linhas = new QList <QString>();
    linhas->clear();

    for (int i=0; i < tokens.size(); i++) {
        Token * dialog = tokens.at(i);
        if (dialog->getTipoDeToken() != "COMENTARIO") {
            tokensLinha += dialog->getTipoDeToken() + " ";
            if ((dialog->getToken() == ";") || (dialog->getToken() == "{")) {
                linhas->push_back(tokensLinha);
                tokensLinha.clear();
            }
            if (dialog->getToken() == "}") {
                if ((i+1) >= tokens.size()) {
                    linhas->push_back(tokensLinha);
                    tokensLinha.clear();
                } else {
                    Token * tmp = tokens.at(i+1);
                    if (tmp->getToken() != "senao") {
                        linhas->push_back(tokensLinha);
                        tokensLinha.clear();
                    }
                }
            }
        }
    }

    Regras * tmp = new Regras();
    QString codigoCompilado = "";

    linhas = tmp->validaLinha(linhas);

    for(int i=0; i<linhas->size(); i++) {
        codigoCompilado += linhas->at(i) + "\n";
    }

    ui->textEditCodigoCompilado->clear();
    ui->textEditCodigoCompilado->setText(codigoCompilado);
}