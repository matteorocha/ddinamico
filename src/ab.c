#include "stdio.h"
#include "stdlib.h"

// sae -> Sub árvore esquerda;
// sad -> Sub árvore direita;

typedef struct no t_no;
struct no
{
    void* info;
    t_no *sae;
    t_no *sad;
    t_no *ancestral;
};

t_no* criar_no(void *info, t_no *ancestral)
{
    t_no* novo = malloc(sizeof(t_no));
    novo -> info = info;
    novo -> ancestral = ancestral;
    novo -> sad = NULL;
    novo -> sae = NULL;

    return novo;
}

typedef struct ab t_ab;
struct ab
{
    t_no* raiz;
    int tamanho;
};

t_ab* criar_ab()
{
    t_ab* nova = malloc(sizeof(t_ab));
    nova -> raiz = NULL;
    nova -> tamanho = 0;
    return nova;
}

static t_no* _inserir_ab(t_no* raiz, void* info, t_no* ancestral)
{
    if (raiz == NULL)
    {
        return criar_no(info, ancestral);
    }
    else
    {
        int k = (sorteio() % 2);
        if (k == 0)
        {
            _inserir_ab(raiz -> sae, raiz, info);
        }
        else
        {
            _inserir_ab(raiz -> sad, raiz, info);
        }
    }
}

void inserir_ab(t_ab *ab, void* info)
{
    _inserir_ab(ab -> raiz, ancestral, info);
}