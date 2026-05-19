#ifndef RED_H
#define RED_H
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
    void eliminarEnrutador(string& );
    void agregarEnrutador(string& ,Enrutador*);
};

#endif // RED_H
