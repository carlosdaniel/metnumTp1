#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <math.h> 

using namespace std;

int main(){
	ifstream file;
    file.open("input.txt",ios::in);
    string line;

    if (file.fail()){
        cout << " No se pudo abrir ";
    }else{
        string leoInt;
        getline(file, leoInt, ' ');
        int cantEq = atoi(leoInt.c_str());
        float A[cantEq][cantEq];
        struct puntosEq {
            int pg; //Partidos ganados
            int pp; //partidos perdidos
        } E [cantEq];
        getline(file, leoInt);
        int cantPartidos = atoi(leoInt.c_str());
        int linea[4];
        string num;
        for(int i = 0; i< cantEq;i++){
            for(int j = 0; j< cantEq;j++){
                A[i][j] = 0;
            }
        }
        for(int i = 0; i< cantEq;i++){
            A[i][i] = 2;
            E[i].pp = 0;
            E[i].pg = 0;
        }

        while(getline(file,line)){
            istringstream leoNumero (line);
            int i = 0;
            while(getline(leoNumero, num,' ')){
                linea[i] = atoi(num.c_str());
                i++;
            }
            A[linea[0]-1][linea[2]-1] --;
            A[linea[2]-1][linea[0]-1] --;
            A[linea[0]-1][linea[0]-1] ++;
            A[linea[2]-1][linea[2]-1] ++;
            if(linea[1] > linea[3]){
                //Gano equipo 1
                E[linea[0]-1].pg ++;
                E[linea[2]-1].pp ++;

            }else{
                E[linea[0]-1].pp ++;
                E[linea[2]-1].pg ++;
            }
        }
        float b[cantEq];
        for (int i = 0; i<cantEq;i++){
            b[i] = 1 + (((float)E[i].pg - (float)E[i].pp)/2);
        }
        
		float acum;

		//comienza el metodo de choleski
		for(int k=0; k<cantEq; k++){
			for(int i=0; i<=k-1; i++){
				acum = 0.0;
				for(int j=0;j<=i-1;j++){
					acum = acum + (A[i][j]*A[k][j]);
				}
				A[k][i]=A[k][i]- (acum/A[i][i]);
			}
			acum = 0.0;
			for (int j=0;j<=k-1;j++){
				acum = acum + A[k][j]*A[k][j];
			}
			A[k][k] = sqrt(A[k][k]-acum);
		}
		
		//declaramos la matriz traspuesta
		float Lt[cantEq][cantEq];
		
		//añadimos los ceros por arriba de la diagonal de A
		//añadimos los ceros por debajo de la diagonal de Lt
		//copiamos espejdamente los valores de A a Lt
		for(int i=0; i<cantEq; i++){ 
			for(int j=0;j<cantEq;j++){ 
				if (j>i){
					A[i][j] = 0.0;
					Lt[j][i] = 0.0;
				}else{
					Lt[j][i]= A[i][j];
				}
			}
		}
		//La matriz A quedó convertida en L, luego Lt es solo intercambiar filas por columnas
        
        
		//falta la resolución
	}
return 0;
}
