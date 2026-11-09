#include "Medicion.h"
#include <iostream>
using namespace std;

Medicion::Medicion(int id,
	string etiqueta,
	string categoria,
	double valorMedido,
	string observacion
)
	:
	id(id),
	etiqueta(etiqueta),
	categoria(categoria),
	valorMedido(valorMedido),
	observacion(observacion),
	siguiente(nullptr)
{

}

int Medicion::getIdentificador() const
{
	return id;
}

string Medicion::getEtiqueta() const {
	return etiqueta;
}

string Medicion::getCategoria() const {
	return categoria;
}

double Medicion::getValorMedido() const {
	return valorMedido;
}

string Medicion::getObservacion() const {
	return observacion;
}

Medicion* Medicion::getSiguiente() const {
	return siguiente;
}

void Medicion::setIdentificador(int id) {
	this->id = id;
}

void Medicion::setEtiqueta(string etiqueta) {
	this->etiqueta = etiqueta;
}

void Medicion::setCategoria(string categoria) {
	this->categoria = categoria;
}

void Medicion::setValorMedido(double valor) {
	this->valorMedido = valor;
}

void Medicion::setObservacion(string observacion) {
	this->observacion = observacion;
}

void Medicion::setSiguiente(Medicion* siguiente) {
	this->siguiente = siguiente;
}