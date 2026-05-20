#ifndef RED_H
#define RED_H
#include <iostream>
#include "enrutador.h"
#include <map>
#include <queue>
#include  <vector>
#include <list>
#include <limits>
using namespace std;

class Red
{
private:
    map<string, Enrutador*> enrutadores;
    void dijkstra(const string& origen);
    void recalcularTodasLasTablas();
public:
    Red();
    ~Red();
    void eliminarEnrutador(const string& nombre);
    void agregarEnrutador(const string& nombre, const map<string,int>& enlaces);
    bool existeEnrutador(const string& nombre) const;

    void agregarEnlace(const string& origen, const string& destino, int costo);
    void eliminarEnlace(const string& origen, const string& destino);

    list<string> caminoMasCorto(const string& origen, const string& destino) const;
    void imprimirCamino(const string& origen, const string& destino) const;
    void imprimirTablaDeEnrutador(const string& nombre) const;
    void imprimirTodasLasTablas() const;
    void imprimirTopologia() const;
};

#endif // RED_H
