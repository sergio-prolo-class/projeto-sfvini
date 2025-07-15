# 🎻 Sistema de Cadastro de Instrumentos Musicais

## 💡 Descrição do Programa

Este programa em linguagem C é um sistema simples para cadastro, consulta, alteração e remoção de instrumentos musicais. Ele armazena as informações em memória e também salva/recupera os dados em um arquivo de texto (`instrumentos.txt`), garantindo que os dados persistam entre execuções.

O programa possui um menu interativo via terminal, permitindo que o usuário escolha entre as opções para manipular a lista de instrumentos.

---

## ⚙️ Funcionalidades

- Listar todos os instrumentos cadastrados.
- Cadastrar um novo instrumento (nome, naipe e preço).
- Alterar o preço de um instrumento existente.
- Excluir um instrumento pelo seu ID.
- Listar instrumentos filtrando por naipe.
- Listar instrumentos filtrando por nome.
- Encerrar o programa.

---

### 💻 Requisitos

- Compilador C instalado (ex: gcc).
- Terminal/Prompt de comando.

---

### 🗂️ Estrutura do projeto

```bash
projeto/
├── main.c
├── utils/
│   ├── function_utils.c
│   ├── function_utils.h
│   └── instrument_utils.h
```

---

### 📄 Passos para compilar e executar

1. Abra o terminal na pasta do projeto.

2. Compile o código:

````bash
gcc main.c utils/function_utils.c -o instrumentos
````

3. Execute o programa:

- Linux/macOS

```bash
./instrumentos
````

- Windows

```bash
instrumentos.exe
````

---
