#include <stdio.h>
#include <stdlib.h>
#include <time.h>//necessário p/ função time()
#include <math.h>

#include "arvore_binaria.h"

#define NUMERO_CONSULTORIOS 4 //define o numero de consultorios

int GeraRequisicao(void) //gera uma requicao de agendamento, aleatório
{
    int dia, hora;
    dia = (rand() % 27) + 1;
    hora = rand() % (20 + 1 - 9) + 9;
    return ((hora*100)*100 + dia); //retorna um inteiro no formato HORADIA
}

int Busca(ArvBina* no, int chave){ //Busca um atendimento e retorna 0 se o periodo do atendimento nao existe na arvore, e 1 se ele conflita com outro atendimento
    if(no != NULL){ //se for nulo entao ja procurou na arvore e nao achou
        if((no->chave==chave) || (((no->chave%100)==(chave%100)) && (abs((no->chave)-chave)<10000))){ //verifica se não há colisão de horarios
            return 1;
        }else if(chave > no->chave) { //procura recursivamente na arvore
            Busca(no->filhoDir,chave);
        }else if(chave < no->chave) { //mesma coisa
            Busca(no->filhoEsq,chave);
        }
    }else{
        return 0;
    }
}

ArvBina* InsereAtendimento(ArvBina* no ,int chave){ //Busca uma chave  na arvore, e verifica se pode ou não inserir a chave com base em sua existencia
    if(Busca(no, chave)==0 && chave<=200028){ //se for 0 entao pode inserir na arvore, o horario maximo de agendamento é 2000 horas
        return InsereArv(no,chave);
    }else{ // se for 1 entao nao pode e retorna o no não modificado
        printf("A solicitacao de agendamento %d nao pode ser efetuada.\n", chave); //exibe uma mensagem caso a requição de agendamento não possa ser efetuada
        return no;
    }
}

int QuantidadeReserva(ArvBina* no) { //Contabiliza quantos atendimentos tem reservado na arvore
    int chamou = 0; // contador
    if(no!=NULL) { // se nao for nulo entao tem elemento
        chamou+= QuantidadeReserva(no->filhoEsq); // incrementa o contador toda vez que tiver algo a esquerda
        chamou+= QuantidadeReserva(no->filhoDir); // incrementa o contador toda vez que tiver algo a direita
        return chamou+1;
    }
    return 0;
}

int ReservaSemanal(ArvBina* no,int semana) { //Printa todos os atendimentos que estão reservados pra determinada semana, mesma logica do QuantidadeReserva
    int chamou=0;
    if(no!=NULL) {
        if(((semana-1)*7)+1<= no->chave%100 && no->chave%100 <= semana*7) { //verifica se os 2 ultimos digitos estao no limite da semana
            chamou++;
            printf("Reserva: dia %02d hora %04d\n", (no->chave)%100, (no->chave)/100); //printa a reserva
        }
        chamou+= ReservaSemanal(no->filhoEsq,semana);
        chamou+= ReservaSemanal(no->filhoDir,semana);
        return chamou;
    }
    return 0;
}
void AgendamentoAuto(ArvBina* consultorios[]){ //função responsável peloa agendamento de requisições aleatórias
    int numero_requisicoes = 0, contador = 0;
    printf("Digite o numero de requisicoes de agendamentos (n>0)..:\n");
    scanf("%d", &numero_requisicoes);
    while(numero_requisicoes<0){//validação da entrada
        while (getchar() != '\n');
        printf("Valor invalida, insira um valor maior que 0..:\n");
        scanf("%d", &numero_requisicoes);
    }
    int i;
    int semana;
    while(contador != numero_requisicoes){
        i = GeraRequisicao();
        semana =((((i%100)-1)/7)+1);
        if((((semana-1)*7)+6) !=i%100 && (((semana-1)*7)+7) !=i%100) {
        int aux = rand() % 4; //gera um numero aleatorio para selecionaro consultorio
        consultorios[aux] = InsereAtendimento(consultorios[aux],i); //insere o agendamento no consultorio selecionado
        }
        contador++; //contador
    }
}

void AgendamentoIndividual(ArvBina* consultorios[]){ //funcao de agendamento "manual"
    int aux = 0, aux2 = 0;;
    printf("Digite o horario e o dia do agendamento (HoraDia)..:\n");
    scanf("%d", &aux);
    int semana;
    semana =((((aux%100)-1)/7)+1);
    while((aux<90001 || aux>200028) || ((((semana-1)*7)+6) ==aux%100 || (((semana-1)*7)+7) ==aux%100 )){//validação da entrada
        while (getchar() != '\n');
        printf("Opcao invalida, insira um valor entre 90001 e 200001 e que seja em um dia de semana valido..:\n");
        printf("Formato (HoraDia).\n");
        scanf("%d", &aux);
        semana =((((aux%100)-1)/7)+1);
    }
    printf("Digite o consultorio em que sera agendado (1,2,3 ou 4)..:\n");
    scanf("%d", &aux2);
    while(aux2<1 || aux2>4){//validação da entrada
        while (getchar() != '\n');
        printf("Opcao invalida, insira um valor entre 1 e 4..:\n");
        scanf("%d", &aux2);
    }
    consultorios[aux2-1] = InsereAtendimento(consultorios[aux2-1], aux); //agendamento
}

void BuscaAtendimento(ArvBina* consultorios[]){//função que busca o agendamento nos consultorio
    int aux1 = 0, aux2 = 0; //variaveis auxiliarres
    printf("Digite o consultorio(1,2,3 ou 4)..:\n");
    scanf("%d", &aux1);
    while(aux1<1 || aux1>4){//validação da entrada
        while (getchar() != '\n');
        printf("Opcao invalida, insira um valor entre 1 e 4..:\n");
        scanf("%d", &aux1);
    }
    printf("Digite o elemento (HoraDia)..:\n");
    scanf("%d", &aux2);
    while(aux2<90001 || aux2>200028){//validação da entrada
        while (getchar() != '\n');
        printf("Opcao invalida, insira um valor entre 90001 e 210001..:\n");
        printf("Formato (HoraDia).\n");
        scanf("%d", &aux2);
    }
    if(ProcuraElemento(consultorios[aux1-1], aux2) != NULL){
        printf("A reserva no consultorio %d no dia e horario solicitados esta confirmada.\n\n", aux1);
    }else{
        printf("A reserva no consultorio %d no dia e horario solicitados nao foi encontrada.\n\n", aux1);
    }
}

void BuscaAtendimentoHorarioDia(ArvBina* consultorios[]){ //função que verifica a situação de um horario de agendamento nos consultorios
    int aux1 = 0, aux2 = 0; //variaveis auxiliarres
    printf("Digite o Horario e o dia desejados (HoraDia)..:\n");
    scanf("%d", &aux2);
    while(aux2<90001 || aux2>200028){//validação da entrada
        while (getchar() != '\n');
        printf("Opcao invalida, insira um valor entre 90001 e 210001..:\n");
        printf("Formato (HoraDia).\n");
        scanf("%d", &aux2);
    }
    while(aux1 < NUMERO_CONSULTORIOS){ //exibe os resultados
        if(ProcuraElemento(consultorios[aux1], aux2) != NULL){
            printf("O consultorio %d no dia e horario solicitados esta ocupado.\n", aux1+1);
        }else{
            printf("O consultorio %d no dia e horario solicitados esta livre.\n", aux1+1);
        }
        aux1++;
    }
}

void RemoveBAgendamentos(ArvBina* consultorios[]){ //função responsável por gerar e remover B agendamentos
    int numero_remocoes = 0, contador = 0;
    printf("Digite o numero de requisicoes de remocoes (n>0)..:\n");
    scanf("%d", &numero_remocoes); //leitura do numero de remoções a serem gerados
    while(numero_remocoes<0){//validação da entrada
        while (getchar() != '\n');
        printf("Valor invalida, insira um valor maior que 0..:\n");
        scanf("%d", &numero_remocoes);
    }
    while(contador != numero_remocoes){
        int aux = rand() % 4; //gera um numero aleatorio para selecionar consultorio
        consultorios[aux] = RemoveElemento(consultorios[aux], GeraRequisicao()); //insere o agendamento no consultorio selecionado
        contador++; //contador
    }
}

void BuscaAntendimentosSemana(ArvBina* consultorios[]){ //função que busca e exibe as reservas em uma semana em todos os consultorios
    int aux1 = 0, aux2 = 0; //variaveis auxiliarres
    printf("Digite a semana a ser exibida (1, 2, 3 ou 4)..:\n");
    scanf("%d", &aux2);
    while(aux2<1 || aux2>4){//validação da entrada
        while (getchar() != '\n');
        printf("Opcao invalida, insira um valor entre 1 e 4..:\n");
        scanf("%d", &aux2);
    }

    while(aux1 < NUMERO_CONSULTORIOS){ //exibe os resultados
        printf("O Consultorio %d, semana %d:\n", aux1+1, aux2);
        printf("Possui %d reservas.\n\n", ReservaSemanal(consultorios[aux1], aux2));
        aux1++;
    }
}

int main()
{
    ArvBina* consultorios[NUMERO_CONSULTORIOS]; //inicializa os consultorios, cada posicao do vetor é um consultorio
    int aux = 0, aux2 = 0; //variavel auxiliar

    while(aux < NUMERO_CONSULTORIOS){//inicializa as raizes das arvores como NULL
        consultorios[aux] = NULL;
        aux++;
    }

    int opc = 0;//variavel para ser usada no menu
    while(opc != 8){ //menu para uso do programa
        printf("\nDigite uma opcao..:\n");
        printf("1) Gerar 'n' agendamentos..:\n");
        printf("2) Exibir a situacao de uma determinada reserva..:\n");
        printf("3) Exibir a situacao de um determinado horario/dia..:\n");
        printf("4) Remover 'B' reservas..:\n");
        printf("5) Exibir a situacao das reservas em 1 semana..:\n");
        printf("6) Exibir a quantidade de reservas..:\n");
        printf("7) Agendamento manual.\n");
        printf("8) Finalizar a execucao.\n");

        scanf("%d", &opc);//entrada
        while(opc<1 || opc>8){//validação da entrada
            while (getchar() != '\n');
            printf("Opcao invalida, insira um valor entre 1 e 8..:\n");
            scanf("%d", &opc);
        }
        switch(opc){
            case 1:
                AgendamentoAuto(consultorios); //chama a funcao responsavel por gerar os casos de entrada(agendamentos)
            break;
            case 2:
                BuscaAtendimento(consultorios); //chama a funcao responsavel por buscar um atendimento
            break;
            case 3:
                BuscaAtendimentoHorarioDia(consultorios); //chama a funcao responsavel por exibir a situacao das reservas em um determiando horario e dia
            break;
            case 4:
                RemoveBAgendamentos(consultorios); //chama a funcao responsavel por gerar n pedidos de remoção aleatorios
            break;
            case 5:
                BuscaAntendimentosSemana(consultorios); //chama a funcao que busca e exibe a situacao das reservas em uma semana especifica
            break;
            case 6: //exibe a quantidade de reservas em cada consultorio
                aux = 0;
                while(aux < NUMERO_CONSULTORIOS){
                    printf("\nA quantidade de reservas no consultorio %d eh..:%d\n", aux+1, QuantidadeReserva(consultorios[aux]));
                    aux++;
                }
            break;
            case 7:
                aux2 = 0;
                printf("Quantos agendamentos serao inseridos (n>0)..:\n");
                scanf("%d", &aux);
                while(aux2 < aux){
                    AgendamentoIndividual(consultorios);
                    aux2++;
                }
            break;
        }
    }
    return 0; //retorna 0 se não houver problemas durante a execução do código
}
