#include<iostream>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<time.h>
using namespace std;

struct equipo
{
	int numero_serie;
	char tipo[50];
	char modelo[50];
	char resguardo[50];
	char edificio[50];
	char area[50];
};
struct equipo reportes[1];

int cantidad_guardada(struct equipo reportes[])
{
	int contador = 1;
	char cadena[100];
	FILE *archivo = fopen("Equipos_guardados.txt", "rt");
	if(archivo != NULL)
	{
		while(fgets(cadena, 100, archivo))
		{
			strtok(cadena, "\n");
			fgets(cadena, 100, archivo);
			strtok(cadena, "\n");
			fgets(cadena, 100, archivo);
			strtok(cadena, "\n");
			fgets(cadena, 100, archivo);
			strtok(cadena, "\n");
			fgets(cadena, 100, archivo);
			strtok(cadena, "\n");
			fgets(cadena, 100, archivo);
			strtok(cadena, "\n");
			fgets(cadena, 100, archivo);
			strtok(cadena, "\n");
			fgets(cadena, 100, archivo);
			strtok(cadena, "\n");
			contador++;
		}
	}
	fclose(archivo);
	return contador;
}

void guardar_datos(int contador, struct equipo reportes[])
{
	FILE *archivo = fopen("Equipos_guardados.txt", "w+");
	
	for(int i=0; i<contador; i++)
	{
		fprintf(archivo, " --- Equipo %i ---\n", i+1);
		fprintf(archivo, "%s\n", reportes[i].resguardo);
		fprintf(archivo, "%i\n", reportes[i].numero_serie);
		fprintf(archivo, "%s\n", reportes[i].modelo);
		fprintf(archivo, "%s\n", reportes[i].tipo);
		fprintf(archivo, "%s\n", reportes[i].area);
		fprintf(archivo, "%s\n", reportes[i].edificio);
		fprintf(archivo, "\n");
	}
	fclose(archivo);
}

void cargar_datos(struct equipo reportes[])
{
	int contador = 0;
	char cadena[100];
	FILE *archivo = fopen("Equipos_guardados.txt", "rt");
	
	if(archivo != NULL)
	{
		while(fgets(cadena, 100, archivo))
		{
			strtok(cadena, "\n");
			
			fgets(cadena, 100, archivo);
			strtok(cadena, "\n");
			strcpy(reportes[contador].resguardo, cadena);
			
			fgets(cadena, 100, archivo);
			strtok(cadena, "\n");
			reportes[contador].numero_serie = atoi(cadena);
			
			fgets(cadena, 100, archivo);
			strtok(cadena, "\n");
			strcpy(reportes[contador].modelo, cadena);
			
			fgets(cadena, 100, archivo);
			strtok(cadena, "\n");
			strcpy(reportes[contador].tipo, cadena);
			
			fgets(cadena, 100, archivo);
			strtok(cadena, "\n");
			strcpy(reportes[contador].area, cadena);
			
			fgets(cadena, 100, archivo);
			strtok(cadena, "\n");
			strcpy(reportes[contador].edificio, cadena);
			
			fgets(cadena, 100, archivo);
			strtok(cadena, "\n");
			contador++;
		}
	}
	else
	{
		cout<<"\n El archivo no ha sido creado.\n";
	}
	fclose(archivo);
}

bool verificar_resguardo(int contador, char *nombre, struct equipo reportes[])
{
	for(int i=0; i<contador; i++)
	{
		if(strcmp(reportes[i].resguardo, nombre) == 0)
		{
			return true;
		}
	}
	return false;
}

bool verificar_numero(int contador, int numero_serie, struct equipo reportes[])
{
	for(int i=0; i<contador; i++)
	{
		if(reportes[i].numero_serie == numero_serie)
		{
			return true;
		}
	}
	return false;
}

bool validar_tipo(int contador, char *tipo, struct equipo reportes[])
{
	if(strcmp(reportes[contador].tipo, "pc") == 0 || strcmp(reportes[contador].tipo, "laptop") == 0)
	{
		return true;
	}
	return false;
}

bool validar_numero(int contador, int numero_serie, struct equipo reportes[])
{
	for(int i=0; i<contador; i++)
	{
		if(numero_serie == reportes[i].numero_serie)
		{
			return false;
		}
	}
	return true;
}

int agregar_equipo(int contador, struct equipo reportes[])
{
	do
	{
		cout<<"\n --- Equipo "<<contador+1<<" ---\n";
		cout<<"\n Numero de serie: "; cin>>reportes[contador].numero_serie;
		if(validar_numero(contador, reportes[contador].numero_serie, reportes) == false)
		{
			cout<<"\n Error, el numero de serie no puede estar repetido.\n";
			cout<<"\n "; system("pause"); system("cls");
		}
	}
	while(validar_numero(contador, reportes[contador].numero_serie, reportes) == false);
		
	do
	{
		cout<<"\n Tipo: "; fflush(stdin); gets(reportes[contador].tipo);
		for(int i=0; i<strlen(reportes[contador].tipo); i++)
		{
			reportes[contador].tipo[i] = tolower(reportes[contador].tipo[i]);
		}
		if(validar_tipo(contador, reportes[contador].tipo, reportes) == false)
		{
			cout<<"\n Error, el tipo debe ser PC o Laptop.\n";
			cout<<"\n "; system("pause"); system("cls");
			cout<<"\n --- Equipo "<<contador+1<<" ---\n";
			cout<<"\n Numero de serie: "<<reportes[contador].numero_serie<<endl;
		}
	}
	while(validar_tipo(contador, reportes[contador].tipo, reportes) == false);
	
	cout<<"\n Resguardo: "; fflush(stdin); gets(reportes[contador].resguardo);
	cout<<"\n Modelo: "; fflush(stdin); gets(reportes[contador].modelo);
	cout<<"\n Area: "; fflush(stdin); gets(reportes[contador].area);
	cout<<"\n Edificio: "; fflush(stdin); gets(reportes[contador].edificio);
	cout<<"\n Equipo agregado con exito."<<endl;
    contador++;
    return contador;
}

void listar_PCs(int contador, struct equipo reportes[])
{
	cout<<"\n\t --- PCs REGISTRADOS O AGREGADOS ---\n";
	for(int i=0; i<contador; i++)
	{
		if(strcmp(reportes[i].tipo, "pc") == 0)
		{
			cout<<"\n --- Equipo "<<i+1<<" ---\n";
			cout<<"\n Resguardo: "<<reportes[i].resguardo;
			cout<<"\n Numero de serie: "<<reportes[i].numero_serie;
			cout<<"\n Modelo: "<<reportes[i].modelo;
			cout<<"\n Tipo: "<<reportes[i].tipo;
			cout<<"\n Area: "<<reportes[i].area;
			cout<<"\n Edificio: "<<reportes[i].edificio<<endl;
		}
	}
}

void listar_laptops(int contador, struct equipo reportes[])
{
	cout<<"\n\t --- LAPTOS REGISTRADAS O AGREGADAS ---\n";
	for(int i=0; i<contador; i++)
	{
		if(strcmp(reportes[i].tipo, "laptop") == 0)
		{
			cout<<"\n --- Equipo "<<i+1<<" ---\n";
			cout<<"\n Resguardo: "<<reportes[i].resguardo;
			cout<<"\n Numero de serie: "<<reportes[i].numero_serie;
			cout<<"\n Modelo: "<<reportes[i].modelo;
			cout<<"\n Tipo: "<<reportes[i].tipo;
			cout<<"\n Area: "<<reportes[i].area;
			cout<<"\n Edificio: "<<reportes[i].edificio<<endl;
		}
	}
}

void listar_equipos(int contador, struct equipo reportes[])
{
	cout<<"\n\t --- REPORTE DE EQUIPOS ---\n";
	for(int i=0; i<contador; i++)
	{
		cout<<"\n --- Equipo "<<i+1<<" ---\n";
		cout<<"\n Resguardo: "<<reportes[i].resguardo;
		cout<<"\n Numero de serie: "<<reportes[i].numero_serie;
		cout<<"\n Modelo: "<<reportes[i].modelo;
		cout<<"\n Tipo: "<<reportes[i].tipo;
		cout<<"\n Area: "<<reportes[i].area;
		cout<<"\n Edificio: "<<reportes[i].edificio<<endl;
	}
}

void buscar_equipo(int contador, struct equipo reportes[])
{
	char nombre[50];
	
	cout<<"\n Nombre de la persona que tiene el equipo asigando: "; fflush(stdin); gets(nombre);
	if(verificar_resguardo(contador, nombre, reportes) == true)
	{
		for(int i=0; i<contador; i++)
		{
			if(strcmp(reportes[i].resguardo, nombre) == 0)
			{
				cout<<"\n --- Equipo "<<i+1<<" ---\n";
				cout<<"\n Resguardo: "<<reportes[i].resguardo;
				cout<<"\n Numero de serie: "<<reportes[i].numero_serie;
				cout<<"\n Modelo: "<<reportes[i].modelo;
				cout<<"\n Tipo: "<<reportes[i].tipo;
				cout<<"\n Area: "<<reportes[i].area;
				cout<<"\n Edificio: "<<reportes[i].edificio<<endl;
			}
		}
	}
	else
	{
		cout<<"\n El nombre no aparece en los reportes.\n";
	}
}

void reasignar_equipo(int contador, struct equipo reportes[])
{
	int numero_serie, posicion;
	
	cout<<"\n Numero de serie del equipo que desea reasignar: "; cin>>numero_serie;
	if(verificar_numero(contador, numero_serie, reportes) == true)
	{
		for(int i=0; i<contador; i++)
		{
			if(reportes[i].numero_serie == numero_serie)
			{
				cout<<"\n --- Equipo "<<i+1<<" ---\n";
				cout<<"\n Resguardo: "<<reportes[i].resguardo;
				cout<<"\n Numero de serie: "<<reportes[i].numero_serie;
				cout<<"\n Modelo: "<<reportes[i].modelo;
				cout<<"\n Tipo: "<<reportes[i].tipo;
				cout<<"\n Area: "<<reportes[i].area;
				cout<<"\n Edificio: "<<reportes[i].edificio<<endl;
				posicion = i;
			}
		}
		cout<<"\n Nombre de la nueva persona a la que se le asignara el equipo: "; fflush(stdin); gets(reportes[posicion].resguardo);
		cout<<"\n El equipo se ha actualizado correctamente.\n";
	}
	else
	{
		cout<<"\n El equipo con ese numero de serie no fue encontrado.\n";
	}
}

int main()
{
	int capacidad = 1, contador = 0, opcion;
	equipo *reportes = NULL;
	
	
	
	capacidad = cantidad_guardada(reportes);
	reportes = (equipo *) malloc(sizeof(equipo)*capacidad);
	
	do
	{
		cout<<"\n --- MENU PRINCIPAL ---\n";
		cout<<"\n [0]. Salir.";
		cout<<"\n [1]. Agregar Equipo.";
		cout<<"\n [2]. Listar todos los Equipos.";
		cout<<"\n [3]. Listar los PCs.";
		cout<<"\n [4]. Listar las Laptops.";
		cout<<"\n [5]. Buscar Equipo por resguardo.";
		cout<<"\n [6]. Reasignar Equipo.";
		cout<<"\n [7]. Guardar archivo.";
		cout<<"\n [8]. Cargar archivo.";
		cout<<"\n\n Ingrese su opcion: "; cin>>opcion;
		system("cls");
		
		switch(opcion)
		{
			case 0:
				cout<<"\n Que vuelva pronto.\n";
			break;
			
			case 1:
			{
				contador = agregar_equipo(contador, reportes);
				capacidad++;
				reportes = (equipo *) realloc(reportes, sizeof(equipo)*capacidad);
			}
			break;
			
			case 2:
			{
				if(contador != 0)
				{
					listar_equipos(contador, reportes);
				}
				else
				{
					cout<<"\n No hay equipos agregados para mostrar.\n";
				}
			}
			break;
			
			case 3:
			{
				if(contador != 0)
				{
					listar_PCs(contador, reportes);
				}
				else
				{
					cout<<"\n No hay equipos agregados para mostrar.\n";
				}
			}
			break;
			
			case 4:
			{
				if(contador != 0)
				{
					listar_laptops(contador, reportes);
				}
				else
				{
					cout<<"\n No hay equipos agregados para mostrar.\n";
				}
			}
			break;
			
			case 5:
			{
				if(contador != 0)
				{
					buscar_equipo(contador, reportes);
				}
				else
				{
					cout<<"\n No hay equipos agregados.\n";
				}
			}
			break;
			
			case 6:
			{
				if(contador != 0)
				{
					reasignar_equipo(contador, reportes);
				}
				else
				{
					cout<<"\n No hay equipos agregados.\n";
				}
			}
			break;
			
			case 7:
				guardar_datos(contador, reportes);
				cout<<"\n Archivo actualizaodo con exito.\n";
			break;
			
			case 8:
				cargar_datos(reportes);
				contador = cantidad_guardada(reportes)-1;
				cout<<"\n Archivo leido con exito.\n";
			break;
			
			default:
				cout<<"\n Error, opcion no valida.\n";
			break;
		}
		cout<<"\n "; system("pause"); system("cls");
	}
	while(opcion!=0);
}
