#include <stdio.h>
#include <string.h>
#include <math.h>
#define max_char 10
#define max_struct 10
#define N 10

typedef struct
{
    float x;
    float y;
    float z;
    char nome[max_char];
} punto;

int carica_dati(FILE *, punto[], int);
void calcola_distanze(punto[], int, char, float[][N], int *);
void stampa(float[][N], int);

int main()
{

    punto vector[max_struct];
    FILE *puntatore;
    int punti_letti;
    char lettera;
    float matrice[N][N];
    int punti_s;

    puntatore = fopen("punti.txt", "r");
    punti_letti = carica_dati(puntatore, vector, max_struct);
    if (punti_letti == EOF)
    {
        printf("Errore nella lettura del file\n");
    }
    else
    {
        printf("Punti letti: %d\n", punti_letti);
    }
    fclose(puntatore);
    printf("Scrivi la lettera:\n");
    scanf("%c", &lettera);
    calcola_distanze(vector, punti_letti, lettera, matrice, &punti_s);
    stampa(matrice, punti_s);

    return 0;
}

int carica_dati(FILE *pointer, punto array[], int max)
{

    int r;
    int i = -1;

    if (pointer == NULL)
    {
        return -1;
    }
    else
    {
        do
        {
            i++;
            r = fscanf(pointer, "%f %f %f %s", &array[i].x, &array[i].y, &array[i].z, array[i].nome);
        } while (r == 4 && i < max);
        return i;
    }
}

void calcola_distanze(punto array[], int punti_letti, char lettera, float matrix[][N], int *p_s)
{
    int j;
    int i = 0;
    int count = 0;
    char *result;
    int indici[10];

    for (j = 0; j < punti_letti; j++)
    {
        result = strchr(array[j].nome, lettera);
        if (result != NULL)
        {
            count++;
            indici[i] = j;
            i++;
            printf("Indirizzo: %p\n", result);
        }
    }

    printf("Visualizzo indici:\n");
    for (j = 0; j < count; j++)
    {
        printf("Indice [%d] -> %d\n", j, indici[j]);
    }

    printf("La lettera e' presente in %d parole\n", count);

    double temp;
    int p;
    int c = 0;

    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count; j++)
        {
            temp = 0;
            temp += pow((array[indici[i]].x - array[indici[j]].x), 2);
            temp += pow((array[indici[i]].y - array[indici[j]].y), 2);
            temp += pow((array[indici[i]].z - array[indici[j]].z), 2);
            temp = sqrt(temp);
            printf("Temp: %f\n", temp);
            matrix[i][j] = temp;
        }
    }
    *p_s = i;
}

void stampa(float matrix[][N], int max)
{

    int i, j;
    for (i = 0; i < max; i++)
    {
        for (j = 0; j < max; j++)
        {
            printf("%f;\t", matrix[i][j]);
        }
        printf("\n");
    }
}