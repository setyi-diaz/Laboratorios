#include "red.h"

Red::Red() {}
Red::~Red(){
    for(auto&it : enrutadores){
        delete it.second;
    }
}
void Red::eliminarEnrutador(string& EnrutParaElim){
    auto it = enrutadores.find(EnrutParaElim);

    if(it != enrutadores.end()){
        delete it->second;
        enrutadores.erase(it);
    }

    for(auto&it : enrutadores){
       Enrutador* enrutTemp= it.second;
        enrutTemp->eliminarEnlace(EnrutParaElim);
    }
}
void Red::agregarEnrutador(string& nombreEnrut,Enrutador* enrutador){
    enrutadores[nombreEnrut] = enrutador;
}
