#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "./utils/function_utils.h"

int main()
{
    Instrumento instrumentos[ESTOQUE];
    int total = 0, proxId = 1, op;

    carregar(instrumentos, &total, &proxId);
    total == 0 ? printf("⚠️  Nenhum dado carregado. Estoque iniciado vazio.\n") : printf("✅ Dados carregados com sucesso!\n");

    sleep(3);
    system("clear");

    do
    {
        printf("\n=====================================\n");
        printf("        GERENCIAMENTO DE ESTOQUE     \n");
        printf("=====================================\n");
        printf("  1 - Listar todos os instrumentos\n");
        printf("  2 - Cadastrar novo instrumento\n");
        printf("  3 - Alterar preço de instrumento\n");
        printf("  4 - Remover instrumento\n");
        printf("  5 - Listar por naipe\n");
        printf("  6 - Listar por nome\n");
        printf("  7 - Sair\n");
        printf("=====================================\n");
        printf("Escolha uma opção: ");

        scanf("%d", &op);
        getchar();

        printf("\n-------------------------------------\n");

        sleep(1);
        system("clear");

        switch (op)
        {
        case 1:
            if (total == 0)
            {
                printf("Nenhum instrumento cadastrado.\n");
            }
            else
            {
                for (int i = 0; i < total; i++)
                {
                    printf("Id: %d | Nome: %s | Naipe: %s | Preço: R$%.2f\n",
                           instrumentos[i].id,
                           instrumentos[i].nome,
                           instrumentos[i].naipe,
                           instrumentos[i].preco);
                }
            }

            sleep(2);
            break;

        case 2:
        {
            char nome[STR], naipe[STR];
            float preco;

            printf("Digite o nome: ");
            fgets(nome, STR, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            printf("Digite o naipe: ");
            fgets(naipe, STR, stdin);
            naipe[strcspn(naipe, "\n")] = '\0';

            printf("Digite o preço: R$");
            scanf("%f", &preco);

            if (cadastrar(instrumentos, nome, naipe, preco, &total, &proxId))
            {
                printf("✅ Instrumento cadastrado com sucesso!\n");
                printf("📦 Estoque disponível: %d\n", ESTOQUE - total);
            }
            else
            {
                printf("❌ Erro ao cadastrar (limite atingido ou dados inválidos).\n");
            }

            sleep(2);
            break;
        }

        case 3:
        {
            int id;
            float novo;

            printf("Digite o ID: ");
            scanf("%d", &id);

            printf("Digite o novo preço: R$");
            scanf("%f", &novo);

            if (alterar(instrumentos, id, novo, &total))
            {
                printf("✅ Preço alterado com sucesso!\n");
            }
            else
            {
                printf("❌ Erro: ID inválido ou instrumento não encontrado.\n");
            }

            sleep(2);
            break;
        }

        case 4:
        {
            int id;

            printf("Digite o ID: ");
            scanf("%d", &id);

            if (remover(instrumentos, id, &total, &proxId))
            {
                printf("✅ Instrumento removido com sucesso!\n");
                printf("📦 Estoque disponível: %d\n", ESTOQUE - total);
            }
            else
            {
                printf("❌ Erro: ID inválido ou instrumento não encontrado.\n");
            }

            sleep(2);
            break;
        }

        case 5:
        {
            char naipe[STR];
            bool achou = false;

            printf("Digite o naipe: ");
            fgets(naipe, STR, stdin);
            naipe[strcspn(naipe, "\n")] = '\0';

            for (int i = 0; i < total; i++)
            {
                if (strcmp(instrumentos[i].naipe, naipe) == 0)
                {
                    printf("Id: %d | Nome: %s | Preço: R$%.2f\n",
                           instrumentos[i].id,
                           instrumentos[i].nome,
                           instrumentos[i].preco);
                    achou = true;
                }
            }

            if (!achou)
            {
                printf("Nenhum instrumento encontrado para esse naipe.\n");
            }

            sleep(2);
            break;
        }

        case 6:
        {
            char nome[STR];
            bool achou = false;

            printf("Digite o nome: ");
            fgets(nome, STR, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            for (int i = 0; i < total; i++)
            {
                if (strcmp(instrumentos[i].nome, nome) == 0)
                {
                    printf("Id: %d | Naipe: %s | Preço: R$%.2f\n",
                           instrumentos[i].id,
                           instrumentos[i].naipe,
                           instrumentos[i].preco);
                    achou = true;
                }
            }

            if (!achou)
            {
                printf("Nenhum instrumento encontrado com esse nome.\n");
            }

            sleep(2);
            break;
        }

        case 7:
            printf("Encerrando o programa...\n");
            break;

        default:
            printf("⚠️ Opção inválida. Tente novamente.\n");
        }

        printf("-------------------------------------\n");
    } while (op != 7);

    return 0;
}
