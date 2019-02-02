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

void registrarHotel(stru_factura Z[100], int &reg, int &posht){
	int n;
	cout<<"\t REGISTRAR HOTELES "<<endl;
	cout<<"Cuantos hoteles: "; cin>>n;
	reg += n;
	cout<<reg<<endl;
	for (int i = 0 ; i < n; i++, posht++) {
		cout<<"Nombre del hotel: "; cin>>Z[posht].hotel[posht].nombre;
		cout<<"Codigo del hotel: "; cin>>Z[posht].hotel[posht].codigo;
		cout<<"Vacantes: "; cin>>Z[posht].hotel[posht].vacantes;
		if (Z[posht].hotel[posht].vacantes > 0) {
			Z[posht].hotel[posht].cupo = 1;
		}


	}



}

void mostrarHoteles(stru_factura Z[100], int &reg){
  system("CLS");
	cout<<"\t HOTELES CON CUPO DISPONIBLE: "<<endl;
	for (int i = 0 ; i < reg; i++) {
		cout<<endl;
		if (Z[i].hotel[i].cupo) {
			cout<<"Nombre del hotel: "<<Z[i].hotel[i].nombre<<endl;
			cout<<"Codigo del hotel: "<<Z[i].hotel[i].codigo<<endl;
			cout<<"Vacantes: "<<Z[i].hotel[i].vacantes<<endl;
		}
	}
}

int reserva(stru_factura Z[100], int &reg, int &poscl){
	system("CLS"); string nombre; int edad, sitio; int op, i = 0; bool es = 0; char p;
	CodigoHotel:

	cout<<"\t MENU DE RESERVA"<<endl;
	cout<<"Digite el codigo del hotel que desea reservar: "; cin>>op;
	for ( i = 0; i < reg; i++) {
		if (op == Z[i].hotel[i].codigo) {
			es = 1;
			sitio = i;
		}
	}

	if (es) {

		cout<<"Nombre de la persona que reserva: "; cin>>nombre;

		cout<<"Edad: "; cin>>edad;

		cout<<"Confirmar reserva? (s/n): "; cin>>p;
		if (p == 's') {
			Z[i].cliente[poscl].nombre = nombre;
			Z[i].cliente[poscl].edad = edad;
			cout<<"Reserva a nombre de "<< Z[i].cliente[poscl].nombre<< " confirmada"; poscl++;
			Z[sitio].hotel[sitio].vacantes--;
			if (Z[sitio].hotel[sitio].vacantes == 0) {
				Z[sitio].hotel[sitio].cupo = 0;
			}

		}
		else{
			cout<<"Reserva cancelada";

		}
	}
	else{
		int x;
		cout<<endl;
		cout<<"No hay un hotel registrado con ese codigo, 1 para intentar nuevamente o 0 para volver al menu: "; cin>>x;
		if(x == 1){
			system("cls");
			goto CodigoHotel;
		}
		else{
			return 0;
		}


	}


}

void menu(){
	int i = 0, op, reg = 0,poscl = 0, posht = 0; stru_factura Z[100];
	do{
		cout<<"\t MENU PRINCIPAL"<<endl<<endl;;
		cout<<"1- Registrar un hotel"<<endl;
		cout<<"2- Ver hoteles"<<endl;
		cout<<"3- Reservar"<<endl;
		cout<<"8- Salir"<<endl;
		cout<<" Escoja una opcion: "; cin>>op;
		switch(op){
			case 1:{
				registrarHotel(Z, reg, posht);
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
