#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_origem> <arquivo_destino>" << std::endl;
        return 1;
    }
    //Esta parte verifica se o programa foi chamado com exatamente três argumentos: o nome do próprio programa, o nome do arquivo de origem e o nome do arquivo de destino. Se o número de argumentos estiver incorreto, uma mensagem de erro é exibida na saída de erro padrão (std::cerr) indicando o uso correto do programa, e o programa termina com um código de erro (return 1;).//
//Esta parte verifica se o programa foi chamado com exatamente três argumentos: o nome do próprio programa, o nome do arquivo de origem e o nome do arquivo de destino. Se o número de argumentos estiver incorreto, uma mensagem de erro é exibida na saída de erro padrão (std::cerr) indicando o uso correto do programa, e o programa termina com um código de erro (return 1;).//
    const char* origem = argv[1];
    const char* destino = argv[2];
//Aqui estou atribuindo os nomes dos arquivos de origem e destino aos ponteiros de caracteres origem e destino, respectivamente, com base nos argumentos fornecidos na linha de comando.//
    std::ifstream arquivo_origem(origem, std::ios::binary);
    if (!arquivo_origem) {
        std::cerr << "Erro ao abrir o arquivo de origem." << std::endl;
        return 1;
    }
    //Estou abrindo o arquivo de origem em modo de leitura binária (std::ios::binary). Se não for possível abrir o arquivo de origem, uma mensagem de erro é exibida na saída de erro padrão e o programa termina com um código de erro.//

    std::ofstream arquivo_destino(destino, std::ios::binary);
    if (!arquivo_destino) {
        std::cerr << "Erro ao criar o arquivo de destino." << std::endl;
        return 1;
    }
//Aqui estou abrindo o arquivo de destino em modo de escrita binária. Se não for possível criar o arquivo de destino, uma mensagem de erro é exibida na saída de erro padrão e o programa termina com um código de erro.//
    arquivo_destino << arquivo_origem.rdbuf();

    arquivo_origem.close();
    arquivo_destino.close();
    //Aqui estou fechando ambos os arquivos após a cópia ter sido concluída, para liberar os recursos associados.//

    std::cout << "Arquivo copiado com sucesso." << std::endl;
    return 0;
}
//Finalmente, estou imprimindo uma mensagem de sucesso na saída padrão e retornando 0 para indicar que o programa foi executado com sucesso//
