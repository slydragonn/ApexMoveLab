#pragma once
#include <iostream>
using namespace std;

class Medicion
{
private:
	int id;
	string etiqueta;
	string categoria;
	double valorMedido;
	string observacion;
	Medicion* siguiente = nullptr;

public:
	Medicion(
		int id,
		string etiqueta,
		string categoria,
		double valorMedido,
		string observacion
	);

	int getIdentificador() const;
	string getEtiqueta() const;
	string getCategoria() const;
	double getValorMedido() const;
	string getObservacion() const;
	Medicion* getSiguiente() const;

	void setIdentificador(int id);
	void setEtiqueta(string etiqueta);
	void setCategoria(string categoria);
	void setValorMedido(double valor);
	void setObservacion(string observacion);
	void setSiguiente(Medicion* siguiente = nullptr);
};

