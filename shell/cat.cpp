#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo>" << std::endl;
        return 1;
    }
//Este trecho verifica se o programa foi chamado com exatamente dois argumentos: o nome do próprio programa e o nome do arquivo que você deseja ler. Se o número de argumentos estiver incorreto, uma mensagem de erro é exibida na saída de erro padrão (std::cerr) indicando o uso correto do programa, e o programa termina com um código de erro (return 1;).//
    const char* arquivo = argv[1];
//Aqui estamos atribuindo o nome do arquivo que você deseja ler à variável arquivo, com base no segundo argumento fornecido na linha de comando.//
    //Aqui estamos atribuindo o nome do arquivo que você deseja ler à variável arquivo, com base no segundo argumento fornecido na linha de comando.//
    std::ifstream file(arquivo);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }
//Estamos abrindo o arquivo especificado em modo de leitura (std::ifstream). Se não for possível abrir o arquivo, uma mensagem de erro é exibida na saída de erro padrão e o programa termina com um código de erro.//
    std::string linha;
    while (std::getline(file, linha)) {
        std::cout << linha << std::endl;
    }
//Aqui estamos lendo o conteúdo do arquivo linha por linha usando a função std::getline(). Cada linha é armazenada na variável linha e depois é impressa na saída padrão (std::cout).//
    file.close();

    return 0;
}
