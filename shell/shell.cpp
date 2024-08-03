#include <iostream> // Inclui a biblioteca de entrada e saída padrão do C++
#include <unistd.h> // Inclui a biblioteca para chamadas de sistema POSIX, como fork() e execve()
#include <sys/wait.h> // Inclui a biblioteca para chamadas de sistema de espera de processos, como waitpid()
#include <vector> // Inclui a biblioteca de vetores do C++
#include <cstring> // Inclui a biblioteca de manipulação de strings em C

#define HISTORY_SIZE 10 // Define o tamanho máximo do histórico de comandos como 10
std::vector<std::string> history; // Declara um vetor para armazenar o histórico de comandos

// Função para gravar o comando no histórico
void record_command(const std::string &command) {
    if (history.size() < HISTORY_SIZE) { // Se o histórico tiver menos de 10 comandos
        history.push_back(command); // Adiciona o comando ao histórico
    } else {
        history.erase(history.begin()); // Remove o comando mais antigo do histórico
        history.push_back(command); // Adiciona o novo comando ao histórico
    }
}

// Função para exibir o histórico de comandos
void show_history() {
    for (size_t i = 0; i < history.size(); ++i) { // Itera sobre o histórico
        std::cout << i << " " << history[i] << std::endl; // Exibe o índice e o comando correspondente
    }
}

// Função para processar comandos
void process_command(std::string command_line) {
    record_command(command_line); // Grava o comando no histórico

    char *command_cstr = new char[command_line.size() + 1]; // Aloca memória para a cópia do comando
    strcpy(command_cstr, command_line.c_str()); // Copia o comando para a memória alocada
    char *token = strtok(command_cstr, " "); // Separa o primeiro token do comando
    if (!token) { // Se não houver token, libera a memória e retorna
        delete[] command_cstr;
        return;
    }
    std::string command = token; // Armazena o primeiro token como comando
    std::vector<char *> args; // Declara um vetor para os argumentos
    args.push_back(token); // Adiciona o comando ao vetor de argumentos

    while ((token = strtok(NULL, " ")) != NULL) { // Itera sobre os tokens restantes
        args.push_back(token); // Adiciona cada token ao vetor de argumentos
    }
    args.push_back(nullptr); // Adiciona nullptr ao final do vetor de argumentos (necessário para execve)
    delete[] command_cstr; // Libera a memória alocada

    // Comandos internos
    if (command == "exit") { // Comando para sair do programa
        exit(0); // Encerra o programa
    } else if (command == "pwd") { // Comando para mostrar o diretório atual
        char cwd[1024]; // Declara um buffer para armazenar o diretório atual
        if (getcwd(cwd, sizeof(cwd)) != NULL) { // Obtém o diretório atual
            std::cout << cwd << std::endl; // Exibe o diretório atual
        } else {
            perror("getcwd"); // Exibe uma mensagem de erro se getcwd falhar
        }
        return;
    } else if (command == "history") { // Comando para exibir o histórico
        show_history(); // Chama a função para exibir o histórico
        return;
    } else if (command.substr(0, 2) == "cd") { // Comando para mudar de diretório
        if (args.size() < 2) { // Verifica se há um argumento para o comando cd
            std::cerr << "cd: missing argument" << std::endl; // Exibe uma mensagem de erro se não houver argumento
        } else {
            if (chdir(args[1]) != 0) { // Muda para o diretório especificado
                perror("chdir"); // Exibe uma mensagem de erro se chdir falhar
            }
        }
        return;
    }

    // Lista de diretórios para buscar o comando
    std::vector<std::string> directories = {"/bin", "/usr/bin", "/usr/local/bin"};
    bool command_found = false; // Flag para indicar se o comando foi encontrado
    for (const std::string &dir : directories) { // Itera sobre os diretórios
        std::string absolute_path = dir + "/" + command; // Cria o caminho absoluto para o comando
        if (access(absolute_path.c_str(), F_OK) == 0) { // Verifica se o arquivo existe
            if (access(absolute_path.c_str(), X_OK) == 0) { // Verifica se o arquivo é executável
                pid_t pid = fork(); // Cria um processo filho
                if (pid < 0) { // Verifica se houve erro ao criar o processo filho
                    std::cout << "Erro de execução!" << std::endl; // Exibe uma mensagem de erro
                    return;
                } else if (pid == 0) { // Processo filho
                    execve(absolute_path.c_str(), args.data(), NULL); // Executa o comando
                    perror("execve"); // Exibe uma mensagem de erro se execve falhar
                    exit(EXIT_FAILURE); // Encerra o processo filho se execve falhar
                } else { // Processo pai
                    waitpid(pid, nullptr, 0); // Espera pelo processo filho terminar
                }
                command_found = true; // Indica que o comando foi encontrado
                break; // Sai do loop
            } else { // Arquivo não é executável
                std::cout << "Permission denied: " << command << std::endl; // Exibe uma mensagem de erro
                command_found = true; // Indica que o comando foi encontrado
                break; // Sai do loop
            }
        }
    }

    if (!command_found) { // Se o comando não foi encontrado
        std::cout << "Command not found: " << command << std::endl; // Exibe uma mensagem de erro
    }
}

// Função principal
int main() {
    while (true) { // Laço infinito
        std::cout << "$> "; // Prompt
        std::string command; // Declara uma string para armazenar o comando
        getline(std::cin, command); // Lê o comando digitado pelo usuário
        process_command(command); // Processa o comando
    }
    return 0; // Indica que o programa terminou com sucesso
}


