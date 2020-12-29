#include <stdio.h>
#include <string.h>

#define max_char 5
#define max_struct 200

typedef struct
{
    char andata[max_char];
    char ritorno[max_char];
} voli;

int load_data(voli[], FILE *, int *);
void tratte_andata_ritorno(voli[], int, voli[], int *);
void visualizza_tratte(voli[], int);

int main()
{

    FILE *stream;
    voli array[max_struct];
    voli tratte[max_struct];
    int righe[20];
    int ris;
    int numero_voli = 0;
    int voli_uguali;

    stream = fopen("input.txt", "r");

    if (stream == NULL)
    {
        printf("Apertura non andata a buon fine\n");
    }
    else
    {

        ris = load_data(array, stream, &numero_voli);
        fclose(stream);

        tratte_andata_ritorno(array, numero_voli, tratte, &voli_uguali);

        visualizza_tratte(tratte, voli_uguali);
    }

    return 0;
}

int load_data(voli array[], FILE *stream, int *n_voli)
{
    int count;
    int result;

    count = 0;
    while (count < 200)
    {
        result = fscanf(stream, "%s %s", array[count].andata, array[count].ritorno);
        if (result == 2)
        {
            count++;
        }
        else
        {
            break;
        }
    }
    *n_voli = count;
}

void tratte_andata_ritorno(voli array[], int n, voli nomi[], int *voli_uguali)
{
    int uguali = 0;
    int i, j;
    int compare = 0;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            compare = 0;
            compare = strcmp(array[i].andata, array[j].ritorno);
            compare += strcmp(array[i].ritorno, array[j].andata);
            if (compare == 0)
            {
                strcpy(nomi[uguali].andata, array[i].andata);
                strcpy(nomi[uguali].ritorno, array[j].ritorno);
                uguali++;
            }
        }
    }
    *voli_uguali = uguali;
}

void visualizza_tratte(voli nomi[], int num_voli)
{
    int i;
    printf("Numero di tratte con andata e ritorno: %d\n", num_voli);
    for (i = 0; i < num_voli; i++)
    {
        printf("%s\t%s\n", nomi[i].andata, nomi[i].ritorno);
    }
}