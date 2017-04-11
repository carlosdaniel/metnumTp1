#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <unistd.h>



using namespace std;



clock_t tiempos(int algoritmo,int cantElementos){
    double M[cantElementos][cantElementos];
    for(int i = 0;i<cantElementos;i++){
        for(int j = 0;j< cantElementos;j++){
            M[i][j] = rand() % 10 + 1;
        }
    }


    double B[cantElementos];

    for(int i = 0;i<cantElementos;i++){
        B[i] = rand() % 10 + 1;
    }

    double elapsed_secs;
    clock_t begin = clock();
    if(algoritmo == 1){
        //Entonces es cholesky
        //Run Algoritmo de cholesky
    }else if(algoritmo == 2){
        //Entonces es elminacion gaussiana
        //Run elminacion gaussiana
    }
    clock_t end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    return elapsed_secs;
}

void experimentoUno(){
    int n;
    cout << "Cuantos casos pruebo"<<endl;
    cin >> n;
    float tiemposC[n];
    float tiemposEg[n];
    for(int i = 0;i<n;i++){
        tiemposC[i] = tiempos(1,i*30);
        tiemposEg[i] = tiempos(2,i*30);
    }

}

void experimentoDos(){
    //Dado una matriz fija, vamos a correr tanto con cholesky como con gaussiana, pero cambiando el b y verificando
    //cuanto tiempo de diferencia empieza a haber cuando la cantidad de veces que corriste el programa es mas grande

    int n,m;
    cout << "Matriz de que tamaño"<<endl;
    cin >> n;
    cout <<"Cuantas veces corremos el programa?"<<endl;
    cin >> m;
    double M[n][n];
    for(int i = 0;i<n;i++){
        for(int j = 0;j< n;j++){
            M[i][j] = rand() % 10 + 1;
        }
    }


    double B[n];

    double tiemposC[n];
    double tiemposEg[n];

    double elapsed_secs;

    //Correr cholesky, para saber L, y guardarla para usarla luego.


    for(int i = 1;i<m;i++){
        for(int i = 0;i<n;i++){
            B[i] = rand() % 10 + 1;
        }
        clock_t begin = clock();

        //correr gauss

        clock_t end = clock();
        elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        tiemposEg[i] = elapsed_secs + tiemposEg[i-1];
        begin = clock();

        //correr cholesky sabiendo la fact...(asi se hace mas rapido)

        end = clock();
        elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        tiemposC[i] = elapsed_secs+ tiemposC[i-1];

    }




}

int main(){

    experimentoUno();
    experimentoDos();


    return 0;
}


