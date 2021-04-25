 /*
 *  GRAFO.CPP - Plantilla para la implementaci�n de la clase GRAFOS
 *
 *
 *  Autores : Antonio Sedeno Noda, Sergio Alonso
 *  Cursos   : 2012-2021
 */

#include "grafo.h"

void GRAFO :: destroy() {
	for (unsigned i=0; i< n; i++)
    {
		LS[i].clear();
		//A[i].clear();
		if (dirigido == 1)
        {
            LP[i].clear();
        };
	}
	LS.clear();
	LP.clear();
	//A.clear();

}

void GRAFO :: build (char nombrefichero[85], int &errorapertura) {
  ElementoLista  dummy;
  ifstream textfile;
  textfile.open(nombrefichero);
    if (textfile.is_open()) {
      errorapertura = 0;
      unsigned i, j, k;
      // leemos por conversion implicita el numero de nodos, arcos y el atributo dirigido
      textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;
      // los nodos internamente se numeran desde 0 a n-1
      // creamos las n listas de sucesores
      LS.resize(n);
      // leemos los m arcos
      for (k=0;k<m;k++) {
        textfile >> (unsigned &) i  >> (unsigned &) j >> (int &) dummy.c; //damos los valores a dummy.j y dummy.c
        if(Es_dirigido() == 1) {         //1 o true (ya que es un booleano)
          LP.resize(n);               //Redimensionamos LP
          dummy.j =  j - 1;     
          LS[i-1].push_back(dummy); //situamos en la posici�n del nodo i a dummy mediante push_back
          dummy.j =  i - 1;
          LP[j-1].push_back(dummy); //pendiente de hacer un segundo push_back si es no dirigido. O no.
        }else {
          if(Es_dirigido() == 0) {       //0 o false (ya que es un booleano)
          dummy.j = i-1;     //dummy.j = i
          LS[j-1].push_back(dummy);
          if(i!= j){
          dummy.j = j-1;
          LS[i-1].push_back(dummy);
          }
        } else {                  //Si no es ninguna exit para evitar fallos (aunque al ser boleano no es necesario)
            exit;
        }
      }
    }
  } else {
    errorapertura = 1;                //pendiente del valor a devolver en errorapertura            ...
  }		
}

void GRAFO::ListaPredecesores() {

}

GRAFO::~GRAFO() {
	destroy();
}

GRAFO::GRAFO(char nombrefichero[85], int &errorapertura) {
	build (nombrefichero, errorapertura);
}

void GRAFO:: actualizar (char nombrefichero[85], int &errorapertura)
{
    //Limpiamos la memoria dinamica asumida en la carga previa, como el destructor
    destroy();
    //Leemos del fichero y actualizamos G con nuevas LS y, en su caso, LP
    build(nombrefichero, errorapertura);
}

unsigned GRAFO::Es_dirigido()
{

}

void GRAFO::Info_Grafo()
{

}

void Mostrar_Lista(vector<LA_nodo> L)
{

}

void GRAFO :: Mostrar_Listas (int l)
{

}

void GRAFO::Mostrar_Matriz() //Muestra la matriz de adyacencia, tanto los nodos adyacentes como sus costes
{

}

void GRAFO::dfs_num(unsigned i, vector<LA_nodo>  L, vector<bool> &visitado, vector<unsigned> &prenum, unsigned &prenum_ind, vector<unsigned> &postnum, unsigned &postnum_ind) {//Recorrido en profundidad recursivo con recorridos enum y postnum

	visitado[i] = true;
    prenum[prenum_ind++]=i;//asignamos el orden de visita prenum que corresponde el nodo i
    for (unsigned j=0;j<L[i].size();j++)
             if (!visitado[L[i][j].j])
                {
                dfs_num(L[i][j].j, L, visitado, prenum, prenum_ind, postnum, postnum_ind);
                };
    postnum[postnum_ind++]=i;//asignamos el orden de visita posnum que corresponde al nodo i
}

void GRAFO::RecorridoProfundidad()
{

}

void GRAFO::bfs_num(	unsigned i, //nodo desde el que realizamos el recorrido en amplitud
				vector<LA_nodo>  L, //lista que recorremos, LS o LP; por defecto LS
				vector<unsigned> &pred, //vector de predecesores en el recorrido
				vector<unsigned> &d) {//vector de distancias a nodo i+1
//Recorrido en amplitud con la construcci�n de pred y d: usamos la cola

    vector<bool> visitado; //creamos e iniciamos el vector visitado
    visitado.resize(n, false);  
    visitado[i-1] = true;
 
    pred.resize(n, 0); //creamos e inicializamos pred y d
    d.resize(n, 0);
    pred[i-1] = i;
    d[i-1] = 0;

    queue<unsigned> cola; //creamos e inicializamos la cola
    cola.push(i);//iniciamos el recorrido desde el nodo i+1
    bool ajuste_desfase = true;
    while (!cola.empty()) { //al menos entra una vez al visitar el nodo i+1 y contin�a hasta que la cola se vac�e
      unsigned k = cola.front(); //cogemos el nodo k+1 de la cola
      cola.pop(); //lo sacamos de la cola
        //Hacemos el recorrido sobre L desde el nodo k+1
      if (ajuste_desfase == true) {
        ajuste_desfase = false;
        k = k - 1;
      }
      for (unsigned h=0;h<L[k].size();h++) {
          //Recorremos todos los nodos u adyacentes al nodo k+1
          //Si el nodo u no est� visitado
        unsigned nodo = L[k][h].j;
        if(visitado[nodo] == false) {    //Si el nodo u no est� visitado
          visitado[nodo] = true;         //Lo visitamos
          cola.push(nodo);               //Lo metemos en la cola
          pred[nodo] = k;                //le asignamos el predecesor
          d[nodo] = d[k]+1;              //le calculamos su etiqueta distancia
      }
      };
        //Hemos terminado pues la cola est� vac�a
    };
}

void GRAFO::RecorridoAmplitud() { //Construye un recorrido en amplitud desde un nodo inicial
  unsigned int i;
  vector<LA_nodo> L(LS);
  vector<unsigned> pred;
  vector<unsigned> d;
  std::cout << "Vamos a construir un recorrido en amplitud" << std::endl;
  std::cout << "Elija nodo de partida [1 - " << n << "]: ";
  std::cin >> i;
  if (i <= 0) {
    std::cerr << "Error: nodo ingresado no válido." << std::endl;
    exit(EXIT_SUCCESS);
  }
  bfs_num(i,L,pred,d);
  for (unsigned int t{0}; t < d.size(); ++t) {
    std::cout << "Distancia " << t << " aristas";
    for (unsigned int h{0}; h < d.size();++h) {
      if(d[h] == t) std::cout << " : " << d[h];
    }
  }

}