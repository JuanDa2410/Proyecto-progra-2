#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <ctime>
#include <cctype>

using namespace std;

bool estadoSesion, admin;
int poscl = 0, regus = 0, usuarioActual, reg = 0,  posht = 0;

void dibujar(){
	cout<< "\t*******************************************************\n";
  cout<<  "\t*                                                     *\n"  ;
  cout<<  "\t*                                                     *\n"  ;
  cout<<  "\t*                      TRIVAGO                        *\n"  ;
  cout<<  "\t*                                                     *\n"  ;
  cout<<  "\t*                                                     *\n"  ;
  cout<<  "\t*                                                     *\n"  ;
  cout<<  "\t*******************************************************\n"  ;
  cout<<endl;
}

struct stru_cliente{
	char nombre[40];
	char contrasena[20];
	int codigo;
	int hotelReserva[10];
	int nReserva;
	int noches[10];


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


void historial(){
	string line;
	ifstream archivo;
	archivo.open("proyecto.txt" , ios::in);
	while ( getline (archivo,line) )
	    {
	      cout << line << endl;
	    }
	    archivo.close();

}

bool validarHotel(int codigo, int reg){
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
	if (validarHotel(codigo, reg)) {

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

	system("CLS"); string nombre, hotel; int edad, sitio, noches; int op, i = 0; bool es = 0; char p;
	char *fecha;
	time_t tAct = time(NULL);
	fecha=asctime(localtime(&tAct));

	ofstream archivo,archivo1;
	archivo.open("proyecto.txt",ios::app);
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

			cout<<"Cantidad de noches: "; cin>>noches;
			cout<<"Confirmar reserva? (s/n): "; cin>>p;
			if (p == 's') {
				cout<<"Reserva a nombre de "<< Z[usuarioActual].cliente[usuarioActual].nombre<< " confirmada";
				cout<<endl;
				Z[usuarioActual].cliente[usuarioActual].noches[Z[usuarioActual].cliente[usuarioActual].nReserva] = noches;
				//
				nombre = Z[usuarioActual].cliente[usuarioActual].nombre;
				archivo1.open(nombre.c_str(),ios::app);
				hotel = Z[sitio].hotel[sitio].nombre;
				archivo<<"NOMBRE: "<<nombre<<" |HOTEL: "<<hotel<<" |FECHA DE RESERVACION: "<<fecha<<endl;
				archivo.close();
				archivo1<<"|HOTEL: "<<hotel<<"|NOCHES: "<<noches<<" |FECHA DE RESERVACION: "<<fecha<<endl;
				archivo.close();
				//
				Z[usuarioActual].cliente[usuarioActual].hotelReserva[Z[usuarioActual].cliente[usuarioActual].nReserva] = op;
				Z[usuarioActual].cliente[usuarioActual].nReserva += 1;

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

void reservasUsuario(){
	string line,nombre;
	ifstream archivo;
	nombre=Z[usuarioActual].cliente[usuarioActual].nombre;
	archivo.open(nombre.c_str(), ios::in);
	while ( getline (archivo,line) )
	    {
	      cout << line << endl;
	    }
	    archivo.close();
}

void registro(){
	char nombre[40], contrasena[20]; int edad;
	ofstream archivo;
	ofstream archivo1;
	Reintentar:
	cout<<"\t REGISTRO"<<endl;
	cout<<"Tu nombre: "; cin>>nombre;
	cout<<"Contrasena: "; cin>>contrasena;
	if (regus != 0) {
		for (int i = 0; i < regus; i++) {
			if (strcmp(nombre, Z[i].cliente[i].nombre) == 0) {
				cout<<"Ya existe un usuario con ese nombre, intente nuevamente"<<endl;
				system("PAUSE");
				system("cls");
				goto Reintentar;
			}
			else{
			    strcpy(Z[poscl].cliente[poscl].nombre, nombre);
				strcpy(Z[poscl].cliente[poscl].contrasena, contrasena );
				archivo.open("usuarios.txt",ios::app);
	            archivo1.open("pass.txt",ios::app);
				archivo<<nombre<<endl;
				archivo1<<contrasena<<endl;
				Z[poscl].cliente[poscl].codigo += 1;
				poscl++;
				regus++;
				break;
			}
		}
	}
	else{
		strcpy(Z[poscl].cliente[poscl].nombre, nombre);
	    strcpy(Z[poscl].cliente[poscl].contrasena, contrasena );
		archivo.open("usuarios.txt",ios::app);
	    archivo1.open("pass.txt",ios::app);
		archivo<<nombre<<endl;
        archivo1<<contrasena<<endl;
		Z[poscl].cliente[poscl].codigo += 1;
		poscl++;
		regus++;
	}


}

void login(){
	char nombre[40], contrasena[20];
	cout<<"\t LOGIN"<<endl;
	cout<<endl;
	if (regus != 0) {
		cout<<"Nombre: "; cin>>nombre;
		cout<<"Contrasena: "; cin>>contrasena;
		for (int i = 0; i <= regus; i++) {
			if (strcmp(nombre, Z[i].cliente[i].nombre) == 0 && strcmp(contrasena,Z[i].cliente[i].contrasena) == 0) {
				usuarioActual = i; estadoSesion = 1;
				break;

			}
			else if(i == regus){
				cout<<"El nombre de usuario no existe o contrasena incorrecta"<<endl;
				system("Pause");
			}
		}

	}
	else{
		cout<<"No hay usuarios registrados"<<endl;
		system("Pause");
	}

}

void menuAdmin(){
 
	int op;
	do{
		dibujar();
		cout<<"\t MENU PRINCIPAL"<<"\t \t USUARIO: Admin "<<endl<<endl;;
		cout<<"1- Registrar un hotel"<<endl;
		cout<<"2- Ver hoteles"<<endl;
		cout<<"3- Historial de reservas"<<endl;
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
				historial();
				break;
			}

			case 8:{
				estadoSesion = 0; admin = 0;
				cout<<"Se ha cerrado sesión"<<endl;
			}
		}
		cout<<endl<<endl;
		system("PAUSE");

		system("cls");
	}while(estadoSesion);


}

void menuCliente(){
	int op;
	do{
		dibujar();
		cout<<"\t MENU PRINCIPAL"<<"\t \t USUARIO: "<<Z[usuarioActual].cliente[usuarioActual].nombre<<endl<<endl;;
		cout<<"1- Ver hoteles"<<endl;
		cout<<"2- Reservar"<<endl;
		cout<<"3- Tus reservas"<<endl;
		cout<<"8- Cerrar Sesion"<<endl;
		cout<<" Escoja una opcion: "; cin>>op;
		switch(op){

			case 1:{
				mostrarHoteles( reg);
				break;
			}

			case 2:{
				reserva( reg, poscl);
				break;
			}

			case 3:{
                system("cls"); 
				reservasUsuario();
				break;
			}
			case 8:{
				estadoSesion = 0;
				cout<<"Se ha cerrado sesión"<<endl;
			}
		}
		cout<<endl<<endl;
		system("PAUSE");

		system("cls");
	}while(estadoSesion);


}
bool lleno = 0;

void llenar(){
   string line, line1;
   ifstream archivo;
   ifstream archivo1;
   archivo.open("usuarios.txt" , ios::in);
   archivo1.open("pass.txt", ios::in);
    	while ( getline (archivo,line) )
	    {
            getline(archivo1,line1);
              
            strcpy(Z[poscl].cliente[poscl].nombre, line.c_str());
			strcpy(Z[poscl].cliente[poscl].contrasena, line1.c_str());
			poscl++;
			regus++;
	    }
	    archivo.close();
}


int main(){
    if(!lleno){
        llenar();
        lleno=1;
    }
	int o;
	Inicio:
	dibujar();
	cout<<"\t 1- Iniciar Sesion"<<endl;
	cout<<"\t 2- Registro"<<endl;
	cout<<"\t Que deseas hacer: ";cin>>o;
	if (o == 1) {
		system("cls");
		dibujar();
		login();

	}
	else if(o == 2){
		registro();
		system("cls");
		dibujar();
		login();
	}
	else if(o == 456){
         admin = 1; estadoSesion = 1;
    }
	else if (o >= 3 || o <= 0) {
		cout<<"Opcion no valida, intente de nuevo"<<endl;
		system("PAUSE");
		system("cls");
		goto Inicio;
	}
	system("cls");
	if (estadoSesion && admin) {
		cout<<"Hola admin"<<endl; Sleep(2000);
		system("cls");
		menuAdmin();
	}
	else if(estadoSesion){
        cout<<"Bienvenido "<<Z[usuarioActual].cliente[usuarioActual].nombre<<endl; Sleep(2000);
		system("cls");
		menuCliente();
    }
	return main();
}
