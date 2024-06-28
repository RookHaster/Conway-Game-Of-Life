#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define CANTCELL 5
#define ALTO 62
#define ANCHO 236
#define ALIVE 'O'
#define DEAD ' '

int randint(int n, int m){
    return n + rand() % (m - n + 1);
}

void print_array(char image[ALTO][ANCHO]) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    DWORD bytes_written;
    SetConsoleCursorPosition(hConsole, coord);
    char buffer[ALTO * (ANCHO + 1)];
    int index = 0;
    for (int f = 0; f < ALTO; f++) {
        for (int c = 0; c < ANCHO; c++) {
            buffer[index++] = image[f][c];
        }
        buffer[index++] = '\n';
    }
    buffer[index] = '\0';
    WriteConsole(hConsole, buffer, strlen(buffer), &bytes_written, NULL);
}

void init_array(char image[ALTO][ANCHO]){
    for (int f = 0; f<=ALTO-1; f++){
        for (int c = 0; c<=ANCHO-1; c++){
            int random = randint(1,CANTCELL);
            if (random == 3){image[f][c] = ALIVE;}
            else{image[f][c] = DEAD;}
        }
        int fila, columna;
        for(fila=0; fila<=ALTO-1; fila++){image[fila][0]=DEAD;}
        for(fila=0; fila<=ALTO-1; fila++){image[fila][ANCHO-1]=DEAD;}
        for(columna=0; columna<=ANCHO-1; columna++){image[0][columna]=DEAD;}
        for(columna=0; columna<=ANCHO-1; columna++){image[ALTO-1][columna]=DEAD;}
    }
}

void init_new(char new[ALTO][ANCHO]){
    for (int f = 0; f<=ALTO-1; f++){
        for (int c = 0; c<=ANCHO-1; c++){
            new[f][c]=DEAD;
        }
    }
}

int dead_alive(char image[ALTO][ANCHO], int n, int m){
    int vecinos;
    if (image[n][m]==ALIVE){
        vecinos = -1;
        for (int f = n-1; f <= n+1; f++){
            for(int c = m-1; c <= m+1; c++){
                if (image[f][c] == ALIVE){vecinos++;}
            }
        }
        if (vecinos<2 || vecinos>3){return 0;}
        else{return 1;}
    }
    else {
        vecinos = 0;
        for (int f = n-1; f <= n+1; f++){
            for(int c = m-1; c <= m+1; c++){
                if (image[f][c] == ALIVE){vecinos++;}
            }
        }
        if (vecinos == 3){return 1;}
        else {return 0;}
    }
}

void check(char new[ALTO][ANCHO], char image[ALTO][ANCHO]){
    int temp;
    for (int n = 1; n <= ALTO-2; n++){
        for(int m = 1; m <= ANCHO-2; m++){
            temp = dead_alive(image, n, m);
            if (temp == 1){new[n][m]=ALIVE;}
            if (temp == 0){new[n][m]=DEAD;}
        }
    }
    for (int n = 0; n <= ALTO-1; n++){
        for (int m = 0; m <= ANCHO-1; m++){
            image[n][m] = new[n][m];
        }
    }
}

//====================== MAIN ============================
int main(){
    srand(time(0));
    char image[ALTO][ANCHO];
    init_array(image);
    char newframe[ALTO][ANCHO];
    init_new(newframe);

    for (;;){
        check(newframe, image);
        print_array(image);
        Sleep(50);
    }

    return 0;
}