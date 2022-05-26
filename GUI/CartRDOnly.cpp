//
// Created by david on 26.05.2022.
//

#include "CartRDOnly.h"
#include <random>


void CartRDOnly::paintEvent(QPaintEvent* ev) {
    srand(time(0));
    QPainter p{ this };
    for(int i = 0; i < srv.cartSize(); i++) {
        p.drawImage(randomPoz(), randomPoz(), QImage("lol.png").scaled(100, 100, Qt::KeepAspectRatio));
    }
}

int CartRDOnly::randomPoz() {
    return rand()%300;
}
