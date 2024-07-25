#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo>" << std::endl;
        return 1;
    }
//Esta parte do código verifica se o programa foi chamado com exatamente dois argumentos: o nome do próprio programa e o nome do arquivo que se deseja remover. Se o número de argumentos estiver incorreto, uma mensagem de erro é impressa na saída de erro padrão (std::cerr) indicando o uso correto do programa, e o programa termina com um código de erro (return 1;).//
    const char* arquivo = argv[1];
    //Aqui, se atribui o nome do arquivo que se deseja remover à variável arquivo, com base no segundo argumento fornecido na linha de comando.//

    // Remove o arquivo
    if (unlink(arquivo) != 0) {
        std::cerr << "Erro ao remover o arquivo." << std::endl;
        return 1;
    }
    //Agora, aqui se  usando a função unlink() para remover o arquivo especificado. Se a remoção do arquivo falhar (ou seja, unlink() retornar um valor diferente de zero), uma mensagem de erro é impressa na saída de erro padrão e o programa termina com um código de erro.//

    std::cout << "Arquivo removido com sucesso." << std::endl;
    return 0;
}
//Finalmente, se a remoção do arquivo for bem-sucedida, uma mensagem de sucesso é impressa na saída padrão e o programa termina com um código de saída zero, indicando que foi executado com sucesso.//
