#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Cara.h"
#include "Vertice.h"

namespace std
{
    class Obj
    {
        //Atributos
    private:
        string nombre;//Nombre del modelo, viene en el obj
    public:
        //Constructor
        Obj(string);
        //Estructuras de almacenamiento
        vector <Cara> caras;
        vector <Vertice> vertices;
        //Métodos
        void nuevaCara(Cara);
        void nuevoVertice(Vertice);
        void agregarNombre(string Nombre);
        //Getter
        string getNombre();
        //Archivo atributos y métodos
        string nombreArchivo;
        void leerArchivo();
    };

    //Constructor
    Obj::Obj(string nombre)
    {
        nombreArchivo = nombre;
    }

    //Agrega nueva cara 
    void Obj::nuevaCara(Cara f)
    {
        caras.push_back(f);
    }

    //Agrega nuevo vertice
    void Obj::nuevoVertice(Vertice v)
    {
        vertices.push_back(v);
    }

    //Agrega nombre al objeto
    void Obj::agregarNombre(string Nombre)
    {
        nombre = Nombre;
    }

    //Getter
    string Obj::getNombre()
    {
        return nombre;
    }

    //Abre, lee y almacena lo que hay en el archivo
    void Obj::leerArchivo()
    {
        ifstream file(nombreArchivo.c_str());//File manipula el archivo
        string parser;
        Vertice v;
        char* leer = (char*)malloc(sizeof(char) * 1000);// reservar memoria dinamica para leer una linea del archivo
        char* siguiente = NULL;
        char* aux = NULL;
        if (file.is_open())//Si el archivo se pudo abrir
        {
            while (file.getline(leer, 1000))//lee linea por linea del archivo y se guarda en "leer"
            {
                string renglon = leer; //Se le asigna a "renglón" lo que tiene "leer"
                parser = renglon.substr(0, 2);//Extrae desde la posición 0 de la palabra y agarra 2 acracteres
                if (parser == "o ")//Si el parcer detecta la "o" significa que ahí esta el nombre de la figura
                    agregarNombre(renglon.substr(2)); //Se lo asigna a la variable "agregar nombre" que está en el renglón 2, empezando de 0 del archivo
                else if (parser == "v ")//Parser detecta si ya empezamos con extracción de vertices
                {
                    //strtok fractura las cadenas de texto extraidas por renglon
                    aux = strtok_s(leer, " ", &siguiente);//Aux guarda lo que hay antes del espacio o sea v y guarda la siguiente ubicación delstring
                    aux = strtok_s(NULL, " ", &siguiente);//Ahora desde donde estamos en nulo busca el siguiente espacio, que es donde esta x y guarda el siguiente
                    v.setX(stod(aux)); //convierte char a int y se gurada el setX
                    aux = strtok_s(NULL, " ", &siguiente);//Desde el \0 anterior guarda y y la siguiente posición
                    v.setY(stod(aux));//convierte char a int y se gurada el sety
                    aux = strtok_s(NULL, " ", &siguiente);
                    v.setZ(stod(aux));//Se mueve coordenada z
                    nuevoVertice(v);//se agrega  vertice al modelo
                }
                else if (parser == "f ")//Parser detecta si ya empezamos con extracción de caras
                {
                    //No se puede hacer igual porque pueden ser más caras o menos caras
                    aux = strtok_s(leer, " ", &siguiente);//asigna a aux f
                    bool i = true;//Ayuda a comprobar si aun estamos en "faces" y si es un nuevo renglon de ellas
                    Cara c;//variable manipular caras
                    while (aux)//hasta que no sea null su valor o sea hasta que no este al final de la linea
                    {
                        if (i == false)
                            c.agregaSiguienteVertice(stod(aux) - 1);
                        else
                            i = false;
                        aux = strtok_s(NULL, " ", &siguiente);//Agarra el valor de la primera cara
                    }
                    nuevaCara(c);//se agrega la cara a modelo
                }
            }
            file.close();//cierra el archivo
        }
        else
        {
            cout << "\n\n\t*** NO SE PUDO ABRIR EL ARCHIVO .OBJ*** \n"; //Si no se puede abrir el archivo
            exit(1);
        }
    }
}