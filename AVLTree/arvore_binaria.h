typedef struct ArvBin { //Estrutura de Dados tipo árvore binária
    int chave; //Dado Inteiro a ser inserido
    int FB; //Fator de Balanceamento da árvore, dependendo disso ela decide se vai balancear ou não
    struct ArvBin *filhoEsq; //Ponteiro pra subárvore esquerda
    struct ArvBin *filhoDir; //Ponteiro pra subárvore direita
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
