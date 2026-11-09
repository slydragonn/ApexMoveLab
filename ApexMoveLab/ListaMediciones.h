#pragma once
#include <iostream>
#include "Medicion.h"
using namespace std;

class ListaMediciones {
public:
	Medicion* cabeza = nullptr;
private:
	int cantidad;
	int siguienteId;

public:
	ListaMediciones();
	~ListaMediciones();

	int insertarMedicion(string etiqueta, string categoria, double valorMedido, string observacion);
	bool existeIdentificador(int id) const;
	Medicion* buscarPorIdentificador(int id) const;
	bool modificarMedicion(int id, string etiqueta, string categoria, double valorMedido, string observacion);
	bool eliminarMedicion(int id);

	void mostrarTodasLasMediciones() const;
	void mostrarMedicionesPorCategoria(string categoria) const;
	void mostrarMedicion(int id) const;

	int contarMediciones(string categoria) const;
	double calcularMedia(string categoria) const;
	double calcularMediana(string categoria) const;
	double calcularMinimo(string categoria) const;
	double calcularMaximo(string categoria) const;
	double calcularDesviacionEstandarPoblacional(string categoria) const;
	double obtenerValorPorPosicion(int posicion) const;

	int contarMedicionesBajas(string categoria) const;
	int contarMedicionesEsperadas(string categoria) const;
	int contarMedicionesAltas(string categoria) const;
	double calcularPorcentaje(int cantidadNivel, double total) const;

	void generarReporteEstadistico(string categoria) const;
	void cargarDatosDemostracion();
	void ordenarLista();

	bool estaVacia() const;
	int obtenerCantidad() const;
	int obtenerSiguienteId() const;
	void limpiar();

private:
	string clasificarNivel(double valorMedido) const;
	bool coincideConCategoria(const Medicion& medicion, string categoria) const;
	void imprimirEncabezado() const;
	void imprimirMedicion(const Medicion& medicion) const;

	void liberarNodos();
};
