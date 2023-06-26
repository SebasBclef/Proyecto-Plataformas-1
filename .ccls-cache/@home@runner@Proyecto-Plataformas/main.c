#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "struct.h"
#define G 6.67430e-11 
#define M 1.989e30     
#define MAX_TEXT_LENGTH 100

int main() {
    const char* nombre_archivo = "Configuracion.txt";
    Configuracion config;
    if (leer_config(nombre_archivo, &config)) {
        printf("ID Objeto: %s\n", config.idObjeto);
        printf("Masa: %.2e kg\n",config.masa);
        printf("Posicion X Perihelio: %.2f m\n", config.X_P);
        printf("Posicion Y Perihelio: %.2f m\n", config.Y_P);
        printf("Posicion X Afelio: %.2f m\n", config.X_A);
        printf("Posicion Y Afelio: %.2f m\n", config.Y_A);
        printf("Posicion X Inicial: %.2f m\n", config.X_I);
        printf("Posicion Y Inicial: %.2f m\n", config.Y_I);
        printf("ID Consulta:  %s\n", config.C_cons);
        printf("ID Objeto: %s\n", config.idObjeto);
        printf("Tiempo: %.2f\n", config.tiempo);
    } else {
        printf("No se encontró la configuración en el archivo.\n");
    }
    Point p1 = {config.X_A, config.Y_A};
    Point p2 = {config.X_P, config.Y_P};
    Point p3= {config.X_I, config.Y_I};
    ;
  
//se toman los datos del struct y por ende, del .txt de configuracion para calcular la elipse
    int T = calcularElipse(p1, p2, config.masa);
//Se calcula una elipse porque las leyes de Kepler establecen que los cuerpos de nuestros sistemas se mueven de manera eliptica
    float vel = calcularVel(p3, T);
    double ang= (2 * M_PI*config.tiempo)/ T;
//Para calcular XF y YF, es necesario calcular el angulo al que se encuentra el cuerpo del centro, que estamos asumiendo que es el Sol.
    double dist = vel * config.tiempo;
    double X_F= calcularCos(config.X_I,dist,ang);
    double Y_F=calcularSen(config.Y_I,dist,ang);
    return 0;
} 
int leer_config(const char* archivo, Configuracion* config) {
    FILE* archivo_txt = fopen("Configuracion.txt", "r");
    if (archivo_txt == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 0;
    }
    char linea[MAX_LINE_LENGTH];
    while (fgets(linea, sizeof(linea), archivo_txt) != NULL) {
        if (strstr(linea, "ID Objeto:") == linea) {
            sscanf(linea, "ID Objeto: %[^\n]", config->idObjeto);
        } else if (strstr(linea, "Masa:") == linea) {
            sscanf(linea, "Masa: %f", &(config->masa));
        } else if (strstr(linea, "Posicion X Perihelio:") == linea) {
            sscanf(linea, "Posicion X Perihelio: %f", &(config->X_P));
        } else if (strstr(linea, "Posicion Y Perihelio:") == linea) {
            sscanf(linea, "Posicion Y Perihelio: %f", &(config->Y_P));
        } else if (strstr(linea, "Posicion X Afelio:") == linea) {
            sscanf(linea, "Posicion X Afelio: %f", &(config->X_A));
        } else if (strstr(linea, "Posicion Y Afelio:") == linea) {
            sscanf(linea, "Posicion Y Afelio: %f", &(config->Y_A));
        } else if (strstr(linea, "Posicion X Inicial:") == linea) {
            sscanf(linea, "Posicion X Inicial: %f", &(config->X_I));
        } else if (strstr(linea, "Posicion Y Inicial:") == linea) {
            sscanf(linea, "Posicion Y Inicial: %f", &(config->Y_I));
        } else if (strstr(linea, "ID Consulta:") == linea) {
            sscanf(linea, "ID Consulta: %[^\n]", config->C_cons);
        } else if (strstr(linea, "ID Objeto:") == linea) {
            sscanf(linea, "ID Objeto: %[^\n]", config->C_obj);
        } else if (strstr(linea, "Tiempo:") == linea) {
            sscanf(linea, "Tiempo: %f", &(config->tiempo));
        }
    }
    fclose(archivo_txt);
  FILE* fr;
  Point p1 = {config->X_A, config->Y_A};
  Point p2 = {config->X_P, config->Y_P};
  Point p3= {config->X_I, config->Y_I};
  int T = calcularElipse(p1, p2, config->masa);
  float vel = calcularVel(p3, T);
  double dist = vel * config->tiempo;
    double ang= (2 * M_PI*config->tiempo)/ T;
  double X_F= calcularCos(config->X_I,dist,ang);
  double Y_F= calcularSen(config->Y_I,dist,ang);
  fr = fopen("respuestas.txt", "a");
  fprintf(fr, "ID de la Consulta: %s\n", config->C_cons);
  fprintf(fr, "Coordenada X en el tiempo %.2f: %f\n", config->tiempo, X_F);
  fprintf(fr, "Coordenada Y en el tiempo %.2f: %f\n", config->tiempo, Y_F);
  fclose(fr);
    return 1;
}