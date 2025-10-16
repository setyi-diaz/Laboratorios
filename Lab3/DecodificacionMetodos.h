#ifndef DECODIFICACIONMETODOS_H
#define DECODIFICACIONMETODOS_H
short int contBitsBloq(const unsigned char c,short int n){
    short int cont=0;
    for(int i = 0; i < n; i++){
        if(((c >> i) & 1)) {
            cont++;}
    }
    return cont;
}
void decodMet1(unsigned char *ptr1, unsigned int tam,short int n){
    unsigned char temp;
    short int ban;
    short int cont;
    short int cont2;
    unsigned char mascara;

    temp = ptr1[0];
    ptr1[0] = (ptr1[0] ^ (255>>(8-n)));

    for(unsigned int i = 1; i < (tam*8)/n; i++){
        cont2 = contBitsBloq(temp,n);
        // validacion 1: si hay mas 1s que 0s, inviertir cada 3 bits
        if(cont2 > n/2){   //funciona con 3 <= n <= 8
            cont = 1;
            ban = n / 3;  //ban, almacena el numero de bits que se pueden codificar
            mascara = (unsigned char)(128);
            while (cont <= ban) {
                if(cont == ban) {
                    mascara = (mascara >> (10-n));
                    break;
                }
                mascara = ((mascara >> 3)|(unsigned char)(128));
                cont++;
            }
            temp = ptr1[i];
            ptr1[i] = (ptr1[i] ^ mascara);
        }
        // si hay igual cantidad de 0s y 1s se invierte cada bit
        else if(cont2 == n/2){
            mascara = (255 >> (8-n));
            temp = ptr1[i];
            ptr1[i] = (ptr1[i] ^ mascara);
        }
        //si hay más 0s que 1s, se invierte cada 2 bits
        else{
            cont = 1;
            ban = n/2;
            mascara = (unsigned char)(128);
            while(cont<=ban){
                if(cont==ban) {    //funciona con 2 <= n <= 8
                    mascara = (mascara >> (9-n));
                    break;
                }
                mascara = ((mascara >> 2) | (unsigned char)(128));
                cont++;
            }
            temp = ptr1[i];
            ptr1[i] = (ptr1[i] ^ mascara);
        }
    }
}
void decodMet2(unsigned char *ptr, unsigned int tam, short int n){
    // (arrayEnBloques,tam,semilla)
    unsigned char temp = 0;
    unsigned char mascara = (1<<(n-1));

    for(unsigned int i = 0; i < (tam*8)/n; i++){
        temp = ((ptr[i] & mascara) >> (n-1));  //almacena el ultimo bit del bloque
        ptr[i] = ((ptr[i] << 1) | temp);
    }
}

#endif // DECODIFICACIONMETODOS_H
