//


#ifndef AJEDREZLITE_AUXILIARES_H
#define AJEDREZLITE_AUXILIARES_H

#include "definiciones.h"

using namespace std;
// definir aqui las funciones
pair<int,int> mp(int a, int b);

vector<pair<int,int>> ordenarVectorPares(vector<pair<int,int>> &v);
tablero inicializarTablero();
coordenada setCoord(int i, int j);
tablero tableroActual ( posicion const &p );
bool esMatriz (tablero const &t);
bool casillasValidas (tablero const &t);
bool sinPeonesNoCoronados (tablero const &t);
bool cantidadValidaPiezas(tablero const &t);
bool cantValidaPeon (tablero const &t);
bool cantValidaAlfil (tablero const &t);
bool cantValidaTorre (tablero const &t);
bool cantValidaRey (tablero const &t);
vector<coordenada> casillasQueAtaca (tablero const &t, casilla const &o);
vector<coordenada> atacadasPeon(tablero const &t,coordenada const &o);
vector<coordenada> movimientosAlfil (tablero const &t, coordenada const &o);
vector<coordenada> movimientosTorre (tablero const &t, coordenada const &o);
vector<coordenada> movimientosRey (tablero const &t, coordenada const &o);
void eliminarRepetidos (vector<coordenada> &v);
bool posIgualesExceptoEn(posicion const &p1, posicion const &p2, coordenada const &o, coordenada const &d);
bool esMovValido (posicion const &p, coordenada const &o, coordenada const &d);
bool esMovPeon (posicion const &p, coordenada const &o, coordenada const &d);
bool pertenece (vector<coordenada> const &v, coordenada c);
bool esMovTorre (posicion const &p, coordenada const &o, coordenada const &d);
bool esMovAlfil (posicion const &p, coordenada const &o, coordenada const &d);
bool esMovRey (posicion const &p, coordenada const &o, coordenada const &d);
bool esCapValida (posicion const &p, coordenada const &o, coordenada const &d);
int indiceMaxNoNuloHasta (vector<casilla> v, int n);
void ordenarFila (vector<casilla> &fila);
void swap (vector<coordenada> &v, int i, int j);
vector<pair<coordenada, coordenada>> movsPosibles (posicion const &p);
vector<pair<coordenada, coordenada>> movsEvitanJaque (posicion const &p);
bool evitaJaque (posicion const &p, coordenada const &o, coordenada const &d);
coordenada dondeEstaElRey(posicion const &p, int jugador);
bool estaEnJaque (posicion const &p, int jugador);
void ejecutarMovimiento (posicion &p, coordenada const &o, coordenada const &d);
bool reyAhogado (posicion const &p);
bool soloDosReyes (posicion const &p);
bool hayEmpate (posicion const &p);
bool hayJaqueMate (posicion const &p);
bool esJaqueDescubierto (posicion const &p);
bool esJugadaLegal (posicion const &p, coordenada const &o, coordenada const &d);
void ejecutarMovimientoForzado(posicion &p);
void mateForzado (posicion &p, int &turno);
vector<pair<coordenada, coordenada>> movsLegales (posicion const &p);
bool mateEnUno (posicion const &p);
bool mateEnDos (posicion const &p);
bool mateEnTres (posicion const &p);
#endif //AJEDREZLITE_AUXILIARES_H