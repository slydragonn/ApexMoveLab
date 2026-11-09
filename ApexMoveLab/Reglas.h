#pragma once
#include <iostream>
#include <array>
using namespace std;

struct CategoriaRuta {
	string codigo;
	string categoria;
	string descripcion;
};

class Reglas
{
private:
	double tiempoMin;
	double tiempoMax;
	double distancia;
	int caracterMinEtiqueta;
	int caracterMaxEtiqueta;
	int caracterMinObservacion;
	int caracterMaxObservacion;
	string unidadTiempo;
	string unidadDistancia;
	string medioTransporte;
	string tipoRecorridos;
	array<CategoriaRuta, 3> categorias;


public:
	Reglas(
		double tiempoMin,
		double tiempoMax,
		double distancia,
		int caracterMinEtiqueta,
		int caracterMaxEtiqueta,
		int caracterMinObservacion,
		int caracterMaxObservacion,
		string unidadTiempo,
		string unidadDistancia,
		string medioTransporte,
		string tipoRecorridos,
		array<CategoriaRuta, 3> categorias
	);

	bool esTiempoMedidoValido(double tiempo) const;
	bool esEtiquetaValida(string etiqueta) const;
	bool esCategoriaValida(string categoria) const;
	bool esObservacionValida(string observacion) const;

	double getTiempoMin() const;
	double getTiempoMax() const;
	int getCaracterMinEtiqueta() const;
	int getCaracterMaxEtiqueta() const;
	int getCaracterMinObservacion() const;
	int getCaracterMaxObservacion() const;
	double getDistancia() const;
	string getUnidadTiempo() const;
	string getUnidadDistancia() const;
	string getMedioTransporte() const;
	string getTipoRecorridos() const;
	array<CategoriaRuta, 3> getCategorias() const;

	void imprimirCategorias() const;
};

