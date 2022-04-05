#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TEXTO 1000 
#define DEBUG 0

char escolherAcao()
{
    char acao;
    printf("Insira 'C' para codificar ou 'D' para decodificar:\n");
    scanf("%c", &acao);
    
    return acao;
}

char* obterTexto()
{
    char* texto = malloc(TAMANHO_TEXTO * sizeof(char));
    printf("Insira o texto a ser processado:\n");
    scanf("%s", texto);
      
#if DEBUG    
    printf("\n TEXTO OBTIDO: %s\n", texto);
#endif

    return texto;
}

char* converter(char* texto)
{
    int i = 0, j = 0, eof = 0;
    char* convertido = malloc(2 * TAMANHO_TEXTO * sizeof(char));
    
    while (i < TAMANHO_TEXTO)
    {
        switch (texto[i])
        {
            case '\0':
                eof = 1;
                break;
                
            case 'Z':
                convertido[j] = texto[i];
                j++;
                convertido[j] = texto[i];
                break;
            
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                convertido[j] = 'Z';
                j++;
                convertido[j] = texto[i] + 17;
                break;
                
            default:
                convertido[j] = texto[i];
                break;
        }
        
        i++;
        j++;
    }
    
#if DEBUG    
    printf("\n TEXTO CONVERTIDO: %s\n", convertido);
#endif

    return convertido;
}

void concatenar(int qtd, char** recodificado, char* ultimo)
{
    if (qtd > 1) 
    {
        char s_qtd[4];
        sprintf(s_qtd, "%d", qtd);
        strcat(*recodificado, s_qtd);
    }
    
    strcat(*recodificado, ultimo);
}

char* recodificar(char* texto)
{
    int i = 1, j = 0, eof = 0;
    char* recodificado = malloc(TAMANHO_TEXTO * sizeof(char));
    char ultimo = texto[0];
    int qtd = 1;
    
    while (i < TAMANHO_TEXTO && texto[i] != '\0')
    {
        if (texto[i] == ultimo) 
        {
            qtd++;
        }
        else
        {
            concatenar(qtd, &recodificado, &ultimo);
            
            ultimo = texto[i];
            qtd = 1;
        }
        
        i++;
    }

    concatenar(qtd, &recodificado, &ultimo);
    
    return recodificado;
}

char* codificar(char* texto)
{
    char* convertido = converter(texto);
    char* recodificado = recodificar(convertido);
    
    free(convertido);
    
    return recodificado;
}

char* decodificar(char* texto)
{
    return NULL;
}

int main(void) 
{
    char acao = escolherAcao();
    char* texto = obterTexto();
    char* processado;
    
    switch (acao) 
    {
        case 'C':
            processado = codificar(texto);
            printf("\nO texto foi codificado:\n");
            printf("%s\n", processado);
            break;
            
        case 'D':
            break;
    }
    
    free(texto);
    free(processado);
    
    return 0;
}

