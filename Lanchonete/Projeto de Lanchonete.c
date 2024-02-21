#include <stdio.h>

#define QTD_LANCHES 44 // Quantidade de lanches que tem no cardápio

struct Cardapio{ // Caracteristicas dos lanches do cardápio
    int Numeracao;
    char Lanche[50];
    float Preco;
};

int main (){

    FILE *ArquivoCardapio, *ArquivoComanda;
    ArquivoCardapio = fopen("cardapio.txt","r"); // Abrir o arquivo, para leitura, do preço dos lanches
    ArquivoComanda = fopen("comanda.txt","a"); // Arquivo que vai funcionar como uma comanda
    struct Cardapio Cardapio[QTD_LANCHES];  
    char NomeDoCliente[50];
    int Sair = 1, Opcao, NumeroDoPedido = 1, aux = 0, NumeroDoLanche, Repeticao, QuantidadeDeLanches;
    float ValorTotal, LanchePedido, ValorRecebido, Troco;

    while(fscanf(ArquivoCardapio, "%d %s %f", &Cardapio[aux].Numeracao, Cardapio[aux].Lanche, &Cardapio[aux].Preco)!=EOF){ 
        aux++;
    } // Laço de repetição para armazenar os lanches contidos no arquivo 

    while(Sair != 0){
        
        VoltarInicio:
        ValorTotal = 0;
        printf("\n\n-------------------------  Menu  -------------------------\n1 - Começar\n0 - Sair\n");
        scanf("%d", &Opcao);
        if(Opcao == 1 || Opcao == 0){
            switch(Opcao){
                case 1:                    
                    printf("\nInforme o nome do cliente: " );
                    getchar();
                    fgets(NomeDoCliente, sizeof(NomeDoCliente), stdin);
                    //scanf("%s", NomeDoCliente);
                    //printf("\n%s", NomeDoCliente);
                    printf("\n\nCardápio: " );
                    printf("\n=================  Hamburguers  =================\n");
                    for(int i = 0; i <= 12 ; i++) printf("%d - %s R$ %0.2f\n", Cardapio[i].Numeracao, Cardapio[i].Lanche, Cardapio[i].Preco);
                    printf("\n=================  Salgados  =================\n");
                    for(int i = 13; i <= 20 ; i++) printf("%d - %s R$ %0.2f\n", Cardapio[i].Numeracao, Cardapio[i].Lanche, Cardapio[i].Preco);
                    printf("\n=================  Doces  =================\n");
                    for(int i = 21; i <= 23 ; i++) printf("%d - %s R$ %0.2f\n", Cardapio[i].Numeracao, Cardapio[i].Lanche, Cardapio[i].Preco);
                    printf("\n=================  Bebidas  =================\n");
                    for(int i = 24; i <= 36 ; i++) printf("%d - %s R$ %0.2f\n", Cardapio[i].Numeracao, Cardapio[i].Lanche, Cardapio[i].Preco);
                    printf("\n=================  Confeitos  =================\n");
                    for(int i = 37; i <= 42 ; i++) printf("%d - %s R$ %0.2f\n", Cardapio[i].Numeracao, Cardapio[i].Lanche, Cardapio[i].Preco);
               
                    printf("\n-------------------------  Pedido do cliente  -------------------------\n");
                    fprintf(ArquivoComanda, "--------------  \n%s--------------\n", NomeDoCliente);
                    PedirNovamente: // Esse "Goto's" servem para repetir a pergunta caso o programa receba uma entrada inesperada
                    printf("\nNumero do Lanche escolhido: "); // Escolher o número que está relacionado ao lanche no cardápio
                    scanf("%d", &NumeroDoLanche);
                    if(NumeroDoLanche < 0 || NumeroDoLanche > 42);
                    printf("\nQuantos %s?\n", Cardapio[NumeroDoLanche].Lanche);
                    scanf("%d", &QuantidadeDeLanches);
                    LanchePedido = Cardapio[NumeroDoLanche].Preco * QuantidadeDeLanches; // Multiplicar a quantidade de lanche que o cliente pediu pelo preço do lanche
                    ValorTotal += LanchePedido;
                    fprintf(ArquivoComanda, "%d x %s\n", QuantidadeDeLanches, Cardapio[NumeroDoLanche].Lanche);

                    MaisAlgo:
                    printf("\nMais Algo?\n 0 - Não\n 1 - Sim\n");
                    scanf("%d", &Repeticao);
                    if(Repeticao == 1) goto PedirNovamente; // Repetir a compra caso o cliente queira mais lanches
                    if(Repeticao != 0 && Repeticao != 1) goto MaisAlgo;
                    if(Repeticao == 0){
                        printf("\nTotal = R$ %0.2f\n", ValorTotal);
                        fprintf(ArquivoComanda, "\nTotal = R$ %0.2f\n\n\n", ValorTotal);
                        VoltarPagamento:
                        printf("\nForma de Pagamento?\n1 - Dinheiro\n2 - Pix\n3 - Cartão de Crédito\n4 - Cartão de Débito\n");
                        scanf("%d", &Opcao);
                        if(Opcao != 1 && Opcao != 2 && Opcao != 3 && Opcao != 4) goto VoltarPagamento;
                        switch(Opcao){
                            
                            case 1:
                                printf("\nValor Recebido? "); scanf("%f", &ValorRecebido);
                                Troco = ValorRecebido - ValorTotal;
                                if(Troco >= 0){
                                    printf("\nTroco = R$ %0.2f\n", Troco);                               
                                } else {
                                    Troco *= -1;
                                    printf("\nEstá faltando R$ %0.2f\n", Troco);
                                }
                            break;

                            case 2:
                                printf("\nChave Pix: (81) 98843-0150\n");
                            break;

                            case 3:
                                printf("\nInsira ou Aproxime o cartão");
                            break;

                            case 4:
                                printf("\nInsira ou Aproxime o cartão");
                            break;
                        }
                    }
                
                break;

                case 0:
                Sair = 0;
                break;    
            }
        } else {
            goto VoltarInicio;
        }
        
    }

    return 0;
}