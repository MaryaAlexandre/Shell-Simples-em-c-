#include <iostream>     // Inclui a biblioteca padrão de entrada e saída do C++
#include <unistd.h>     // Inclui a biblioteca POSIX para usar funções como fork, execve e getcwd
#include <sys/wait.h>   // Inclui a biblioteca para usar a função waitpid
#include <vector>       // Inclui a biblioteca padrão do C++ para usar o contêiner std::vector
#include <cstring>      // Inclui a biblioteca padrão do C++ para manipulação de strings C

#define HISTORY_SIZE 10 // Define uma constante para o tamanho máximo do histórico de comandos
std::vector<std::string> history; // Declara um vetor de strings para armazenar o histórico de comandos

// Função para gravar o comando no histórico
void record_command(const std::string &command) {
    if (history.size() < HISTORY_SIZE) { // Verifica se o tamanho do histórico é menor que HISTORY_SIZE
        history.push_back(command);      // Adiciona o comando ao histórico
    } else {
        history.erase(history.begin());  // Remove o comando mais antigo do histórico
        history.push_back(command);      // Adiciona o novo comando ao histórico
    }
}

// Função para exibir o histórico de comandos
void show_history() {
    for (size_t i = 0; i < history.size(); ++i) {   // Itera sobre o histórico
        std::cout << i << " " << history[i] << std::endl; // Imprime o índice e o comando correspondente no histórico
    }
}

// Função para processar o comando
void process_command(const std::string &command_line) {
    record_command(command_line); // Grava a linha de comando no histórico

    // Tokeniza a linha de comando
    char *command_cstr = new char[command_line.size() + 1]; // Aloca memória para armazenar a linha de comando como uma string C
    strcpy(command_cstr, command_line.c_str());             // Copia a linha de comando para a string C

    char *token = strtok(command_cstr, " "); // Divide a linha de comando em tokens, separando pelos espaços
    if (!token) {                            // Se não houver tokens
        delete[] command_cstr;               // Libera a memória alocada
        return;                              // Retorna
    }

    std::string command = token;    // Armazena o primeiro token como o comando
    std::vector<char*> args;        // Declara um vetor para armazenar os argumentos do comando
    args.push_back(token);          // Adiciona o primeiro token (comando) aos argumentos

    while ((token = strtok(NULL, " ")) != NULL) { // Itera sobre os tokens restantes
        args.push_back(token);        // Adiciona cada token aos argumentos
    }
    args.push_back(NULL);             // Adiciona um ponteiro nulo ao final dos argumentos (necessário para execve)

    delete[] command_cstr;            // Libera a memória alocada para a string C

    // Comandos internos
    if (command == "exit") {          // Se o comando for "exit"
        exit(0);                      // Termina o programa
    } else if (command == "pwd") {    // Se o comando for "pwd"
        char cwd[1024];               // Declara um array de caracteres para armazenar o diretório atual
        if (getcwd(cwd, sizeof(cwd)) != NULL) { // Obtém o diretório atual
            std::cout << cwd << std::endl; // Imprime o diretório atual
        } else {
            perror("getcwd");         // Exibe uma mensagem de erro se getcwd falhar
        }
        return;                       // Retorna
    } else if (command.substr(0, 3) == "cd ") { // Se o comando começar com "cd "
        std::string dir = command.substr(3); // Obtém o diretório especificado no comando
        if (chdir(dir.c_str()) != 0) {  // Muda o diretório atual
            perror("chdir");           // Exibe uma mensagem de erro se chdir falhar
        }
        return;                        // Retorna
    } else if (command == "history") { // Se o comando for "history"
        show_history();                // Exibe o histórico de comandos
        return;                        // Retorna
    }

    // Lista de diretórios para buscar o comando
    std::vector<std::string> directories = {"./shell", "/bin", "/usr/bin", "/usr/local/bin"};
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
        std::string command;
        getline(std::cin, command); // Lê o comando digitado pelo usuário
        process_command(command); // Processa o comando
    }
    return 0; // Indica que o programa terminou com sucesso
}
