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
    file.open("entrada.txt",ios::in);
    string line;

    if (file.fail()){
        cout << " No se pudo abrir ";
    }else{
        string leoInt;
        getline(file, leoInt, ' ');
        int cantEq = atoi(leoInt.c_str());
        double A[cantEq][cantEq];
        struct puntosEq {
            int pg; //Partidos ganados
            int pp; //partidos perdidos
        } E [cantEq];
        getline(file, leoInt);
        int cantPartidos = atoi(leoInt.c_str());
        int linea[5];
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
            A[linea[1]-1][linea[3]-1] --;
            A[linea[3]-1][linea[1]-1] --;
            A[linea[1]-1][linea[1]-1] ++;
            A[linea[3]-1][linea[3]-1] ++;
            if(linea[2] > linea[4]){
                //Gano equipo 1
                E[linea[1]-1].pg ++;
                E[linea[3]-1].pp ++;

            }else{
                E[linea[1]-1].pp ++;
                E[linea[3]-1].pg ++;
            }
        }
        
        cout << "la matriz inicial es esta: " << endl;
        for(int i=0; i<cantEq ; i++){
			for (int j=0; j<cantEq ; j++){
			cout << "|" << A[i][j] << "|";
			}
			cout << endl;
		}
        
        double b[cantEq];
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
		
		cout << "la matriz despues de cholesky es la sgte:" << endl;
		for(int i=0;i<cantEq;i++){
			for(int j=0;j<cantEq;j++){
				cout << "|" << A[i][j] << "|";
			}
			cout << endl;
		}
		//como A es triangular inferior y Lt es es triangular superior 		
		//vamos a unir las dos matrices en A, de manera que A queda simetrica.
		
		for(int i=1; i<cantEq; i++){ 
			for(int j=0;j<i;j++){ 
				A[j][i] = A[i][j];
			}
		}
		//La matriz A quedó convertida en L, luego Lt es solo intercambiar filas por columnas
        //La idea de cholesky es la siguiente:
        //Ax = b ......   A=L*Lt
        //Ax = b es lo mismo que resolver L * Lt*x = b, tenemos L vamos a usar Lt*x = y
        //resolvemos L * y = b
        
        double y[cantEq];
        y[0]=b[0]/A[0][0];
        //vamos armando el vector Y progresivamente A es triangular inferior
        for(int i=1;i<cantEq;i++){
			acum = 0.0;
			for(int j=0;j<i;j++){
				acum = acum + (A[i][j]*y[j]);
			}
			y[i]=(b[i]-acum)/A[i][i];
		}
				
		//ya se tiene el vector y, lo que falta realizar es Lt *x = y 
		double x[cantEq];
		x[cantEq]=y[cantEq-1]/A[cantEq-1][cantEq-1];
		
		for(int i=cantEq-2;i>=0;i--){
			acum = 0.0;
			for(int j=cantEq-1;j>i;j--){
				acum = acum + A[i][j]*x[j];
			}
			x[i]=(y[i]-acum)/A[i][i];
		}

	}
return 0;
}
