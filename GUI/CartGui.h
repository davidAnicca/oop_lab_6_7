//
// Created by david on 13.05.2022.
//

#ifndef HABITAT_CARTGUI_H
#define HABITAT_CARTGUI_H

#include "../srv/Service.h"
#include <QWidget>
#include <QtWidgets>

class CartGui : public QWidget{
public:
    explicit CartGui(Service& service): service{service}{
        init();
        connectSig();
        reloadList(service.getCart());
    }

private:
    Service& service;
    QHBoxLayout* mainL = new QHBoxLayout;
    QListWidget* lst;
    QPushButton* btnEmpty;
    QPushButton* btnExport;
    QPushButton* btnImport;
    QLineEdit* txtImportPath = new QLineEdit;
    QLineEdit* txtExportPath =  new QLineEdit;
    QPushButton* btnClose;

    QPushButton* btnGenerate;
    QLineEdit* txtGenerate = new QLineEdit;
    void init();
    void connectSig();
    void reloadList(const std::vector<Movie>& movies);
};


#endif //HABITAT_CARTGUI_H
