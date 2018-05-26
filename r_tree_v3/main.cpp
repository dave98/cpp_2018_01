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

//CREATED BY jose david mamani vilca. jose.mamani.vilca@ucsp.edu.pe
#define KEY_ESC 27
using namespace std;

c_r_tree<float, 2, 3> arbol;
vector< c_point<float, 2> > data_point;
vector< c_nodo<float, 2, 3> > rect;//ESTOS DOS VAN DE LA MANO
vector< int > profundidad;

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
//en el caso que la ventana cambie de tama�o
GLvoid window_redraw(GLsizei, GLsizei);
GLvoid window_key(unsigned char, int, int);

int main(int argc, char** argv){
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

void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
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

void graficar_rectangulos_v2(){
  cout<<"Pintando..."<<endl;
  int color = 0;
  float paleta = 0.1;
  arbol.get_transformation();
  cout<<"Transformada obtenida"<<endl;
  for(unsigned int i = 0; i < rect.size(); i++){
    if(color != profundidad[i]){
      color = profundidad[i];
      paleta += 0.2;
    }
    glBegin(GL_POLYGON);
    glColor3d(paleta, 0, 0.3);
    glVertex2f(rect[i].l_d.p_data[0], rect[i].l_d.p_data[1]);
    glVertex2f(rect[i].l_d.p_data[0], rect[i].u_r.p_data[1]);
    glVertex2f(rect[i].u_r.p_data[0], rect[i].u_r.p_data[1]);
    glVertex2f(rect[i].u_r.p_data[0], rect[i].l_d.p_data[1]);
    glEnd();
  }

}


void graficar_puntos(){
  glPointSize(2);
  glBegin(GL_POINTS);
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
  graficar_puntos();
  graficar_rectangulos_v2();
  //graficar_rectangulos();
  //graficar_cuadrantes( c_point(0,0) , c_point(1000, 1000));
	//add_late_points();
	//graficar_cuadrantes_v2();
	//graficar_puntos();
	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

void OnMouseMotion(int x, int y){
  vector<float> datos;
  float x_2 = (float)x;
  float y_2 = (float)y;

  translate_points(x_2, y_2);

  datos.push_back((float)x_2);
  datos.push_back((float)y_2);

  c_point<float, 2> tempo(datos);
  data_point.push_back(tempo);

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

  datos.push_back((float)x_2);
  datos.push_back((float)y_2);
  c_point<float, 2> tempo(datos);
  data_point.push_back(tempo);
  arbol.insert(tempo);
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
