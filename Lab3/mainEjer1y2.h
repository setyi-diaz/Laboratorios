#ifndef MAINEJER1Y2_H
#define MAINEJER1Y2_H
void pruebaMetCodDec(){
    unsigned char *arrBloq = nullptr;
    unsigned short int semilla;
    unsigned int opcion;
    unsigned int tam = 0;
    string nomArchInt;
    string nomArchOut;


    cout << "Ingrese el nombre del archivo fuente: ";
    cin >> nomArchInt;
    cout << "Ingrese el nombre del archivo de salida: ";
    cin >> nomArchOut;


    unsigned char *datArch = leer_archivo(nomArchInt.c_str(), tam);

    if (!datArch || tam == 0) {
        cout << "No se pudo leer archivo.\n";
        delete[] datArch;
        return 1;
    }

    cout << "Ingrese 1: para usar el metodo de codificacion 1 "<<endl;
    cout << "Ingrese 2: para usar el metodo de codificacion 2 "<<endl;
    cout << "opcion: ";
    cin >> opcion;
    cout << "Ingrese la semilla que desea emplear para la codificacion: ";
    cin >> semilla;

    arrBloq = construirArrBloq(datArch,tam,semilla);

    if(opcion==1){
        codMet1(arrBloq,tam,semilla);
    }
    else if (opcion==2){
        codMet2(arrBloq,tam,semilla);
    }
    construirArrOrigin(arrBloq,datArch,tam,semilla);
    ofstream out(nomArchOut, ios::binary);
    if (!out) {
        cout << "No se pudo crear el archivo." << endl;
        delete[] datArch; delete[] arrBloq;
        return 1;
    }
    // Escribir el contenido del arreglo en el archivo
    out.write(reinterpret_cast<const char*>(arrBloq), tam);
    out.close();

    delete[] datArch;
    delete[] arrBloq;
    return 0;
}
#endif // MAINEJER1Y2_H
