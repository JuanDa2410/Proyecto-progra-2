#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <string>
using namespace std;

struct stru_cliente{
	string nombre;
	int edad;
};

struct stru_hoteles{
	int codigo;
	char nombre[20];
	int vacantes;
	bool cupo;
};

struct stru_factura{
	int nose;
	stru_hoteles hotel[100];
	stru_cliente cliente[100];
};

void registrarHotel(stru_factura Z[100], int &reg){
	cout<<"Cuantos hoteles: "; cin>>reg;
	for (int i = 0 ; i < reg; i++) {
		cout<<"Nombre del hotel: "; cin>>Z[i].hotel[i].nombre;
		cout<<"Codigo del hotel: "; cin>>Z[i].hotel[i].codigo;
	}



}

void mostrarHoteles(stru_factura Z[100], int &reg){
  system("CLS");
	cout<<"\t HOTELES CON CUPO DISPONIBLE: "<<endl;
	for (int i = 0 ; i < reg; i++) {
		cout<<endl;
		cout<<"Nombre del hotel: "<<Z[i].hotel[i].nombre<<endl;
		cout<<"Codigo del hotel: "<<Z[i].hotel[i].codigo<<endl;;
	}
}

void reserva(stru_factura Z[100], int &reg, int &poscl){
	system("CLS"); string nombre; int edad;
	cout<<"\t MENU DE RESERVA"<<endl;
	int op, i = 0; bool es = 0; char p;
	cout<<"Digite el codigo del hotel que desea reservar: "; cin>>op;
	for ( i = 0; i < reg; i++) {
		if (op == Z[i].hotel[i].codigo) {
			es = 1;
		}
	}

	if (es) {

		cout<<"Nombre de la persona que reserva: "; cin>>nombre;

		cout<<"Edad: "; cin>>edad;
	}

	cout<<"Confirmar reserva? (s/n): "; cin>>p;
	if (p == 's') {
		Z[i].cliente[poscl].nombre = nombre;
		Z[i].cliente[poscl].edad = edad;
		cout<<"Reserva a nombre de "<< Z[i].cliente[poscl].nombre<< " confirmada";
	}
	else{
		cout<<"Reserva cancelada";
	}
}

void menu(){
	int i = 0, op, reg = 0,poscl = 0; stru_factura Z[100];
	do{
		cout<<"\t MENU PRINCIPAL"<<endl<<endl;;
		cout<<"1- Registrar un hotel"<<endl;
		cout<<"2- Ver hoteles"<<endl;
		cout<<"3- Reservar"<<endl;
		cout<<"8- Salir"<<endl;
		cout<<" Escoja una opcion: "; cin>>op;
		switch(op){
			case 1:{
				registrarHotel(Z, reg);
				break;
			}

			case 2:{
				mostrarHoteles(Z, reg);
				break;
			}

			case 3:{
				reserva(Z, reg, poscl);
				break;
			}
		}
		cout<<endl<<endl;
		system("PAUSE");

		system("cls");
	}while(op != 8);


}

int main(){

	menu();

}
