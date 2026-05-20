#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <map>
#include <string>
using namespace std;

class Enrutador
{
private:
    string nombre;
    map<string,int> enlacesDir;

public:
    Enrutador();
    Enrutador(const string& ,const map<string,int>&);
    void añadirEnlaceDirecto(const string& , int );
    bool buscarEnlaceDirecto(const string& ) const;
    void eliminarEnlace(const string&);
    string getNombre() const;
    void setNombre(const string &newNombre);
    const map<string, int>& getEnlacesDir() const;
};

#endif // ENRUTADOR_H
