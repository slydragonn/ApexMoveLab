#include "Reglas.h"
#include <iostream>
#include <array>
#include <string>
using namespace std;

Reglas::Reglas(
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
) :
	tiempoMin(tiempoMin),
	tiempoMax(tiempoMax),
	distancia(distancia),
	caracterMinEtiqueta(caracterMinEtiqueta),
	caracterMaxEtiqueta(caracterMaxEtiqueta),
	caracterMinObservacion(caracterMinObservacion),
	caracterMaxObservacion(caracterMaxObservacion),
	unidadTiempo(unidadTiempo),
	unidadDistancia(unidadDistancia),
	medioTransporte(medioTransporte),
	tipoRecorridos(tipoRecorridos),
	categorias(categorias)
{

}

bool Reglas::esTiempoMedidoValido(double tiempo) const
{
	return tiempo >= this->tiempoMin && tiempo <= this->tiempoMax;
}

bool Reglas::esEtiquetaValida(string etiqueta) const
{
	size_t longitud = etiqueta.length();
	return longitud >= static_cast<size_t>(this->caracterMinEtiqueta)
		&& longitud <= static_cast<size_t>(this->caracterMaxEtiqueta);
}

bool Reglas::esCategoriaValida(string categoria) const
{
	for (const auto& fila : this->categorias) {
		if (categoria == fila.codigo) {
			return true;
		}
	}

	return false;
}

bool Reglas::esObservacionValida(string observacion) const
{
	size_t longitud = observacion.length();
	return longitud >= static_cast<size_t>(this->caracterMinObservacion)
		&& longitud <= static_cast<size_t>(this->caracterMaxObservacion);
}

double Reglas::getTiempoMin() const
{
	return tiempoMin;
}

double Reglas::getTiempoMax() const
{
	return tiempoMax;
}

int Reglas::getCaracterMinEtiqueta() const
{
	return caracterMinEtiqueta;
}

int Reglas::getCaracterMaxEtiqueta() const
{
	return caracterMaxEtiqueta;
}

int Reglas::getCaracterMinObservacion() const
{
	return caracterMinObservacion;
}

int Reglas::getCaracterMaxObservacion() const
{
	return caracterMaxObservacion;
}

double Reglas::getDistancia() const
{
	return distancia;
}

string Reglas::getUnidadTiempo() const
{
	return unidadTiempo;
}

string Reglas::getUnidadDistancia() const
{
	return unidadDistancia;
}

string Reglas::getMedioTransporte() const
{
	return medioTransporte;
}

string Reglas::getTipoRecorridos() const
{
	return tipoRecorridos;
}

array<CategoriaRuta, 3> Reglas::getCategorias() const
{
	return categorias;
}

void Reglas::imprimirCategorias() const
{
	cout << "Categorias disponibles: " << endl;

	for (const auto& fila : categorias) {
		std::cout << fila.codigo << " | "
			<< fila.categoria << " | "
			<< fila.descripcion << "\n";
	}
}