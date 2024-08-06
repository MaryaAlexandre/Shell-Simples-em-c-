#include <iostream>     // Inclui a biblioteca padrão de entrada e saída do C++
#include <unistd.h>     // Inclui a biblioteca POSIX para usar funções como fork, execve e getcwd
#include <sys/wait.h>   // Inclui a biblioteca para usar a função waitpid
#include <vector>       // Inclui a biblioteca padrão do C++ para usar o contêiner std::vector
#include <cstring>      // Inclui a biblioteca padrão do C++ para manipulação de strings C
#include <sys/stat.h>   // Inclui a biblioteca para usar funções de manipulação de arquivos
#include <fstream>      // Inclui a biblioteca para manipulação de arquivos em C++

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

// Função para criar um diretório
void make_directory(const char* dir) {
    if (mkdir(dir, 0777) == -1) { // Cria o diretório com permissões 0777
        perror("mkdir");          // Exibe uma mensagem de erro se mkdir falhar
    }
}

// Função para remover um arquivo ou diretório
void remove_file(const char* file) {
    if (remove(file) == -1) { // Remove o arquivo ou diretório
        perror("remove");     // Exibe uma mensagem de erro se remove falhar
    }
}

// Função para copiar um arquivo
void copy_file(const char* source, const char* destination) {
    std::ifstream src(source, std::ios::binary);       // Abre o arquivo fonte
    std::ofstream dst(destination, std::ios::binary);  // Cria o arquivo de destino
    dst << src.rdbuf();                                // Copia o conteúdo do arquivo fonte para o arquivo de destino
}

// Função para exibir o conteúdo de um arquivo
void cat_file(const char* file) {
    std::ifstream infile(file); // Abre o arquivo para leitura
    std::string line;
    while (std::getline(infile, line)) { // Lê o arquivo linha por linha
        std::cout << line << std::endl;  // Imprime cada linha
    }
}

// Função para mudar o proprietário e grupo de um arquivo
void change_owner(const char* file, const char* owner_group) {
    std::string command = "chown " + std::string(owner_group) + " " + std::string(file);
    system(command.c_str()); // Usa o comando system para executar chown
}

// Função para processar o comando
void process_command(const std::string &command_line) {
    record_command(command_line); // Grava a linha de comando no histórico

    // Tokeniza a linha de comando
    char *command_cstr = new char[command_line.size() + 1]; // Aloca memória para armazenar a linha de comando como uma string C
    strcpy(command_cstr, command_line.c_str());             // Copia a linha de comando para a string C

    std::vector<char*> args;        // Declara um vetor para armazenar os argumentos do comando
    char *token = strtok(command_cstr, " "); // Divide a linha de comando em tokens, separando pelos espaços
    while (token != nullptr) { // Itera sobre os tokens
        args.push_back(token);        // Adiciona cada token aos argumentos
        token = strtok(NULL, " ");
    }
    args.push_back(nullptr);             // Adiciona um ponteiro nulo ao final dos argumentos (necessário para execve)

    std::string command = args[0]; // O primeiro argumento é o comando

    // Comandos internos
    if (command == "exit") {          // Se o comando for "exit"
        delete[] command_cstr; // Libera a memória alocada
        exit(0);                      // Termina o programa
    } else if (command == "pwd") {    // Se o comando for "pwd"
        char cwd[1024];               // Declara um array de caracteres para armazenar o diretório atual
        if (getcwd(cwd, sizeof(cwd)) != nullptr) { // Obtém o diretório atual
            std::cout << cwd << std::endl; // Imprime o diretório atual
        } else {
            perror("getcwd");         // Exibe uma mensagem de erro se getcwd falhar
        }
        delete[] command_cstr; // Libera a memória alocada
        return;                       // Retorna
    } else if (command == "cd") { // Se o comando for "cd"
        if (args.size() < 2) { // Verifica se foi passado um diretório
            std::cerr << "cd: missing operand" << std::endl;
        } else {
            if (chdir(args[1]) != 0) {  // Muda o diretório atual
                perror("chdir");           // Exibe uma mensagem de erro se chdir falhar
            }
        }
        delete[] command_cstr; // Libera a memória alocada
        return;                        // Retorna
    } else if (command == "history") { // Se o comando for "history"
        show_history();                // Exibe o histórico de comandos
        delete[] command_cstr; // Libera a memória alocada
        return;                        // Retorna
    } else if (command == "mkdir") { // Se o comando for "mkdir"
        if (args.size() < 2) { // Verifica se foi passado um diretório
            std::cerr << "mkdir: missing operand" << std::endl;
        } else {
            make_directory(args[1]); // Cria o diretório
        }
        delete[] command_cstr; // Libera a memória alocada
        return;                        // Retorna
    } else if (command == "rm") { // Se o comando for "rm"
        if (args.size() < 2) { // Verifica se foi passado um arquivo ou diretório
            std::cerr << "rm: missing operand" << std::endl;
        } else {
            remove_file(args[1]); // Remove o arquivo ou diretório
        }
        delete[] command_cstr; // Libera a memória alocada
        return;                        // Retorna
    } else if (command == "cp") { // Se o comando for "cp"
        if (args.size() < 3) { // Verifica se foram passados os arquivos fonte e destino
            std::cerr << "cp: missing operand" << std::endl;
        } else {
            copy_file(args[1], args[2]); // Copia o arquivo
        }
        delete[] command_cstr; // Libera a memória alocada
        return;                        // Retorna
    } else if (command == "cat") { // Se o comando for "cat"
        if (args.size() < 2) { // Verifica se foi passado um arquivo
            std::cerr << "cat: missing operand" << std::endl;
        } else {
            cat_file(args[1]); // Exibe o conteúdo do arquivo
        }
        delete[] command_cstr; // Libera a memória alocada
        return;                        // Retorna
    } else if (command == "chown") { // Se o comando for "chown"
        if (args.size() < 3) { // Verifica se foram passados o proprietário:grupo e o arquivo
            std::cerr << "chown: missing operand" << std::endl;
        } else {
            change_owner(args[2], args[1]); // Muda o proprietário e grupo do arquivo
        }
        delete[] command_cstr; // Libera a memória alocada
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
                    std::cerr << "Erro de execução!" << std::endl; // Exibe uma mensagem de erro
                    delete[] command_cstr; // Libera a memória alocada
                    return;
                } else if (pid == 0) { // Processo filho
                    execve(absolute_path.c_str(), args.data(), nullptr); // Executa o comando
                    perror("execve"); // Exibe uma mensagem de erro se execve falhar
                    exit(EXIT_FAILURE); // Encerra o processo filho se execve falhar
                } else { // Processo pai
                    waitpid(pid, nullptr, 0); // Espera pelo processo filho terminar
                }
                command_found = true; // Indica que o comando foi encontrado
                break; // Sai do loop
            } else { // Arquivo não é executável
                std::cerr << "Permission denied: " << command << std::endl; // Exibe uma mensagem de erro
                command_found = true; // Indica que o comando foi encontrado
                break; // Sai do loop
            }
        }
    }

    if (!command_found) { // Se o comando não foi encontrado
        std::cerr << "Command not found: " << command << std::endl; // Exibe uma mensagem de erro
    }

    delete[] command_cstr; // Libera a memória alocada
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
