#include "ListaMediciones.h"
#include "Medicion.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

ListaMediciones::ListaMediciones()
	: cabeza(nullptr),
	cantidad(0),
	siguienteId(101)
{
}

ListaMediciones::~ListaMediciones()
{
	liberarNodos();
}

int ListaMediciones::insertarMedicion(
	string etiqueta,
	string categoria,
	double valorMedido,
	string observacion
)
{
	int id = siguienteId;
	Medicion* medicion = new Medicion(
		id,
		etiqueta,
		categoria,
		valorMedido,
		observacion
	);

	if (cabeza == nullptr) {
		cabeza = medicion;
	}
	else {
		Medicion* ultimaMedicion = cabeza;

		while (ultimaMedicion->getSiguiente() != nullptr) {
			ultimaMedicion = ultimaMedicion->getSiguiente();
		}
		ultimaMedicion->setSiguiente(medicion);
	}

	cantidad++;
	siguienteId++;
	return id;
}

bool ListaMediciones::existeIdentificador(int id) const {
	Medicion* actual = cabeza;

	while (actual != nullptr) {
		if (actual->getIdentificador() == id) {
			return true;
		}
		actual = actual->getSiguiente();
	}

	return false;
}

Medicion* ListaMediciones::buscarPorIdentificador(int id) const {
	Medicion* actual = cabeza;

	while (actual != nullptr) {
		if (actual->getIdentificador() == id) {
			return actual;
		}
		actual = actual->getSiguiente();
	}

	return nullptr;
}

bool ListaMediciones::modificarMedicion(
	int id,
	string etiqueta,
	string categoria,
	double valorMedido,
	string observacion
)
{
	Medicion* medicion = buscarPorIdentificador(id);

	if (medicion == nullptr) {
		return false;
	}

	medicion->setEtiqueta(etiqueta);
	medicion->setCategoria(categoria);
	medicion->setValorMedido(valorMedido);
	medicion->setObservacion(observacion);
	return true;
}

bool ListaMediciones::eliminarMedicion(int id) {
	if (cabeza == nullptr) {
		return false;
	}

	if (cabeza->getIdentificador() == id) {
		Medicion* nodoAEliminar = cabeza;
		cabeza = cabeza->getSiguiente();
		delete nodoAEliminar;
		cantidad--;
		return true;
	}

	Medicion* actual = cabeza;

	while (actual->getSiguiente() != nullptr
		&& actual->getSiguiente()->getIdentificador() != id) {
		actual = actual->getSiguiente();
	}

	if (actual->getSiguiente() == nullptr) {
		return false;
	}

	Medicion* nodoAEliminar = actual->getSiguiente();
	actual->setSiguiente(nodoAEliminar->getSiguiente());
	delete nodoAEliminar;
	cantidad--;
	return true;
}

void ListaMediciones::imprimirEncabezado() const {
	cout << left
		<< setw(6) << "ID"
		<< setw(42) << "Etiqueta"
		<< setw(11) << "Categoria"
		<< setw(16) << "Duracion (min)"
		<< "Observacion" << endl;
}

void ListaMediciones::imprimirMedicion(const Medicion& medicion) const {
	cout << left
		<< setw(6) << medicion.getIdentificador()
		<< setw(42) << medicion.getEtiqueta()
		<< setw(11) << medicion.getCategoria()
		<< setw(16) << fixed << setprecision(1) << medicion.getValorMedido()
		<< medicion.getObservacion() << endl;
}

void ListaMediciones::mostrarTodasLasMediciones() const {
	if (estaVacia()) {
		cout << "No hay mediciones registradas." << endl;
		return;
	}

	imprimirEncabezado();

	for (Medicion* actual = cabeza; actual != nullptr; actual = actual->getSiguiente()) {
		imprimirMedicion(*actual);
	}
}

void ListaMediciones::mostrarMedicionesPorCategoria(string categoria) const {
	if (estaVacia()) {
		cout << "No hay mediciones registradas." << endl;
		return;
	}

	bool hayCoincidencias = false;
	Medicion* actual = cabeza;

	while (actual != nullptr) {
		if (coincideConCategoria(*actual, categoria)) {
			if (!hayCoincidencias) {
				imprimirEncabezado();
				hayCoincidencias = true;
			}
			imprimirMedicion(*actual);
		}
		actual = actual->getSiguiente();
	}

	if (!hayCoincidencias) {
		cout << "No hay mediciones para la categoria " << categoria << "." << endl;
	}
}

void ListaMediciones::mostrarMedicion(int id) const {
	Medicion* medicion = buscarPorIdentificador(id);

	if (medicion == nullptr) {
		cout << "No existe una medicion con el ID " << id << "." << endl;
		return;
	}

	imprimirEncabezado();
	imprimirMedicion(*medicion);
}

int ListaMediciones::contarMediciones(string categoria) const
{
	int contador = 0;

	for (Medicion* actual = cabeza; actual != nullptr; actual = actual->getSiguiente()) {
		if (coincideConCategoria(*actual, categoria)) {
			contador++;
		}
	}

	return contador;
}

double ListaMediciones::calcularMedia(string categoria) const
{
	int total = contarMediciones(categoria);

	if (total == 0) {
		return 0.0;
	}

	double suma = 0.0;

	for (Medicion* actual = cabeza; actual != nullptr; actual = actual->getSiguiente()) {
		if (coincideConCategoria(*actual, categoria)) {
			suma += actual->getValorMedido();
		}
	}

	return suma / total;
}

double ListaMediciones::calcularMediana(string categoria) const
{
	vector<double> valores;

	for (Medicion* actual = cabeza; actual != nullptr; actual = actual->getSiguiente()) {
		if (coincideConCategoria(*actual, categoria)) {
			valores.push_back(actual->getValorMedido());
		}
	}

	if (valores.empty()) {
		return 0.0;
	}

	sort(valores.begin(), valores.end());
	size_t cantidadValores = valores.size();

	if (cantidadValores % 2 != 0) {
		return valores[cantidadValores / 2];
	}

	return (valores[cantidadValores / 2 - 1] + valores[cantidadValores / 2]) / 2.0;
}

double ListaMediciones::calcularMinimo(string categoria) const
{
	int total = contarMediciones(categoria);

	if (total == 0) {
		return 0.0;
	}

	bool primero = true;
	double minimo = 0.0;

	for (Medicion* actual = cabeza; actual != nullptr; actual = actual->getSiguiente()) {
		if (coincideConCategoria(*actual, categoria)) {
			double valor = actual->getValorMedido();
			if (primero || valor < minimo) {
				minimo = valor;
				primero = false;
			}
		}
	}

	return minimo;
}

double ListaMediciones::calcularMaximo(string categoria) const
{
	int total = contarMediciones(categoria);

	if (total == 0) {
		return 0.0;
	}

	bool primero = true;
	double maximo = 0.0;

	for (Medicion* actual = cabeza; actual != nullptr; actual = actual->getSiguiente()) {
		if (coincideConCategoria(*actual, categoria)) {
			double valor = actual->getValorMedido();
			if (primero || valor > maximo) {
				maximo = valor;
				primero = false;
			}
		}
	}

	return maximo;
}

double ListaMediciones::calcularDesviacionEstandarPoblacional(string categoria) const
{
	int total = contarMediciones(categoria);

	if (total == 0) {
		return 0.0;
	}

	double media = calcularMedia(categoria);
	double suma = 0.0;

	for (Medicion* actual = cabeza; actual != nullptr; actual = actual->getSiguiente()) {
		if (coincideConCategoria(*actual, categoria)) {
			double diferencia = actual->getValorMedido() - media;
			suma += diferencia * diferencia;
		}
	}

	return sqrt(suma / total);
}

double ListaMediciones::obtenerValorPorPosicion(int posicion) const {
	if (posicion < 0) {
		return 0.0;
	}

	int indice = 0;

	for (Medicion* actual = cabeza; actual != nullptr; actual = actual->getSiguiente()) {
		if (indice == posicion) {
			return actual->getValorMedido();
		}
		indice++;
	}

	return 0.0;
}

int ListaMediciones::contarMedicionesBajas(string categoria) const
{
	int contador = 0;

	for (Medicion* actual = cabeza; actual != nullptr; actual = actual->getSiguiente()) {
		if (coincideConCategoria(*actual, categoria)
			&& clasificarNivel(actual->getValorMedido()) == "bajo") {
			contador++;
		}
	}

	return contador;
}

int ListaMediciones::contarMedicionesEsperadas(string categoria) const
{
	int contador = 0;

	for (Medicion* actual = cabeza; actual != nullptr; actual = actual->getSiguiente()) {
		if (coincideConCategoria(*actual, categoria)
			&& clasificarNivel(actual->getValorMedido()) == "esperado") {
			contador++;
		}
	}

	return contador;
}

int ListaMediciones::contarMedicionesAltas(string categoria) const
{
	int contador = 0;

	for (Medicion* actual = cabeza; actual != nullptr; actual = actual->getSiguiente()) {
		if (coincideConCategoria(*actual, categoria)
			&& clasificarNivel(actual->getValorMedido()) == "alto") {
			contador++;
		}
	}

	return contador;
}

double ListaMediciones::calcularPorcentaje(int cantidadNivel, double total) const
{
	if (total <= 0) {
		return 0.0;
	}

	return (static_cast<double>(cantidadNivel) / total) * 100.0;
}

void ListaMediciones::generarReporteEstadistico(string categoria) const
{
	int total = contarMediciones(categoria);

	cout << "\n=== Reporte estadistico ===" << endl;
	cout << "Categoria: " << categoria << endl;
	cout << "Total de mediciones: " << total << endl;

	if (total == 0) {
		cout << "No hay mediciones para generar estadisticas." << endl;
		return;
	}

	cout << fixed << setprecision(2);
	cout << "Media: " << calcularMedia(categoria) << endl;
	cout << "Mediana: " << calcularMediana(categoria) << endl;
	cout << "Valor minimo registrado: " << calcularMinimo(categoria) << endl;
	cout << "Valor maximo registrado: " << calcularMaximo(categoria) << endl;
	cout << "Desviacion estandar poblacional: " << calcularDesviacionEstandarPoblacional(categoria) << endl;

	int bajas = contarMedicionesBajas(categoria);
	int esperadas = contarMedicionesEsperadas(categoria);
	int altas = contarMedicionesAltas(categoria);

	cout << "Mediciones bajas: " << bajas
		<< " (" << calcularPorcentaje(bajas, total) << "%)" << endl;
	cout << "Mediciones esperadas: " << esperadas
		<< " (" << calcularPorcentaje(esperadas, total) << "%)" << endl;
	cout << "Mediciones altas: " << altas
		<< " (" << calcularPorcentaje(altas, total) << "%)" << endl;
}

void ListaMediciones::cargarDatosDemostracion() {
	limpiar();

	insertarMedicion("Residencial Norte", "RES", 6.5, "Poco trafico");
	insertarMedicion("Residencial Sur", "RES", 8.0, "Trafico normal");
	insertarMedicion("Comercial Centro", "COM", 20.0, "Trafico moderado");
	insertarMedicion("Comercial Mall", "COM", 24.5, "Congestion");
	insertarMedicion("Universitaria Este", "UNI", 12.0, "Trafico normal");
	insertarMedicion("Universitaria Oeste", "UNI", 14.0, "Hora de entrada");
	insertarMedicion("Residencial Centro", "RES", 7.0, "Trafico bajo");
	insertarMedicion("Comercial Avenida", "COM", 18.0, "Trafico alto");

	cout << "Se cargaron 8 mediciones de demostracion." << endl;
}

void ListaMediciones::ordenarLista() {
	if (cabeza == nullptr || cabeza->getSiguiente() == nullptr) {
		return;
	}

	bool huboCambio;

	do {
		huboCambio = false;
		Medicion* actual = cabeza;

		while (actual->getSiguiente() != nullptr) {
			Medicion* siguiente = actual->getSiguiente();

			if (actual->getValorMedido() > siguiente->getValorMedido()) {
				int idTemporal = actual->getIdentificador();
				string etiquetaTemporal = actual->getEtiqueta();
				string categoriaTemporal = actual->getCategoria();
				double valorTemporal = actual->getValorMedido();
				string observacionTemporal = actual->getObservacion();

				actual->setIdentificador(siguiente->getIdentificador());
				actual->setEtiqueta(siguiente->getEtiqueta());
				actual->setCategoria(siguiente->getCategoria());
				actual->setValorMedido(siguiente->getValorMedido());
				actual->setObservacion(siguiente->getObservacion());

				siguiente->setIdentificador(idTemporal);
				siguiente->setEtiqueta(etiquetaTemporal);
				siguiente->setCategoria(categoriaTemporal);
				siguiente->setValorMedido(valorTemporal);
				siguiente->setObservacion(observacionTemporal);

				huboCambio = true;
			}

			actual = actual->getSiguiente();
		}
	} while (huboCambio);
}

bool ListaMediciones::estaVacia() const {
	return cabeza == nullptr;
}

int ListaMediciones::obtenerCantidad() const {
	return cantidad;
}

int ListaMediciones::obtenerSiguienteId() const {
	return siguienteId;
}

void ListaMediciones::limpiar() {
	liberarNodos();
	siguienteId = 101;
}

string ListaMediciones::clasificarNivel(double valorMedido) const
{
	if (valorMedido <= 8) {
		return "bajo";
	}
	if (valorMedido > 8 && valorMedido <= 20) {
		return "esperado";
	}
	return "alto";
}

bool ListaMediciones::coincideConCategoria(const Medicion& medicion, string categoria) const
{
	return categoria == "Todas" || medicion.getCategoria() == categoria;
}

void ListaMediciones::liberarNodos()
{
	Medicion* actual = cabeza;

	while (actual != nullptr)
	{
		Medicion* nodoALiberar = actual;
		actual = actual->getSiguiente();
		delete nodoALiberar;
	}

	cabeza = nullptr;
	cantidad = 0;
}
