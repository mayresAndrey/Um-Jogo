#include "definesUno.h"

#include <string.h>
#include <time.h> 

//=====================================================================

void teste(void){
    printf("OI,gay\n\n");
}

//=====================================================================

baralho* inicializaBaralho(){
    baralho* caixa = (baralho*)malloc(sizeof(baralho)*1);
    caixa->tam = numBin+numEspCor+numEsp+numLog;
    
    enum cores cores = Preto;
    enum efeito efeito = Nenhum;
    char nomes[50];
    for(int i=0; i<numBin; i++){
        caixa->cartasBin[i].num = i % 10; //num de 0 a 9
        if(i < 20) cores = Azul;
        else if(i >= 20 && i<40) cores = Amarelo;
        else if(i >= 40 && i<60) cores = Verde;
        else if(i>=60 && i<80) cores = Vermelho;
        caixa->cartasBin[i].cor = cores;
        caixa->cartasBin[i].usada = false;
    }
    for(int i=0; i<numEspCor; i++){
        //alterna a cor de 6 em 6
        if(i<6) cores = Azul;
        else if(i>=6 && i<12) cores = Amarelo;
        else if(i>=12 && i<18) cores = Verde;
        else if(i>=18 && i<24) cores = Vermelho;
        //alterna os 3 nomes a cada duas cartas
        if(i%3==0) {strcpy(nomes,"MaisDois\0"); efeito = MaisDois;}
        else if(i%3==1) {strcpy(nomes,"Bloqueio\0"); efeito = Bloqueia;}
        else if(i%3==2) {strcpy(nomes, "InverteDirecao\0"); efeito = InverteDirecao;}
        //atribuições
        strcpy(caixa->cartasEspCor[i].nome, nomes);
        caixa->cartasEspCor[i].cor = cores;
        caixa->cartasEspCor[i].efeito = efeito; 
        caixa->cartasEspCor[i].usada = false;
    }

    for(int i=0; i<numEsp; i++){
        caixa->cartasEspPret[i].cor = Preto;
        caixa->cartasEspPret[i].usada = false;
        if(i<3){
            strcpy(nomes, "MaisQuatro");
            efeito = MaisQuatro;
        }
        else if(i>=3 && i<6){
            strcpy(nomes, "EscolheCor");
            efeito = EscolheCor;
        }
        strcpy(caixa->cartasEspPret[i].nome, nomes);
        caixa->cartasEspPret[i].efeito = efeito;
    }
    
    for(int i=0; i<numLog; i++){
        if(i<2) {
            strcpy(nomes, "While"); 
            efeito = ManterCor;
            cores = Nenhum;
        }
        else if(i>=2 && i<4){
            strcpy(nomes, "Break");
            efeito = Quebrar;
            cores = Nenhum;
        }
        else if(i>=4 && i<6){
            strcpy(nomes, "Exit");
            efeito = TrocaMaos;
            cores = Nenhum;
        }
        else if(i>=6 && i<8){
            strcpy(nomes, "If");
            efeito = EscolheEfeito;
            cores = Nenhum;
        }
        else if(i>=8 && i<10){
            strcpy(nomes, "IfNot");
            efeito = EscolheEfeito;
            cores = Nenhum;
        }
        strcpy(caixa->cartasLogicas->nome, nomes);
        caixa->cartasLogicas->efeito1 = efeito;
        caixa->cartasLogicas->efeito2 = cores;
        caixa->cartasLogicas[i].usada = false;
    }

    return caixa;
}

void freeBaralho(baralho* bar){
    free(bar);
}

void printBaralho(baralho* bar){
    printf("Bararlho\nTamanho: %d\n", bar->tam);

    char cor[50] = "Nenhum";
    printf("Cartas Numericas\n");
    for(int i=0; i<numBin; i++){
        strcpy(cor, (( bar->cartasBin[i].cor == Azul) ? ("Azul") : 
                        ( (bar->cartasBin[i].cor == Amarelo) ? ("Amarelo") : 
                            ( (bar->cartasBin[i].cor == Verde) ? ("Verde") : 
                                ( (bar->cartasBin[i].cor == Vermelho) ? ("Vermelho") : 
                                    ("Nenhum") 
                    )))));
        printf("\tCarta %s, Num %d\n", cor, bar->cartasBin[i].num);
    }
    printf("Cartas Especiais com Cores\n");
    for(int i=0; i<numEspCor; i++){
        strcpy(cor, (( bar->cartasEspCor[i].cor == Azul) ? ("Azul") : 
                        ( (bar->cartasEspCor[i].cor == Amarelo) ? ("Amarelo") : 
                            ( (bar->cartasEspCor[i].cor == Verde) ? ("Verde") : 
                                ( (bar->cartasEspCor[i].cor == Vermelho) ? ("Vermelho") : 
                                    ("Nenhum") 
                    )))));
        printf("\tEfeito %s, cor %s\n" , bar->cartasEspCor[i].nome, cor);
    }
    printf("Cartas Especiais Pretas\n");
    for(int i=0; i<numEsp; i++){
        printf("\tEspecial, Efeito %s\n", bar->cartasEspPret[i].nome);
    }
    printf("Cartas Logicas\n");
    for(int i=0; i<numLog; i++){
        printf("\tLogica, Efeito %s\n", bar->cartasLogicas[i].nome);
    }
}

//=====================================================================

//escolha das cartas
int escolheNumBin(baralho* bar, int valor){
    int escolha = (numBin + (valor % numBin));
    for(int i=0; i<escolha; i++){
        if(!bar->cartasBin[i].usada){
            bar->cartasBin[i].usada = true;
            return i; 
        }
    }
    for(int i=escolha; i<numBin; i++){
        if( ! bar->cartasBin[i].usada){
            bar->cartasBin[i].usada = true;
            return i; 
        }
    }
    return -1;
}
int escolheEspCor(baralho* bar, int valor){
    int escolha = (numEspCor + (valor % numEspCor));
    for(int i=0; i<escolha; i++){
        if(!bar->cartasEspCor[i].usada){
            bar->cartasEspCor[i].usada = true;
            return i; 
        }
    }
    for(int i=escolha; i<numEspCor; i++){
        if(!bar->cartasEspCor[i].usada){
            bar->cartasEspCor[i].usada = true;
            return i; 
        }
    }
    return -1;
}
int escolheEsp(baralho* bar, int valor){
    int escolha = (numEsp + (valor % numEsp));
    for(int i=0; i<escolha; i++){
        if(!bar->cartasEspPret[i].usada){
            bar->cartasEspPret[i].usada = true;
            return i; 
        }
    }
    for(int i=escolha; i<numEsp; i++){
        if( ! bar->cartasEspPret[i].usada){
            bar->cartasEspPret[i].usada = true;
            return i; 
        }
    }
    return -1;
}
int escolheLog(baralho* bar, int valor){
    int escolha = (numLog + (valor % numLog));
    for(int i=0; i<escolha; i++){
        if(!bar->cartasLogicas[i].usada){
            bar->cartasLogicas[i].usada = true;
            return i; 
        }
    }
    for(int i=escolha; i<numLog; i++){
        if( ! bar->cartasLogicas[i].usada){
            bar->cartasLogicas[i].usada = true;
            return i; 
        }
    }
    return -1;
}

jogador* inicializaJogadores(baralho* bar, int tam){
    //dividir 7 cartas para cada jogador
    //o num de jogadores vezes 7 deve ser menor doq três quartos do num de cartas no baralho
    //7 * (~12) = 90  //máximo de 12 jogadores (muita coisa)
    if(tam<1 || tam>12) {
        printf("Forçando para 6 jogadores\n");
        tam = 6; 
    }

    jogador* jogadores = (jogador*) malloc(sizeof(jogador)*tam);
    
    //cada jogador deve receber 7 cartas e ter um numero de cartas menor do que a soma das cartas dos outros jogadores com as cartas que sobraram
    
    for(int i=0; i<tam; i++){
        //inicializando valores
        jogadores[i].cartasMao = 7;
        jogadores[i].cartasBin = NULL;
        jogadores[i].cartasEspCor = NULL;
        jogadores[i].cartasEspPret = NULL;
        jogadores[i].cartasLogicas = NULL;

        int valor = 0; 
        int contNB=0, contEC=0, contE=0, contL=0;

        //escolhendo cada carta para cada jogador
        for(int j = 0; j<7; j++){
            valor = (bar->tam + (rand() % bar->tam));
            int escolhido = 0;

            if(valor >= 0 && valor < numBin){ //carta binária
                escolhido = escolheNumBin(bar, valor);
                if(escolhido >= 0){
                    jogadores[i].cartasBin = (cartasNUM*)realloc(jogadores[i].cartasBin, sizeof(cartasNUM)*(contNB+1));
                    jogadores[i].cartasBin[contNB] = bar->cartasBin[escolhido]; 
                    contNB++;
                } else jogadores[i].cartasMao--;
            }
            else if(valor >= numBin && valor < numEspCor){ //carta especial com cor 
                escolhido = escolheEspCor(bar, valor);
                if(escolhido >= 0){
                    jogadores[i].cartasEspCor = (cartasEsp*)realloc(jogadores[i].cartasEspCor, sizeof(cartasEsp)*(contEC+1));
                    jogadores[i].cartasEspCor[contEC] = bar->cartasEspCor[escolhido]; 
                    contEC++;
                } else jogadores[i].cartasMao--;
            }
            else if(valor >= numEspCor && valor < numEsp){ //carta especial sem cor 
                escolhido = escolheEsp(bar, valor);
                if(escolhido >= 0){
                    jogadores[i].cartasEspPret = (cartasEsp*)realloc(jogadores[i].cartasEspPret, sizeof(cartasEsp)*(contE+1));
                    jogadores[i].cartasEspPret[contE] = bar->cartasEspPret[escolhido]; 
                    contE++;
                } else jogadores[i].cartasMao--;
            }
            else if(valor >= numEsp && valor < numLog){ //cartas logicas 
                escolhido = escolheLog(bar, valor);
                if(escolhido >= 0){
                    jogadores[i].cartasLogicas = (cartasLog*)realloc(jogadores[i].cartasLogicas, sizeof(cartasLog)*(contL+1));
                    jogadores[i].cartasLogicas[contL] = bar->cartasLogicas[escolhido]; 
                    contL++;
                } else jogadores[i].cartasMao--;
            }
        }
        jogadores[i].cartasBin->size = contNB;
        jogadores[i].cartasEspCor->size = contEC;
        jogadores[i].cartasEspPret->size = contE;
        jogadores[i].cartasLogicas->size = contL;
    }
    return jogadores;
}

void printJogadores(jogador* jor, int size){
    for(int i=0; i < size; i++){
        char cor[50] = "Nenhum";
        printf("Jogador %d\nNum de Cartas %d", i, jor[i].cartasMao);
        printf("\tCartas Numericas:\n");
        for(int j=0; j < jor[i].cartasBin->size; j++){
            strcpy(cor, (( jor[i].cartasBin[j].cor == Azul) ? ("Azul") : 
                        ( (jor[i].cartasBin[j].cor == Amarelo) ? ("Amarelo") : 
                            ( (jor[i].cartasBin[j].cor == Verde) ? ("Verde") : 
                                ( (jor[i].cartasBin[j].cor == Vermelho) ? ("Vermelho") : 
                                    ("Nenhum") 
                    )))));
            printf("\t\tNum %d, Cor %s\n", jor[i].cartasBin[j].num, cor);
        }
        printf("\tCartas Especiais com Cores:\n"); 
        for(int j=0; j < jor[i].cartasEspCor->size; j++){
            strcpy(cor, (( jor[i].cartasEspCor[j].cor == Azul) ? ("Azul") : 
                        ( (jor[i].cartasEspCor[j].cor == Amarelo) ? ("Amarelo") : 
                            ( (jor[i].cartasEspCor[j].cor == Verde) ? ("Verde") : 
                                ( (jor[i].cartasEspCor[j].cor == Vermelho) ? ("Vermelho") : 
                                    ("Nenhum") 
                    )))));
            printf("\t\tEfeito %s, Cor %s\n", jor[i].cartasEspCor[j].nome, cor);
        }
        printf("\tCartas Especiais Preto:\n"); 
        for(int j=0; j < jor[i].cartasEspPret->size; j++){
            printf("\t\tEspecial, Efeito %s\n", jor[i].cartasEspPret[j].nome);
        }
        printf("\tCartas Logicas:\n"); 
        for(int j=0; j < jor[i].cartasLogicas->size; j++){
            printf("\t\tLogica, Efeito %s\n", jor[i].cartasLogicas[j].nome);
        }
        
    }
}

void freeJogadores(jogador* jor, int size){
    for(int i=0; i < size; i++){
        free(jor[i].cartasBin);
        free(jor[i].cartasEspCor);
        free(jor[i].cartasEspPret);
        free(jor[i].cartasLogicas);
    }
    free(jor);
}

//=====================================================================

