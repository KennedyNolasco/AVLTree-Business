typedef struct ArvBin { //Estrutura de Dados tipo �rvore bin�ria
    int chave; //Dado Inteiro a ser inserido
    int FB; //Fator de Balanceamento da �rvore, dependendo disso ela decide se vai balancear ou n�o
    struct ArvBin *filhoEsq; //Ponteiro pra sub�rvore esquerda
    struct ArvBin *filhoDir; //Ponteiro pra sub�rvore direita
} ArvBina;

int Maximo(int A, int B);
ArvBina* CriarNo(int chave);
ArvBina* MenordosMaiores(ArvBina* procurador);
ArvBina* ProcuraElemento(ArvBina* no, int chave);
//int Busca(ArvBina* no, int chave);
ArvBina* RemoveElemento(ArvBina* no, int chave);
ArvBina* RotacaoSimplesDireita(ArvBina* no);
ArvBina* RotacaoSimplesEsquerda(ArvBina* no);
ArvBina* RotacaoDuplaDireita(ArvBina* no);
ArvBina* RotacaoDuplaEsquerda(ArvBina* no);
int DiferencaAltura(ArvBina* no);
ArvBina* Balanceia(ArvBina* no);
ArvBina* InsereArv(ArvBina* no,int chave);
void OrdemCresc(ArvBina* no);
