#ifndef C_R_TRRE_H
#define C_R_TRRE_H

#include <iostream>
#include <vector>
#include "c_nodo.h"
#include "c_point.h"

using namespace std;


template <class T, int D, int C>//De momento no añadimos ningún parámetro propio del rtree
class c_r_tree{
public:
  c_nodo<T, D, C>* head;
  int tree_records_number;

  c_r_tree();
  ~c_r_tree();

  ///FUNCIONES_PRIMARIAS
  void insert(c_point<T,D>);
  void search(c_point<T,D>);

  ///FUNCIONES SECUNDARIOS pero importantes, no borrar
  int choose_leaf(c_nodo<T,D,C>**, c_point<T, D>); //Nuestro navegante y el punto con el que haremos las comparaciones
    float get_area_affected(c_point<T,D>, c_point<T, D>, c_point<T,D>);//Devuelve el area de una region afectada por un punto externo,
                                                                      //El nuevo punto es el tercer parametro
    void set_area_affected(c_nodo<T,D,C>*, c_point<T,D>);
  //void split_node(c_nodo<T,D,C>**);//Mandaremos el navegante para hacer el split.
  void split_nodo_v2(c_nodo<T,D,C>**);
    void pick_seeds(c_nodo<T,D,C>**, int*, int*);
    void pick_seeds_region(c_nodo<T,D,C>**, int*, int*);
    bool pick_next(c_nodo<T,D,C>*, c_nodo<T,D,C>*, const c_point<T,D>&);
    bool pick_next_region(c_nodo<T,D,C>*, c_nodo<T,D,C>*, c_nodo<T,D,C>*);
    void tree_overview();
};

template<class T, int D, int C>
c_r_tree<T,D,C>::c_r_tree(){
  this->head = NULL;
  this->tree_records_number = 0;
}

template<class T, int D, int C>
c_r_tree<T,D,C>::~c_r_tree(){}


//////////////////////////////FUNCIONES PRIMARIAS//////////////////////////
//NOTAS:
//Cada nuevo nodo, generalmente, se crea con un punto interno el cuál nos permitirá la creación de un
//rectángulo. INDEFINIDO
template<class T, int D, int C>
void c_r_tree<T,D,C>::insert(c_point<T,D> incoming_point){
  bool travel_condition = true;
  int _node_id = 0;
  //Ya no necesitamos un backtrack por medio de listas


  c_nodo<T, D, C>** navegante = &head;
  while(travel_condition){
    if(*navegante == NULL or (*navegante)->is_leaf == true){
      cout<<"CATEDRIAN_1"<<endl;
      travel_condition = false;
      //(*navegante)->node_id = _node_id;
      //Recorremos el arbol hasta llegar a una hoja o si llegamos a un punto vacío.
    }
    else{//AQUI SOLO SE LLEGA SI NO ES UNA HOJA O NO ES EL INICIO, en otras palabras solo cuando la cabeza se llena
        // y se debe buscar la region a la que le corresponde.
      //navegante = &((*navegante)->region[ this->choose_leaf( navegante, incoming_point) ]);
      //Debe ser una funcion que retorne la region(int) a la cual descenderemos.
      cout<<"CATEDRIAN_2"<<endl;
      cout<<"Pasando por la region de limites: "<<(*navegante)->l_d<<"; "<<(*navegante)->u_r<<endl;
      (*navegante)->node_id = _node_id;
      _node_id++;
      navegante = &((*navegante)->region[ (*navegante)->right_leaf(incoming_point) ]);//REEMPLAZO AL choose_leaf, incrustado en el nodo

    }
  }

  if(*navegante == NULL){//En el caso de la cabeza por ejemplo
    cout<<"Creando cabeza con: "<<incoming_point<<endl;
    *navegante = new c_nodo<T, D, C>(incoming_point); //Creamos el nuevo nodo con un punto ya listo
    this->tree_records_number++;
  }
  else{//Significa que estamos en un hoja
      //añadiremos una condicion para evitar punto identicos mas adelante.
      if((*navegante)->add_point(incoming_point)){
        this->tree_records_number++;
        cout<<"Poniendo punto: "<<incoming_point<<endl;
        cout<<"Rango de la region actual"<<(*navegante)->l_d<<"; "<<(*navegante)->u_r<<endl;
        if(!(*navegante)->right_number_of_menbers()){
          cout<<"Se ha producido un SPLIT con "<<incoming_point<<endl;
          //Aca debe haber una funcion de split
          //Esta funcion de split afecta de inversa al arbol por lo que debe ser apropiado
          //del arbol
          this->split_nodo_v2(navegante);
          //this->get_transformation();
        }
      }
  }
  cout<<"Existen "<<this->tree_records_number<<" en el arbol."<<endl;

}


template<class T, int D, int C>
void c_r_tree<T,D,C>::search(c_point<T,D> incoming_point){
  c_nodo<T,D,C>** navegante = &this->head;
  bool travel_condition = true;

  while(travel_condition){
    if(*navegante == NULL or (*navegante)->is_leaf == true){
      travel_condition = false;
      //Recorremos el arbol hasta llegar a una hoja o si llegamos a un punto vacío.
    }
    else{//AQUI SOLO SE LLEGA SI NO ES UNA HOJA O NO ES EL INICIO, en otras palabras solo cuando la cabeza se llena
        // y se debe buscar la region a la que le corresponde.
      //cout<<"Descendiendo a la hoja: "<<this->choose_leaf( navegante, incoming_point)<<endl;
      navegante = &((*navegante)->region[ (*navegante)->right_leaf(incoming_point)  ]);//De momento bajaremos siempre por la region cero
                                              //Debe ser una funcion que retorne la region(int) a la cual descenderemos.
    }
    if(*navegante == NULL){
      cout<<"Arbol vacio, nada que buscar"<<endl;
      return;
    }
    else{
      for(unsigned int i = 0; i < (*navegante)->inner_points.size(); i++){
        if(incoming_point == (*navegante)->inner_points[i]){
          cout<<"Se ha encontrado el punto"<<endl;
          return;
        }
      }
      cout<<"No se ha encontrado el punto"<<endl;
      return;
    }
  }
}


//////////////////////////////FUNCIONES SECUNDARIAS///////////////////////////////
//NOTA: esta funcion me permite ir bajando a la ramas mas inferiores. Deberia ir expandiendo las ramas
//conforme voy escogiendo a cual bajar. Es decir, por ejemplo, si voy a la rama 1 por que en esta el
//area de expansion es la más pequeña y ademas si dicho punto esta fuera de tal rama, entonces la amplio
//y de paso le digo al navegante a cual rama debe bajar. El navegante ya no expandirá dicha rama.

template<class T, int D, int C>//Ya no se usa
int c_r_tree<T,D,C>::choose_leaf(c_nodo<T,D,C>** navegante_interno, c_point<T, D> incoming_point){
  int answer = 0;//Por defecto retornaremos el primer cuadrante.
  float best_area = 0.0;//Acá almacenaremos la mejor area posible.
  float original_area = 0.0;
  float area_with_new_point = 0.0;

  for(unsigned int i = 0; i < (*navegante_interno)->region.size();  i++){//Recorremos todas la regiones hijas                                                                      //a las que podemos acceder
    original_area = area_n_dimension((*navegante_interno)->region[i]->l_d, (*navegante_interno)->region[i]->u_r);
    area_with_new_point = this->get_area_affected((*navegante_interno)->region[i]->l_d, (*navegante_interno)->region[i]->u_r, incoming_point);
    //El area afectada debe ser mas grande que el area original
    area_with_new_point = area_with_new_point - original_area;//Sacamos la diferencia entre ambos rectangulos
    if(best_area >= area_with_new_point){
      best_area = area_with_new_point;
      answer = i;//Igualamos la respuesta a la region que menos se ampliará.
    }
  }

  //Una vez encontrada la mejor area debemos ampliarla para que dicho punto sea parte de la nueva area.
  //Usada seguidamente esta funcion ampliara todas los rectangulos por donde pase.
  this->set_area_affected((*navegante_interno)->region[answer], incoming_point);
  return answer;
}

//Calculamos el tamaño de un area afectada por un punto externo
template<class T, int D, int C>
float c_r_tree<T,D,C>::get_area_affected(c_point<T, D> _l_d, c_point<T,D> _u_r, c_point<T, D> incoming_point){
  for(unsigned int i = 0; i < D; i++){
    if(_l_d.p_data[i] > incoming_point.p_data[i]){
      _l_d.p_data[i] = incoming_point.p_data[i];
    }
    if(_u_r.p_data[i] < incoming_point.p_data[i]){
      _u_r.p_data[i] = incoming_point.p_data[i];
    }
  }

  return area_n_dimension(_l_d, _u_r);
}

template<class T, int D, int C>//Ya no se usa
void c_r_tree<T,D,C>::set_area_affected(c_nodo<T,D,C>* chariot, c_point<T,D> incoming_point){
  for(unsigned int i = 0; i < D; i++){
      if(chariot->l_d.p_data[i] > incoming_point.p_data[i]){
        chariot->l_d.p_data[i] = incoming_point.p_data[i];
      }
      if(chariot->u_r.p_data[i] < incoming_point.p_data[i]){
        chariot->u_r.p_data[i] = incoming_point.p_data[i];
      }
  }
}


template <class T, int D, int C>
void c_r_tree<T,D,C>::split_nodo_v2(c_nodo<T,D,C>** navegante_interno){
//Existe un split para las regiones y otros para los nodos con datos.
//rect.clear();
//profundidad.clear();
  if((*navegante_interno)->is_leaf){
    cout<<"Segmentando hoja"<<endl;
    int index_for_seed_1 = 0;
    int index_for_seed_2 = 0;
    (*navegante_interno)->nodo_select_picks(&index_for_seed_1, &index_for_seed_2);
    c_nodo<T,D,C>* new_region_1 = new c_nodo<T,D,C> ((*navegante_interno)->inner_points[index_for_seed_1]);
    c_nodo<T,D,C>* new_region_2 = new c_nodo<T,D,C> ((*navegante_interno)->inner_points[index_for_seed_2]);
    //Retornara la posicion en el array de puntos de los dos mas distantes en teoria,
    //index_for_seed_1 equivale al l_d y index_for_seed_2 equivale al u_r
    //Nos deshacemos de las semilla en el punto.ISSUES
    if(index_for_seed_1 < index_for_seed_2){
      (*navegante_interno)->inner_points.erase((*navegante_interno)->inner_points.begin() + index_for_seed_1);
      (*navegante_interno)->inner_points.erase((*navegante_interno)->inner_points.begin() + index_for_seed_2 -1);
    }
    else{
      (*navegante_interno)->inner_points.erase((*navegante_interno)->inner_points.begin() + index_for_seed_2);
      (*navegante_interno)->inner_points.erase((*navegante_interno)->inner_points.begin() + index_for_seed_1 -1);
    }

    for(unsigned int i = 0; i < (*navegante_interno)->inner_points.size(); i++){
      if(this->pick_next(new_region_1, new_region_2, (*navegante_interno)->inner_points[i])){
        new_region_2->add_point((*navegante_interno)->inner_points[i]);
      }
      else{
        new_region_1->add_point((*navegante_interno)->inner_points[i]);
      }
    }

    cout<<"Split: "<<endl;
    cout<<"Region deshecha: "<<(*navegante_interno)->l_d<<" ; "<<(*navegante_interno)->u_r<<endl;
    cout<<"Nuevas regiones: 1-> "<<new_region_1->l_d<<" ; "<<new_region_1->u_r<<" con "<<new_region_1->inner_points.size()<<" puntos."<<" Is leaf: "<<new_region_1->is_leaf<<endl;
    cout<<"PUNTOS:"<<endl;
    for(unsigned int i = 0; i < new_region_1->inner_points.size(); i++){
      cout<<new_region_1->inner_points[i]<<" ";
    }
    cout<<endl;
    cout<<"Nuevas regiones: 2-> "<<new_region_2->l_d<<" ; "<<new_region_2->u_r<<" con "<<new_region_2->inner_points.size()<<" puntos."<<" Is leaf: "<<new_region_2->is_leaf<<endl;
    cout<<"PUNTOS:"<<endl;
    for(unsigned int i = 0; i < new_region_2->inner_points.size(); i++){
      cout<<new_region_2->inner_points[i]<<" ";
    }
    cout<<endl;

    //La cabeza hace split una vez en toda su vida cuando se trata de puntos
    if(*navegante_interno == this->head){
      (*navegante_interno)->inner_points.clear();//Vaciamos nuestro nodo actual.
      (*navegante_interno)->is_leaf = false;//Ahora solo somos un nodo de paso.
      //Disponemos las regiones creadas acorde al tipo nodo con el que tratamos
      //El padre ya no volvera a almacenar puntos
      new_region_1->dad = *navegante_interno;//El contenido del navegante es un puntero que apunta al nodo de origen.
      new_region_2->dad = *navegante_interno;//       "       "
      (*navegante_interno)->add_region(new_region_1);
      (*navegante_interno)->add_region(new_region_2);
      //No hay necesidad de ver un desborde de regiones en la raiz, es su primera división.
    }
    else{
      c_nodo<T,D,C>* padre = (*navegante_interno)->dad;//Es el padre del nodo al que apunta el puntero contenido puntero
      new_region_1->dad = padre;
      new_region_2->dad = padre;

      for(unsigned int i = 0; i < padre->region.size(); i++){
        if(padre->region[i] == (*navegante_interno)){
          padre->region.erase(padre->region.begin() + i); //Nos deshacemos de la region que dividimos. Ahora navegante_interno es el unico que apunta a algo inexistente
        }
      }

      delete (*navegante_interno);//Borramos el nodo que se dividio. Ahora navegante_interno esta en NULL;
      padre->add_region(new_region_1);
      padre->add_region(new_region_2);

      //if(! padre->right_number_of_regions){
        //this->split_nodo_v2(&padre);
      //}
      cout<<"Segmentacion de hoja finalizadas"<<endl;

      bool adjust_tree = true;
      while(adjust_tree and padre){
        if(! padre->right_number_of_regions()){
          adjust_tree = false;
        }
        else{
          padre = padre->dad;
        }
      }

      if(!adjust_tree){
        this->split_nodo_v2(&padre);
      }
      else{return;}
    }
  }
  else{
    //Entramos acá si existe un desborde en el numero de regiones almacenadas en una region.
    cout<<"Segmentando region"<<endl;
    int index_for_seed_1 = 0;
    int index_for_seed_2 = 0;
    (*navegante_interno)->nodo_select_picks_region(&index_for_seed_1, &index_for_seed_2);
    c_nodo<T,D,C>* new_region_1 = new c_nodo<T,D,C>((*navegante_interno)->region[index_for_seed_1]->l_d, (*navegante_interno)->region[index_for_seed_1]->u_r);//ISSUES: Mejorar se van a examinar rangos estupidos
    cout<<"PUNTOS: "<<endl;
    for(unsigned int i = 0; i < new_region_1->inner_points.size(); i++){
      cout<<new_region_1->inner_points[i]<<" ";
    }
    cout<<endl;
    cout<<"REGIONES: "<<endl;
    for(unsigned int i = 0; i < new_region_1->region.size(); i++){
      cout<<new_region_1->region[i]->l_d<<" - "<<new_region_1->region[i]->u_r<<" ";
    }
    cout<<endl;
    c_nodo<T,D,C>* new_region_2 = new c_nodo<T,D,C>((*navegante_interno)->region[index_for_seed_2]->l_d, (*navegante_interno)->region[index_for_seed_2]->u_r);
    cout<<"PUNTOS: "<<endl;
    for(unsigned int i = 0; i < new_region_2->inner_points.size(); i++){
      cout<<new_region_2->inner_points[i]<<" ";
    }
    cout<<endl;
    cout<<"REGIONES: "<<endl;
    for(unsigned int i = 0; i < new_region_2->region.size(); i++){
      cout<<new_region_2->region[i]->l_d<<" - "<<new_region_2->region[i]->u_r<<" ";
    }
    cout<<endl;
    //new_region_1->is_leaf = false;
    //new_region_2->is_leaf = false;
    //Nos deshacemos de las regiones que actuaron como semillas para la segmentacion
    if(index_for_seed_1 < index_for_seed_2){
      (*navegante_interno)->region.erase((*navegante_interno)->region.begin() + index_for_seed_1);
      (*navegante_interno)->region.erase((*navegante_interno)->region.begin() + index_for_seed_2 -1);
    }
    else{
      (*navegante_interno)->region.erase((*navegante_interno)->region.begin() + index_for_seed_2);
      (*navegante_interno)->region.erase((*navegante_interno)->region.begin() + index_for_seed_1 -1);
    }
    //Procedemos a repartir las demás regiones en base a las semillas obtenidas
    for(unsigned int i = 0; i < (*navegante_interno)->region.size(); i++){
      if(this->pick_next_region(new_region_1, new_region_2, (*navegante_interno)->region[i])){
        new_region_2->add_region((*navegante_interno)->region[i], true);
      }
      else{
        new_region_1->add_region((*navegante_interno)->region[i], true);
      }
    }

    cout<<"Split de regiones: "<<endl;
    cout<<"Region deshecha: "<<(*navegante_interno)->l_d<<" ; "<<(*navegante_interno)->u_r<<endl;
    cout<<"Nuevas regiones: 1-> "<<new_region_1->l_d<<" ; "<<new_region_1->u_r<<" con "<<new_region_1->region.size()<<" regiones."<<" Is leaf: "<<new_region_1->is_leaf<<endl;
    cout<<"Nuevas regiones: 2-> "<<new_region_2->l_d<<" ; "<<new_region_2->u_r<<" con "<<new_region_2->region.size()<<" regiones."<<" Is leaf: "<<new_region_2->is_leaf<<endl;

    if(*navegante_interno == this->head){
      (*navegante_interno)->region.clear();//Somos una cabeza que nos vamos a dividir
      new_region_1->dad = *navegante_interno;//Este nodo de paso ahora apunta a su origen.
      new_region_2->dad = *navegante_interno;
      (*navegante_interno)->add_region(new_region_1, true);//ISSUES
      (*navegante_interno)->add_region(new_region_2, true);
    }
    else{
      c_nodo<T,D,C>* padre = (*navegante_interno)->dad;
      new_region_1->dad = padre;
      new_region_2->dad = padre;
      for(unsigned int i = 0; i < padre->region.size(); i++){
        if(padre->region[i] == (*navegante_interno)){
          padre->region.erase(padre->region.begin()+ i);
        }
      }
      delete (*navegante_interno);//Borramos el nodo que se dividio. Ahora navegante_interno esta en NULL;
      padre->add_region(new_region_1);
      padre->add_region(new_region_2);

      //if(! padre->right_number_of_regions){
        //this->split_nodo_v2(&padre);
      //}
      cout<<"Segmentacion de region finalizada"<<endl;
      bool adjust_tree = true;
      while(adjust_tree and padre){
        if(! padre->right_number_of_regions()){
          adjust_tree = false;
        }
        else{
          padre = padre->dad;
        }
      }

      if(!adjust_tree){
        this->split_nodo_v2(&padre);
      }
      else{return;}
    }
  }
}
//SPLIT NODE solo funcionará con los nodos que contengan como minimo dos datos
//SPLIT NODE dividirá dicho nodo en DOS segmentos
//Creo que aquí tambien haremos
/*
template<class T, int D, int C>
void c_r_tree<T,D,C>::split_node(c_nodo<T,D,C>** navegante_interno){
  //El ultimo dato del backtrack es mi navegante interno.
  if((*navegante_interno)->is_leaf){ //TODA ESTA SEGMENTACION ES SI NUESTRO NODO ES UNA HOJA
    cout<<"Split node hoja"<<endl;
    int index_for_seed_1 = 0;//DEFAULT
    int index_for_seed_2 = 0;//DEFAULT
    this->pick_seeds(navegante_interno, &index_for_seed_1, &index_for_seed_2);//Obtenemos las semillas con las que vamos a trabajar.
    c_nodo<T,D,C>* new_region_1 = new c_nodo<T,D,C>((*navegante_interno)->inner_points[index_for_seed_1]);//Creamos las nuevas regiones con los puntos
    c_nodo<T,D,C>* new_region_2 = new c_nodo<T,D,C>((*navegante_interno)->inner_points[index_for_seed_2]);//Creamos las nuevas regiones con los puntos
    cout<<"Nuevas regiones 1 con rangos l_d: "<<new_region_1->l_d<<" u_r: "<<new_region_1->u_r<<endl;
    cout<<"Nuevas regiones 2 con rangos l_d: "<<new_region_2->l_d<<" u_r: "<<new_region_2->u_r<<endl;

    //El indexado de la semilla 1 esta siempre por delante del indexado de la semilla 2
    (*navegante_interno)->inner_points.erase((*navegante_interno)->inner_points.begin() + index_for_seed_1);
    (*navegante_interno)->inner_points.erase((*navegante_interno)->inner_points.begin() + index_for_seed_2 - 1);

    //Ahora procederemos a asignar a los puntos restantes.
    for(unsigned int i = 0; i < (*navegante_interno)->inner_points.size(); i++){
      if(this->pick_next(new_region_1, new_region_2, (*navegante_interno)->inner_points[i])){
        new_region_2->add_point((*navegante_interno)->inner_points[i]);
      }
      else{
        new_region_1->add_point((*navegante_interno)->inner_points[i]);
      }
    }

    cout<<"Region 1 finalizados con rangos l_d: "<<new_region_1->l_d<<" u_r: "<<new_region_1->u_r<<endl;
    cout<<"Region 2 finalizados con rangos l_d: "<<new_region_2->l_d<<" u_r: "<<new_region_2->u_r<<endl;

    if(backtrack.empty()){//Si el backtrack esta vacio es que tratamos con el padre
      (*navegante_interno)->is_leaf = false;
      (*navegante_interno)->inner_points.clear();//Vaciamos la hoja
      //Finalizamos de repartir el resto de punto entre las nuevas regiones.

      (*navegante_interno)->add_region(new_region_1);
      (*navegante_interno)->add_region(new_region_2);
      //(*navegante_interno)->region.push_back(new_region_1);//Añadimos las dos nuevas regiones al padre
      //(*navegante_interno)->region.push_back(new_region_2);//Añadimos las dos nuevas regiones al padre

      //Si a al raiz le llega la hora de dividirse
      if(!(*navegante_interno)->right_number_of_regions()){
        this->split_node(navegante_interno, backtrack);//Dividiremos ahora la raiz pero como rama ya no como hoja
      }
      else{
        return;
      }
    }
    else{
      //Si aun existen datos en el backtrack, eliminamos la rama en donde se produjo el split y añadimos sus ramas consecuentes
      // a la lista de regiones de su padre.
      for(unsigned int i = 0; i < (backtrack.back())->region.size(); i++){
        if((backtrack.back())->region[i] == *navegante_interno){
          (backtrack.back())->region.erase((backtrack.back())->region.begin()+i);
          i = (backtrack.back())->region.size();
        }
      }

      (backtrack.back())->add_region(new_region_1);
      (backtrack.back())->add_region(new_region_2);
      if(! (backtrack.back())->right_number_of_regions()){
        this->split_node(&(backtrack.back()), backtrack);
      }
      else{
        return;
      }
    }
  }
  else{//Split para un nodo
    int index_for_seed_1 = 0;//DEFAULT
    int index_for_seed_2 = 0;//DEFAULT
    this->pick_seeds_region(navegante_interno, &index_for_seed_1, &index_for_seed_2);//Obtenemos las semillas con las que vamos a trabajar.
    //c_nodo<T,D,C>* new_region_1 = new c_nodo<T,D,C>((*navegante_interno)->inner_points[index_for_seed_1]);//Creamos las nuevas regiones con los puntos
    //c_nodo<T,D,C>* new_region_2 = new c_nodo<T,D,C>((*navegante_interno)->inner_points[index_for_seed_2]);//Creamos las nuevas regiones con los puntos
    c_nodo<T,D,C>* new_region_1 = new c_nodo<T,D,C>((*navegante_interno)->region[index_for_seed_1]->l_d, (*navegante_interno)->region[index_for_seed_1]->u_r);//Creamos las nuevas regiones con los puntos
    c_nodo<T,D,C>* new_region_2 = new c_nodo<T,D,C>((*navegante_interno)->region[index_for_seed_2]->l_d, (*navegante_interno)->region[index_for_seed_2]->u_r);//Creamos las nuevas regiones con los puntos
    new_region_1->is_leaf = false;
    new_region_2->is_leaf = false;

    (*navegante_interno)->region.erase((*navegante_interno)->region.begin() + index_for_seed_1);
    if(index_for_seed_1 > index_for_seed_2){
      (*navegante_interno)->region.erase((*navegante_interno)->region.begin() + index_for_seed_2);
    }
    else{
      (*navegante_interno)->region.erase((*navegante_interno)->region.begin() + index_for_seed_2 - 1);
    }
    //Ahora procederemos a asignar a los puntos restantes.

    for(unsigned int i = 0; i < (*navegante_interno)->region.size(); i++){
      if(this->pick_next_region(new_region_1, new_region_2, (*navegante_interno)->region[i])){
        //new_region_2->add_point((*navegante_interno)->inner_points[i]);
        new_region_2->add_region((*navegante_interno)->region[i]);
      }
      else{
        //new_region_1->add_point((*navegante_interno)->inner_points[i]);
        new_region_1->add_region((*navegante_interno)->region[i]);
      }
    }

    if(backtrack.empty()){//Tratamos con la raiz
          (*navegante_interno)->is_leaf = false;//Sabes que antes ha sido rama.
          (*navegante_interno)->region.clear(); //Limpiamos las regiones anteriores
          (*navegante_interno)->add_region(new_region_1);//Añadimos las regiones que acabamos de crear.
          (*navegante_interno)->add_region(new_region_2);//Añadimos las regiones que acabamos de crear.
          if(!((*navegante_interno)->right_number_of_regions())){
            split_node(navegante_interno, backtrack);
          }
          else{
            return;
          }
    }
    else{
      for(unsigned int i = 0; i < (backtrack.back())->region.size(); i++){
        if((backtrack.back())->region[i] == *navegante_interno){
          (backtrack.back())->region.erase((backtrack.back())->region.begin()+i);
          i = (backtrack.back())->region.size();
        }
      }

      (backtrack.back())->add_region(new_region_1);
      (backtrack.back())->add_region(new_region_2);

      if(! (backtrack.back())->right_number_of_regions()){
        this->split_node(&(backtrack.back()), backtrack);
      }
      else{
        return;
      }
    }
  }
}
*/

//Trabajaremos con los inner points de este nodo para conseguir los nodos que me consigan el mejor split posible.
//Recordar que el dato que causo el overflow tambien esta considerado en el split ypor la tanto en la seleccion de semillas
//Para evitartanto refernecias a memoria, lo unico que manejare seran enteros que me digan en que psocion del vector de puntos se encuentran
//los datos que actuarán como semillas, asi cuando proceda a añadir a los demás los evitaré.
template<class T, int D, int C>
void c_r_tree<T,D,C>::pick_seeds(c_nodo<T,D,C>** navegante_interno, int* seed_1, int* seed_2){//Only works for nodes with numbers.
  *seed_1 = 0;
  *seed_2 = 1;
  float area_base = area_n_dimension((*navegante_interno)->l_d, (*navegante_interno)->u_r);//Sacamos el area para restar con las demás
  //float changed_area = area_n_dimension((*navegante_interno)->inner_points[seed_1], (*navegante_interno)->inner_points[seed_2]);
  //float minimun_area = area_base - changed_area; // mayor a cero
  float changed_area = 0;
  float minimun_area = 0;
  //Todos estos puntos están dentro de la region
  //Estamos buscando el area que desperdicie mas espacio
  //Comportamiento cuadratico por que recorrera dos veces la columnas de los puntos
  //for(unsigned int i = 0; i < (*navegante_interno)->inner_points.size()-1; i++){//Recorremos los puntos de dicho nodo
    //for(unsigned int j = i+1; j < (*navegante_interno)->inner_points.size(); j++){
  for(unsigned int i = 0; i < (*navegante_interno)->inner_points.size(); i++){//Recorremos los puntos de dicho nodo
    for(unsigned int j = 0; j < (*navegante_interno)->inner_points.size(); j++){
      changed_area = area_n_dimension((*navegante_interno)->inner_points[i], (*navegante_interno)->inner_points[j]);
      if((area_base - changed_area) >= minimun_area){
        *seed_1 = i;
        *seed_2 = j;
        minimun_area = area_base - changed_area;
      }
    }
  }
}

template<class T, int D, int C>
void c_r_tree<T,D,C>::pick_seeds_region(c_nodo<T,D,C>** navegante_interno, int* seed_1, int* seed_2){//Only works for nodes with numbers.
  *seed_1 = 0;
  *seed_2 = 1;
  float area_base = area_n_dimension((*navegante_interno)->l_d, (*navegante_interno)->u_r);//Sacamos el area para restar con las demás
  //float changed_area = area_n_dimension((*navegante_interno)->inner_points[seed_1], (*navegante_interno)->inner_points[seed_2]);
  //float minimun_area = area_base - changed_area; // mayor a cero
  float changed_area = 0;
  float minimun_area = 0;
  //Todos estos puntos están dentro de la region
  //Estamos buscando el area que desperdicie mas espacio
  //Comportamiento cuadratico por que recorrera dos veces la columnas de los puntos
  //Cambiado porque las ramas ya no tienen puntos que comparar
  for(unsigned int i = 0; i < (*navegante_interno)->region.size(); i++){
    for(unsigned int j = 0; j < (*navegante_interno)->region.size(); j++){
      //changed_area = area_n_dimension((*navegante_interno)->inner_points[i], (*navegante_interno)->inner_points[j]);
      //ahora los puntos medios decada region para marcarlos como referencia.
      changed_area = area_n_dimension((*navegante_interno)->region[i]->l_d, (*navegante_interno)->region[j]->u_r);
      if((area_base - changed_area) >= minimun_area){
        *seed_1 = i;
        *seed_2 = j;
        minimun_area = area_base - changed_area;
      }
    }
  }
}


/*
template<class T, int D, int C>
bool c_r_tree<T,D,C>::pick_next(c_nodo<T,D,C>* new_region_1, c_nodo<T,D,C>* new_region_2, c_point<T,D> incoming_point){
    float area_total_1 = area_n_dimension(new_region_1->l_d, new_region_1->u_r);//Conseguimos las nuevas areas
    float area_total_2 = area_n_dimension(new_region_2->l_d, new_region_2->u_r);//Conseguimos las nuevas areas
    float area_affected_1 = get_area_affected(new_region_1->l_d, new_region_1->u_r, incoming_point);
    float area_affected_2 = get_area_affected(new_region_2->l_d, new_region_2->u_r, incoming_point);
    area_total_1 = area_affected_1 - area_total_1; //El area con el nuevo punto debe ser mas grande que el area original
    area_total_2 = area_affected_2 - area_total_2;
    if(area_total_1 < area_total_2){
      return false;//0 para la region uno
    }
    else{
      return true;//1 para la region dos
    }
}
*/
//IMPROVED VERSION OF PICK_NEXT
template<class T, int D, int C>
bool c_r_tree<T,D,C>::pick_next(c_nodo<T,D,C>* region_1, c_nodo<T,D,C>* region_2, const c_point<T, D>& incoming_point){
  float area_1 = region_1->nodo_get_affected_area(incoming_point) - region_1->nodo_get_area();
  float area_2 = region_2->nodo_get_affected_area(incoming_point) - region_2->nodo_get_area();
  //Constatación de errores
  if((area_1 < 0 or (area_2 < 0))){
    cout<<"Oye en pick next una de las restas salio a negativa, ven a ver"<<endl;
  }

  if(area_1 < area_2){
    return false;//0 para la region 1
  }
  else{
    return true;//1 para la region 2
  }

}

/*No es la implementacion correcta.
template<class T, int D, int C>
bool c_r_tree<T,D,C>::pick_next_region(c_nodo<T,D,C>* new_region_1, c_nodo<T,D,C>* new_region_2, c_nodo<T,D,C>* incoming_region){
  float area_affected_1 = area_n_dimension(new_region_1->get_middle_point(), incoming_region->get_middle_point());
  float area_affected_2 = area_n_dimension(new_region_2->get_middle_point(), incoming_region->get_middle_point());
  if(area_affected_1 < area_affected_2){
    return false;//0 para la region uno
  }
  else{
    return true;//1 para la region dos
  }
}
*/

template <class T, int D, int C>
bool c_r_tree<T,D,C>::pick_next_region(c_nodo<T,D,C>* region_1, c_nodo<T,D,C>* region_2, c_nodo<T,D,C>* incoming_region){
  float area_1 = region_1->nodo_get_affected_area_by_region(*incoming_region) - region_1->nodo_get_area();
  float area_2 = region_2->nodo_get_affected_area_by_region(*incoming_region) - region_2->nodo_get_area();
  //Constatación de errores
  if((area_1 < 0 or (area_2 < 0))){
    cout<<"Oye en pick next region una de las restas salio a negativa, ven a ver"<<endl;
  }

  if(area_1 < area_2){
    return false;//0 para la region 1
  }
  else{
    return true;//1 para la region 2
  }
}

template <class T, int D, int C>
void c_r_tree<T,D,C>::tree_overview(){
  vector< c_nodo<T,D,C>* > stack;
  stack.push_back(this->head);
  while(!stack.empty()){
      for(unsigned int i = 0; i < stack[0]->region.size(); i++){
        stack.push_back(stack[0]->region[i]);
      }
      stack[0]->print_nodo();
      cout<<endl;
      stack.erase(stack.begin());
  }
}


#endif
