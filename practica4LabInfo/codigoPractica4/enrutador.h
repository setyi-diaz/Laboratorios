#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <map>
#include <string>
using namespace std;

class Enrutador
{
private:
    string nombre;
    map<string,int> enlaces;

public:
    Enrutador();
    void getEnlace(string* ) const;
    string getNombre() const;
    void setNombre(const string &newNombre);
};

#endif // ENRUTADOR_H
