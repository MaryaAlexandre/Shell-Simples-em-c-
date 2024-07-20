#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <cstring>
//#include <unistd.h> biblioteca para fornecer acesso a várias chamadas de sistema POSIX
//#include <sys/wait.h> biblioteca para fornecer funções para esperar por mudanças de estado em processos filhos;
//#include < vector> biblioteca padrão para uso de vetores (arrays dinâmicos)
//#include <cString> biblioteca para manipulção de strings em c++

#define HISTORY_SIZE 10
// Define o tamanho máximo do histórico de comandos como 10
std::vector<std::string> history;
// Declara um vetor para armazenar o histórico de comandos

void record_command(const std::string &command) {
    if (history.size() < HISTORY_SIZE) {
        history.push_back(command);
    } else {
        history.erase(history.begin());
        history.push_back(command);
    }
}
//Declarei a função 'record_command' que vai receber uma String como parâmetro e adicionará o comando ao histórico. Ela verifica se o histórico - Comando como argumento 
// Verifica se o histórico atual tem menos comandos do que o limite máximo;
// Adiciona o novo comando ao final do histórico, se o o histórico já tiver o tamanho máximo, remove o comando mais antigo (primeiro comando), adiciona o novo comando ao final do histórico

void show_history() {
    for (size_t i = 0; i < history.size(); ++i) {
        std::cout << i << " " << history[i] << std::endl;
    }
}
// Itera sobre o histórico de comandos e exibe o índice e o comando correspondente
// função declarada não recebe argumentos, itera sobre o vetor de histórico, exibe o índice e o comando correspondente

void process_command(const std::string &command) {
    record_command(command);
  // declara a função 'process_command' que recebe um comando como argumento e adiciona o comando ao histórico.

    // Comandos internos
    if (command == "exit") { // verificar se o comando é exit e sai do programa
        exit(0); 
    } else if (command == "pwd") { // verifica se o comando é pwd e exibe o diretório atual
        char cwd[1024]; // declara uma variável(buffer) para armazenar o caminho do diretório atual
        if (getcwd(cwd, sizeof(cwd)) != NULL) { // verifica se o comando é pwd e exibe o diretório atual através da função getcwd que vê o tamanho do buffer
            std::cout << cwd << std::endl; // exibir o diretório atual
        } else {
            perror("getcwd"); //se falhar getcwd vai exibir uma mensagem de erro
        }
        return;
    } else if (command.substr(0, 3) == "cd ") { // verifica se o comando é cd seguido de um espaço
        std::string dir = command.substr(3); // obtém o diretório alvo
        if (chdir(dir.c_str()) != 0) { // tenta mudar o diretório atual para o diretório alvo usando a função chdir
            perror("chdir");
        }
        return;
    } else if (command == "history") { // verifica se o comando é history e exibe o histórico de comandos
        show_history(); // chama a função para exibir o histórico de comandos
        return;
    }

    // Comandos externos 
    std::string absolute_path = "/bin/" + command;//constrói um caminho para o comando, através de concatenação 
    if (access(absolute_path.c_str(), F_OK) == 0) { // verificar se o arquivo existe no diretório
        if (access(absolute_path.c_str(), X_OK) == 0) { // verificar se o arquivo é executável
            pid_t pid = fork(); // caso sim cria um processo filho 
            if (pid < 0) { // verifica se houve erro ao criar o processo filho
                std::cout << "Erro de execução!" << std::endl; // vai exibir uma mensagem de erro
                return;
            } else if (pid == 0) { // se for o processo filho
                char *argv[2] = { (char *)command.c_str(), nullptr }; // prepara os argumentos para o comando 
                execve(absolute_path.c_str(), argv, NULL); // executa o comando usando execve
            } else { // Processo pai
                waitpid(pid, nullptr, 0); // espera pelo processo filho terminar
            }
        } else { // se não for  executável
            std::cout << "permission denied: " << command << std::endl;// vai exibir uma mensagem de permissão negada 
        }
    } else { // Arquivo não existe
        std::cout << "Command not found: " << command << std::endl; // mensagem de comando não encontrado
    }
}
//Função Principal
int main() { // declara a função do programa 
    while (true) { // entra em um laço infinito 
        std::cout << "$> "; // exibe o prompt '$>'
        std::string command; // declara uma variável para armazenar o comando digitado pelo usuário
        getline(std::cin, command); // lê o comando digitado pelo usuário
        process_command(command);// processa o comando usando a função 'process_command'
    }
    return 0; // indica que o programa terminou com sucesso ( embora nesse caso o programa saia do laço infinito)
}

