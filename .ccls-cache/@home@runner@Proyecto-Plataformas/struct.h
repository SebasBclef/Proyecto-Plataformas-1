#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_LINE_LENGTH 1024
#define G 6.67430e-11 
#define M 1.989e30 


typedef struct {
    char idObjeto[MAX_LINE_LENGTH];
    float masa;
    float X_P;
    float Y_P;
    float X_A;
    float Y_A;
    float X_I;
    float Y_I;
    char C_cons[MAX_LINE_LENGTH];
    char C_obj[MAX_LINE_LENGTH];
    float tiempo;
} Configuracion;
typedef struct {
    float x;
    float y;
} Point;


int calcularElipse(Point p1, Point p2, float masa) {
  Configuracion config;
    double cx = (p1.x + p2.x) / 2.0;  // Coordenada x del centro de la elipse
    double cy = (p1.y + p2.y) / 2.0;  // Coordenada y del centro de la elipse
    double a = fabs(cx - p1.x);  // Semi-eje mayor
    double b = fabs(cy - p1.y); // Semi-eje menor
//la funcion fabs me da el valor absoluto
    double denominador = G * (M + masa);
    double T = 2 * M_PI * sqrt(pow(a*10e4, 3) / denominador);
    return T;
}
int calcularVel(Point p3, int T) {
  Configuracion config;
    int distance = sqrt(pow(p3.x, 2) + pow(p3.y, 2));
    int velocity = (2 * M_PI * distance) / T;
    return velocity;
}
int calcularCos(double X_I, double distance, double ang){
  return X_I + distance * cos(ang);
}
int calcularSen(double Y_I, double distance, double ang){
  return Y_I+ distance * sin(ang);
}
// las funciones calcularSen, calcularCos, calcularVel y calcularElipse fueron hechas con chatgpt