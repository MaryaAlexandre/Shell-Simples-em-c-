#include <iostream>
#include <sys/stat.h>
#include <string>

bool createDirectory(const std::string& path) {
    // Verifica se o diretório já existe
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        // Se não existe, cria o diretório
        if (mkdir(path.c_str(), 0777) != 0) {
            // Se ocorrer um erro ao criar o diretório, retorna falso
            std::cerr << "Erro ao criar o diretório." << std::endl;
            return false;
        }
        return true;
    } else if (!(info.st_mode & S_IFDIR)) {
        // Se o caminho já existe, mas não é um diretório, retorna falso
        std::cerr << "O caminho especificado já existe, mas não é um diretório." << std::endl;
        return false;
    }
    // Se o diretório já existe, retorna verdadeiro
    return true;
}

int main() {
    std::string directoryName = "test_directory"; // Nome do diretório a ser criado

    if (createDirectory(directoryName)) {
        std::cout << "Diretório criado com sucesso." << std::endl;
    } else {
        std::cerr << "Falha ao criar o diretório." << std::endl;
        return 1;
    }

    return 0;
}
//Utilizamos a função mkdir da biblioteca sys/stat.h para criar o diretório. Antes de chamar mkdir, verificamos se o diretório já existe usando stat. Se o diretório já existir, a função mkdir não será chamada. Caso o caminho especificado exista, mas não seja um diretório, retornamos falso indicando uma falha na criação. A função createDirectory retorna verdadeiro se o diretório for criado com sucesso, e falso em caso de erro.//
