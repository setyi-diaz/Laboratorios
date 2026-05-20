#ifndef RED_H
#define RED_H
#include <iostream>
#include "enrutador.h"
#include <map>
using namespace std;

class Red
{
private:
    map<string, Enrutador*> enrutadores;
public:
    Red();
    ~Red();
    void eliminarEnrutador(const string& nombre);
    void agregarEnrutador(const string& nombre, const map<string,int>& enlaces);
    void agregarEnlace(const string& origen, const string& destino, int costo);
    void eliminarEnlace(const string& origen, const string& destino);
    bool existeEnrutador(const string& nombre) const;
    void imprimirTopologia() const;
};

#endif // RED_H
