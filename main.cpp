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

#define ENTER 13

bool estadoSesion, admin;
int poscl = 0, regus = 0, usuarioActual, reg = 0,  posht = 0, posvac = 0;

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
	int habitacion[10];
	int nReserva;



};

struct stru_hoteles{
	int codigo;
	char nombre[20];
	int cantidadVacantes;
	int vacantes[20];
	bool cupo;
	char ciudad[20];
	int estrellas;
};

struct stru_factura{
	int nose;
	stru_hoteles hotel[100];
	stru_cliente cliente[100];
};

stru_factura Z[100];



void historial(){
	int cont=0;
	string line;
	ifstream archivo;
	archivo.open("historial.txt" , ios::in);
	while ( getline (archivo,line) )
	    {
	      cout << line << endl;
	    }
	    if(cont<1){
		cout<<"\t NO HAY RESERVAS AUN "<<endl;
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
	ofstream cod, nom, ciu, hab, cup,est;
	int n, codigo;

	cod.open("codigo_h.txt",ios::app);
	nom.open("nombre_h.txt",ios::app);
	ciu.open("ciudad_h.txt",ios::app);
	hab.open("habitaciones_h.txt",ios::app);
	cup.open("cupos_h.txt",ios::app);
	est.open("estrellas_h.txt",ios::app);

	cout<<"\t REGISTRAR HOTELES "<<endl;
	cout<<"Codigo del hotel: "; cin>>codigo;
	if (validarHotel(codigo, reg)) {

		cout<<"Nombre del hotel: "; cin>>Z[posht].hotel[posht].nombre;
		nom<<Z[posht].hotel[posht].nombre<<endl;
		Z[posht].hotel[posht].codigo = codigo;
		cod<<codigo<<endl;
		cout<<"Ciudad: "; cin>>Z[posht].hotel[posht].ciudad;
		ciu<<Z[posht].hotel[posht].ciudad<<endl;
		cout<<"Habitaciones: "; cin>>Z[posht].hotel[posht].cantidadVacantes;
		hab<<Z[posht].hotel[posht].cantidadVacantes<<endl;
		for(int i = 1; i <= Z[posht].hotel[posht].cantidadVacantes; i++){
					cout<<"Cupos de la habitacion "<< i <<": "; cin>> Z[posht].hotel[posht].vacantes[i];
					cup<<Z[posht].hotel[posht].vacantes[i]<<endl;
		}
    cout<<"Estrellas: "; cin>>Z[posht].hotel[posht].estrellas;
		est<<Z[posht].hotel[posht].estrellas<<endl;
		if (Z[posht].hotel[posht].vacantes > 0) {
			Z[posht].hotel[posht].cupo = 1;
		}
		cod.close();
		nom.close();
		ciu.close();
		hab.close();
		cup.close();
		est.close();
		posht++; reg++;
	}
	else{
		cout<<"Ya existe un hotel con ese codigo"<<endl;
	}

}

bool verCupo(int reg){
	int cont=0;
	if(reg != 0){
		for (int i = 0; i < reg; i++) {
			if (Z[i].hotel[i].cupo) {
				cont++;
			}
			else{
				cont=cont+0;
			}
		}
		if(cont>0){
			return 1;
		}
	}
	else{
		return 0;
	}
}

void refrescar(){

	int cont=0;
	ofstream hab,cup;
	hab.open("habitaciones_h.txt",ios::out);
	cup.open("cupos_h.txt",ios::out);
	while(cont<reg){
		hab<<Z[cont].hotel[cont].cantidadVacantes<<endl;
		for(int i = 1; i <= Z[cont].hotel[cont].cantidadVacantes; i++){
					Z[cont].hotel[cont].vacantes[i];
					cup<<Z[cont].hotel[cont].vacantes[i]<<endl;
		}

		cont++;

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
				cout<<"Codigo del hotel: "<<Z[i].hotel[i].codigo<<endl<<endl;
				cout<<"Ciudad: "<<Z[i].hotel[i].ciudad<<endl;
				cout<<"Habitaciones: "<<endl;
				for(int x = 1; x <= Z[i].hotel[i].cantidadVacantes ; x++){
					if(Z[i].hotel[i].vacantes[x] != 0){
						cout<<"Habitacion "<< x <<": "<< Z[i].hotel[i].vacantes[x]<<endl;
					}


			}
				cout<<endl;
				cout<<"Estrellas: ";
				for(int n = 0; n < Z[i].hotel[i].estrellas; n++) {
					cout<<"* ";
				}
			}
			cout<<endl;
			cout<<"-------------------------------------------"<<endl<<endl;

		}
	}
else{
		cout<<endl<< "NO HAY HOTELES DISPONIBLES EN ESTE MOMENTO"<<endl;
}
}

int reserva( int &reg, int &poscl){

	system("CLS"); string nombre, hotel; int edad, sitio, noches, room; int op, i = 0; bool es = 0; char p;
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
			cout<<"Que habitacion: "; cin>>room;
			cout<<"Confirmar reserva? (s/n): "; cin>>p;
			if (p == 's') {
				cout<<"Reserva a nombre de "<< Z[usuarioActual].cliente[usuarioActual].nombre<< " confirmada";
				cout<<endl;
				//
				nombre = Z[usuarioActual].cliente[usuarioActual].nombre;
				archivo1.open(nombre.c_str(),ios::app);
				archivo.open("historial.txt",ios::app);
				hotel = Z[sitio].hotel[sitio].nombre;
				archivo<<"|NOMBRE: "<<nombre<<" |HOTEL: "<<hotel<<"|NOCHES:"<<noches<<"|HABITACION: "<<room<<" |FECHA DE RESERVACION: "<<fecha<<endl;
				archivo.close();
				archivo1<<"|HOTEL: "<<hotel<<"|NOCHES: "<<noches<<"|HABITACION: "<<room<<" |FECHA DE RESERVACION: "<<fecha<<endl;
				archivo1.close();
				//
				for ( i = 0; i < reg; i++) {
					if (room == Z[sitio].hotel[sitio].vacantes[i]) {
						room = i;
						break;
					}
				}

				Z[usuarioActual].cliente[usuarioActual].hotelReserva[Z[usuarioActual].cliente[usuarioActual].nReserva] = op;
				Z[usuarioActual].cliente[usuarioActual].habitacion[Z[usuarioActual].cliente[usuarioActual].nReserva] = room;
				Z[sitio].hotel[sitio].vacantes[room] = 0;
				Z[usuarioActual].cliente[usuarioActual].nReserva += 1;

				for(int j=1; j <= Z[sitio].hotel[sitio].cantidadVacantes ;j++){
						if(Z[sitio].hotel[sitio].vacantes[j] > 0){
							Z[sitio].hotel[sitio].cupo = 1;
							break;
						}
						else{
							if(j == Z[sitio].hotel[sitio].cantidadVacantes && Z[sitio].hotel[sitio].vacantes[j]==0){
								Z[sitio].hotel[sitio].cupo = 0;
							}
						}

				}

				refrescar();

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
	int cont=0;
	nombre=Z[usuarioActual].cliente[usuarioActual].nombre;
	archivo.open(nombre.c_str(), ios::in);
	while ( getline (archivo,line))
	    {
	      cout << line << endl;
	      cont++;
	    }
	    if(cont<1){
		cout<<"\t NO HAY RESERVACIONES AUN "<<endl;
		}
	    archivo.close();
}

void registro(){
	char nombre[40], contrasena[20]; int edad,i;
	ofstream archivo;
	ofstream archivo1;
	ofstream nreserva;
	cout<<"\t REGISTRO"<<endl;
	cout<<"Tu nombre: "; cin>>nombre;
	cout<<"Contrasena: "; cin>>contrasena;
	if (regus != 0) {
		for ( i = 0; i < regus; i++) {
			if (strcmp(nombre, Z[i].cliente[i].nombre) == 0) {
				cout<<"Ya existe un usuario con ese nombre, intente nuevamente"<<endl;
				system("PAUSE");
				system("cls");
				break;
							}
			}
			if(i == regus){
			  strcpy(Z[poscl].cliente[poscl].nombre, nombre);
				strcpy(Z[poscl].cliente[poscl].contrasena, contrasena );
				Z[poscl].cliente[poscl].nReserva = 0;
				archivo.open("usuarios.txt",ios::app);
	      archivo1.open("pass.txt",ios::app);
				nreserva.open("nreserva.txt",ios::app);
				nreserva<<Z[poscl].cliente[poscl].nReserva<<endl;
				archivo<<nombre<<endl;
				archivo1<<contrasena<<endl;

				Z[poscl].cliente[poscl].codigo += 1;
				poscl++;
				regus++;
				cout<<"Registro exitoso"<<endl;
				archivo.close();
				archivo1.close();

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
		cout<<"Registro exitoso"<<endl;
		archivo.close();
		archivo1.close();
	}


}

/*void ocultarContrasena(char contrasena[20]){
	char c; int i = 0;
	while((c = getch()) != ENTER){
		contrasena[i] = c;
		cout<<"*";
		i++;
	}
}*/

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
				mostrarHoteles(reg);
				break;
			}

			case 3:{
				historial();
				break;
			}

			case 8:{
				estadoSesion = 0; admin = 0;
				cout<<"Se ha cerrado sesión"<<endl;
				break;
			}
			default: cout<<endl<<"Opcion no valida"<<endl;
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
				break;
			}
			default: cout<<endl<<"Opcion no valida"<<endl;
		}
		cout<<endl<<endl;
		system("PAUSE");

		system("cls");
	}while(estadoSesion);


}
bool lleno_h = 0;

void llenar_h(int &reg, int &posht){
	string s_cod, s_nom, s_ciu, s_hab, s_cup, s_est;

	ifstream cod,nom,ciu,hab,cup,est;

	cod.open("codigo_h.txt",ios::in);
	nom.open("nombre_h.txt",ios::in);
	ciu.open("ciudad_h.txt",ios::in);
	hab.open("habitaciones_h.txt",ios::in);
	cup.open("cupos_h.txt",ios::in);
	est.open("estrellas_h.txt",ios::in);
	while(getline(nom,s_nom)){
		getline(cod,s_cod);
		getline(ciu,s_ciu);
		getline(hab,s_hab);
		getline(est,s_est);
		int s_cod1 = atoi(s_cod.c_str());
		int s_hab1 = atoi(s_hab.c_str());
		int s_est1 = atoi(s_est.c_str());
		Z[posht].hotel[posht].codigo = s_cod1;
		strcpy(Z[posht].hotel[posht].nombre, s_nom.c_str());
		strcpy(Z[posht].hotel[posht].ciudad, s_ciu.c_str());
		Z[posht].hotel[posht].cantidadVacantes = s_hab1;
		for(int i = 1; i <= Z[posht].hotel[posht].cantidadVacantes; i++){
				getline(cup,s_cup);
				int s_cup1 = atoi(s_cup.c_str());
	 			Z[posht].hotel[posht].vacantes[i] = s_cup1;
		}
		Z[posht].hotel[posht].estrellas = s_est1;
		for(int j=1; j <= Z[posht].hotel[posht].cantidadVacantes ;j++){
				if(Z[posht].hotel[posht].vacantes[j] > 0){
					Z[posht].hotel[posht].cupo = 1;
					break;
				}
				else{
					if(Z[posht].hotel[posht].cantidadVacantes == j && Z[posht].hotel[posht].vacantes[j]==0){
						Z[posht].hotel[posht].cupo = 0;
						break;
					}
				}

		}
		posht++;
		reg++;
		}

			cod.close();
			nom.close();
			ciu.close();
			hab.close();
			cup.close();
			est.close();
}


bool lleno = 0;

void llenar(){
   string line, line1, s_nre;
	 int nreserva;
   ifstream archivo;
   ifstream archivo1;
	 ifstream nreserva1;
	 nreserva1.open("nreserva.txt", ios::in);
   archivo.open("usuarios.txt" , ios::in);
   archivo1.open("pass.txt", ios::in);
    	while ( getline (archivo,line) )
	    {
            getline(archivo1,line1);
						getline(nreserva1,s_nre);
						int nreserva = atoi(s_nre.c_str());
			Z[poscl].cliente[poscl].nReserva=nreserva;
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
		if(!lleno_h){
			llenar_h(reg,posht);
			lleno_h=1;
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
	    system("Pause");
		system("cls");
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
		cout<<endl<<endl<<endl;
        cout<<"\t  \t     Bienvenido "<<Z[usuarioActual].cliente[usuarioActual].nombre<<endl; Sleep(2000);
		system("cls");
		menuCliente();
    }
	return main();
}
