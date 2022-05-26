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
#include "CartRDOnly.h"

class MovieGui: public QWidget, public Observer, public Observable {
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
    QPushButton* btnOpenRCart;

    //CartGui* cartWindow;
    //CartRDOnly* cartRW;

    QWidget* btnDyn = new QWidget;
    QWidget* btnDyn2 = new QWidget;
    QHBoxLayout* btnDynL = new QHBoxLayout;
    void initGUICmps();
    void connectSignalsSlots();
    void reloadList(const std::vector<Movie>& movies);
    void addNewMovie();
    void delMovie();
    void modMovie();

    void addButtons(const std::vector<Movie> &movies);
    void updateCartLabel();
    void openCartWindow();
    void openCartRWindow();

    void update() override{
        notify();
    }
};


#endif //HABITAT_MOVIEGUI_H
