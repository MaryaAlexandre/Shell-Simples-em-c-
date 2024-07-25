#include <iostream>
#include <dirent.h>
// Essas são as diretivas de inclusão (#include) que trazem as declarações necessárias das bibliotecas iostream (para entrada e saída padrão) e dirent.h (para operações de diretório).//
int main(int argc, char *argv[]) {
    //Aqui começa a definição da função main(). Ela é o ponto de entrada do seu programa. Os argumentos argc e argv[] permitem que você passe argumentos para o programa a partir da linha de comando.//
    const char *dir_name;

    // Verifica se o diretório foi especificado como argumento
    if (argc == 2) {
        dir_name = argv[1];
    } else {
        // Se nenhum diretório for especificado, usa o diretório de trabalho atual
        dir_name = ".";
    }
    //Aqui se define uma variável dir_name que irá conter o nome do diretório que você deseja listar. Se o programa for chamado com dois argumentos (o próprio nome do programa e o nome do diretório), o segundo argumento é atribuído à variável dir_name. Caso contrário, o diretório atual é utilizado.//

    DIR *dir = opendir(dir_name);
    if (dir == nullptr) {
        std::cerr << "Erro ao abrir o diretório." << std::endl;
        return 1;
    }
    //Se utiliza a função opendir() para abrir o diretório especificado. Se a abertura falhar (ou seja, opendir() retorna nullptr), uma mensagem de erro é impressa na saída de erro padrão (std::cerr) e o programa termina com um código de erro (return 1;).//

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::cout << entry->d_name << std::endl;
    }
    //Neste trecho, se utiliza a função readdir() para ler os arquivos dentro do diretório aberto. A função retorna um ponteiro para uma estrutura dirent, que contém informações sobre o próximo arquivo no diretório. Você imprime o nome de cada arquivo na saída padrão (std::cout).//

    closedir(dir);

    return 0;
}
