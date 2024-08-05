# Shell Simples em C++

Este repositório contém uma implementação de uma shell simples em C++ que demonstra conceitos básicos de gerenciamento de processos em sistemas operacionais Unix e derivados. A shell é capaz de executar comandos internos e externos, manter um histórico de comandos e mudar o diretório de trabalho. 

## Funcionalidades

### Parte 1: Básico

1. **Prompt de Comando**
   - O prompt é exibido como `$> `.
   - O usuário pode digitar comandos e argumentos que serão processados pela shell.

2. **Entrada e Processamento de Comandos**
   - A shell lê uma linha de comando do usuário.
   - A linha é processada para separar o comando dos argumentos.
   - A shell executa o comando, que pode ser um comando interno ou um comando externo.

3. **Execução de Comandos Externos**
   - A shell usa `fork()` para criar um processo filho.
   - O processo filho usa `execve()` para substituir seu código com o código do comando externo.
   - O processo pai espera o processo filho terminar usando `waitpid()`.

4. **Comandos Internos**
   - **`exit`**: Sai da shell e retorna 0.
   - **`pwd`**: Exibe o diretório atual.
   - **`cd dir`**: Muda o diretório atual para `dir`, se o diretório existir.
   - **`history`**: Exibe os últimos 10 comandos digitados.

### Parte 2: Comandos Internos

- **`exit [n]`**
  - Sai da shell. Opcionalmente, pode ser fornecido um valor `n` que será retornado como o status de saída.
  
- **`pwd`**
  - Exibe o caminho do diretório atual.

- **`cd dir`**
  - Muda o diretório atual para o especificado em `dir`.

- **`history [-c] [offset]`**
  - **Sem argumentos**: Exibe os últimos 10 comandos com um índice.
  - **`-c`**: Limpa o histórico de comandos.
  - **`[offset]`**: Executa o comando do histórico correspondente ao `offset`.

### Parte 3: Comandos Externos

- A shell procura comandos em `/bin/` por padrão.
- Se o comando existe e é executável, é executado em um processo filho.
- Se o comando não for encontrado ou não for executável, uma mensagem de erro é exibida.

## Estrutura do Código

1. **Função `record_command`**
   - Adiciona comandos ao histórico.
   - Mantém o tamanho do histórico limitado a 10 comandos.

2. **Função `show_history`**
   - Exibe o histórico de comandos com índice.

3. **Função `process_command`**
   - Processa o comando digitado:
     - Se for um comando interno, executa a ação correspondente.
     - Se for um comando externo, cria um processo filho para executar o comando.

4. **Função `main`**
   - Inicia um loop infinito que exibe o prompt e lê comandos do usuário.
   - Passa o comando para `process_command`.

## Como Compilar e Executar

1. **Compilação**
   - Use o seguinte comando para compilar a shell:
     ```bash
     g++ -o shell shell.cpp
     ```

2. **Execução**
   - Execute a shell com:
     ```bash
     ./shell
     ```

## Notas

- **Variáveis de Ambiente**: No momento, a shell não implementa variáveis de ambiente.
