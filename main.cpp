#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <string>
using namespace std;

bool estadoSesion;
int poscl = 0, regus = 0, usuarioActual;

struct stru_cliente{
	char nombre[40];
	int edad;
	int codigo;
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

stru_factura Z[100];

bool validarHotel(int codigo, int reg, stru_factura Z[100]){
	if(reg != 0){
		for (int i = 0; i < reg; i++) {
			if (Z[i].hotel[i].codigo == codigo) {
				return 0;
			}
			else{
				return 1;
			}
		}
	}
	else{
		return 1;
	}
}

void registrarHotel( int &reg, int &posht){
	int n, codigo;
	cout<<"\t REGISTRAR HOTELES "<<endl;
	cout<<"Codigo del hotel: "; cin>>codigo;
	if (validarHotel(codigo, reg, Z)) {

		cout<<"Nombre del hotel: "; cin>>Z[posht].hotel[posht].nombre;
		Z[posht].hotel[posht].codigo = codigo;
		cout<<"Vacantes: "; cin>>Z[posht].hotel[posht].vacantes;

		if (Z[posht].hotel[posht].vacantes > 0) {
			Z[posht].hotel[posht].cupo = 1;
		}
		posht++; reg++;
	}
	else{
		cout<<"Ya existe un hotel con ese codigo"<<endl;
	}

}

bool verCupo(int reg){
	if(reg != 0){
		for (int i = 0; i < reg; i++) {
			if (Z[i].hotel[i].cupo) {
				return 1;
			}
			else{
				return 0;
			}
		}
	}
	else{
		return 0;
	}
}

void mostrarHoteles( int &reg){
  system("CLS");
	if (verCupo(reg)) {
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
	else{
		cout<<endl<< "NO HAY HOTELES DISPONIBLES EN ESTE MOMENTO"<<endl;
	}
}

int reserva( int &reg, int &poscl){

	system("CLS"); string nombre; int edad, sitio; int op, i = 0; bool es = 0; char p;
	CodigoHotel:
	if (verCupo(reg)) {
		mostrarHoteles(reg);
		cout<<endl;
		cout<<"\t MENU DE RESERVA"<<endl;
		cout<<"Digite el codigo del hotel que desea reservar: "; cin>>op;
		for ( i = 0; i < reg; i++) {
			if (op == Z[i].hotel[i].codigo) {
				es = 1;
				sitio = i;
				break;
			}
		}

		if (es) {


			cout<<"Confirmar reserva? (s/n): "; cin>>p;
			if (p == 's') {
				cout<<"Reserva a nombre de "<< Z[usuarioActual].cliente[usuarioActual].nombre<< " confirmada";
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
	else{
		cout<<endl<< "NO HAY HOTELES DISPONIBLES EN ESTE MOMENTO"<<endl;
	}


}


void registro(){
	char nombre[40]; int edad;
	Reintentar:
	cout<<"\t REGISTRO"<<endl;
	cout<<"Tu nombre: "; cin>>nombre;
	cout<<"Tu edad: "; cin>>edad;
	if (regus != 0) {
		for (int i = 0; i < regus; i++) {
			if (strcmp(nombre, Z[i].cliente[i].nombre) == 0) {
				cout<<"Ya existe un usuario con ese nombre, intente nuevamente"<<endl;
				system("PAUSE");
				system("cls");
				goto Reintentar;
			}
			else{
			  strcpy(	Z[poscl].cliente[poscl].nombre, nombre);
				Z[poscl].cliente[poscl].edad = edad ;
				Z[poscl].cliente[poscl].codigo += 1;
				poscl++;
				regus++;
				break;
			}
		}
	}
	else{
		strcpy(	Z[poscl].cliente[poscl].nombre, nombre);
		Z[poscl].cliente[poscl].edad = edad ;
		Z[poscl].cliente[poscl].codigo += 1;
		poscl++;
		regus++;
	}


}

void login(){
	char nombre[40];
	cout<<"\t LOGIN"<<endl;
	if (regus != 0) {
		cout<<"Tu nombre: "; cin>>nombre;
		for (int i = 0; i <= regus; i++) {
			if (strcmp(nombre, Z[i].cliente[i].nombre) == 0) {
				usuarioActual = i; estadoSesion = 1;
				break;

			}
			else if(i == regus){
				cout<<"El nombre de usuario no existe"<<endl;
			}
		}

	}
	else{
		cout<<"No hay usuarios registrados"<<endl;
	}
	system("Pause");
}

void menu( int poscl){
	int i = 0, op, reg = 0, posht = 0;
	do{
		cout<<"\t MENU PRINCIPAL"<<"\t USUARIO: "<<Z[usuarioActual].cliente[usuarioActual].nombre<<endl<<endl;;
		cout<<"1- Registrar un hotel"<<endl;
		cout<<"2- Ver hoteles"<<endl;
		cout<<"3- Reservar"<<endl;
		cout<<"8- Cerrar Sesion"<<endl;
		cout<<" Escoja una opcion: "; cin>>op;
		switch(op){
			case 1:{
				registrarHotel( reg, posht);
				break;
			}

			case 2:{
				mostrarHoteles( reg);
				break;
			}

			case 3:{
				reserva( reg, poscl);
				break;
			}
			case 8:{
				estadoSesion = 0;
			}
		}
		cout<<endl<<endl;
		system("PAUSE");

		system("cls");
	}while(estadoSesion);


}


int main(){
	int o;
	Inicio:
	cout<<"1- Iniciar Sesion"<<endl;
	cout<<"2- Registro"<<endl;
	cout<<"Que deseas hacer: ";cin>>o;
	if (o == 1) {
		login();
	}
	else if(o == 2){
		registro();
		system("cls");
		login();
	}
	else if (o >= 3 || o <= 0) {
		cout<<"Opcion no valida, intente de nuevo"<<endl;
		system("PAUSE");
		system("cls");
		goto Inicio;
	}
	system("cls");
	if (estadoSesion) {
		menu( poscl);
	}
	return main();
}
