#include "definiciones.h"
#include "auxiliares.h"
#include "ejercicios.h"
#include "iostream"
using namespace std;


// TEST
vector<pair<int,int>> ordenarVectorPares(vector<pair<int,int>> &v) {
    sort(v.begin(), v.end());
//    v.erase(unique(v.begin(), v.end()), v.end());
    return v;
}

coordenada setCoord(int i, int j) {
    return make_pair(i,j);
}

tablero tableroActual ( posicion const &p ) {
    return p.first;
}


bool esMatriz (tablero const &t){
    bool resp = false;
    if (t.size() == ANCHO_TABLERO){
        resp = true;
        int k = 0;
        while (resp && k < ANCHO_TABLERO){
            resp = t[k].size() == ANCHO_TABLERO;
            k++;
        }
    }
    return resp;
}

bool casillasValidas (tablero const &t){
    bool resp = true;
    for (int i = 0; i < ANCHO_TABLERO; i++){
        for (int j = 0; j < ANCHO_TABLERO; j++){
            int t0 = PEON <= t[i][j].first && t[i][j].first <= REY;
            int t1 = BLANCO <= t[i][j].second && t[i][j].second <= NEGRO;
            resp = resp && ((t0 && t1) || (t[i][j] == cVACIA));
        }
    }
    return resp;
}

bool sinPeonesNoCoronados (tablero const &t){
    bool resp = true;
    for (int j = 0; j < ANCHO_TABLERO; j++){
        resp = resp && (t[0][j].first != PEON) && (t[ANCHO_TABLERO - 1][j].first != PEON);
    }
    return resp;
}

bool cantidadValidaPiezas (tablero const &t){
    return (cantValidaPeon(t) && cantValidaAlfil(t) && cantValidaTorre(t) && cantValidaRey(t));
}

bool cantValidaPeon (tablero const &t){
    int cantPeonesN = 0;
    int cantPeonesB = 0;
    for (int i = 0; i < ANCHO_TABLERO; i++){
        for (int j = 0; j < ANCHO_TABLERO; j++){
            if (t[i][j] == cPEON_N){
                cantPeonesN++;
            }
            if (t[i][j] == cPEON_B){
                cantPeonesB++;
            }
        }
    }
    bool resp = (cantPeonesB <= ANCHO_TABLERO && cantPeonesN <= ANCHO_TABLERO);
    return resp;
}

bool cantValidaAlfil (tablero const &t){
    int cantAlfilN = 0;
    int cantAlfilB = 0;
    for (int i = 0; i < ANCHO_TABLERO; i++){
        for (int j = 0; j < ANCHO_TABLERO; j++){
            if (t[i][j] == cALFIL_N){
                cantAlfilN++;
            }
            if (t[i][j] == cALFIL_B){
                cantAlfilB++;
            }
        }
    }
    bool resp = (cantAlfilB <= 2 && cantAlfilN <= 2);
    return resp;
}

bool cantValidaTorre (tablero const &t){
    int cantPeonesN = 0;
    int cantPeonesB = 0;
    int cantTorreN = 0;
    int cantTorreB = 0;
    for (int i = 0; i < ANCHO_TABLERO; i++){
        for (int j = 0; j < ANCHO_TABLERO; j++){
            if (t[i][j] == cPEON_N){
                cantPeonesN++;
            } else if (t[i][j] == cPEON_B){
                cantPeonesB++;
            } else if (t[i][j] == cTORRE_N){
                cantTorreN++;
            } else if (t[i][j] == cTORRE_B){
                cantTorreB++;
            }
        }
    }
    bool resp = cantTorreN <= 2 + (ANCHO_TABLERO - cantPeonesN);
    resp = resp && (cantTorreB <= 2 + (ANCHO_TABLERO - cantPeonesB));
    return resp;
}

bool cantValidaRey (tablero const &t){
    int cantReyN = 0;
    int cantReyB = 0;
    for (int i = 0; i < ANCHO_TABLERO; i++){
        for (int j = 0; j < ANCHO_TABLERO; j++){
            if (t[i][j] == cREY_N){
                cantReyN++;
            } else if (t[i][j] == cREY_B){
                cantReyB++;
            }
        }
    }
    bool resp = (cantReyN == 1) && (cantReyB == 1);
    return resp;
}
vector<coordenada> casillasQueAtaca (tablero const &t, coordenada const &o) {
    vector<coordenada> cA;
    casilla c = t[o.first][o.second];
    if (c.first == PEON) {
        cA = atacadasPeon(t, o);
    } else if (c.first == ALFIL){
        cA = movimientosAlfil(t, o);
    } else if (c.first == TORRE){
        cA = movimientosTorre(t, o);
    } else {
        cA = movimientosRey(t, o);
    }
    return cA;
}

vector<coordenada> atacadasPeon(tablero const &t,coordenada const &o){
    vector<coordenada> cA;
    casilla c = t[o.first][o.second];
    int sentido = pow((-1),(c.second));
    if (o.second != ANCHO_TABLERO - 1){
        coordenada p0 = make_pair(o.first + sentido, o.second + 1);
        cA.push_back(p0);
    }
    if (o.second != 0){
        coordenada p1 = make_pair(o.first + sentido, o.second - 1);
        cA.push_back(p1);
    }
    return cA;
}

vector<coordenada> movimientosAlfil (tablero const &t, coordenada const &o){
    vector<coordenada> movimientos;
    bool encUR, encUL, encDR, encDL = false;
    int i = o.first;
    int j = o.second;
    while (encUR == false && i > -1 && j < ANCHO_TABLERO){
        coordenada d = make_pair(i, j);
        if (t[i][j] != cVACIA && d != o){
            encUR = true;
            movimientos.push_back(d);
        } else {
            movimientos.push_back(d);
        }
        i--;
        j++;
    }
    i = o.first;
    j = o.second;
    while (encUL == false && i > -1 && j > -1){
        coordenada d = make_pair(i, j);
        if (t[i][j] != cVACIA && d != o){
            encUL = true;
            movimientos.push_back(d);
        } else {
            movimientos.push_back(d);
        }
        i--;
        j--;
    }
    i = o.first;
    j = o.second;
    while (encDR == false && i < ANCHO_TABLERO && j < ANCHO_TABLERO){
        coordenada d = make_pair(i, j);
        if (t[i][j] != cVACIA && d != o){
            encDR = true;
            movimientos.push_back(d);
        } else {
            movimientos.push_back(d);
        }
        i++;
        j++;
    }
    i = o.first;
    j = o.second;
    while (encDL == false && i < ANCHO_TABLERO && j > -1){
        coordenada d = make_pair(i, j);
        if (t[i][j] != cVACIA && d != o){
            encDL = true;
            movimientos.push_back(d);
        } else {
            movimientos.push_back(d);
        }
        i++;
        j--;
    }
    return movimientos;
}

vector<coordenada> movimientosTorre (tablero const &t, coordenada const &o){
    vector<coordenada> movimientos;
    bool encU, encD, encR, encL = false;
    int i = o.first - 1;
    int j = o.second;
    while (encU == false && i > -1){
        coordenada d = make_pair(i, j);
        if (t[i][j] != cVACIA && d != o){
            encU = true;
            movimientos.push_back(d);
        } else {
            movimientos.push_back(d);
        }
        i--;
    }
    i = o.first + 1;
    j = o.second;
    while (encD == false && i < ANCHO_TABLERO){
        coordenada d = make_pair(i, j);
        if (t[i][j] != cVACIA && d != o){
            encD = true;
            movimientos.push_back(d);
        } else {
            movimientos.push_back(d);
        }
        i++;
    }
    i = o.first;
    j = o.second + 1;
    while (encR == false && j < ANCHO_TABLERO){
        coordenada d = make_pair(i, j);
        if (t[i][j] != cVACIA && d != o){
            encR = true;
            movimientos.push_back(d);
        } else {
            movimientos.push_back(d);
        }
        j++;
    }
    i = o.first;
    j = o.second - 1;
    while (encL == false && j > -1){
        coordenada d = make_pair(i, j);
        if (t[i][j] != cVACIA && d != o){
            encL = true;
            movimientos.push_back(d);
        } else {
            movimientos.push_back(d);
        }
        j--;
    }
    return movimientos;
}

vector<coordenada> movimientosRey (tablero const &t, coordenada const &o){
    vector<coordenada> movimientos;
    for (int i = o.first - 1; i < o.first + 2; i++){
        for (int j = o.second - 1; j < o.second + 2; j++){
            coordenada d = make_pair(i, j);
            if (-1 < i && i < ANCHO_TABLERO && j > -1 && j < ANCHO_TABLERO && d != o){
                movimientos.push_back(d);
            }
        }
    }
    return movimientos;
}

void eliminarRepetidos (vector<coordenada> &v){
    for (int i = 0; i < v.size(); i++){
        for (int j = 0; j < v.size(); j++){
            if (v[i] == v[j] && i != j) {
                v.erase(v.begin() + j);
            }
        }
    }
}

bool posIgualesExceptoEn(posicion const &p1, posicion const &p2, coordenada const &o, coordenada const &d){
    bool res = true;
    for (int i = 0; i < ANCHO_TABLERO; i++){
        for (int j = 0; j < ANCHO_TABLERO; j++){
            coordenada coord = make_pair(i, j);
            if (coord != o && coord != d){
                casilla c1 = p1.first[coord.first][coord.second];
                casilla c2 = p2.first[coord.first][coord.second];
                if (c1 != c2){
                    res = false;
                }
            }
        }
    }
    return res;
}

bool esMovValido (posicion const &p, coordenada const &o, coordenada const &d){
    bool res;
    int pieza = p.first[o.first][o.second].first;
    casilla destino = p.first[d.first][d.second];
    if (pieza == PEON){
        res = esMovPeon(p, o, d);
    } else if (pieza == TORRE){
        res = esMovTorre(p, o, d);
    } else if (pieza == ALFIL){
        res = esMovAlfil(p, o, d);
    } else {
        res = esMovRey(p, o, d);
    }
    res = res && (destino == cVACIA);
    return res;
}

bool esMovPeon (posicion const &p, coordenada const &o, coordenada const &d){
    bool res;
    int sentido = pow((-1), p.second);
    res = (d.first == (o.first + sentido));
    res = res && (o.second == d.second);
    return res;
}

bool pertenece (vector<coordenada> const &v, coordenada c){
    bool res = false;
    for (int i = 0; i < v.size(); i++){
        if (v[i] == c){
            res = true;
        }
    }
    return res;
}

bool esMovTorre (posicion const &p, coordenada const &o, coordenada const &d) {
    bool res;
    res = pertenece(movimientosTorre(p.first, o), d);
    return res;
}

bool esMovAlfil (posicion const &p, coordenada const &o, coordenada const &d){
    bool res;
    res = pertenece(movimientosAlfil(p.first, o), d);
    return res;
}

bool esMovRey (posicion const &p, coordenada const &o, coordenada const &d){
    bool res;
    res = pertenece(movimientosRey(p.first, o), d);
    return res;
}

bool esCapValida (posicion const &p, coordenada const &o, coordenada const &d){
    bool res;
    int pieza = p.first[o.first][o.second].first;
    int colorRival = 3 - p.second;
    if (pieza == PEON){
        res = pertenece(atacadasPeon(p.first, o), d);
    } else if (pieza == TORRE){
        res = esMovTorre(p, o, d);
    } else if (pieza == ALFIL){
        res = esMovAlfil(p, o, d);
    } else {
        res = esMovRey(p, o, d);
    }
    res = res && (p.first[d.first][d.second].second == colorRival);
    return res;
}

int indiceMaxNoNuloHasta (vector<casilla> v, int n){
    int res = n;
    int max = v[n].first;
    for (int i = 0; i <= n; i++){
        if (v[i] != cVACIA){
           if (v[i].first > max){
               res = i;
               max = v[i].first;
           }
        }
    }
    return res;
}

void ordenarFila (vector<casilla> &fila){
    for (int i = fila.size() - 1; i > -1; i--){
        if (fila[i] != cVACIA){
            swap(fila, i, indiceMaxNoNuloHasta(fila, i));
        }
    }
}

void swap (vector<casilla> &v, int i, int j){
    casilla aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

vector<pair<coordenada, coordenada>> movsPosibles (posicion const &p){
    vector<pair<coordenada, coordenada>> posibles;
    for (int i = 0; i < ANCHO_TABLERO; i++){
        for (int j = 0; j < ANCHO_TABLERO; j++) {
            coordenada o = make_pair(i, j);
            if (p.first[o.first][o.second] != cVACIA && p.first[o.first][o.second].second == p.second) {
                for (int x = 0; x < ANCHO_TABLERO; x++) {
                    for (int y = 0; y < ANCHO_TABLERO; y++) {
                        coordenada d = make_pair(x, y);
                        if (o != d) {
                            if (esMovValido(p, o, d) || esCapValida(p, o, d)) {
                                pair<coordenada, coordenada> movimiento = make_pair(o, d);
                                posibles.push_back(movimiento);
                            }
                        }
                    }
                }
            }
        }
    }
    return posibles;
}

vector<pair<coordenada, coordenada>> movsEvitanJaque (posicion const &p){
    vector<pair<coordenada, coordenada>> posibles = movsPosibles(p);
    vector<pair<coordenada, coordenada>> jugadasSalvadoras = {};
    for (int i = 0; i < posibles.size(); i++){
        if (evitaJaque(p, posibles[i].first, posibles[i].second)){
            jugadasSalvadoras.push_back(posibles[i]);
        }
    }
    return jugadasSalvadoras;
}

bool evitaJaque (posicion const &p, coordenada const &o, coordenada const &d){
    bool res = false;
    posicion p2 = p;
    ejecutarMovimiento(p2, o, d);
    if (!(estaEnJaque(p2, p.second))){
        res = true;
    }
    return res;
}

coordenada dondeEstaElRey(posicion const &p, int jugador){
    coordenada rey;
    for (int i = 0; i < ANCHO_TABLERO; i++){
        for (int j = 0; j < ANCHO_TABLERO; j++){
            if (p.first[i][j] == make_pair(4, jugador)){
                rey = make_pair(i, j);
            }
        }
    }
    return rey;
}

bool estaEnJaque (posicion const &p, int jugador){
    bool reyAtacado = false;
    int colorRival = 3 - jugador;
    if (pertenece(casillasAtacadas(p, colorRival), dondeEstaElRey(p, jugador))){
        reyAtacado = true;
    }
    return reyAtacado;
}

void ejecutarMovimiento (posicion &p, coordenada const &o, coordenada const &d){
    int ultimaFila = 7*p.second - 7;
    if (d.first == ultimaFila && p.first[o.first][o.second].first == PEON){
        p.first[d.first][d.second] = make_pair(TORRE, p.second);
    } else {
        p.first[d.first][d.second] = p.first[o.first][o.second];
    }
    p.first[o.first][o.second] = cVACIA;
    p.second = 3 - p.second;
}

bool reyAhogado(posicion const &p){
    bool ahogado = true;
    if (!estaEnJaque(p, p.second)){
        vector<pair<coordenada, coordenada>> posibles = movsPosibles(p);
        for (int i = 0; i < posibles.size(); i++){
            posicion p2 = p;
            ejecutarMovimiento(p2, posibles[i].first, posibles[i].second);
            if (!estaEnJaque(p2, p.second)){
                ahogado = false;
            }
        }
    } else {
        ahogado = false;
    }
    return ahogado;
}

bool soloDosReyes(posicion const &p){
    bool res = true;
    for (int i = 0; i < ANCHO_TABLERO; i++){
        for (int j = 0; j < ANCHO_TABLERO; j++){
            if (p.first[i][j].first != REY && p.first[i][j] != cVACIA){
                res = false;
            }
        }
    }
    return res;
}

bool hayEmpate (posicion const &p){
    bool resp = reyAhogado(p) || soloDosReyes(p);
    return resp;
}

bool hayJaqueMate (posicion const &p){
    bool res = false;
    if (estaEnJaque(p, p.second) && movsEvitanJaque(p).size() < 1){
        res = true;
    }
    return res;
}

bool esJaqueDescubierto (posicion const &p){
    posicion p0 = p;
    bool res = false;
    for (int i = 0; i < movsLegales(p).size(); i++){
        if (esMovValido(p, movsLegales(p)[i].first, movsLegales(p)[i].second) ||
            esCapValida(p, movsLegales(p)[i].first, movsLegales(p)[i].second)){
            ejecutarMovimiento(p0, movsLegales(p)[i].first, movsLegales(p)[i].second);
            if (estaEnJaque(p0, p0.second)){
                res = true;
            }
        }
        p0 = p;
    }
    return res;
}


bool esJugadaLegal (posicion const &p, coordenada const &o, coordenada const &d) {
    posicion p0 = p;
    bool resp = true;
    ejecutarMovimiento(p0, o, d);
    if (estaEnJaque(p0, p.second)) {
        resp = false;
    }
    return resp;
}

void ejecutarMovimientoForzado (posicion &p){
    for (int i = 0; i < movsPosibles(p).size(); i++){
        if (esJugadaLegal(p, movsPosibles(p)[i].first, movsPosibles(p)[i].second)){
            ejecutarMovimiento(p, movsPosibles(p)[i].first, movsPosibles(p)[i].second);
            return;
        }
    }
}


vector<pair<coordenada, coordenada>> movsLegales (posicion const &p){
    vector<pair<coordenada, coordenada>> movsLegales = {};
    for (int i = 0; i < movsPosibles(p).size(); i++){
        if (esJugadaLegal(p, movsPosibles(p)[i].first, movsPosibles(p)[i].second)){
            movsLegales.push_back(movsPosibles(p)[i]);
        }
    }
    return movsLegales;
}

bool mateEnUno (posicion const &p) {
    bool res = false;
    posicion p0 = p;
    for (int i = 0; i < movsLegales(p).size(); i++) {
        ejecutarMovimiento(p0, movsLegales(p)[i].first, movsLegales(p)[i].second);
        bool mate = hayJaqueMate(p0);
        if (mate) {
                res = true;
                return res;
        }
        p0 = p;
    }
    return res;
}

bool mateEnDos (posicion const &p){
    bool res = false;
    posicion p0 = p;
    for (int i = 0; i < movsLegales(p).size(); i++){
        ejecutarMovimiento(p0, movsLegales(p)[i].first, movsLegales(p)[i].second);
        if (movsLegales(p0).size() == 1){
            ejecutarMovimientoForzado(p0);
            bool uno = mateEnUno(p0);
            if (uno){
                res = true;
                return res;
            }
        }
        p0 = p;
    }
    return res;
}

bool mateEnTres (posicion const &p){
    bool res = false;
    posicion p0 = p;
    for (int i = 0; i < movsLegales(p).size(); i++){
        ejecutarMovimiento(p0, movsLegales(p)[i].first, movsLegales(p)[i].second);
        if (movsLegales(p0).size() == 1){
            ejecutarMovimientoForzado(p0);
            bool dos = mateEnDos(p0);
            if (dos){
                res = true;
                return res;
            }
        }
        p0 = p;
    }
    return res;
}

void mateForzado (posicion &p, int &turno){
    posicion p0 = p;
    if (mateEnUno(p)) {
        turno = 1;
        return;
    } else if (mateEnDos(p)){
        turno = 2;
        return;
    } else if (mateEnTres(p)){
        turno = 3;
        return;
    } else {
        turno = -1;
        return;
    }
}