#include <iostream>
#include <vector>

using namespace std;

class Cara
{
	public:
		vector <int> index;//Guarda los indices de los v�rtices para la cara
	public:
		Cara();//Constructor
		void agregaSiguienteVertice(int);//M�todo que agrega el siguiente v�tices
};