#include <iostream>
#include <filesystem>
#include <sys/stat.h>

namespace fs = std::filesystem;
// void change_permissions(const std::string& path, mode_t mode): Aqui estamos definindo uma função chamada change_permissions que recebe dois parâmetros: o caminho do arquivo ou diretório (path) como uma string e o modo de permissões (mode) como um mode_t. Esta função não retorna nenhum valor (void). try {: Inicia um bloco try para capturar exceções que podem ocorrer durante a execução das instruções dentro deste bloco.//
void change_permissions(const std::string& path, mode_t mode) {
    try {
        // Verifica se o caminho existe 
        if (fs::exists(path)) {
            // Altera as permissões do arquivo ou diretório
            //if (fs::exists(path)): Verifica se o caminho especificado pelo usuário existe usando a função //
            //fs::exists(). Se o caminho existir, continuamos com a alteração das permissões. Se não existir, exibimos uma mensagem de erro.//
            //chmod(path.c_str(), mode): Utiliza a função chmod() da biblioteca <sys/stat.h> para alterar as permissões do arquivo ou diretório especificado pelo caminho path. O path.c_str() é usado para converter a string path em um array de caracteres do tipo const char* exigido pela função chmod(). O mode representa as permissões que desejamos definir.//
            if (chmod(path.c_str(), mode) == 0) {
                std::cout << "Permissões de '" << path << "' alteradas com sucesso." << std::endl;
                //std::cout << "Permissões de '" << path << "' alteradas com sucesso." << std::endl;: Se a operação chmod() for bem-sucedida, exibimos uma mensagem informando ao usuário que as permissões foram alteradas com sucesso.//
            } else {
                std::cerr << "Erro ao alterar as permissões de '" << path << "'" << std::endl;
            }
        } else {
            std::cerr << "Erro: '" << path << "' não encontrado." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro ao alterar as permissões de '" << path << "': " << e.what() << std::endl;
    }
}
//catch (const std::exception& e): Captura e trata exceções que podem ser lançadas durante a execução das instruções no bloco try.//
//std::cerr << "Erro ao alterar as permissões de '" << path << "': " << e.what() << std::endl;: Se ocorrer uma exceção, exibimos uma mensagem de erro indicando o erro específico que ocorreu. A função e.what() retorna uma descrição da exceção lançada.//

int main() {
    std::string file_path;
    mode_t permissions;

    std::cout << "Informe o caminho do arquivo/diretório: ";
    std::cin >> file_path;

    std::cout << "Informe as permissões (em octal): ";
    std::cin >> std::oct >> permissions;

    change_permissions(file_path, permissions);

    return 0;
}
