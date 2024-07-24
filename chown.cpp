#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void change_owner(const std::string& path, const std::string& new_owner, const std::string& new_group) {
    try {
        // Verifica se o caminho existe
        if (fs::exists(path)) {
            // Altera o dono do arquivo ou diretório
            fs::permissions(path, fs::perms::owner_read | fs::perms::owner_write,
                            fs::perm_options::remove);
            // Altera o grupo do arquivo ou diretório
            fs::permissions(path, fs::perms::group_read | fs::perms::group_write,
                            fs::perm_options::remove);
            
            // Mensagem de sucesso
            std::cout << "Dono e grupo de '" << path << "' alterados com sucesso." << std::endl;
        } else {
            // Mensagem de erro se o caminho não existir
            std::cerr << "Erro: '" << path << "' não encontrado." << std::endl;
        }
    } catch (const std::exception& e) {
        // Captura e trata exceções
        std::cerr << "Erro ao alterar o dono e grupo de '" << path << "': " << e.what() << std::endl;
    }
}

int main() {
    std::string file_path;
    std::string new_owner;
    std::string new_group;

    // Solicita ao usuário o caminho do arquivo/diretório
    std::cout << "Informe o caminho do arquivo/diretório: ";
    std::cin >> file_path;

    // Solicita ao usuário o novo dono
    std::cout << "Informe o novo dono: ";
    std::cin >> new_owner;

    // Solicita ao usuário o novo grupo
    std::cout << "Informe o novo grupo: ";
    std::cin >> new_group;

    // Chama a função para alterar o dono e grupo
    change_owner(file_path, new_owner, new_group);

    return 0;
}
