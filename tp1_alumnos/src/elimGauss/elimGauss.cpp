#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <vector>

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
        float A[cantEq][cantEq];
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
                E[linea[1]-1].pg ++;
            }
        }
        cout << "la matriz inicial es esta: " << endl;
        for(int i=0; i<cantEq ; i++){
			cout << "|| ";
			for (int j=0; j<cantEq ; j++){
			cout << A[i][j] << " || ";
			}
			cout << endl;
		}
		
        cout << "B inicial: " << endl;
        float B[cantEq];
        for (int i = 0; i<cantEq;i++){
            B[i] = 1 + (((float)E[i].pg - (float)E[i].pp)/2);
            cout << B[i] << " , ";
        }
        cout << endl;
        /*
        for(int i = 0;i<cantEq;i++){
            for(int j = 0;j<cantEq;j++){
                cout << A[i][j]<<" ; ";
            }
            cout <<endl;
        }*/
		float mult;
                
        for(int k=0; k<cantEq-1; k++){
			for(int i=k+1;i<cantEq; i++){
				if (A[i][k]!=0){
					mult = A[i][k]/A[k][k];
					A[i][k]=0.0;
					for(int j=k+1;j<cantEq;j++){
						A[i][j] = A[i][j] - mult*A[k][j];
					}
					B[i] = B[i] - mult * B[k];
				}
			}
		}
        
        cout << "la matriz diagonalizada es esta: " << endl;
        for(int i=0; i<cantEq ; i++){
			cout << "|| ";
			for (int j=0; j<cantEq ; j++){
			cout << A[i][j] << " || ";
			}
			cout << endl;
		}
        //Despues de esto ya esta triangulada, y solo hace falta resolver.
        float result[cantEq];
        for (int i = 0;i<cantEq;i++){
            result[i] = 0;
        }
        /*for(int i = 0;i<cantEq;i++){
            for(int j = 0;j<cantEq;j++){
                cout << A[i][j]<<" ; ";
            }
            cout <<endl;
        }*/
        for(int i = 1; i<cantEq+1;i++){
                /*
            float suma = 0;
            for(int j = cantEq-i+1; j<cantEq;j++){
                suma = - (float)A[cantEq-i][j]*result[j];
            }
            result[cantEq-i] = (float)(1/A[cantEq-i][cantEq-i])*(B[cantEq-i] + suma);*/
            float suma = B[cantEq-i];
            for (int j = cantEq-i+1;j<cantEq;j++){
                suma = suma - A[cantEq-i][j]*result[j];
            }
            result[cantEq-i] = (float)(1/A[cantEq-i][cantEq-i]) *suma;
        }
                cout << "Imprimo B: " << endl;
        for(int i = 0; i<cantEq;i++){
            cout << B[i] << endl;
        }
        cout << "Imprimo result: "<< endl;
        for(int i = 0; i<cantEq;i++){
            cout << result[i]<<endl;
        }
    }
    return 0;
}
