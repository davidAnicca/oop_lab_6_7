//
// Created by david on 26.05.2022.
//

#ifndef HABITAT_CARTRDONLY_H
#define HABITAT_CARTRDONLY_H
#include "../srv/Service.h"
#include "Observer.h"
#include "CartGui.h"
//#include "MovieGui.h"
#include <QWidget>
#include <QtWidgets>

class CartRDOnly: public QWidget, public Observer {
    ///CartGui& mainC;
    Service& srv;
    QLabel* howMany = new QLabel("");
    QWidget* paintZOne = new QWidget();
    QVBoxLayout* mainL  = new QVBoxLayout;
public:
    explicit CartRDOnly(Service& srv):srv{srv}{
        setAttribute(Qt::WA_DeleteOnClose);
        init();

    }
    void update() override{
        howMany->setText(QString::fromStdString(std::to_string(srv.cartSize())));
        repaint();
    }
    void init(){
        srv.addObserver(this);
        setLayout(mainL);
        setFixedSize(500, 500);
        ///mainL->setGeometry(QRect(100, 100, 100, 100));
        //mainL->addWidget(howMany);
        mainL->addWidget(paintZOne);
        update();
    };
    void paintEvent(QPaintEvent* ev) override;
    int randomPoz();
    void closeEvent(QCloseEvent* ev) override{
        srv.removeObserver(this);
        ev->accept();
    };

};


#endif //HABITAT_CARTRDONLY_H
