#include <algorithm>
#include "ejercicios.h"
#include "auxiliares.h"
#include "iostream"
#include "math.h"
using namespace std;

// EJERCICIO 1
bool posicionValida ( pair < tablero, int > const &p ) {
    bool resp = false;
    tablero t = p.first;
    resp = esMatriz(t) && casillasValidas(t) && sinPeonesNoCoronados(t) && cantidadValidaPiezas(t);
    int jug = p.second;
    resp = resp && (jug == 1 || jug == 2);
    return resp;
}

// EJERCICIO 2
bool posicionInicial ( posicion const &p ) {
    bool resp = false;
    tablero t = {{cTORRE_N, cVACIA, cALFIL_N, cVACIA, cREY_N, cALFIL_N, cVACIA, cTORRE_N},
                 {cPEON_N, cPEON_N, cPEON_N, cPEON_N, cPEON_N, cPEON_N, cPEON_N, cPEON_N},
                 {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
                 {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
                 {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
                 {cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA},
                 {cPEON_B, cPEON_B, cPEON_B, cPEON_B, cPEON_B, cPEON_B, cPEON_B, cPEON_B},
                 {cTORRE_B, cVACIA, cALFIL_B, cVACIA, cREY_B, cALFIL_B, cVACIA, cTORRE_B}};
    resp = (p.first == t);
    resp = resp && (p.second == BLANCO);
    return resp;
}
// EJERCICIO 3
vector <coordenada> casillasAtacadas ( posicion const &p, int j ) {
    vector <coordenada> cA;
    tablero t = p.first;
    for (int i = 0; i < ANCHO_TABLERO; i++) {
        for (int k = 0; k < ANCHO_TABLERO; k++) {
            coordenada o = make_pair(i, k);
            if (t[o.first][o.second].second == j) {
                vector<coordenada> queAtaca = casillasQueAtaca(t, o);
                cA.insert(cA.begin(), queAtaca.begin(), queAtaca.end());
            }
        }
    }
    eliminarRepetidos(cA);
    ordenarVectorPares(cA);
    return cA;
}
// EJERCICIO 4
bool posicionSiguienteCorrecta ( posicion const &p1, posicion const &p2, coordenada o, coordenada d ) {
    bool resp;
    resp = posIgualesExceptoEn(p1, p2, o, d);
    resp = resp && (p2.first[o.first][o.second] == cVACIA);
    resp = resp && (esMovValido(p1, o, d) || esCapValida(p1, o, d));
    resp = resp && (p2.first[d.first][d.second] == p1.first[o.first][o.second]);
    return resp;
}
// EJERCICIO 5
void ordenarTablero ( posicion &p ) {
    for (int i = 0; i < ANCHO_TABLERO; i++){
        ordenarFila(p.first[i]);
    }
}
// EJERCICIO 6
bool finDeLaPartida ( posicion const &p, int &j ) {
    bool resp = false;
    if (hayJaqueMate(p)){
        resp = true;
        j = 3 - p.second;
    } else if (hayEmpate(p)){
        resp = true;
        j = 0;
    }
    return resp;
}
// EJERCICIO 7
bool hayJaqueDescubierto ( posicion const &p ) {
    bool resp = esJaqueDescubierto(p);
    return resp;
}
// EJERCICIO 8
void ejecutarSecuenciaForzada ( posicion &p, secuencia s ) {
    for (int i = 0; i < s.size(); i++){
        ejecutarMovimiento(p, s[i].first, s[i].second);
        ejecutarMovimientoForzado(p);
    }
    return;
}
// EJERCICIO 9
int seVieneElJaqueEn ( posicion const & p ) {
    posicion p0 = p;
    int resp = 0;
    mateForzado(p0, resp);
    return resp;
}
