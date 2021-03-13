#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _REG_FIXO_AUX {
    char uf[2];
    char nomeUf[17];
    char mesorregiao[20];
    char nomeMesorregiao[31];
    char microrregiao[20];
    char nomeMicrorregiao[33];
    char codigo[8];
    char codigoCompleto[23];
    char nomeMunicipio[55];
    char delim;
} REG_FIXO_AUX;

typedef struct _REGISTRO {
    int uf;
    char estado[19];
} REGISTRO;

int main()
{
    FILE *fp;
    REG_FIXO_AUX aux;
    REGISTRO reg;
    char auxEstado[19],buffer[4096], *p;
    int c, count, estado;


    if( (fp = fopen("ibge_municipios_coluna_fixa_sem_cab.txt","rt")) == NULL ) {
        printf("Arquivo nao encontrado.\n");
        exit(-1);
    }

    c = 1;
    count = 0;
    while (!feof(fp)) {
        //limpa a memória
        memset(buffer,0, 4096);

        //coloca a linha no buffer
        fgets(buffer,4096,fp);

        // coloca o p apontando para o buffer
        p = buffer;

        // remove a quebra de linha
        while( *p != '\0' ) {
            if( *p == '\n' || *p == '\r' ) {
                *p='\0';
                break;
            }
            p++;
        }

        //passa do buffer para o registro auxiliar
        memcpy((void*)&aux, buffer, sizeof(REG_FIXO_AUX));

        //coloca \0 no delimitador
        aux.delim = '\0';

        //limpa o registro
        memset((void*)&reg, 0, sizeof(REGISTRO));

        //coloca \0 no final da string
        aux.nomeUf[17] = '\0';

        //passa pro registro
        reg.uf = atoi(aux.uf);
        strcpy(reg.estado, aux.nomeUf);

        //se o estado continuar igual aumenta 1 o número de municípios caso não escreve o nome do estado e o número de municipios
        /*
        Saída errada não reconhece acentos e alguns estados possuem nome muito extenso
        if(c == 1 || estado == reg.uf){
            count++;
        } else {
            printf("%s: %d\n", auxEstado, count);
            count = 1;
        }
        */

        if(c == 1 || estado == reg.uf){
            count++;
        } else {
            switch (estado){
                case 11:
                    printf("Rondônia           : %d\n", count);
                    break;
                case 15:
                    printf("Pará               : %d\n", count);
                    break;
                case 16:
                    printf("Amapá              : %d\n", count);
                    break;
                case 21:
                    printf("Maranhão           : %d\n", count);
                    break;
                case 22:
                    printf("Piauí              : %d\n", count);
                    break;
                case 23:
                    printf("Ceará              : %d\n", count);
                    break;
                case 24:
                    printf("Rio Grande do Norte: %d\n", count);
                    break;
                case 25:
                    printf("Paraíba            : %d\n", count);
                    break;
                case 32:
                    printf("Espírito Santo     : %d\n", count);
                    break;
                case 35:
                    printf("São Paulo          : %d\n", count);
                    break;
                case 41:
                    printf("Paraná             : %d\n", count);
                    break;
                case 50:
                    printf("Mato Grosso do Sul : %d\n", count);
                    break;
                case 52:
                    printf("Goiás              : %d\n", count);
                    break;
                default:
                    printf("%s: %d\n", auxEstado, count);
                    break;
            } 
            count = 1;
        }

        //passa para as variaveis auxiliares
        strcpy(auxEstado, reg.estado);
        auxEstado[17] = ' ';
        auxEstado[18] = ' ';
        auxEstado[19] = '\0';
        estado = reg.uf;

        c++;
    }
    fclose(fp);
    return 0;
}
