#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <windows.h>
#include <math.h>
#include <vector>
#include <GL/glut.h>
#include "c_r_tree.h"
#include "c_point.h" //Alllows me to interact with points of n dimensions
#include "c_nodo.h"
#include <ctime>
#include <fstream>

//CREATED BY jose david mamani vilca. jose.mamani.vilca@ucsp.edu.pe
#define KEY_ESC 27
using namespace std;

c_r_tree<float, 2, 3> arbol;
vector< c_point<float, 2> > data_point;
vector< c_nodo<float, 2, 3> > rect;//ESTOS DOS VAN DE LA MANO
vector< int > profundidad;
vector<float > data_late;

//inicializacion de OpenGL
void init_GL(void);
void glPaint(void);
void OnMouseClick(int, int, int, int);
void OnMouseMotion(int, int);
void idle();
//MINE
void translate_points(float& ,float& );
void graficar_rectangulos();
void graficar_rectangulos_v2();
void graficar_puntos();
void set_new_color(vector<float>&);
void imprimir_paleta(vector<float>);
void read_document();
//en el caso que la ventana cambie de tama�o
GLvoid window_redraw(GLsizei, GLsizei);
GLvoid window_key(unsigned char, int, int);

int main(int argc, char** argv){

  char answer;
	cout<<"Document loader: (Y/N)"<<endl;
	cin>>answer;

	if(answer == 'Y' or answer == 'y'){
		read_document();
	}

  //Inicializacion de la GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1365, 700); //tama�o de la ventana
	glutInitWindowPosition(0, 0); //posicion de la ventana
	glutCreateWindow("R-Tree Simulation"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);

	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
  glutIdleFunc(&idle);

  glutMainLoop(); //bucle de rendering

  return 0;
}

void read_document(){
	float point_x, point_y;//Local store for coming data.
	char txt_name[20];//Nombre con el archivo de puntos
	//vector<float> x_list;
	//vector<float> y_list;

	cout<<"Nombre del Archivo: "<<endl;
	cin>>txt_name;

	fstream reader(txt_name, ios::in);

	//reader >> point_x; max_x = point_x; min_x = point_x;// main configurations
	//reader >> point_y; max_y = point_y; min_y = point_y;//
	//coming_counter++;
	while(reader >> point_x and reader >> point_y){
    data_late.push_back(point_x);
    data_late.push_back(point_y);
	}

  cout<<"The document reading process has ended. Drawing a window, next to it, points will be inserted."<<endl;
	cin>>txt_name;
}


void add_late_points(void){
	if(!data_late.empty()){
		for(unsigned int i = 0; i < data_late.size(); i+=2){
			float _x = data_late[i]; float _y = data_late[i+1];
      cout<<_x<<"  "<<_y<<endl;
      //translate_points(_x, _y);
      vector<float> v_tempo;
      v_tempo.push_back(_x);
      v_tempo.push_back(_y);
      //translate_points(_x, _y);
      c_point<float, 2> p_tempo(v_tempo);
			data_point.push_back(p_tempo);
			arbol.insert(p_tempo);
		}
		data_late.clear();
    arbol.get_transformation();
	}
}


void init_GL(void) {
	//Color del fondo de la escena
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	//glClearColor(255, 255, 255, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void translate_points(float& a, float& b){//Adapt incoming data to the new format needed in our map
	a = a / ( (float)glutGet(GLUT_WINDOW_WIDTH)/100.0f);
	b = ( (float)glutGet(GLUT_WINDOW_HEIGHT) - b ) / ( (float)glutGet(GLUT_WINDOW_HEIGHT) / 100.0f);
}

void graficar_rectangulos(){
  cout<<"Pintando"<<endl;
  glBegin(GL_POLYGON);
  glColor3d(0.1,0,0);
  glVertex2f(0.0f, 0.0f);
  glVertex2f(0.0f, 50.0f);
  glVertex2f(75.0f, 75.0f);
  glVertex2f(50.0f, 50.0f);
  glVertex2f(50.0f, 0.0f);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3d(1.4,1.4,1.4);
  glVertex2f(0.0f, 0.0f);
  glVertex2f(0.0f, 60.0f);
  glVertex2f(60.0f, 60.0f);
  glVertex2f(60.0f, 0.0f);
  glEnd();
}

void set_new_color(vector<float>& incoming){
  int grade = rand()%3;
  incoming[grade] = (rand()%10 + 1) / 10;
}

void imprimir_paleta(vector<float> incoming){
  for(unsigned int i = 0; i < incoming.size(); i++){
    cout<<incoming[i]<<" ";
  }
  cout<<endl;
}

void graficar_rectangulos_v2(){
  //cout<<"Pintando..."<<endl;
  int color = 0;
  //float paleta = 0.1;
  vector<float> paleta(3, 0.0f);
  paleta[0] = 0.0f;
  paleta[1] = 0.4f;
  paleta[2] = 0.0f;
  //set_new_color(paleta);
  //imprimir_paleta(paleta);
  //arbol.get_transformation();
  //cout<<"Transformada obtenida"<<endl;
  for(unsigned int i = 0; i < rect.size(); i++){
    if(color != profundidad[i]){
      color = profundidad[i];
      paleta[(color%3)] = ( (paleta[color%3] * 10) + ((color%10) + 1) )/10;
      //set_new_color(paleta);
      //paleta += 0.1;
    }
    /*


    glBegin(GL_POLYGON);
    glColor3d(paleta[0], paleta[1], paleta[2]);
    glVertex2f(rect[i].l_d.p_data[0], rect[i].l_d.p_data[1]);
    glVertex2f(rect[i].l_d.p_data[0], rect[i].u_r.p_data[1]);
    glVertex2f(rect[i].u_r.p_data[0], rect[i].u_r.p_data[1]);
    glVertex2f(rect[i].u_r.p_data[0], rect[i].l_d.p_data[1]);
    glEnd();
    */
    glBegin(GL_LINES);
    glColor3d(paleta[0], paleta[1], paleta[2]);
    //glColor3d(0.0, 0.0, 0.0);
    glVertex2f(rect[i].l_d.p_data[0], rect[i].l_d.p_data[1]);
    glVertex2f(rect[i].l_d.p_data[0], rect[i].u_r.p_data[1]);
    glVertex2f(rect[i].l_d.p_data[0], rect[i].u_r.p_data[1]);
    glVertex2f(rect[i].u_r.p_data[0], rect[i].u_r.p_data[1]);
    glVertex2f(rect[i].u_r.p_data[0], rect[i].u_r.p_data[1]);
    glVertex2f(rect[i].u_r.p_data[0], rect[i].l_d.p_data[1]);
    glVertex2f(rect[i].u_r.p_data[0], rect[i].l_d.p_data[1]);
    glVertex2f(rect[i].l_d.p_data[0], rect[i].l_d.p_data[1]);
    glEnd();
  }

}


void graficar_puntos(){
  glPointSize(2);
  glBegin(GL_POINTS);
  //glColor3d(0,0,0);
  glColor3d(255,255,255);
  for(unsigned int i = 0; i < data_point.size(); i++){
    glVertex2f(data_point[i].p_data[0], data_point[i].p_data[1]);
  }
  glEnd();
}

//funcion llamada a cada imagen, se llama infinitamente por lo que constantemente se incializa
void glPaint(void) {
	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT); //CAMBIO
	glLoadIdentity();
	//glOrtho(-300.0f,  300.0f,-300.0f, 300.0f, -1.0f, 1.0f);//Setting up configuration of  inner windows
	glOrtho(0.0f,  100.0f, 0.0f, 100.0f, -1.0f, 1.0f);//Setting up configuration of  inner windows
	//dibujar quadTree (qt->draw())
	//dibuja el gizmo
	//displayGizmo();//It's my own function
  graficar_rectangulos_v2();
  add_late_points();
  graficar_puntos();
  //graficar_rectangulos();
  //graficar_cuadrantes( c_point(0,0) , c_point(1000, 1000));
	//add_late_points();
	//graficar_cuadrantes_v2();
	//graficar_puntos();
	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

void OnMouseMotion(int x, int y){
  //vector<float> datos;
  //float x_2 = (float)x;
  //float y_2 = (float)y;

  //translate_points(x_2, y_2);

  //datos.push_back((float)x_2);
  //datos.push_back((float)y_2);

  //c_point<float, 2> tempo(datos);
  //data_point.push_back(tempo);

  //float x_2 = (float)x;
	//float y_2 = (float)y;
	//translate_points(x_2, y_2);
	//data_point.push_back(tempo);
	//Sleep(0.5);
	//arbol.insert(x_2, y_2);
}

void OnMouseClick(int button, int state, int x, int y){
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
  vector< float > datos;
  float x_2 = (float)x;
  float y_2 = (float)y;

  translate_points(x_2, y_2);
  cout<<x_2<<"  "<<y_2<<endl;
  datos.push_back((float)x_2);
  datos.push_back((float)y_2);
  c_point<float, 2> tempo(datos);
  data_point.push_back(tempo);
  arbol.insert(tempo);
  arbol.get_transformation();
	/*for(unsigned int i = 0; i < data_point.size(); i++){
		cout<<data_point[i]<<" ";
	}*/
	//cout<<mar_iz_down<<"; "<<mar_der_up<<endl;
	//Graficamos el punto
	}
}

void idle(){ // AGREGAR ESTA FUNCION
	glutPostRedisplay();
}

GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-300.0f,  300.0f,-300.0f, 300.0f, -1.0f, 1.0f);
	glOrtho(0.0f,  100.0f, 0.0f, 100.0f, -1.0f, 1.0f);//Setting up configuration of  inner windows
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;
	default:
		break;
	}
}


/*
c_r_tree<int, 2, 3> a_a;
while(true){
  c_point<int, 2> tempo;
  cout<<"Inserte datos"<<endl;
  cin>>tempo;
  a_a.insert(tempo);
}
*/

/* EVALUATING HIGH AMOUNT OF POINTS
  char a;
  t0 = clock();
  vector< c_point<int, 90> > v_a(500000, c_point<int,90>(true));
  t1 = clock();

  double time = (double(t1-t0)/CLOCKS_PER_SEC);
  cout << "Execution Time: " << time << endl;
  cin>>a;
*/

//Es equivalente al tratamiento con puro vector:
// cien mil puntos 90 dimensiones: 0.049, 0.062, 0.058, 0.056
