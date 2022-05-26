//
// Created by david on 13.05.2022.
//

#include "CartGui.h"
#include "../utils/MyUtils.h"

void CartGui::connectSig() {
    QObject::connect(btnEmpty,
                     &QPushButton::clicked,
                     [&](){
        service.emptyCart();
        reloadList(service.getCart());
        notify();
    });

    QObject::connect(btnClose,
                     &QPushButton::clicked,
                     [&](){
        this->close();
        delete this;
    });

    QObject::connect(btnImport,
                     &QPushButton::clicked,
                     [&](){
        std::string filePath = txtImportPath->text().toStdString();
        txtImportPath->setText("");
        if(filePath == "")return;
        try {
            service.importCart(filePath);
            reloadList(service.getCart());
            notify();
        }catch(fileException& e){
            QMessageBox::warning(this,
                                 "warning",
                                 QString::fromStdString(e.msg));
        }
    });

    QObject::connect(btnGenerate,
                     &QPushButton::clicked,
                     [&](){
        try{
            service.generateRandomCart(MyUtils::stringToInt(
                    txtGenerate->text().toStdString()
                    ));
            txtGenerate->setText("");
            reloadList(service.getCart());
            notify();
        }catch(uiException& e){
            QMessageBox::warning(this,
                                 "Warning",
                                 QString::fromStdString(e.msg));
        }
    });

    QObject::connect(btnExport,
                     &QPushButton::clicked,
                     [&](){
        std::string filePath = txtExportPath->text().toStdString();
        txtExportPath->setText("");
        if(filePath == "")return;
        try {
            service.exportCart(filePath);
            reloadList(service.getCart());
            notify();
        }catch(fileException& e){
            QMessageBox::warning(this,
                                 "warning",
                                 QString::fromStdString(e.msg));
        }
    });
}

void CartGui::init() {
    setLayout(mainL);
    QWidget* w = new QWidget;
    QVBoxLayout* v = new QVBoxLayout;
    w->setLayout(v);
    lst = new QListWidget;
    v->addWidget(lst);
    btnClose = new QPushButton("inchide");
    btnEmpty = new QPushButton("goleste");
    btnGenerate = new QPushButton("genereaza");
    v->addWidget(btnEmpty);
    btnExport = new QPushButton("exporta");
    btnImport = new QPushButton("importa");


    QHBoxLayout* importL = new QHBoxLayout;
    importL->addWidget(txtImportPath);
    importL->addWidget(btnImport);
    QWidget* importW = new QWidget;
    importW->setLayout(importL);
    v->addWidget(importW);

    QHBoxLayout* exportL = new QHBoxLayout;
    exportL->addWidget(txtExportPath);
    exportL->addWidget(btnExport);
    QWidget* exportW = new QWidget;
    exportW->setLayout(exportL);
    v->addWidget(exportW);

    QHBoxLayout* generateL = new QHBoxLayout;
    generateL->addWidget(txtGenerate);
    generateL->addWidget(btnGenerate);
    QWidget* generateW = new QWidget;
    generateW->setLayout(generateL);
    v->addWidget(generateW);

    QWidget* closeW = new QWidget;
    QHBoxLayout* closeL = new QHBoxLayout;
    closeL->addWidget(btnClose);
    closeW->setLayout(closeL);
    v->addWidget(closeW);

    mainL->addWidget(w);
}

void CartGui::reloadList(const vector<Movie> &movies) {
    lst->clear();
    for (const auto& m : movies) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(m.title()));
        item->setData(Qt::UserRole, QString::fromStdString(std::to_string(m.year())));
        lst->addItem(item);
    }
}
