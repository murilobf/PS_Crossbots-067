#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace std;

/*Para facilitar o armazenamento de diferentes dados que podem ser relevantes para o jogador foi criada uma classe com tais dados*/
class Apostador{
    public:

    int creditos;
    int vitorias;
    int derrotas;

    Apostador(int qntdInicial){
        creditos = qntdInicial;
        vitorias = 0;
        derrotas = 0;
    }
};

void mostraInformacoes(Apostador *cliente){

    cout << "Quantidade de creditos: " << cliente->creditos << endl;
    cout << "Quantidade de vitorias: " << cliente->vitorias << endl;
    cout << "Quantidade de derrotas: " << cliente->derrotas << endl;
}

void blackjack(int aposta, Apostador *cliente){

    /*Os dois cout ao inves de 1 foram so pra nao ficar um texto comprido demais*/
    cout << "Sera dada uma carta aleatoria por rodada para voce e outra para a banca, cada carta vale o numero escrito nela, com o as valendo 1 e o rei, ";
    cout << "a rainha e a dama valendo 10. O pagamento e de 1.5x o valor investido\n" << endl;

    /*Flag criada pra decidir quando o jogo acaba*/
    bool jogando = 1;

    /*Variavel para armazenar os pontos do jogador e da banca*/
    int valorJogador = 0;
    int valorBanca = 0;

    int cartaJogador;
    int cartaBanca;

    while(jogando){

        if(valorJogador < 21 && valorBanca < 21){

            cout << "Voce possui " << valorJogador << " pontos, enquanto a banca tem " << valorBanca << endl;
            cout << "Digite 0 para parar de jogar e 1 para continuar " << endl;

            cin >> jogando;

            /*Os turnos de jogada do jogador humano*/
            if(jogando){

                /*Gera um numero aleatorio entre 1 e 10, equivalente as cartas do As ao Rei. Cria-se uma nova variavel ao inves de somar diretamente
                para que o valor da carta possa ser mostrada ao usuario. Para simplificar as coisas o As so vale 1*/
                cartaJogador = rand() % 10 + 1;

                /*O tempo de espera serve pra dar um efeito dramatico*/
                this_thread::sleep_for(chrono::milliseconds(500));
                cout << "\nCarta do jogador: " << cartaJogador;

                valorJogador += cartaJogador;
            }

            /*Os turnos de jogada da banca.Segue uma regra de comportamento da banca que achei na internet, onde a banca para de pegar cartas 
            assim que chega em 17 ou mais*/
            if(valorBanca < 17){

                cartaBanca = rand() % 10 + 1;
                valorBanca += cartaBanca;

                this_thread::sleep_for(chrono::milliseconds(500));
                cout << "\nCarta da banca:\n" << cartaBanca << endl;
            }
        }
        /*Para o jogo caso o valor ultrapasse os 21 pontos*/
        else{

            jogando = false;
        }
    }

    /*Apos o fim, seja por decisao do jogador ou por estouro dos pontos, verifica quem ganhou*/ 

    /*Pro caso do jogador ultrapassar o valor mas a banca nao*/
    if(valorJogador > 21 && valorBanca <= 21){

        cout << "Perdeu, ultrapassou o valor limite de 21" << endl;
        cliente->creditos -= aposta;
        cliente->derrotas ++;
    }

    /*Pro caso de tanto a banca quanto o jogador ultrapassarem o valor*/
    else if(valorJogador > 21 && valorBanca > 21){

        cout << "Empate, ambos ultrapassaram o valor" << endl;
    }   

    /*Pro caso de apenas a banca ultrapassar o valor. OBS: a variavel valorJogador pode ser omitida pois ja foi verificado nos casos anteriores
    se seu valor ultrapassava 21*/  
    else if(valorBanca > 21){

        cout << "Ganhou, a banca ultrapassou o valor" << endl;
        cliente->creditos += (aposta*1.5);
        cliente->vitorias ++;
    }

    /*Pros dois casos em que nenhum dos dois ultrapassar o valor, nesse caso verifica quem chegou mais proximo de 21*/

    /*Caso em que o jogador ganha*/
    else if(valorJogador > valorBanca){

        cout << "Parabens, ganhou com " << valorJogador << " pontos, enquanto a banca tinha " << valorBanca << endl;
        cliente->creditos += (aposta*1.5);
        cliente->vitorias ++;
    }

    /*Caso em que a banca ganha*/
    else if (valorJogador < valorBanca){

        cout << "Perdeu, voce tinha " << valorJogador << " pontos, enquanto a banca tinha " << valorBanca << endl; 
        cliente->creditos -= aposta;
        cliente->derrotas ++;
    }

    /*Pro ultimo dos casos, onde ocorre empate*/
    else{

        cout << "Houve empate, portanto voce nem perde nem ganha nada" << endl;
    }
}

void cacaNiqueis(int aposta, Apostador *cliente){

    /*Explicacao do jogo*/
    cout << "Para ganhar, devem ser sorteados 3 simbolos iguais, o retorno e de 20x o valor apostado" << endl;
    /*Variavel dos simbolos do caca niquel, uso um vetor de inteiros para facilitar a leitura e o sorteio pelo programa*/
    int slots[3];
    /*Variavel para verificar se o jogador venceu ou perdeu o jogo*/
    bool vitoria = true;

    /*Faz o caça niqueis "girar" 5x (apenas para dar uma sensação de ser um jogo de verdade)*/
    for(int i = 0; i < 3; i++){

        /*Apenas para dar um efeito dramatico, faz o programa esperar meio segundo antes sortear o proximo simbolo*/
        this_thread::sleep_for(chrono::milliseconds(500));

        /*Sorteia os simbolos, tendo um total de 10 diferentes*/
        slots[i] = rand() % 10;

        /*Com base na tabela ASCII, converte os numeros em simbolos para que o usuario veja simbolos realmente e nao apenas numeros*/
        cout << char('!' + slots[i]) << " ";

        /*A partir do segundo simbolo sorteado, verifica se eles sao diferentes, o que significaria que o jogador perdeu*/
        if(i > 0 && slots[i] != slots[i-1]){
            vitoria = false;
        }
    }

    printf("\n\n");
    
    /*Com base na variavel "vitoria" decide se o jogador perdeu ou ganhou o jogo*/
    if(vitoria){

        cout << "Parabens, voce ganhou" << endl;
        cliente->creditos += (aposta * 20);
        cliente->vitorias++;
    }
    else{

        cout << "Nao foi dessa vez" << endl;
        cliente->creditos -= aposta;
        cliente->derrotas++;
    }
}

void roleta(int aposta, Apostador *cliente){

    /*Variaveis relativas a qual tipo de aposta o jogador faz e a qual numero sera sorteado na roleta*/
    int escolha;
    int numEscolhido;
    int numSorteado;
    
    cout << "A roleta possui 37 numeros, do 0 ao 36. Voce pode apostar em 3 categorias diferentes:" << endl;
    cout << "Em numeros individuais, que retornam 35x o valor apostado" << endl;
    cout << "Em cores, sendo o preto o mesmo que numeros pares (exceto 0) e o vermelho sendo numeros impares, que retornam 2x o valor" << endl;
    cout << "E em grupos, que retornam 3x o valor" << endl << endl;

    cout << "DIGITE 1 PARA APOSTAR EM NUMEROS INDIVIDUAIS" << endl;
    cout << "DIGITE 2 PARA APOSTAR EM CORES" << endl;
    cout << "DIGITE 3 PARA APOSTAR EM GRUPOS DE NUMEROS" << endl;

    cin >> escolha;

    /*Faz o sorteio do numero, isso e feito antes do jogador escolher o numero para que ja seja possivel dar a resposta na mesma
    condicional onde o jogador escolhe o numero que quer, caso contrario seria necessario outro grupo de "if"*/
    numSorteado = rand() % 37;

    /*Le o numero/o grupo de numeros que o jogador quer*/

    if(escolha == 1){

        cout << "Escolha um numero de 0 a 36 " << endl;
        cin >> numEscolhido;

        if(numSorteado == numEscolhido){

            cout << "Parabens, voce ganhou!" << endl;
            cliente->creditos += (aposta*35);
            cliente->vitorias++;
        }

        else{

            cout << "Infelizmente nao foi dessa vez" << endl;
            cliente->creditos -= aposta;
            cliente->derrotas++;
        }
    }

    else if(escolha == 2){
        
        cout << "Digite 0 para apostar na cor preta e 1 para apostar na cor vermelha " << endl;
        cin >> numEscolhido;

        /*Para simplificar as coisas vermelho significa impar e preto par (exceto 0)*/
        if(numSorteado % 2 == numEscolhido && numSorteado != 0){

            cout << "Parabens, voce ganhou!" << endl;
            cliente->creditos += (aposta*2);
            cliente->vitorias++;
        }

        else{

            cout << "Infelizmente nao foi dessa vez" << endl;
            cliente->creditos -= aposta;
            cliente->derrotas++;
        }
    }

    else if(escolha == 3){

        cout << "Digite 1 para apostar nos numeros de 1 a 12, 2 para apostar nos numeros de 13 a 24 e 3 para apostar nos numeros de 25 a 36 " << endl;
        cin >> numEscolhido;

        /*Verifica se o numero sorteado esta dentro do grupo escolhido pelo jogador, a condicao basicamente ve se o numero esta dentro dos limites de cada grupo.
        Exemplificando para facilitar o entendimento da logica: se o jogador pegou o grupo 1 (1-12) e o numero sorteado foi o 13 (que entra na 2ª condicao), 13/12 da 1
        e sobra 1, com a soma de 1 da condicao fica 2 (que e justamente o grupo do 13), portanto o jogador perde. Agora se o jogador pegou o grupo 1 e o numero sorteado 
        foi o 12, entra a 2ª condicao onde o numero da divisao da 1 e sobra 0, portanto o jogador vence.*/
        if((((numSorteado / 12) + 1 == numEscolhido && numSorteado % 12 != 0) || ((numSorteado/12) == numEscolhido && numSorteado % 12 == 0)) && numSorteado != 0){

            cout << "Parabens, voce ganhou!" << endl;
            cliente->creditos += (aposta*3);
            cliente->vitorias++;
        }
        else{

            cout << "Infelizmente nao foi dessa vez" << endl;
            cliente->creditos -= aposta;
            cliente->derrotas++;
        }
    }

    else{

        cout << "Escolha invalida.";
    }
}

int pedeAposta(Apostador *cliente){

    int aposta;
    cout << "Insira o valor que deseja investir:" << endl;

    cin >> aposta;

    /*Pro caso da pessoa inserir um valor invalido, entra numa especie de loop por causa da recursao ate que a pessoa insira um valor valido*/
    if(aposta > cliente->creditos || aposta < 1){

        cout << "Valor invalido. O valor tem que ser maior que 0 e menor que a quantidade de creditos disponivel, tente novamente" << endl;

        return pedeAposta(cliente);
    }
    else{

        return aposta;
    }
}

void chamaJogos(Apostador *cliente){

    int escolha;
    int aposta;
    bool continua;

    cout << "DIGITE 1 PARA JOGAR BLACKJACK" << endl;
    cout << "DIGITE 2 PARA JOGAR MAQUINA CACA-NIQUEIS" << endl;
    cout << "DIGITE 3 PARA JOGAR ROLETA" << endl;
    cout << "DIGITE 4 PARA SAIR" << endl;

    cin >> escolha;

    cout << "Quanto deseja apostar? Lembrando que seu saldo e de " << cliente->creditos << endl;
    aposta = pedeAposta(cliente);

    while(escolha != 4){

        if(escolha == 1){

            blackjack(aposta, cliente);
        }

        else if(escolha == 2){

            cacaNiqueis(aposta, cliente);   
        }

        else if(escolha == 3){

            roleta(aposta, cliente);
        }

        else if(escolha != 4){

            cout << "Valor invalido, insira novamente" << endl;
            cin >> escolha;
        }

        /*Parece redundante, mas eh para o caso da pessoa querer parar (sem esse if ele perguntaria mesmo quando a pessoa quer parar)*/
        if(escolha !=4){

            cout << "Voce possui " << cliente->creditos << " creditos. Continue jogando para aumentar esse numero!!\n" << endl;
            cout << "Deseja continuar no mesmo jogo? " << endl;
            cout << "DIGITE 0 PARA PARAR E 1 PARA CONTINUAR " << endl;

            cin >> continua;
        }

        /*Faz a pessoa inserir de novo qual escolha quer, o jogador dizer que quer trocar de jogo significa que e necessario mudar novamente o valor de escolha,
        enquanto ele falar que deseja continuar significa que o valor da variavel pode permanecer o mesmo*/
        if(!continua){

            cout << "Qual jogo deseja jogar?" << endl;
            cout << "Lembrando que, para escolher, deve digitar 1 para Blackjack, 2 para Caca-Niqueis, 3 para Roleta e 4 para sair" << endl;

            cin >> escolha;
        }

        /*Novamente, parece redundante mas evita de perguntar quando a pessoa quer sair*/
        if(escolha != 4){

            cout << "Digite a quantidade que deseja apostar. Lembrando que voce tem " << cliente->creditos << " creditos" << endl;
            cin >> aposta;
        }

        /*"Expulsa" o jogador do cassino quando o dinheiro acaba*/
        if(cliente->creditos <= 0){

            cout << "Perdeu todo o dinheiro, deve sair de nosso cassino. Mas volte sempre que tiver mais dinheiro para investir. " << endl;
            escolha = 4;
        }
    }
}

bool processaEscolha(int escolha, Apostador *cliente){

    if(escolha == 1){
        mostraInformacoes(cliente);
    }

    else if(escolha == 2){

        chamaJogos(cliente);
    }
    
    /*O unico caso em que o programa se encerra*/
    else if(escolha == 3){

        return true;
    }

    /*Pra caso a pessoa digite algo sem ser um dos valores aceitos*/
    else{

        cout << "Valor invalido." << endl;
    }


    return false;
}

void cassino(Apostador *cliente){

    bool fim = false;
    while(!fim){

        cout << "Escolha o que quer fazer:\n" << endl;

        cout << "DIGITE 1 PARA CONSULTAR SEUS DADOS" << endl;
        cout << "DIGITE 2 PARA JOGAR" << endl;
        cout << "DIGITE 3 PARA SAIR DO CASSINO\n" << endl;

        int escolha;

        cin >> escolha; 
        fim = processaEscolha(escolha, cliente);
    }
}

int main(){

    /*Inicializa a seed de aleatoriedade para garantir diferentes sequencias*/
    srand((unsigned)time(NULL));

    int qntdInicial = 0;

    cout << "BEM VINDO AO CROSSBETS" << endl;
    cout << "Cada um de nossos jogos retorna uma porcentagem diferente do valor investido. Mas cuidado, se perder todo o dinheiro sera expulso." << endl;
    cout << "A taxa de retorno de cada jogo sera informada antes de seu inicio.\n" << endl;

    /*Loop para garantir que a pessoa insira um valor valido*/
    while(qntdInicial < 1){

        cout << "Insira a quantidade inicial de dinheiro que quer depositar" << endl;
        cin >> qntdInicial;

        if(qntdInicial < 1){

            cout << "Insira um valor valido (maior que 0)" << endl;
        }
    }

    Apostador cliente(qntdInicial);
    cassino(&cliente);

    cout << "Volte sempre";

    return 0;
}