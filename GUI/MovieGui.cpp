//
// Created by david on 12.05.2022.
//

#include "MovieGui.h"
#include "../utils/MyUtils.h"



void MovieGui::initGUICmps() {
    //cosul de cumparaturi



    setLayout(mainL);
    QWidget* wDreapta = new QWidget;
    QVBoxLayout* v = new QVBoxLayout;
    wDreapta->setLayout(v);
    lst = new QListWidget;
    v->addWidget(lst);

    QWidget* widBtnDreapta = new QWidget;
    QHBoxLayout* lyBtnsDr = new QHBoxLayout;
    widBtnDreapta->setLayout(lyBtnsDr);
    btnFilterByGenre = new QPushButton("filtrare dupa titlu");
    lyBtnsDr->addWidget(btnFilterByGenre);

    btnFilterByYear = new QPushButton("filtrare dupa an");
    lyBtnsDr->addWidget(btnFilterByYear);

    btnUndo = new QPushButton("undo");
    lyBtnsDr->addWidget(btnUndo);

    v->addWidget(widBtnDreapta);
    mainL->addWidget(wDreapta);

    QWidget* widInput = new QWidget;
    QFormLayout* form = new QFormLayout;
    widInput->setLayout(form);
    txtTitle = new QLineEdit;
    QLabel* title = new QLabel("titlu");
    form->addWidget(title);
    form->addRow(txtTitle);
    QLabel* genre = new QLabel("gen");
    form->addWidget(genre);
    txtGenre = new QLineEdit;
    form->addRow(txtGenre);
    QLabel* year = new QLabel("an");
    form->addWidget(year);
    txtYear = new QLineEdit;
    form->addRow(txtYear);
    QLabel* protagonist = new QLabel("protagonist");
    form->addWidget(protagonist);
    txtProtagonist = new QLineEdit;
    form->addRow(txtProtagonist);
    btnAdd = new QPushButton("Adauga");
    btnDel = new QPushButton("Sterge");
    btnMod = new QPushButton("Modificare");
    form->addWidget(btnAdd);
    form->addWidget(btnDel);
    form->addWidget(btnMod);
    mainL->addWidget(widInput);

    btnDyn->setLayout(lyBtnDy);
    mainL->addWidget(btnDyn);

    QWidget* wCos = new QWidget;
    QVBoxLayout* cosL = new QVBoxLayout;
    cartLabel = new QLabel("0 produse in cos");
    cosL->addWidget(cartLabel);
    wCos->setLayout(cosL);
    btnAddCart = new QPushButton("adauga in cos");
    btnOpenCart = new QPushButton("vezi cos");
    btnOpenRCart = new QPushButton("vezi produse");
    cosL->addWidget(btnAddCart);
    cosL->addWidget(btnOpenCart);
    cosL->addWidget(btnOpenRCart);
    mainL->addWidget(wCos);

    mainL->addWidget(btnDyn2);
    btnDyn2->setLayout(btnDynL);
}

void MovieGui::updateCartLabel(){
    cartLabel->clear();
    cartLabel->setText(QString::fromStdString(std::to_string(service.cartSize())+" produse in cos"));
}

void MovieGui::connectSignalsSlots() {
    QObject::connect(btnOpenCart,
                     &QPushButton::clicked,
                     this,
                     &MovieGui::openCartWindow);

    QObject::connect(btnOpenRCart,
                     &QPushButton::clicked,
                     this,
                     &MovieGui::openCartRWindow);

    QObject::connect(btnAddCart, &QPushButton::clicked, [&](){
        try {
            service.addCart(txtTitle->text().toStdString(),
                            MyUtils::stringToInt(txtYear->text().toStdString()));
            updateCartLabel();
        }catch(uiException& e){
            QMessageBox::warning(this,
                                 "warning",
                                 QString::fromStdString(e.msg));

        }catch(repoException& e){
            QMessageBox::warning(this,
                                 "Warning",
                                 QString::fromStdString(e.msg));
        }
    });

    QObject::connect(btnFilterByGenre, &QPushButton::clicked, [&]() {
        //qDebug() << "am ajuns aici!!!";
        if(txtTitle->text().toStdString() == ""){
            reloadList(service.getAll());
        }else
            reloadList(service.filterByTitle(txtTitle->text().toStdString()));
    });
    QObject::connect(btnUndo, &QPushButton::clicked, [&](){
        service.undo();
        reloadList(service.getAll());
    });
    QObject::connect(btnFilterByYear, &QPushButton::clicked, [&](){
        if(txtYear->text().toStdString() == ""){
            reloadList(service.getAll());
        }else
            try {
                reloadList(service.filterByYear(MyUtils::stringToInt(txtYear->text().toStdString())));
            }catch(uiException& e){
                QMessageBox::warning(this,
                                     "Warning",
                                     QString::fromStdString(e.msg));
            }
    });
    QObject::connect(btnDel,
                     &QPushButton::clicked,
                     this, &MovieGui::delMovie);

    QObject::connect(btnMod,
                     &QPushButton::clicked,
                     this,
                     &MovieGui::modMovie);

    QObject::connect(btnAdd, &QPushButton::clicked, this, &MovieGui::addNewMovie);

    QObject::connect(lst, &QListWidget::itemSelectionChanged, [&](){
        auto sel = lst->selectedItems();
        if(sel.isEmpty()){
            txtTitle->setText("");
            txtGenre->setText("");
            txtYear->setText("");
            txtProtagonist->setText("");
        }else{
            auto selItem = sel.at(0);
            auto title = selItem->text();
            auto year = selItem->data(Qt::UserRole).toString();
            txtTitle->setText(title);
            txtYear->setText(year);
            auto m = service.search(title.toStdString(), MyUtils::stringToInt(year.toStdString()));
            txtGenre->setText(QString::fromStdString(m.genre()));
            txtProtagonist->setText(QString::fromStdString(m.protagonist()));
        }
    });
}

void clearLayout(QLayout* layout, bool deleteWidgets = true)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

void MovieGui::addButtons(const std::vector<Movie> &movies){
    std::vector<std::string> genres;
    for(const auto& m: movies){
        bool gasit = false;
        for(auto& g: genres){
            if(g == m.genre())gasit = true;
        }
        if(!gasit){
            genres.push_back(m.genre());
        }
    }
    clearLayout(btnDynL);
    for(auto& g: genres){
        QPushButton* but = new QPushButton{QString::fromStdString(g)};
        btnDynL->addWidget(but);
        QObject::connect(but, &QPushButton::clicked, [but, this](){
            vector<Movie> v;
            for(auto& m : service.getAll()){
                if(m.genre() == but->text().toStdString())
                    v.push_back(m);
            }
            reloadList(v);
        });
    }
}

void MovieGui::reloadList(const vector<Movie> &movies) {
    lst->clear();
    for (const auto& m : movies) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(m.title()));
        item->setData(Qt::UserRole, QString::fromStdString(std::to_string(m.year())));
        lst->addItem(item);
    }
    addButtons(movies);
}

void MovieGui::addNewMovie() {
    try{
        std::string title = txtTitle->text().toStdString();
        std::string genre = txtGenre->text().toStdString();
        int year  = MyUtils::stringToInt(txtYear->text().toStdString());
        std::string protagonist = txtProtagonist->text().toStdString();
        service.add(title, genre, year, protagonist);
        reloadList(service.getAll());
    }catch(repoException& e){
        QMessageBox::warning(this,
                             "Warning",
                             QString::fromStdString(e.msg));
    }catch(uiException& e){
        QMessageBox::warning(this,
                             "Warning",
                             QString::fromStdString(e.msg));
    }
}

void MovieGui::modMovie() {
    try{
        service.mod(txtTitle->text().toStdString(),
                    MyUtils::stringToInt(txtYear->text().toStdString()),
                    txtGenre->text().toStdString(),
                    txtProtagonist->text().toStdString());
        reloadList(service.getAll());
    }catch(repoException& e){
        QMessageBox::warning(this,
                             "Warning",
                             QString::fromStdString(e.msg));
    }catch(uiException& e){
        QMessageBox::warning(this,
                             "Warning",
                             QString::fromStdString(e.msg));
    }
}

void MovieGui::delMovie() {
    try{
        service.del(txtTitle->text().toStdString(),
                    MyUtils::stringToInt(txtYear->text().toStdString()));
        reloadList(service.getAll());
    }catch(repoException& e){
        QMessageBox::warning(this,
                             "Warning",
                             QString::fromStdString(e.msg));
    }catch(uiException& e){
        QMessageBox::warning(this,
                             "Warning",
                             QString::fromStdString(e.msg));
    }
}

void MovieGui::openCartWindow() {
    cartWindow->show();
}

void MovieGui::openCartRWindow() {
    cartRW->show();
}
