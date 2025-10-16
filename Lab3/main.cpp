#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <CodificacionMetodos.h>
using namespace std;

unsigned char* leer_archivo(const char* nombre, unsigned int &tam) {
    ifstream f(nombre, ios::binary | ios::ate);
    if (!f) { tam = 0; return nullptr; }
    tam = (size_t)f.tellg();
    f.seekg(0, ios::beg);
    unsigned char* datos = new unsigned char[tam];
    f.read(reinterpret_cast<char*>(datos), (std::streamsize)tam);
    return datos;
}
unsigned char* construirArrBloq(unsigned char *ptr,unsigned int tam, unsigned int n){
    unsigned char *arrDin = new unsigned char [(tam*8)/n];
    unsigned char  temp = (char)(0);
    unsigned short int bitsTemp = 0;
    unsigned char mascara = (255>>(8-n));
    unsigned char bloque = (char)(0);
    bool ban = false;
    unsigned short int pos = 0;

    for(unsigned int i = 0; i < tam; i++){
        temp = ptr[i];
        bitsTemp += 8;
        while (bitsTemp >= n) {
            bitsTemp -= n;
            bloque = ((temp>>bitsTemp) & mascara);
            if (ban == true){
                arrDin[pos] = (arrDin[pos] | bloque);
                ban = false;
                pos++;
            }
            else{
                arrDin[pos] = bloque;
                pos++;
            }
        }
        if(bitsTemp > 0 && pos <= (tam*8/n)){
            arrDin[pos] = ((temp<<(n-bitsTemp)) & mascara);
            ban = true;
        }
    }
    return arrDin;
}
void construirArrOrigin(unsigned char* arrBloq,unsigned char* arrOrigin, unsigned int tam, unsigned int n) {
    unsigned int pos = 0;
    unsigned short temp = 0;
    unsigned int bitsTemp = 0;

    for (unsigned int i = 0; i < (tam * 8) / n; i++) {
        // Agregar bloque al buffer
        temp = (temp << n) | arrBloq[i];
        bitsTemp += n;

        // Extraer bytes completos del buffer
        while (bitsTemp >= 8) {
            bitsTemp -= 8;
            unsigned char byteRec = (temp >> bitsTemp) & 0xFF;
            arrOrigin[pos++] = byteRec;
        }
    }
}
bool soloNumeros(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}
bool numeroValido(const string& str) {
    bool punto = false;
    for (char c : str) {
        if (c == '.' && !punto) {
            punto = true;
        } else if (!isdigit(c)) {
            return false;
        }
    }
    return !str.empty(); // No estar vacío
}
void guardarArch2(const string& nombreArchivo, const string& datos) {
    ofstream archivo(nombreArchivo, ios::binary | ios::trunc);
    if (!archivo.is_open()) {
        cout << "Error al guardar el archivo usuarios.\n";
        return;
    }

    archivo.write(datos.c_str(), datos.size());
    archivo.close();
}
string leerArch2(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cout << "Error al leer el archivo usuarios.\n";
        return "";
    }

    // Obtener tamaño del archivo
    archivo.seekg(0, ios::end);
    size_t tam = archivo.tellg();
    archivo.seekg(0, ios::beg);

    // Crear string del tamaño exacto
    string datos(tam, '\0');
    archivo.read(&datos[0], tam);

    archivo.close();
    return datos;
}
int main()
{
    unsigned char *arrBloq = nullptr;
    unsigned char *buffer2=nullptr;
    unsigned char buffer1[10];  //almacenar la contraseña del userAdmin
    unsigned short int semilla=8;
    unsigned int opcion1;
    unsigned int opcion2=1;
    unsigned int tamArchSudo = 0;
    unsigned int tamArchUsua = 0;
    int cont;
    string nomArchInt;
    string nomArchOut;
    string contrAdmin;
    string cedula, claveU, saldo;
    string usuarioNuevo;
    string cadUsuarios;
    string cadUsuariosSinCod;
    string cadenaSudo;

    //-------------codificacion de sudo.txt-------------
    nomArchInt="sudosincod.txt";
    nomArchOut="sudo.txt";
    unsigned char *sudo = leer_archivo(nomArchInt.c_str(), tamArchSudo);

    if (!sudo || tamArchSudo == 0) {
        cout << "No se pudo leer archivo sudosincod.txt o el archivo esta vacio \n";
        delete[] sudo;
        return 1;
    }
    arrBloq = construirArrBloq(sudo,tamArchSudo,semilla);
    codMet2(arrBloq,tamArchSudo,semilla);
    construirArrOrigin(arrBloq,sudo,tamArchSudo,semilla);
    cadenaSudo=string(reinterpret_cast<char*>(sudo), tamArchSudo); //string importante para validar contraseña userAdmin
    ofstream out(nomArchOut, ios::binary);
    if (!out) {
        cout << "No se pudo crear el archivo sudo.txt" << endl;
        delete[] sudo; delete[] arrBloq;
        return 1;
    }
    // Escribir el contenido del arreglo en el archivo
    out.write(reinterpret_cast<const char*>(sudo), tamArchSudo);
    out.close();
    delete[] sudo;
    delete[] arrBloq;
    arrBloq=nullptr;
    //------------------------------------------------------

    cadUsuariosSinCod=leerArch2("usuariosSinCod.txt");
    cadUsuarios=leerArch2("usuarios.txt");

    do{
        do{
        cout<<"-----------------Bienvenido--------------"<<endl;
        cout<<"Ingrese 1: para acceder como ADMINISTRADOR"<<endl;
        cout<<"Ingrese 2: para acceder como USUARIO"<<endl;
        cout<<"Ingrese 0: para salir del sistema"<<endl;
        cin>>opcion1;
        if (cin.fail()) {      // Si ingresan letras u otro valor inválido
            cin.clear();       // Limpia el estado de error
            cin.ignore(1000, '\n');
            opcion1 = -1;      // Asigna valor inválido
        }
        if (opcion1 != 0 && opcion1 != 1 && opcion1 != 2)
            cout << "Opcion invalida, intente de nuevo.\n";

        }while(opcion1!=0 && opcion1!=1 && opcion1!=2);

        switch (opcion1) {
        case 1:
            usuarioNuevo="";
            do{
                do {
                    cout << "Ingresa tu contrasena: ";
                    cin >> contrAdmin;

                    if (contrAdmin.size() == 0 || contrAdmin.size() > 10) {
                        cout << "La contraseña debe tener entre 1 y 10 caracteres." << endl;
                        cout << "Intente de nuevo." << endl;
                    }

                } while (contrAdmin.size() == 0 || contrAdmin.size() > 10);

                memcpy(buffer1, contrAdmin.c_str(), contrAdmin.size()); //almacena en un arreglo una cadena tipo string
                arrBloq = construirArrBloq(buffer1,contrAdmin.size(),semilla);
                codMet2(arrBloq,contrAdmin.size(),semilla);
                construirArrOrigin(arrBloq,buffer1,contrAdmin.size(),semilla);

                contrAdmin=string(reinterpret_cast<char*>(buffer1), contrAdmin.size());
                // Mostrar contrAdmin en hexadecimal
                cout << "Resultado decodificado (HEX): ";
                for (unsigned char c : contrAdmin) {
                    cout << "0x"
                         << hex << uppercase
                         << setw(2) << setfill('0')
                         << (int)c << " ";
                }
                cout << endl;

                // Mostrar cadenaSudo en hexadecimal
                cout << "Clave real (HEX): ";
                for (unsigned char c : cadenaSudo) {
                    cout << "0x"
                         << hex << uppercase
                         << setw(2) << setfill('0')
                         << (int)c << " ";
                }
                cout << endl;
                if(contrAdmin!=cadenaSudo){
                    cout<<" Contrasena incorrecta!"<<endl;
                }
                delete[] arrBloq;
                arrBloq=nullptr;
            }while(contrAdmin!=cadenaSudo);
            cout<<"Validacion exitosa!"<<endl;
            cont=0;
            while(opcion2!=0){
                cout<<"Ingrese 1: para registrar un USUARIO"<<endl;
                cout<<"Ingrese 0: para volver al menu principal "<<endl;
                cin>>opcion2;
                switch (opcion2) {
                case 1:
                    cont++;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    do {
                        cout << "Ingrese cedula del usuario: ";
                        getline(cin, cedula);
                        if (!soloNumeros(cedula) || cedula.length() < 6 || cedula.length() > 10) {
                            cout << "Cedula invalida. Debe contener solo numeros y tener entre 6 y 10 caracteres.\n";
                        }
                    } while (!soloNumeros(cedula) || cedula.length() < 6);
                    do {
                        cout << "Ingrese clave: ";
                        getline(cin, claveU);
                        if (claveU.empty()) {
                            cout << "La clave no puede estar vacia.\n";
                        }
                    } while (claveU.empty());
                    do {
                        cout << "Ingrese saldo inicial: ";
                        getline(cin, saldo);
                        if (!numeroValido(saldo)) {
                            cout << "Saldo invalido. Ingrese solo numeros\n";
                        }
                    } while (!numeroValido(saldo));

                    usuarioNuevo+= cedula+','+claveU+','+saldo+'\n';
                    cadUsuariosSinCod+=usuarioNuevo;

                    buffer2=new unsigned char [usuarioNuevo.size()];
                    memcpy(buffer2, usuarioNuevo.c_str(), usuarioNuevo.size());
                    arrBloq = construirArrBloq(buffer2,usuarioNuevo.size(),semilla);
                    codMet1(arrBloq,usuarioNuevo.size(),semilla);
                    construirArrOrigin(arrBloq,buffer2,usuarioNuevo.size(),semilla);

                    usuarioNuevo=string(reinterpret_cast<char*>(buffer2), usuarioNuevo.size());
                    cadUsuarios+=usuarioNuevo;

                    guardarArch2("usuariosSinCod.txt",cadUsuariosSinCod);
                    guardarArch2("usuarios.txt",cadUsuarios);
                    cout<<"Usuario registrado exitosamente"<<endl;

                    delete[] arrBloq;
                    delete[] buffer2;
                    arrBloq=nullptr;
                    buffer2=nullptr;
                    break;
                case 0:
                    cout<<"Cuenta USUARIOADMIN cerrada....."<<endl;
                    break;
                default:
                    cout<<"opcion invalida!"<<endl;
                    break;
                }
            }
            break;
        case 0:
            cout<<"Gracias por utilizar nuestros servicios"<<endl;
            cout<<"Hasta la proxima......"<<endl;
            guardarArch2("usuarios.txt",cadUsuarios);
            guardarArch2("usuariosSinCod.txt",cadUsuariosSinCod);
            break;
        default:
            cout<<"opcion invalida!"<<endl;
            break;
        }
    }while (opcion1!=0);
    return 0;
}



/*//-------------------------------
                for(size_t i = 0;i<contrAdmin.size();i++){
                    cout<<"0x"<<hex<<buffer1[i]<<" ";
                }
                //--------------------------*/
/*//-------------------------------
                for (char c : contrAdmin) {
                    // Convertimos a unsigned para evitar valores negativos
                    cout << "0x" << hex << uppercase << setw(2) << setfill('0')
                         << (static_cast<unsigned int>(static_cast<unsigned char>(c))) << " ";
                }
                //-------------------------------*/
