#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void remove_directory(const std::string& path) {
    try {
        // Verifica se o caminho existe e é um diretório
        if (fs::exists(path) && fs::is_directory(path)) {
            // Itera sobre os itens no diretório
            for (const auto& entry : fs::directory_iterator(path)) {
                // Se o item for um diretório, chama recursivamente remove_directory()
                if (fs::is_directory(entry.path())) {
                    remove_directory(entry.path());
                }
                // Se o item for um arquivo, o remove
                else {
                    fs::remove(entry.path());
                }
            }
            // Remove o diretório vazio
            fs::remove(path);
            std::cout << "Diretório '" << path << "' removido com sucesso." << std::endl;
        } else {
            std::cerr << "Erro: '" << path << "' não é um diretório válido." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro ao remover diretório '" << path << "': " << e.what() << std::endl;
    }
}

int main() {
    std::string directory_to_remove;
    std::cout << "Informe o caminho do diretório a ser removido: ";
    std::cin >> directory_to_remove;

    remove_directory(directory_to_remove);

    return 0;
}
