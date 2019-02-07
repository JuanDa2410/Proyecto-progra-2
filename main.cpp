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
void menuCliente();
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
	int estado[20];
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
	      cont++;
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

void filtro(){
	if(verCupo(reg)){
		cout<<"Ciudades registradas: "<<endl; char ciudad[20], op[20]; int n = 1;

		for(int i = 1; i <= reg; i++){
			if(strcmp(ciudad, Z[i+1].hotel[i+1].ciudad) != 0 || i == reg){
				strcpy(ciudad, Z[i].hotel[i].ciudad);
				cout<<n<<"- "<<ciudad<<endl;
				n++;

			}
		}
		cout<<endl;
		cout<<"Escoge una ciudad: "; cin>>op;
		cout<<"Hoteles en "<<op<<endl;
	}
}

void refrescar(){

	int cont=0;
	ofstream hab,cup,est;
	hab.open("habitaciones_h.txt",ios::out);
	cup.open("cupos_h.txt",ios::out);
	est.open("estado.txt", ios::out);
	while(cont<reg){
		hab<<Z[cont].hotel[cont].cantidadVacantes<<endl;
		for(int i = 1; i <= Z[cont].hotel[cont].cantidadVacantes; i++){
					Z[cont].hotel[cont].vacantes[i];
					cup<<Z[cont].hotel[cont].vacantes[i]<<endl;
					est<<Z[cont].hotel[cont].estado[i]<<endl;
		}

		cont++;

	}
}

void mostrarHoteles( int &reg){
  system("CLS");

		cout<<"\t HOTELES CON CUPO DISPONIBLE: "<<endl;
		for (int i = 0 ; i < reg; i++) {
			cout<<endl;
				cout<<"Nombre del hotel: "<<Z[i].hotel[i].nombre<<endl;
				cout<<"Codigo del hotel: "<<Z[i].hotel[i].codigo<<endl<<endl;
				cout<<"Ciudad: "<<Z[i].hotel[i].ciudad<<endl;
				cout<<"Habitaciones: "<<endl;
				for(int x = 1; x <= Z[i].hotel[i].cantidadVacantes ; x++){
					if(Z[i].hotel[i].estado[x] == 0){
						cout<<"Habitacion "<< x <<": "<< Z[i].hotel[i].vacantes[x]<<endl;
					}
					else{
                cout<<"Habitacion "<< x <<": "<< Z[i].hotel[i].vacantes[x]<<":RESERVADA"<<endl;
          }


				}
				cout<<endl;
				cout<<"Estrellas: ";
				for(int n = 0; n < Z[i].hotel[i].estrellas; n++) {
					cout<<"* ";
				}

			cout<<endl;
			cout<<"-------------------------------------------"<<endl<<endl;

		}

}

int reserva( int &reg, int &poscl){

	system("CLS"); string nombre, hotel,nom_c,nom_h; int edad, sitio, noches, room; int op, i = 0; bool es = 0; char p;
	char *fecha;
	time_t tAct = time(NULL);
	fecha=asctime(localtime(&tAct));

	ofstream archivo,archivo1,nombre_c,nombre_h;
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
			if (Z[sitio].hotel[sitio].estado[room] == 0) {
					cout<<"Confirmar reserva? (s/n): "; cin>>p;
					if (p == 's') {
						cout<<"Reserva a nombre de "<< Z[usuarioActual].cliente[usuarioActual].nombre<< " confirmada";
						cout<<endl;
						//
						nombre = Z[usuarioActual].cliente[usuarioActual].nombre;
						nom_c = Z[usuarioActual].cliente[usuarioActual].nombre;
						nom_h = Z[usuarioActual].cliente[usuarioActual].nombre;
						archivo1.open(nombre.c_str(),ios::app);
						archivo.open("historial.txt",ios::app);
						nombre_c.open((nom_c.append("_codh")).c_str(),ios::app);
						nombre_h.open((nom_h.append("_numh")).c_str(),ios::app);
						nombre_c<<Z[sitio].hotel[sitio].codigo<<endl;
						nombre_h<<room<<endl;
						hotel = Z[sitio].hotel[sitio].nombre;
						Z[sitio].hotel[sitio].estado[room] = 1;
						archivo<<"|NOMBRE: "<<nombre<<" |HOTEL: "<<hotel<<"|NOCHES:"<<noches<<"|HABITACION: "<<room<<" |FECHA DE RESERVACION: "<<fecha;
						archivo.close();
						archivo1<<"|HOTEL: "<<hotel<<"|NOCHES: "<<noches<<"|HABITACION: "<<room<<" |FECHA DE RESERVACION: "<<fecha;
						archivo1.close();
						nombre_c.close();
						nombre_h.close();
						//
						for ( i = 0; i < reg; i++) {
							if (room == Z[sitio].hotel[sitio].vacantes[i]) {
								room = i;
								break;
							}
						}

						Z[usuarioActual].cliente[usuarioActual].hotelReserva[Z[usuarioActual].cliente[usuarioActual].nReserva] = op;
						Z[usuarioActual].cliente[usuarioActual].habitacion[Z[usuarioActual].cliente[usuarioActual].nReserva] = room;
						Z[usuarioActual].cliente[usuarioActual].nReserva += 1;

						for(int j=1; j <= Z[sitio].hotel[sitio].cantidadVacantes ;j++){
								if(Z[sitio].hotel[sitio].estado[j] == 0){
									Z[sitio].hotel[sitio].cupo = 1;
									break;
								}
								else{
									if(j == Z[sitio].hotel[sitio].cantidadVacantes && Z[sitio].hotel[sitio].estado[j]==1){
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
				cout<<"La habitacion ya esta reservada, intente nuevamente"<<endl;
				system("Pause");
				system("cls");
				goto CodigoHotel;
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
	string line,line1,nombre;
	ifstream archivo;
	ifstream archivo1;
	int cont=0,cont1=0;
	nombre=Z[usuarioActual].cliente[usuarioActual].nombre;
	archivo.open(nombre.c_str(), ios::in);
	while ( getline (archivo,line)){cont++;}
	archivo.close();
	archivo1.open(nombre.c_str(),ios::in);
	while (cont1<cont){
				getline(archivo1,line1);
				cout <<"|#:"<<(cont1+1)<< line1 << endl<<endl;
                cont1++;
			}
			if(cont<1){
		cout<<"\t NO HAY RESERVACIONES AUN "<<endl;
		system("PAUSE");
		system("CLS");
		menuCliente();

		}
			archivo1.close();
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

void refrescar_reserva(int op){
	int cont=0,cont1=1;
	string nombre,nombre1,nombre2, line,line1,lin,lin1,li,li1;
	ofstream nuevo1, reemplaza,remp1,remp2,remp3,remp4;
	ifstream nuevo,reemplaza1,rem1,rem2,rem3,rem4;
	nombre = Z[usuarioActual].cliente[usuarioActual].nombre;
	nombre1 = Z[usuarioActual].cliente[usuarioActual].nombre;
	nombre2 = Z[usuarioActual].cliente[usuarioActual].nombre;
	reemplaza.open("name",ios::out);
	remp1.open("name1",ios::out);
	remp2.open("name2",ios::out);
	rem1.open((nombre1.append("_codh")).c_str(),ios::in);
	rem2.open((nombre2.append("_numh")).c_str(),ios::in);
	nuevo.open(nombre.c_str(),ios::in);
	while(getline(nuevo,line)){
		(getline(rem1,lin));
		getline(rem2,li);
		remp1<<lin<<endl;
		remp2<<li<<endl;
		reemplaza<<line<<endl;
		cont++;
	}
	nuevo.close();
	reemplaza.close();
	remp1.close();
	remp2.close();
	rem1.close();
	rem2.close();
	remp3.open(nombre1.c_str(),ios::out);
	remp4.open(nombre2.c_str(),ios::out);
	rem3.open("name1",ios::in);
	rem4.open("name2",ios::in);
	nuevo1.open(nombre.c_str(),ios::out);
	reemplaza1.open("name",ios::in);
	while(cont1<=cont){
		if(cont1!=op){
		getline(reemplaza1,line1);
		getline(rem3,lin1);
		getline(rem4,li1);
		nuevo1<<line1<<endl;
		remp3<<lin1<<endl;
		remp4<<li1<<endl;
	}
	 else{
    getline(reemplaza1,line1);
		getline(rem3,lin1);
		getline(rem4,li1);
		nuevo1<<line1<<" |ï¿½CANCELADA!"<<endl;
		remp3<<"0"<<endl;
		remp4<<"0"<<endl;
  }
	cont1++;
	}
}

void ocultarContrasena(char contrasena[10]){
	char c; int i = 0;
	while((c = getch()) != ENTER){
		contrasena[i] = c;
		cout<<"";
		i++;
	}
	contrasena[i] = '\0';
}

void login(){
	char nombre[40], contrasena[10];
	cout<<"\t LOGIN"<<endl;
	cout<<endl;
	if (regus != 0) {
		cout<<"Nombre: "; cin>>nombre;
		cout<<"Contrasena: "; ocultarContrasena(contrasena);
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



int cancelar(){
	int op,cont=0;
	int sitio;
	ifstream n_c, n_h,prueba;
	string nm_c,nm_h,pr;
	string nombre,nombre1;
	nombre = Z[usuarioActual].cliente[usuarioActual].nombre;
	nombre1 = Z[usuarioActual].cliente[usuarioActual].nombre;
	n_c.open((nombre.append("_codh")).c_str(),ios::in);
	n_h.open((nombre1.append("_numh")).c_str(),ios::in);
	reintentar:
	cout<<"Digite el numero de reserva o 0 para volver al menu: ";
	cin>>op;

	if(op==0){
		return 0;
	}

	prueba.open(nombre.c_str(), ios::in);
	while(getline(prueba,pr)){
		cont++;
	}
	if(op<=cont&&op>0){
	for(int i=0; i<op;i++){
		getline(n_c,nm_c);
		getline(n_h,nm_h);
	}
		int nombre_c = atoi(nm_c.c_str());
		int nombre_h = atoi(nm_h.c_str());
		if(nombre_c==0){
			cout<<"YA ESTA CANCELADA ESTA RESERVACION"<<endl;
			system("PAUSE");
			system("cls");
			reservasUsuario();
			goto reintentar;
		}
		else{
			for (int i = 0; i < reg; i++) {
				if (nombre_c == Z[i].hotel[i].codigo) {
					sitio = i;
					break;
				}
			}
					cout<<nombre_h<<endl;
					Z[sitio].hotel[sitio].estado[nombre_h] = 0;
			cout<<"cancelacion exitosa:"<<endl;
			refrescar();
			refrescar_reserva(op);
		}
	}
	else{
     cout<<"NO DIGITO UN NUMERO CORRECTO DE RESERVACION"<<endl;
     system("PAUSE");
     system("CLS");
     reservasUsuario();
     goto reintentar;
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
				cout<<"Se ha cerrado sesion"<<endl;
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
		cout<<"4- Buscar hotel"<<endl;
		cout<<"5- Cancelar reservas"<<endl;
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
			case 4:{
				system("cls");
				filtro();
				break;
			}
			case 5:{
				system("cls");
				reservasUsuario();
				cancelar();
				break;
			}
			case 8:{
				estadoSesion = 0;
				cout<<"Se ha cerrado sesion"<<endl;
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
	string s_cod, s_nom, s_ciu, s_hab, s_cup, s_est,s_esta;

	ifstream cod,nom,ciu,hab,cup,est,esta;

	cod.open("codigo_h.txt",ios::in);
	nom.open("nombre_h.txt",ios::in);
	ciu.open("ciudad_h.txt",ios::in);
	hab.open("habitaciones_h.txt",ios::in);
	cup.open("cupos_h.txt",ios::in);
	est.open("estrellas_h.txt",ios::in);
	esta.open("estado.txt",ios::in);

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
				getline(esta,s_esta);
				int s_cup1 = atoi(s_cup.c_str());
				int s_esta1 = atoi(s_esta.c_str());
	 			Z[posht].hotel[posht].vacantes[i] = s_cup1;
	 			Z[posht].hotel[posht].estado[i] = s_esta1;
		}
		Z[posht].hotel[posht].estrellas = s_est1;
		for(int j=1; j <= Z[posht].hotel[posht].cantidadVacantes ;j++){
				if(Z[posht].hotel[posht].estado[j] == 0){
					Z[posht].hotel[posht].cupo = 1;
					break;
				}
				else{
					if(Z[posht].hotel[posht].cantidadVacantes == j && Z[posht].hotel[posht].estado[j]==1){
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
