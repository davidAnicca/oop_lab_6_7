//
// Created by david on 26.05.2022.
//

#ifndef HABITAT_CARTRDONLY_H
#define HABITAT_CARTRDONLY_H
#include "../srv/Service.h"
#include "Observer.h"
#include "CartGui.h"
#include <QWidget>
#include <QtWidgets>

class CartRDOnly: public QWidget, public Observer {
    CartGui& mainC;
    Service& srv;
    QLabel* howMany = new QLabel("");
    QVBoxLayout* mainL  = new QVBoxLayout;
public:
    CartRDOnly(CartGui& mainC, Service& srv):mainC{mainC}, srv{srv}{
        init();
        update();
    }
    void update() override{
        howMany->setText(QString::fromStdString(std::to_string(srv.cartSize())));
    }
    void init(){
        setLayout(mainL);
        mainL->addWidget(howMany);
    };
};


#endif //HABITAT_CARTRDONLY_H
