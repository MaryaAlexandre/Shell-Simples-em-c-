#include <iostream>
#include <sys/sysinfo.h>
//Aqui estou incluindo as bibliotecas necessárias para o programa. iostream é usada para entrada e saída padrão, enquanto sys/sysinfo.h é usada para obter informações sobre o sistema.//
int main() {
    //Começo aqui a definição da função main(), que é o ponto de entrada do programa. Neste caso, não estou passando argumentos para o programa.//
    struct sysinfo info;
    //Eu declaro uma estrutura sysinfo chamada info. Vou usá-la para armazenar as informações sobre o sistema.//
    
    if (sysinfo(&info) != 0) {
        std::cerr << "Erro ao obter informações de sistema." << std::endl;
        return 1;
    }
    //Aqui estou chamando a função sysinfo() para obter informações sobre o sistema e passo um ponteiro para a estrutura info para armazenar essas informações. Se a função sysinfo() falhar (ou seja, retornar um valor diferente de zero), imprimo uma mensagem de erro na saída de erro padrão (std::cerr) e encerro o programa com um código de erro (return 1;).//

    long uptime_seconds = info.uptime;
    int uptime_days = uptime_seconds / (60 * 60 * 24);
    int uptime_hours = (uptime_seconds % (60 * 60 * 24)) / (60 * 60);
    int uptime_minutes = (uptime_seconds % (60 * 60)) / 60;
    uptime_seconds %= 60;
    //Aqui estou calculando o tempo de atividade do sistema a partir das informações obtidas pela chamada à função sysinfo(). Divido o tempo de atividade total em segundos para calcular os dias, horas, minutos e segundos correspondentes de tempo de atividade.//

    std::cout << "Tempo de atividade do sistema: ";
    std::cout << uptime_days << " dias, ";
    std::cout << uptime_hours << " horas, ";
    std::cout << uptime_minutes << " minutos e ";
    std::cout << uptime_seconds << " segundos." << std::endl;
    //Agora, estou imprimindo na saída padrão (std::cout) o tempo de atividade do sistema formatado de maneira legível.//

    return 0;
}
