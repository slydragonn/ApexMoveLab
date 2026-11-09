#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "Medicion.h"
#include "ListaMediciones.h"
#include "Reglas.h"

using namespace std;

const string CATEGORIA_TODAS = "Todas";

string trim(const string& texto)
{
	size_t inicio = texto.find_first_not_of(" \t\r\n");

	if (inicio == string::npos)
	{
		return "";
	}

	size_t fin = texto.find_last_not_of(" \t\r\n");
	return texto.substr(inicio, fin - inicio + 1);
}

bool leerTexto(const string& mensaje, string& valor)
{
	if (!mensaje.empty())
	{
		cout << mensaje;
	}

	if (!getline(cin, valor))
	{
		return false;
	}

	valor = trim(valor);
	return true;
}

bool leerEntero(const string& mensaje, int& valor)
{
	while (true)
	{
		string linea;

		if (!leerTexto(mensaje, linea))
		{
			return false;
		}

		try
		{
			size_t posicion = 0;
			int numero = stoi(linea, &posicion);

			if (posicion == linea.size())
			{
				valor = numero;
				return true;
			}
		}
		catch (...)
		{
		}

		cout << "Entrada invalida. Debe ingresar un numero entero." << endl;
	}
}

bool leerDouble(const string& mensaje, double& valor)
{
	while (true)
	{
		string linea;

		if (!leerTexto(mensaje, linea))
		{
			return false;
		}

		replace(linea.begin(), linea.end(), ',', '.');

		try
		{
			size_t posicion = 0;
			double numero = stod(linea, &posicion);

			if (posicion == linea.size())
			{
				valor = numero;
				return true;
			}
		}
		catch (...)
		{
		}

		cout << "Entrada invalida. Debe ingresar un numero." << endl;
	}
}

int solicitarOpcion()
{
	string linea;

	if (!leerTexto("Opcion: ", linea))
	{
		return -1;
	}

	if (linea.empty())
	{
		return -2;
	}

	try
	{
		size_t posicion = 0;
		int opcion = stoi(linea, &posicion);

		if (posicion == linea.size())
		{
			return opcion;
		}
	}
	catch (...)
	{
	}

	return -2;
}

void mostrarMenuPrincipal()
{
	cout << endl;
	cout << "=== Bienvenidos a APEX Move ===" << endl;
	cout << "Selecciona una opcion para continuar:" << endl;
	cout << "1. Gestion de mediciones" << endl;
	cout << "2. Consulta y analisis" << endl;
	cout << "3. Cargar datos de demostracion" << endl;
	cout << "4. Salir" << endl;
}

void mostrarSubmenuGestion()
{
	cout << endl;
	cout << "=== Submenu: Gestion ===" << endl;
	cout << "Selecciona una opcion para continuar:" << endl;
	cout << "1. Registrar medicion" << endl;
	cout << "2. Modificar medicion" << endl;
	cout << "3. Eliminar medicion" << endl;
	cout << "4. Volver al menu principal" << endl;
}

void mostrarSubmenuConsultaAnalisis()
{
	cout << endl;
	cout << "=== Submenu: Consulta y Analisis ===" << endl;
	cout << "Selecciona una opcion para continuar:" << endl;
	cout << "1. Buscar por identificador" << endl;
	cout << "2. Mostrar todas las mediciones" << endl;
	cout << "3. Mostrar mediciones de una categoria" << endl;
	cout << "4. Generar estadisticas" << endl;
	cout << "5. Volver al menu principal" << endl;
}

void mostrarSubmenuEstadisticas()
{
	cout << endl;
	cout << "=== Submenu: Estadisticas ===" << endl;
	cout << "Selecciona una opcion para continuar:" << endl;
	cout << "1. Estadisticas generales" << endl;
	cout << "2. Estadisticas por categoria" << endl;
	cout << "3. Volver a consulta y analisis" << endl;
}

bool pedirEtiqueta(const Reglas& reglas, string& etiqueta)
{
	while (true)
	{
		string mensaje = "Etiqueta ("
			+ to_string(reglas.getCaracterMinEtiqueta())
			+ "-"
			+ to_string(reglas.getCaracterMaxEtiqueta())
			+ " caracteres): ";

		if (!leerTexto(mensaje, etiqueta))
		{
			return false;
		}

		if (reglas.esEtiquetaValida(etiqueta))
		{
			return true;
		}

		cout << "Etiqueta invalida. Debe tener entre "
			<< reglas.getCaracterMinEtiqueta()
			<< " y "
			<< reglas.getCaracterMaxEtiqueta()
			<< " caracteres." << endl;
	}
}

bool pedirCategoria(const Reglas& reglas, string& categoria)
{
	reglas.imprimirCategorias();

	while (true)
	{
		if (!leerTexto("Categoria (codigo): ", categoria))
		{
			return false;
		}

		for (char& caracter : categoria)
		{
			caracter = static_cast<char>(toupper(static_cast<unsigned char>(caracter)));
		}

		if (reglas.esCategoriaValida(categoria))
		{
			return true;
		}

		cout << "Categoria invalida. Use uno de los codigos mostrados." << endl;
	}
}

bool pedirDuracion(const Reglas& reglas, double& duracion)
{
	ostringstream mensaje;
	mensaje << "Duracion en " << reglas.getUnidadTiempo()
		<< " (" << reglas.getTiempoMin() << "-" << reglas.getTiempoMax() << "): ";

	while (true)
	{
		if (!leerDouble(mensaje.str(), duracion))
		{
			return false;
		}

		if (reglas.esTiempoMedidoValido(duracion))
		{
			return true;
		}

		cout << "Duracion fuera de rango. Debe estar entre "
			<< reglas.getTiempoMin()
			<< " y "
			<< reglas.getTiempoMax()
			<< " " << reglas.getUnidadTiempo() << "." << endl;
	}
}

bool pedirObservacion(const Reglas& reglas, string& observacion)
{
	string mensaje = "Observacion ("
		+ to_string(reglas.getCaracterMinObservacion())
		+ "-"
		+ to_string(reglas.getCaracterMaxObservacion())
		+ " caracteres, puede dejarla vacia): ";

	while (true)
	{
		if (!leerTexto(mensaje, observacion))
		{
			return false;
		}

		if (reglas.esObservacionValida(observacion))
		{
			return true;
		}

		cout << "Observacion invalida. Debe tener entre "
			<< reglas.getCaracterMinObservacion()
			<< " y "
			<< reglas.getCaracterMaxObservacion()
			<< " caracteres." << endl;
	}
}

void accionRegistrarMedicion(ListaMediciones& lista, const Reglas& reglas)
{
	string etiqueta;
	string categoria;
	string observacion;
	double duracion = 0.0;

	if (!pedirEtiqueta(reglas, etiqueta))
	{
		return;
	}

	if (!pedirCategoria(reglas, categoria))
	{
		return;
	}

	if (!pedirDuracion(reglas, duracion))
	{
		return;
	}

	if (!pedirObservacion(reglas, observacion))
	{
		return;
	}

	int id = lista.insertarMedicion(etiqueta, categoria, duracion, observacion);
	cout << "Medicion registrada correctamente con ID " << id << "." << endl;
}

void accionModificarMedicion(ListaMediciones& lista, const Reglas& reglas)
{
	int id = 0;

	if (!leerEntero("ID de la medicion a modificar: ", id))
	{
		return;
	}

	if (!lista.existeIdentificador(id))
	{
		cout << "No existe una medicion con el ID " << id << "." << endl;
		return;
	}

	cout << "Datos actuales:" << endl;
	lista.mostrarMedicion(id);

	string etiqueta;
	string categoria;
	string observacion;
	double duracion = 0.0;

	if (!pedirEtiqueta(reglas, etiqueta))
	{
		return;
	}

	if (!pedirCategoria(reglas, categoria))
	{
		return;
	}

	if (!pedirDuracion(reglas, duracion))
	{
		return;
	}

	if (!pedirObservacion(reglas, observacion))
	{
		return;
	}

	if (lista.modificarMedicion(id, etiqueta, categoria, duracion, observacion))
	{
		cout << "Medicion " << id << " modificada correctamente." << endl;
	}
}

void accionEliminarMedicion(ListaMediciones& lista)
{
	int id = 0;

	if (!leerEntero("ID de la medicion a eliminar: ", id))
	{
		return;
	}

	if (lista.eliminarMedicion(id))
	{
		cout << "Medicion " << id << " eliminada correctamente." << endl;
	}
	else
	{
		cout << "No existe una medicion con el ID " << id << "." << endl;
	}
}

void accionBuscarMedicion(const ListaMediciones& lista)
{
	int id = 0;

	if (!leerEntero("ID de la medicion a buscar: ", id))
	{
		return;
	}

	lista.mostrarMedicion(id);
}

void accionMostrarPorCategoria(const ListaMediciones& lista, const Reglas& reglas)
{
	string categoria;

	if (!pedirCategoria(reglas, categoria))
	{
		return;
	}

	lista.mostrarMedicionesPorCategoria(categoria);
}

void accionCargarDatosDemostracion(ListaMediciones& lista)
{
	string respuesta;

	cout << "Esto reemplazara las mediciones actuales. ¿Continuar? (s/n): ";

	if (!leerTexto("", respuesta))
	{
		return;
	}

	if (respuesta == "s" || respuesta == "S"
		|| respuesta == "si" || respuesta == "SI" || respuesta == "Si")
	{
		lista.cargarDatosDemostracion();
	}
	else
	{
		cout << "Operacion cancelada." << endl;
	}
}

void menuEstadisticas(const ListaMediciones& lista, const Reglas& reglas);

void menuGestion(ListaMediciones& lista, const Reglas& reglas)
{
	int opcion = 0;

	do
	{
		mostrarSubmenuGestion();
		opcion = solicitarOpcion();

		if (opcion == -1)
		{
			return;
		}

		switch (opcion)
		{
		case 1:
			accionRegistrarMedicion(lista, reglas);
			break;
		case 2:
			accionModificarMedicion(lista, reglas);
			break;
		case 3:
			accionEliminarMedicion(lista);
			break;
		case 4:
			break;
		default:
			cout << "Opcion invalida." << endl;
			break;
		}
	} while (opcion != 4);
}

void menuConsulta(ListaMediciones& lista, const Reglas& reglas)
{
	int opcion = 0;

	do
	{
		mostrarSubmenuConsultaAnalisis();
		opcion = solicitarOpcion();

		if (opcion == -1)
		{
			return;
		}

		switch (opcion)
		{
		case 1:
			accionBuscarMedicion(lista);
			break;
		case 2:
			lista.mostrarTodasLasMediciones();
			break;
		case 3:
			accionMostrarPorCategoria(lista, reglas);
			break;
		case 4:
			menuEstadisticas(lista, reglas);
			break;
		case 5:
			break;
		default:
			cout << "Opcion invalida." << endl;
			break;
		}
	} while (opcion != 5);
}

void menuEstadisticas(const ListaMediciones& lista, const Reglas& reglas)
{
	int opcion = 0;

	do
	{
		mostrarSubmenuEstadisticas();
		opcion = solicitarOpcion();

		if (opcion == -1)
		{
			return;
		}

		switch (opcion)
		{
		case 1:
			lista.generarReporteEstadistico(CATEGORIA_TODAS);
			break;
		case 2:
		{
			string categoria;

			if (pedirCategoria(reglas, categoria))
			{
				lista.generarReporteEstadistico(categoria);
			}
			break;
		}
		case 3:
			break;
		default:
			cout << "Opcion invalida." << endl;
			break;
		}
	} while (opcion != 3);
}

int main()
{
	ListaMediciones lista;

	Reglas reglas(
		1,
		120,
		2,
		1,
		40,
		0,
		100,
		"min",
		"km",
		"automovil",
		"urbanos simulados",
		{{
			{"RES", "Residencial", "Recorridos por zonas de viviendas."},
			{"COM", "Comercial", "Recorridos por sectores con tiendas y negocios."},
			{"UNI", "Universitaria", "Recorridos por zonas cercanas a universidades."}
		}}
	);

	int opcion = 0;

	do
	{
		mostrarMenuPrincipal();
		opcion = solicitarOpcion();

		if (opcion == -1)
		{
			cout << "\nFin del programa." << endl;
			break;
		}

		switch (opcion)
		{
		case 1:
			menuGestion(lista, reglas);
			break;
		case 2:
			menuConsulta(lista, reglas);
			break;
		case 3:
			accionCargarDatosDemostracion(lista);
			break;
		case 4:
			cout << "Fin del programa." << endl;
			break;
		default:
			cout << "Opcion invalida." << endl;
			break;
		}
	} while (opcion != 4);

	return 0;
}
