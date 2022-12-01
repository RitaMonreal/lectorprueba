#include <iostream>
#include <vector>

using namespace std;

class Cara
{
	public:
		vector <int> index;//Guarda los indices de los vértices para la cara
	public:
		Cara();//Constructor
		void agregaSiguienteVertice(int);//Método que agrega el siguiente vétices
};