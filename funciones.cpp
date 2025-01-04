//funciones.cpp
#include "minijuegos.h"
#include <iostream>
#include<stdlib.h>
#include<ctime>
#include <climits>
using namespace std;
/////////////////////////////////////////////////// juego del 3 en raya //////////////////////////////////////////////
jugador_3enraya jugador1_3enraya(1,'X',0);
jugador_3enraya jugador2_3enraya(2,'O',0);


int minijuego_3_raya() {//main
    cout << "Tres en raya: \n" << "Empiecen! \n";
    cout << "1  | 2 | 3\n";
    cout << "___|___|___\n";
    cout << "4  | 5 | 6\n";
    cout << "___|___|___\n";
    cout << "   |   |\n";
    cout << "7  | 8 | 9\n";
    cout << "jugador 1: X"<< endl<<"jugador 2: O"<< endl;
    bool tres = true;
    while (tres){
        entrada_player(&jugador1_3enraya);
        imprime_3_raya();
        ganar_tresenraya(&jugador1_3enraya);
        gano_3(tres,&jugador1_3enraya);
        entrada_player(&jugador2_3enraya);
        imprime_3_raya();
        ganar_tresenraya(&jugador2_3enraya);
        gano_3(tres,&jugador2_3enraya);
    }
    return puntaje_3enraya;
}
void imprime_3_raya(){
    system("cls");
    cout << pos1<<"  | "<<pos2<<" | "<<pos3<<"\n";
    cout << "___|___|___\n";
    cout << pos4<<"  | "<<pos5<<" | "<<pos6<<"\n";
    cout << "___|___|___\n";
    cout << "   |   |\n";
    cout << pos7<<"  | "<<pos8<<" | "<<pos9<<"\n";
}
void verificador_posicion(char &pos,bool &ocupado,jugador_3enraya *j3enraya){
    if(ocupado == false){
        pos = j3enraya->simbolo;
        ocupado = true;
    }
    else{
        cout << "ERROR: lugar ocupado... \n";
        entrada_player(j3enraya);
    }
}
void entrada_player(jugador_3enraya *j3enraya ){
    cout << "Jugador "<< j3enraya->num  <<" Selecciona una posición: "; cin >> posicion;
    while (cin.fail()){
        cin.clear(); // Quitar el valor no válido.
        cin.ignore(INT_MAX, '\n'); // Quitar el valor no válido.
        cout << "Solo puedes ingresar números\n";
        cout << "Jugador "<< j3enraya->num  <<" Selecciona una posición: ";
        cin >> posicion;
    	}
    switch(posicion){
        case 1: verificador_posicion(pos1, ocupada1,j3enraya);break;
        case 2: verificador_posicion(pos2, ocupada2,j3enraya);break;
        case 3: verificador_posicion(pos3, ocupada3,j3enraya);break;
        case 4: verificador_posicion(pos4, ocupada4,j3enraya);break;
        case 5: verificador_posicion(pos5, ocupada5,j3enraya);break;
        case 6: verificador_posicion(pos6, ocupada6,j3enraya);break;
        case 7: verificador_posicion(pos7, ocupada7,j3enraya);break;
        case 8: verificador_posicion(pos8, ocupada8,j3enraya);break;
        case 9: verificador_posicion(pos9, ocupada9,j3enraya);break;
    }
}
void ganar_tresenraya(jugador_3enraya *j3enraya){
    if ( (pos1!=' ')&&(pos1==j3enraya->simbolo)&&(pos1==pos2)&&(pos1==pos3)) j3enraya->ganar=1;
    if ( (pos1!=' ')&&(pos1==j3enraya->simbolo)&&(pos1==pos4)&&(pos1==pos7)) j3enraya->ganar=1;
    if ( (pos1!=' ')&&(pos1==j3enraya->simbolo)&&(pos1==pos5)&&(pos1==pos9)) j3enraya->ganar=1;
    if ( (pos4!=' ')&&(pos4==j3enraya->simbolo)&&(pos4==pos5)&&(pos4==pos6)) j3enraya->ganar=1;
    if ( (pos7!=' ')&&(pos7==j3enraya->simbolo)&&(pos7==pos8)&&(pos7==pos9)) j3enraya->ganar=1;
    if ( (pos2!=' ')&&(pos2==j3enraya->simbolo)&&(pos2==pos5)&&(pos2==pos8)) j3enraya->ganar=1;
    if ( (pos3!=' ')&&(pos3==j3enraya->simbolo)&&(pos3==pos6)&&(pos3==pos9)) j3enraya->ganar=1;
    if ( (pos7!=' ')&&(pos7==j3enraya->simbolo)&&(pos7==pos5)&&(pos7==pos3)) j3enraya->ganar=1;
}
int gano_3(bool &tres,jugador_3enraya *j3enraya){ //7 alguien gano, 5 es empate
    if (jugador1_3enraya.ganar == 1){
    	cout << "Felicidades, gano el jugador retado " << j3enraya->num << endl; puntaje_3enraya=3;
        tres = false;
	}
	else if (jugador2_3enraya.ganar == 1){
    	cout << "El jugador retado perdió " << j3enraya->num << endl; puntaje_3enraya=1;
        tres = false;
	}
    else if(ocupada1 == true && ocupada2== true && ocupada3== true && ocupada4== true && ocupada5== true && ocupada6== true && ocupada7== true && ocupada8== true && ocupada9 == true){
        cout << "Todas las piezas han sido seleccionadas" << "GAME OVER"<< endl; puntaje_3enraya=2;
        tres = false;
    }
  return puntaje_3enraya;
}


///////////////////////////////////////////////////////// buscaminas ///////////////////////////////////////////////////////////
int busca_minas(){//main
    cout << "Busca minas: " << endl;
    cout<<"  Instrucciones:Muévete con cuidado de no encontrar bombas, si logras 5 movimientos sin morir ganas\n";
	char tab_min[f][c],visual_min[f][c], comando_min;
    bool b_min= true;
    int b_f=0, b_c=0, temp=0,g;
	crea_map_minas(tab_min); //crea el mapa con bombas, este no se muestra en pantalla
	mapa_visual_minas(visual_min); //crea mapa sin minas, si se uestra en pantalla a medida que avanza se muestran partes del mapa anterior
    visual_min[b_f][b_c] = '*';
	print_minas(visual_min);
    while (b_min){
    	cout<<"Ingrese movimiento: "; cin >> comando_min;
    	if (comando_min == 'w'){
    	    visual_min[b_f][b_c] = tab_min[b_f][b_c];
		    b_f = b_f -2;
		}
    	if (comando_min == 's'){
    	    visual_min[b_f][b_c] = tab_min[b_f][b_c];
		    b_f = b_f +2;
		}
    	if (comando_min == 'a'){
    	    visual_min[b_f][b_c] = tab_min[b_f][b_c];
		    b_c = b_c -2;
		}
    	if (comando_min == 'd'){
    	    visual_min[b_f][b_c] = tab_min[b_f][b_c];
		    b_c = b_c +2;
		}
    	visual_min[b_f][b_c] = '*';
    	radio(b_f, b_c, visual_min, tab_min);
		print_minas(visual_min);
		temp += 1;
        for(int x=0; x<f; x++){ //recore el mapa buscando una bomba, si es así pierdes
            for(int y=0; y<c ; y++){
                if (visual_min[x][y] =='O'){ b_min = false; cout <<"Game over"<< endl; g=1; break; }}}
        if (temp == 5){ b_min = false; cout <<"Ganaste!!"<<endl; g=3; break; }
		if(b_min==false) break;
	}
	return g;
}//buscaminas 2gane 1perder
void crea_map_minas(char tab_min[f][c]){
	char val[11]={'X','X','X','X','X','X','X','X','X','X','O'}; // X=nomal,  O=bomba
	int temp=0, indice;
	srand (time(NULL));
	for (int i=0; i<f; i++){
		for (int j=0; j<c; j++){
			if(temp==30){ tab_min[i][j] = val[1];} //max. 30 bombas en el tablero
			else{
			    indice = 1+rand()%(11 - 1);
				tab_min[i][j] = val[indice];
			    if (indice==10){ temp += 1; }
			}
		}
	}
	for (int j=5;j<c; j++) tab_min[0][j] = val[0];
	for (int j=5;j<c; j++) tab_min[1][j] = val[0];
	for (int i=0; i<5; i++){
		for (int j=0; j<5; j++){
			tab_min[i][j] = val[1];
        }
	}
}
void mapa_visual_minas(char visual_min[f][c]){
    for(int x=0; x<f; x++){
        for(int y=0; y<c ; y++){
            visual_min[x][y] = '_';
        }
        cout << endl;
    }
}
void print_minas(char tablero[f][c]){
	system("cls");
    for(int x=0; x<f; x++){
        for(int y=0; y<c ; y++){
            cout << tablero[x][y] << " ";
        }
        cout << endl;
    }
}
void radio(int b_f, int b_c, char visual_min[f][c], char tab_min[f][c]) {
    visual_min[b_f -1][b_c] = tab_min[b_f -1][b_c];
    visual_min[b_f +1][b_c] = tab_min[b_f +1][b_c];
    visual_min[b_f][b_c -1] = tab_min[b_f][b_c -1] ;
    visual_min[b_f][b_c +1] = tab_min[b_f][b_c +1] ;
    visual_min[b_f -1][b_c -1] = tab_min[b_f - 1][b_c -1];
    visual_min[b_f -1][b_c +1] = tab_min[b_f - 1][b_c +1];
    visual_min[b_f +1][b_c -1] = tab_min[b_f +1][b_c -1];
    visual_min[b_f +1][b_c +1] = tab_min[b_f +1][b_c +1];
}
////////////////////////////////////////////////////////// tron  ///////////////////////////////////////////////////////////
int random_enemigos(int com){
    char comando_e;
    if(com == 1){ comando_e = 'w'; }
    else if(com == 2){ comando_e = 'd'; }
    else if(com == 3){ comando_e = 's'; }
    else if(com ==4){ comando_e = 'a'; }
    return comando_e;
}
int tron_M_juego(){

    cout << "TRON " << endl;
    cout<<"  Instrucciones: Sobrevive sin chocar con el resto\n";
    mapa_cl_tron mapa_tron;
    jugador_d_tron jug_1('*');
    jugador_d_tron jug_2('X');
    jugador_d_tron jug_3('X');
    bool e = true;
	bool gano;
    char comando;
    srand((unsigned int)time(NULL));
	int f1_f = rand() % (mapa_tron.num_1-3) +2;
	int f1_c = rand() % (mapa_tron.num_1-3) +2;
	int f2_f = rand() % (mapa_tron.num_1-3) +1;
	int f2_c = rand() % (mapa_tron.num_1-3) +1;
    mapa_tron.my_mapa [f1_f][f1_c]='X';
    mapa_tron.my_mapa [f2_f][f2_c]='Q';
    mapa_tron.my_mapa [1][1]= '*';
    mapa_tron.imprimir();
    char ultimo;
    int contador = 0,timer = 30;
    int com_1,com_2;
    srand((unsigned int)time(NULL));
    com_1 = rand() % 3 +1;
    com_2 = rand() % 3 +1;
    f_t=1;
    c_t=1;
    while(e){
        cin >> comando;
        char coman_1 = random_enemigos(com_1), coman_2 = random_enemigos(com_2);
		contador+=1;
	    timer-=1;
		if(contador == 4){
		    com_1 = rand() % 3 +1;
		    com_2 = rand() % 4 +1;
			contador = 0;
		}
        jug_1.movimiento(mapa_tron, comando, '*',f_t,c_t);
        jug_2.movimiento(mapa_tron, coman_1, 'X',f1_f,f1_c);
        jug_3.movimiento(mapa_tron, coman_2, 'X',f2_f,f2_c);
        mapa_tron.imprimir();
	    if(timer == 0) gano=true;
	    if(gano == false){
	      cout<<" Enemigo 1: "<<coman_1<<"\n";
	      cout<<" Enemigo 2: "<<coman_2<<"\n";
	      cout<<" Tiempo restante: "<<timer<<"\n";
	    }
	    else if(gano == true){
	      cout<<" Felicitaciones Ganaste!! \n";puntaje_tron=3;
		  e = false;
	    }
    }
    return puntaje_tron;
}

/////HANOI/////////////////////////////////////////////////////////////////////////////////////

void inicializarJuego(int a){
	void rellenarArray(int* a,int b, int c);
	tab1.reiniciarTablero(a);
	ba1.reiniciarBaston(a,1);
	ba2.reiniciarBaston(a,0);
	ba3.reiniciarBaston(a,0);
	if(a==3){
		rellenarArray(c1_1,2,4);rellenarArray(c2_1,5,4);rellenarArray(c3_1,8,4);
		rellenarArray(c4_1,0,0);rellenarArray(c5_1,0,0);rellenarArray(c1_2,2,12);
		rellenarArray(c2_2,5,12);rellenarArray(c3_2,8,12);rellenarArray(c4_2,0,0);
		rellenarArray(c5_2,0,0);rellenarArray(c1_3,2,20);rellenarArray(c2_3,5,20);
		rellenarArray(c3_3,8,20);rellenarArray(c4_3,0,0);rellenarArray(c5_3,0,0);
	}
	else if(a==5){
		rellenarArray(c1_1,3,6);rellenarArray(c2_1,6,6);rellenarArray(c3_1,9,6);
		rellenarArray(c4_1,12,6);rellenarArray(c5_1,15,6);rellenarArray(c1_2,3,18);
		rellenarArray(c2_2,6,18);rellenarArray(c3_2,9,18);rellenarArray(c4_2,12,18);
		rellenarArray(c5_2,15,18);rellenarArray(c1_3,3,30);rellenarArray(c2_3,6,30);
		rellenarArray(c3_3,9,30);rellenarArray(c4_3,12,30);rellenarArray(c5_3,15,30);
	}
}
bool verificarGameOver(){
	if(ba2.array[0]==1||ba3.array[0]==1){
		return true;
	}
	else{
		return false;
	}

}
void rellenarArray(int* a,int b, int c){
	a[0]=b;a[1]=c;
}
bool cambiarBloques(int a, int b, int x){
	switch (a){
		case 1:
			if(ba1.array[x-1]==0){
				cout<<"Ese bastón está vació!\n";
				return false;
			}
			else if(ba1.array[0]==1){
				cout<<"Se moverá el bloque 1 del bastón 1 al bastón "<<b<<endl;
				if(b==2){
					ba2.array[x-1]=ba1.array[0];
					ba1.array[0]=0;return true;
				}else if(b==3){
					ba3.array[x-1]=ba1.array[0];
					ba1.array[0]=0;return true;
				}else{
					return false;
				}
			}
			else{
				for(int k=(x-1);k>-1;k--){
					if(ba1.array[k]==0){
						int temp=k+1;
						cout<<"Se moverá el bloque "<<ba1.array[k+1]<<" del bastón 1 al bastón "<<b<<endl;
						k=-1;

							if(b==2){
								for(int k=x-1;k>-1;k--){
									if ((ba2.array[k]==0 && ba2.array[k+1]!=0)||(ba2.array[k]==0 && k==x-1)){
										if(ba2.array[k+1]<ba1.array[temp]&&k!=x-1){
											cout<<"Movimiento no permitido!\n";
											return false;
											k=-1;
										}else{
											ba2.array[k]=ba1.array[temp];
											ba1.array[temp]=0;
											k=-1;
											return true;
										}

									}
								}
							}else if(b==3){
								for(int k=x-1;k>-1;k--){
									if ((ba3.array[k]==0 && ba3.array[k+1]!=0)||(ba3.array[k]==0 && k==x-1)){
										if(ba3.array[k+1]<ba1.array[temp] && k!=x-1){
											cout<<"Movimiento no perminitdo!\n";
											return false;
											k=-1;
										}else{
											ba3.array[k]=ba1.array[temp];
											ba1.array[temp]=0;
											k=-1;
											return true;
										}

									}
								}

							}else{
								return false;
							}

					}
				}
			}break;
		case 2:
			if(ba2.array[x-1]==0){
				cout<<"Ese bastón está vació!\n";
				return false;
			}
			else if(ba2.array[0]==1){
				cout<<"Se moverá el bloque 1 del bastón 2 al bastón "<<b<<endl;
				if(b==1){
					ba1.array[x-1]=ba2.array[0];
					ba2.array[0]=0;return true;
				}else if(b==3){
					ba3.array[x-1]=ba2.array[0];
					ba2.array[0]=0;return true;
				}else{
					return false;
				}
			}
			else{
				for(int k=(x-1);k>-1;k--){
					if(ba2.array[k]==0){
						int temp=k+1;
						cout<<"Se moverá el bloque "<<ba2.array[k+1]<<" del bastón 2 al bastón "<<b<<endl;
						k=-1;

				if(b==1){
					for(int k=x-1;k>-1;k--){
						if ((ba1.array[k]==0 && ba1.array[k+1]!=0)||(ba1.array[k]==0 && k==x-1)){
							if(ba1.array[k+1]<ba2.array[temp]&&k!=x-1){
								cout<<"Movimiento no permitido!\n";
								return false;
								k=-1;
							}else{
								ba1.array[k]=ba2.array[temp];
								ba2.array[temp]=0;
								k=-1;
								return true;
							}
						}
					}
				}else if(b==3){
					for(int k=x-1;k>-1;k--){
						if ((ba3.array[k]==0 && ba3.array[k+1]!=0)||(ba3.array[k]==0 && k==x-1)){
							if(ba3.array[k+1]<ba2.array[temp]&&k!=x-1){
								cout<<"Movimeinto no permitido!\n";
								return false;
								k=-1;
							}else{
								ba3.array[k]=ba2.array[temp];
								ba2.array[temp]=0;
								k=-1;
								return true;
							}

						}
					}

				}else{
					return false;
				}
			}}
			}break;
		case 3:
			if(ba3.array[x-1]==0){
				cout<<"Ese bastón está vació!\n";
				return false;
			}
			else if(ba3.array[0]==1){
				cout<<"Se moverá el bloque 1 del bastón 3 al bastón "<<b<<endl;
				if(b==1){
					ba1.array[x-1]=ba3.array[0];
					ba3.array[0]=0;return true;
				}else if(b==2){
					ba1.array[x-1]=ba3.array[0];
					ba3.array[0]=0;return true;
				}
			}
			else{
				for(int k=(x-1);k>-1;k--){
					if(ba3.array[k]==0){
						int temp=k+1;
						cout<<"Se moverá el bloque "<<ba3.array[k+1]<<" del bastón 3 al bastón "<<b<<endl;
						k=-1;

				if(b==1){
					for(int k=x-1;k>-1;k--){
						if ((ba1.array[k]==0 && ba1.array[k+1]!=0)||(ba1.array[k]==0 && k==x-1)){
							if(ba1.array[k+1]<ba3.array[temp]&&k!=x-1){
								cout<<"Movimiento no válido!\n";
								return false;
								k=-1;
							}else{
								ba1.array[k]=ba3.array[temp];
								ba3.array[temp]=0;
								k=-1;
								return true;
							}

						}
					}
				}else if(b==2){
					for(int k=x-1;k>-1;k--){
						if ((ba2.array[k]==0 && ba2.array[k+1]!=0)||(ba2.array[k]==0 && k==x-1)){
							if(ba2.array[k+1]<ba3.array[temp]&&k!=x-1){
								cout<<"Movimiento no válido!\n";
								return false;
								k=-1;
							}else{
								ba2.array[k]=ba3.array[temp];
								ba3.array[temp]=0;
								k=-1;
								return true;
							}

						}
					}

				}else{
					return false;
				}
			}}
			}break;
		default:
			return false;
	}
}
void dibujarBloques(int a){
		tab1.dibujarTablero();
			//Primer bastón.
			for(int i=0;i<a;i++){
				switch(ba1.array[i]){
					case 0:break;
					case 1:
						switch(i){
							case 0:blo1.formarBloque(c1_1[0],c1_1[1]);break; case 1:blo1.formarBloque(c2_1[0],c2_1[1]);break;
							case 2:blo1.formarBloque(c3_1[0],c3_1[1]);break; case 3:blo1.formarBloque(c4_1[0],c4_1[1]);break;
							case 4:blo1.formarBloque(c5_1[0],c5_1[1]);break;
						}break;
					case 2:
						switch(i){
							case 0:blo2.formarBloque(c1_1[0],c1_1[1]);break; case 1:blo2.formarBloque(c2_1[0],c2_1[1]);break;
							case 2:blo2.formarBloque(c3_1[0],c3_1[1]);break; case 3:blo2.formarBloque(c4_1[0],c4_1[1]);break;
							case 4:blo2.formarBloque(c5_1[0],c5_1[1]);break;
						}break;
					case 3:
						switch(i){
							case 0:blo3.formarBloque(c1_1[0],c1_1[1]);break; case 1:blo3.formarBloque(c2_1[0],c2_1[1]);break;
							case 2:blo3.formarBloque(c3_1[0],c3_1[1]);break; case 3:blo3.formarBloque(c4_1[0],c4_1[1]);break;
							case 4:blo3.formarBloque(c5_1[0],c5_1[1]);break;
						}break;
					case 4:
						switch(i){
							case 0:blo4.formarBloque(c1_1[0],c1_1[1]);break; case 1:blo4.formarBloque(c2_1[0],c2_1[1]);break;
							case 2:blo4.formarBloque(c3_1[0],c3_1[1]);break; case 3:blo4.formarBloque(c4_1[0],c4_1[1]);break;
							case 4:blo4.formarBloque(c5_1[0],c5_1[1]);break;
						}break;
					case 5:
						switch(i){
							case 0:blo5.formarBloque(c1_1[0],c1_1[1]);break; case 1:blo5.formarBloque(c2_1[0],c2_1[1]);break;
							case 2:blo5.formarBloque(c3_1[0],c3_1[1]);break; case 3:blo5.formarBloque(c4_1[0],c4_1[1]);break;
							case 4:blo5.formarBloque(c5_1[0],c5_1[1]);break;
						}break;
				}
			}
			//Segundo bastón.
			for(int i=0;i<a;i++){
				switch(ba2.array[i]){
					case 0:break;
					case 1:
						switch(i){
							case 0:blo1.formarBloque(c1_2[0],c1_2[1]);break; case 1:blo1.formarBloque(c2_2[0],c2_2[1]);break;
							case 2:blo1.formarBloque(c3_2[0],c3_2[1]);break; case 3:blo1.formarBloque(c4_2[0],c4_2[1]);break;
							case 4:blo1.formarBloque(c5_2[0],c5_2[1]);break;
						}break;
					case 2:
						switch(i){
							case 0:blo2.formarBloque(c1_2[0],c1_2[1]);break; case 1:blo2.formarBloque(c2_2[0],c2_2[1]);break;
							case 2:blo2.formarBloque(c3_2[0],c3_2[1]);break; case 3:blo2.formarBloque(c4_2[0],c4_2[1]);break;
							case 4:blo2.formarBloque(c5_2[0],c5_2[1]);break;
						}break;
					case 3:
						switch(i){
							case 0:blo3.formarBloque(c1_2[0],c1_2[1]);break; case 1:blo3.formarBloque(c2_2[0],c2_2[1]);break;
							case 2:blo3.formarBloque(c3_2[0],c3_2[1]);break; case 3:blo3.formarBloque(c4_2[0],c4_2[1]);break;
							case 4:blo3.formarBloque(c5_2[0],c5_2[1]);break;
						}break;
					case 4:
						switch(i){
							case 0:blo4.formarBloque(c1_2[0],c1_2[1]);break; case 1:blo4.formarBloque(c2_2[0],c2_2[1]);break;
							case 2:blo4.formarBloque(c3_2[0],c3_2[1]);break; case 3:blo4.formarBloque(c4_2[0],c4_2[1]);break;
							case 4:blo4.formarBloque(c5_2[0],c5_2[1]);break;
						}break;
					case 5:
						switch(i){
							case 0:blo5.formarBloque(c1_2[0],c1_2[1]);break; case 1:blo5.formarBloque(c2_2[0],c2_2[1]);break;
							case 2:blo5.formarBloque(c3_2[0],c3_2[1]);break; case 3:blo5.formarBloque(c4_2[0],c4_2[1]);break;
							case 4:blo5.formarBloque(c5_2[0],c5_2[1]);break;
						}break;
				}
			}
			//Tercer Bastón.
			for(int i=0;i<a;i++){
				switch(ba3.array[i]){
					case 0:break;
					case 1:
						switch(i){
							case 0:blo1.formarBloque(c1_3[0],c1_3[1]);break; case 1:blo1.formarBloque(c2_3[0],c2_3[1]);break;
							case 2:blo1.formarBloque(c3_3[0],c3_3[1]);break; case 3:blo1.formarBloque(c4_3[0],c4_3[1]);break;
							case 4:blo1.formarBloque(c5_3[0],c5_3[1]);break;
						}break;
					case 2:
						switch(i){
							case 0:blo2.formarBloque(c1_3[0],c1_3[1]);break; case 1:blo2.formarBloque(c2_3[0],c2_3[1]);break;
							case 2:blo2.formarBloque(c3_3[0],c3_3[1]);break; case 3:blo2.formarBloque(c4_3[0],c4_3[1]);break;
							case 4:blo2.formarBloque(c5_3[0],c5_3[1]);break;
						}break;
					case 3:
						switch(i){
							case 0:blo3.formarBloque(c1_3[0],c1_3[1]);break; case 1:blo3.formarBloque(c2_3[0],c2_3[1]);break;
							case 2:blo3.formarBloque(c3_3[0],c3_3[1]);break; case 3:blo3.formarBloque(c4_3[0],c4_3[1]);break;
							case 4:blo3.formarBloque(c5_3[0],c5_3[1]);break;
						}break;
					case 4:
						switch(i){
							case 0:blo4.formarBloque(c1_3[0],c1_3[1]);break; case 1:blo4.formarBloque(c2_3[0],c2_3[1]);break;
							case 2:blo4.formarBloque(c3_3[0],c3_3[1]);break; case 3:blo4.formarBloque(c4_3[0],c4_3[1]);break;
							case 4:blo4.formarBloque(c5_3[0],c5_3[1]);break;
						}break;
					case 5:
						switch(i){
							case 0:blo5.formarBloque(c1_3[0],c1_3[1]);break; case 1:blo5.formarBloque(c2_3[0],c2_3[1]);break;
							case 2:blo5.formarBloque(c3_3[0],c3_3[1]);break; case 3:blo5.formarBloque(c4_3[0],c4_3[1]);break;
							case 4:blo5.formarBloque(c5_3[0],c5_3[1]);break;
						}break;
				}
			}
	}

int minijuego_hanoi(){
setlocale(LC_CTYPE, "Spanish");
	void dibujarBloques(int a);
	bool cambiarBloques(int a, int b, int x);
	bool gameOver=false;
	void rellenarArray(int* a,int b, int c);
	void inicializarJuego(int a);
	bool verificarGameOver();
	//------------------------
	srand((unsigned int)time(NULL));
	int turnos;
	int decision=rand()%2;
	if(decision==0){
		decision=3;
		turnos=7;}
	else{decision=5;
		turnos=31;}
	
	int v1=0,v2=0,contador=0;
	bool turno, turnoValido=false;
	//------------------------
	inicializarJuego(decision);
	dibujarBloques(decision);
	cout<<"Torres de Hanoi\n";
	cout<<"  Instrucciones: Mueva todos los bloques a la otra torre en "<<turnos<<" movimientos\n";
	tab1.imprimirTablero();
	//------------------------
	while(gameOver==false){
		cout<<"ingrese el número del que quiere sacar una pieza y el número donde quiere introducirla(escriba 0 para rendirse)\n";
		cin>>v1;
		
		while (cin.fail()){
        cin.clear(); // Quitar el valor no válido.
        cin.ignore(INT_MAX, '\n'); // Quitar el valor no válido.
        cout << "Solo puedes ingresar números\n";
        cout << "ingrese el número del que quiere sacar una pieza (escriba 0 para rendirse)\n";
        cin >> v1;
    	}
		cout<<endl;
		
		if (v1==0){
			gameOver=true;
			cout<<"El jugador se rindió\n";
			return 1;
		}
		cout << "ingrese el número donde quiere introducir la pieza\n";
		cin>>v2;
		
		while (cin.fail()){
        cin.clear(); // Quitar el valor no válido.
        cin.ignore(INT_MAX, '\n'); // Quitar el valor no válido.
        cout << "Solo puedes ingresar números\n";
        cout << "ingrese el número donde quiere introducir la pieza\n";
        cin >> v2;
    	}
		
		turno=cambiarBloques(v1,v2,decision);
		dibujarBloques(decision);
		tab1.imprimirTablero();
		if(turno ==true)contador++;
		cout<<"Movimientos: "<<contador<<endl;
		
		if(verificarGameOver() == true){
			cout<<"Lo completaste en "<<contador<<" turnos\n";
			if (contador>turnos + (decision-1) ){
				cout<<"Demasiados turnos!\n";
				return 1;
			}else if(contador==turnos){
				cout<<"Perfecto!\n";
				return 3;
			}else{
				cout<<"Bien!\n";
				return 2;
			}
			gameOver=true;
		}
		
		

	}}
