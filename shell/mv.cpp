#include <iostream>
#include <cstring>
#include <cerrno>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <origem> <destino>" << std::endl;
        return 1;
    }
    //Aqui estou incluindo as bibliotecas necessárias para o programa. iostream é usada para entrada e saída padrão, cstring é necessária para utilizar a função strerror() que converte códigos de erro em mensagens de erro legíveis, cerrno é utilizada para acessar a variável errno que armazena códigos de erro de chamadas de sistema, e unistd.h é usada para acessar a chamada de sistema rename().//
//Aqui estou verificando se o programa foi chamado com exatamente três argumentos: o nome do próprio programa, o nome do arquivo de origem e o nome do arquivo de destino. Se o número de argumentos estiver incorreto, uma mensagem de erro é exibida na saída de erro padrão (std::cerr) indicando o uso correto do programa, e o programa termina com um código de erro (return 1;).//
    const char* origem = argv[1];
    const char* destino = argv[2];
    //Aqui estou atribuindo os nomes dos arquivos de origem e destino aos ponteiros de caracteres origem e destino, respectivamente, com base nos argumentos fornecidos na linha de comando.//

    // Move o arquivo
    if (rename(origem, destino) != 0) {
        std::cerr << "Erro ao mover o arquivo: " << strerror(errno) << std::endl;
        return 1;
    }
    //Aqui estou utilizando a função rename() para mover o arquivo da origem para o destino. Se não for possível mover o arquivo (ou seja, rename() retornar um valor diferente de zero), uma mensagem de erro é exibida na saída de erro padrão, indicando o tipo de erro que ocorreu, e o programa termina com um código de erro.//

    std::cout << "Arquivo movido com sucesso." << std::endl;
    return 0;
}
//Finalmente, se a operação de movimentação do arquivo for bem-sucedida, uma mensagem de sucesso é impressa na saída padrão e o programa termina com um código de saída zero, indicando que foi executado com sucesso.//
