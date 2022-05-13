//
// Created by david on 12.05.2022.
//

#ifndef HABITAT_MOVIEGUI_H
#define HABITAT_MOVIEGUI_H
#include "CartGui.h"
#include <QtWidgets>
#include <QListWidget>
#include <QPushButton>
#include "Service.h"

class MovieGui: public QWidget {
public:
    explicit MovieGui(Service& service): service{service}{
        initGUICmps();
        connectSignalsSlots();
        reloadList(service.getAll());

    };

private:
    Service& service;
    QHBoxLayout* mainL = new QHBoxLayout;
    QListWidget* lst;
    QPushButton* btnFilterByYear;
    QPushButton* btnFilterByGenre;
    QLineEdit* txtTitle;
    QLineEdit* txtGenre;
    QLineEdit* txtYear;
    QLineEdit* txtProtagonist;
    QPushButton* btnAdd;
    QPushButton* btnDel;
    QPushButton* btnMod;
    QVBoxLayout* lyBtnDy = new QVBoxLayout;
    QPushButton* btnUndo;
    QLabel* cartLabel;

    QPushButton* btnAddCart;
    QPushButton* btnOpenCart;

    CartGui* cartWindow;

    QWidget* btnDyn = new QWidget;
    void initGUICmps();
    void connectSignalsSlots();
    void reloadList(const std::vector<Movie>& movies);
    void addNewMovie();
    void delMovie();
    void modMovie();

    void updateCartLabel();
    void openCartWindow();
};


#endif //HABITAT_MOVIEGUI_H
