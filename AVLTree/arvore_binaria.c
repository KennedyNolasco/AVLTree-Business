#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "arvore_binaria.h"

/*ATENÇÃO LER ISSO ANTES DE VER O CODIGO
    Existem 3 tipos de funções, as principais e as auxiliares e optativas

    As funções principais são as funções que voce chama na main
    As auxiliares so servem pra serem chamadas pelas funções principais, so servem pra dar apoio, voce não chama na main
    A função optativa serve apenas pra resolver possiveis erros caso ocorram

ATENÇÃO LER ISSO ANTES DE VER O CODIGO*/

int Maximo(int A, int B) { //Função auxiliar à de balanceamento, simplesmente recebe 2 numeros e retorna o maior deles
    if(A>B) {
        return A;
    }
    else {
        return B;
    }
}
ArvBina* CriarNo(int chave) { //Função auxiliar,recebe uma chave,aloca dinamicamente um espaço de memória a ser usado e retorna esse espaço criado com a chave já dentro
    ArvBina* no = malloc(sizeof(ArvBina));
    no->FB = 0;
    no->filhoEsq = NULL; //seta os filhos pra null
    no->filhoDir = NULL;
    no->chave = chave;
    return no;
}
ArvBina* MenordosMaiores(ArvBina* procurador) { //Função auxiliar,Verifica o menor numero da subarvore direita
    if(procurador==NULL) { //se o no for nulo retorna nulo
        return NULL;
    }
    else if(procurador->filhoEsq!=NULL) { //se o filhoEsquerdo não é nulo então não achou o menor, então repete
        MenordosMaiores(procurador->filhoEsq); //acessa o filhoEsquerdo desse no
        //procurador = MenordosMaiores(procurador->filhoEsq); nao sei qual versao é "melhor" ou se sequer faz alguma diferença
    }
    else { // se o filhoEsquerdo for nulo então achamos o menor dos maiores, retornamos esse no achado
        return procurador;
    }
}
ArvBina* ProcuraElemento(ArvBina* no, int chave) { //Função principal,Procura um elemento na arvore se existir, e retorna esse elemento
    if(no==NULL || no->chave == chave) {
        return no;
    }
    else if(chave > no->chave) {
        ProcuraElemento(no->filhoDir,chave);
    }
    else if(chave < no->chave) {
        ProcuraElemento(no->filhoEsq,chave);
    }
}

ArvBina* RemoveElemento(ArvBina* no, int chave) { //Função Principal, Remove um elemento na arvore e retorna esse no modificado
    if(no==NULL) { // se for nulo entao nao existe
        return no;
    }
    else if(chave > no->chave) { // procura na arvore
        no->filhoDir = RemoveElemento(no->filhoDir,chave);
    }
    else if(chave < no->chave) { // procura na arvore
        no->filhoEsq = RemoveElemento(no->filhoEsq,chave);
    }
    else { //se existe entao vamos fazer uma serie de comparacoes pra ver se tem filho ou nao esse no
        if(no->filhoEsq == no->filhoDir) { // se nao tem filhos entao simplesmente deleta
            free(no);
            no = NULL;
        }
        else if(no->filhoEsq == NULL) { //se o filho esquerdo é nulo e o direito existe, temos que botar esse filho direito no pai

            ArvBina* aux = no;
            no = no->filhoDir;
            free(aux);
        }
        else if(no->filhoDir == NULL) { // se o filho direito é nulo, bota o filho esquerdo no pai, que é o que deseja remover
            ArvBina* aux = no;
            no = no->filhoEsq;
            free(aux);
        }
        else { // se existir dois filhos, nos usamos o menor do maiores recursivamente pra poder descobrir qual no bota no lugar do no removido

            ArvBina* aux =  MenordosMaiores(no->filhoDir);
            no->chave = aux->chave;
            no->filhoDir = RemoveElemento(no->filhoDir,aux->chave);
        }
    }
    DiferencaAltura(no); //apos a remoção, atualizamos a diferenca de altura de cada no
	no = Balanceia (no);  //depois  chamanos a função balanceia, que verifica se precisa de uma rotação
    return no; //retorna esse no modificado ou não
}

ArvBina* RotacaoSimplesDireita(ArvBina* no) {   //Função auxiliar,dados 3 elementos consecutivos a esquerda A,B e C, ele faz a troca de forma a balancear os niveis de uma subarvore
    ArvBina* Sub = no->filhoEsq;
    no->filhoEsq = Sub->filhoDir;
    Sub->filhoDir = no;
    no = Sub;
    return no;
}
ArvBina* RotacaoSimplesEsquerda(ArvBina* no) { //Função auxiliar,dados 3 elementos consecutivos a direita A,B e C, ele faz a troca de forma a balancear os niveis de uma subarvore
    ArvBina* Sub = no->filhoDir;
    no->filhoDir = Sub->filhoEsq;
    Sub->filhoEsq = no;
    no = Sub;
    return no;
}
ArvBina* RotacaoDuplaDireita(ArvBina* no) { //Função auxiliar,dados 3 nos consecutivos, A sendo raiz, B o filho esquerdo da raiz e C o filho direito de B, ele realiza 2 trocas e balanceia uma subarvore
    no->filhoEsq = RotacaoSimplesEsquerda(no->filhoEsq);
    no = RotacaoSimplesDireita(no);
    return no;
}
ArvBina* RotacaoDuplaEsquerda(ArvBina* no) { //Função auxiliar,dados 3 nos consecutivos, A sendo raiz, B o filho direito da raiz e C o filho esquerdo de B, ele realiza 2 trocas e balanceia uma subarvore
    no->filhoDir = RotacaoSimplesDireita(no->filhoDir);
    no = RotacaoSimplesEsquerda(no);
    return no;
}
int DiferencaAltura(ArvBina* no) { //Função auxiliar,dado um no, ele calcula a diferenca de altura de seus dois filhos
    int DifEsq,DifDir,Dif;
    if(no==NULL) { // se o no for nulo entao altura é 0
        return 0;
    }
    else { //usa recursao pra calcular de baixo pra cima os fatores de balanceamento, sendo que o no pai vai ter Fator de balanceamento do filho +1
        DifEsq = DiferencaAltura(no->filhoEsq);
        DifDir = DiferencaAltura(no->filhoDir);
        Dif = DifEsq - DifDir;
        no->FB = Dif;
        return (1+Maximo(DifEsq,DifDir));
    }
}
ArvBina* Balanceia(ArvBina* no) { //Função auxiliar, dado um no, ele chama funções de rotação com base no seu fator de balanceamento
    if(no!=NULL) {
        if(abs(no->FB)>=2) { // se fator de balanceamento(FB) for maior ou igual a 2, entao ta desbalanceado
            ArvBina* aux;
            if(no->FB > 1) {  //se FB for maior que 1 entao entramos nos casos de necessidade de rotacões a esquerda, pois o filho esquerdo é maior
                aux = no->filhoEsq;  //verificamos o FB do filho esquerdo pra ver se é uma rotacao dupla ou simples
                if(aux->FB < 0 ) { //se for menor que 0 é uma dupla pois o filho direito do filho esquerdo ta desbalanceado
                    no = RotacaoDuplaDireita(no);
                }
                else {// se nao o filho esquerdo do filho esquerdo esta desbalanceado
                    no = RotacaoSimplesDireita(no);
                }
            }
            else { //se FB não for maior que 1 entao entramos nos casos de necessidade de rotacões a direita, pois o filho direita é maior
                aux = no->filhoDir; //mesma coisa, pegamos o filho direito pra verificar qual rotacao
                if(aux->FB > 0) { // se for maior que 0 o FB do filho, é uma rotacao dupla pois o filho esquerdo do filho direito esta desbalanceado
                    no = RotacaoDuplaEsquerda(no);
                }
                else { // se nao é o filho direito do filho direito, rotacao simple resolve
                    no = RotacaoSimplesEsquerda(no);
                }
            }
        }
    }
    return no; // retornamos o no, modificado ou não
}
ArvBina* InsereArv(ArvBina* no,int chave) { //Função Principal,Insere Balanceadamente na arvore um inteiro
    if(no==NULL || no->chave == 0) { //se no for nulo entao é necessario criar um novo no, estou verificando se é 0 só por precaução
        no = CriarNo(chave);
        return no;
    }
    else if(no->chave > chave) { //se a chave do no é maior que a chave, chamamos recursivamente a função com o filho esquerdo pra buscar o no nulo
        no->filhoEsq = InsereArv(no->filhoEsq,chave);
    }
    else { //se a chave nao for maior que a chave do no, entao é menor, buscamos no filho direito
        no->filhoDir = InsereArv(no->filhoDir,chave);
    }
    DiferencaAltura(no);//apos a busca, atualizamos a diferenca de altura de cada no
    no = Balanceia (no); //depois  chamanos a função balanceia, que verifica se precisa de uma rotação
    return no; // retornamos o no, modificado ou não
}

void OrdemCresc(ArvBina* no) { //Função optativa, foi usada pra bug-testing, ela imprime todos as chaves da arvore em forma crescente
    if(no!=NULL) { //se no nao for nulo entao tem mais pra procurar
        OrdemCresc(no->filhoEsq);// recursao a esquerda ate ser nulo
        printf("%d\n",no->chave); // printa todas as chamadas recursivas
        OrdemCresc(no->filhoDir); //mesma coisa a direita
    }
}
