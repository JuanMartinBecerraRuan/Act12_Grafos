#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <fstream>

list<Neurona> lista;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

bool MainWindow::id_repetido(int id){
    bool bandera = true;
    list<Neurona>::iterator aux = lista.begin();
    while(aux!=lista.end()){
        if(id==aux->getId()){
            bandera=false;
        }
        aux++;
    }
    return bandera;
}

void MainWindow::ordenamiento_burbuja_mejorada(list<Neurona> &objetos){
    int n = objetos.size();
    bool intercambio = true;
    auto iterador_actual = objetos.begin();
    auto iterador_siguiente = objetos.begin();
    if (n < 2) {
        return;
    }
    for (int i = 0; i < n - 1 && intercambio; i++) {
        intercambio = false;
        iterador_actual = objetos.begin();
        iterador_siguiente = objetos.begin();
        iterador_siguiente++;

        for (int j = 0; j < n - 1 - i; j++) {
            if (*iterador_actual < *iterador_siguiente) {
                swap(*iterador_actual, *iterador_siguiente);
                intercambio = true;
            }
            iterador_actual++;
            iterador_siguiente++;
        }
    }
}

double MainWindow::distance(Point p1, Point p2){
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

pair<MainWindow::Point, int> MainWindow::bruteForce(Point p, vector<Point> &points){
    double min_dist = INFINITY; // distancia mínima inicializada en infinito
    Point closest_point; // punto más cercano
    for (auto point : points) { // recorremos todos los puntos
        if (point.x == p.x && point.y == p.y) { // validamos si el punto es el mismo
            continue;
        }
        double dist = distance(p, point); // calculamos la distancia
        if (dist < min_dist) { // si la distancia es menor que la actual
            min_dist = dist; // actualizamos la distancia mínima
            closest_point = point; // actualizamos el punto más cercano
        }
    }
    return make_pair(closest_point, min_dist);
}

void MainWindow::on_pushButton_clicked(){
    //INSERTAR AL INICIO
    int id, posicion_x,posicion_y,red,green,blue;
    double voltaje;
    id=ui->id_spinBox->value();
    bool bandera;
    bandera=id_repetido(id);
    voltaje=ui->voltaje_doubleSpinBox->value();
    posicion_x=ui->Pos_x_spinBox_2->value();
    posicion_y=ui->Pos_y_spinBox_2->value();
    red=ui->red_spinBox_4->value();
    green=ui->green_spinBox_5->value();
    blue=ui->spinBox_6->value();
    if(!bandera){
        QMessageBox::warning(this,"Mensaje","Id repetido.");
    }else{
        if((id == 0 or voltaje == 0 or id == NULL or voltaje == NULL)){
            QMessageBox::warning(this,"Mensaje","Tiene que existir un voltaje y un id.");
        }else{
            Neurona *nuevo = new Neurona(id,voltaje,posicion_x,posicion_y,red,green,blue);
            lista.push_front(*nuevo);
            ui->id_spinBox->clear();
            ui->voltaje_doubleSpinBox->clear();
            ui->Pos_x_spinBox_2->clear();
            ui->Pos_y_spinBox_2->clear();
            ui->red_spinBox_4->clear();
            ui->green_spinBox_5->clear();
            ui->spinBox_6->clear();
        }
    }
}

void MainWindow::on_pushButton_2_clicked(){
    //INSERTAR AL FINAL
    int id, posicion_x,posicion_y,red,green,blue;
    double voltaje;
    id=ui->id_spinBox->value();
    bool bandera;
    bandera=id_repetido(id);
    voltaje=ui->voltaje_doubleSpinBox->value();
    posicion_x=ui->Pos_x_spinBox_2->value();
    posicion_y=ui->Pos_y_spinBox_2->value();
    red=ui->red_spinBox_4->value();
    green=ui->green_spinBox_5->value();
    blue=ui->spinBox_6->value();
    if(!bandera){
        QMessageBox::warning(this,"Mensaje","Id repetido.");
    }else{
        if(id == 0 or voltaje == 0 or id == NULL or voltaje == NULL){
            QMessageBox::warning(this,"Mensaje","Tiene que existir un voltaje y un id.");
        }else{
            Neurona *nuevo = new Neurona(id,voltaje,posicion_x,posicion_y,red,green,blue);
            lista.push_back(*nuevo);
            ui->id_spinBox->clear();
            ui->voltaje_doubleSpinBox->clear();
            ui->Pos_x_spinBox_2->clear();
            ui->Pos_y_spinBox_2->clear();
            ui->red_spinBox_4->clear();
            ui->green_spinBox_5->clear();
            ui->spinBox_6->clear();
        }
    }
}

void MainWindow::on_pushButton_3_clicked(){
    //MOSTRAR EN EL QPLAINTEXTEDID
    if(!lista.empty()){
        ui->plainTextEdit->clear();
        list<Neurona>::iterator aux = lista.begin();
        while(aux!=lista.end()){
            ui->plainTextEdit->insertPlainText("ID: "+QString::number(aux->getId())+"\n");
            ui->plainTextEdit->insertPlainText("VOLTAJE: "+QString::number(aux->getVoltaje())+"\n");
            ui->plainTextEdit->insertPlainText("POS_X: "+QString::number(aux->getPosX())+"\n");
            ui->plainTextEdit->insertPlainText("POS_Y: "+QString::number(aux->getPosY())+"\n");
            ui->plainTextEdit->insertPlainText("RED: "+QString::number(aux->getRed())+"\n");
            ui->plainTextEdit->insertPlainText("GREEN: "+QString::number(aux->getGreen())+"\n");
            ui->plainTextEdit->insertPlainText("RED: "+QString::number(aux->getRed())+"\n\n");
            aux++;
        }
    }else{
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText("La lista esta vacia...");
    }
}


void MainWindow::on_pushButton_4_clicked(){
    //RESPALDO DE UN ARCHIVO
    string delimitador = "|";
    if(!lista.empty()){
        QString filename = QFileDialog::getSaveFileName(this, "Save file","respaldo.txt");
        ofstream archivo(filename.toStdString(),ios::out);
        list<Neurona>::iterator aux = lista.begin();
        while(aux!=lista.end()){
            archivo<<aux->getId()<<delimitador;
            archivo<<aux->getVoltaje()<<delimitador;
            archivo<<aux->getPosX()<<delimitador;
            archivo<<aux->getPosY()<<delimitador;
            archivo<<aux->getRed()<<delimitador;
            archivo<<aux->getGreen()<<delimitador;
            archivo<<aux->getBlue()<<delimitador;
            aux++;
        }
        QMessageBox::information(this,"Guardado","Guardado exitosamente...");
    }else{
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText("La lista esta vacia...");
    }
}


void MainWindow::on_pushButton_5_clicked(){
    //RECUPERAR DE UN ARCHIVO
    int id, posicion_x,posicion_y,red,green,blue;
    double voltaje;
    string registro;
    QString filename = QFileDialog::getOpenFileName(this, "Open file","C://");
    ifstream archivo(filename.toStdString(),ios::in);
    if(!archivo.fail()){
        while(!archivo.eof()){
            getline(archivo,registro,'|');
            id=atoi(registro.c_str());
            if(id != NULL){
                getline(archivo,registro,'|');
                voltaje=strtof(registro.c_str(), nullptr);
                getline(archivo,registro,'|');
                posicion_x=atoi(registro.c_str());
                getline(archivo,registro,'|');
                posicion_y=atoi(registro.c_str());
                getline(archivo,registro,'|');
                red=atoi(registro.c_str());
                getline(archivo,registro,'|');
                green=atoi(registro.c_str());
                getline(archivo,registro,'|');
                blue=atoi(registro.c_str());
                Neurona *nuevo = new Neurona(id,voltaje,posicion_x,posicion_y,red,green,blue);
                lista.push_back(*nuevo);
            }
        }
        QMessageBox::information(this,"Recuperado","Se recuperaron los archivos correctamente...");
    }else{
        QMessageBox::critical(this,"Error","El archivo no se abrio correctamente...");
    }
}

void MainWindow::on_tabWidget_tabBarClicked(int index){
    //MOSTRAR ELEMENTOS EN TABLA AL PRESIONAR EL BAR "BUSCAR"
    ui->tableWidget->clear();
    int tamano = lista.size();
    int i=0;
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(tamano);
    QStringList nom_colum={"ID","VOLTAJE","POS_X","POS_Y"};
    ui->tableWidget->setHorizontalHeaderLabels(nom_colum);
    if(index == 1){
        if(!lista.empty()){
            list<Neurona>::iterator aux = lista.begin();
            while(aux!=lista.end()){
                QString a = QString::number(aux->getId());
                QTableWidgetItem *c= new QTableWidgetItem(a);
                ui->tableWidget->setItem(i,0,c);
                a = QString::number(aux->getVoltaje());
                c= new QTableWidgetItem(a);
                ui->tableWidget->setItem(i,1,c);
                a = QString::number(aux->getPosX());
                c= new QTableWidgetItem(a);
                ui->tableWidget->setItem(i,2,c);
                a = QString::number(aux->getPosY());
                c= new QTableWidgetItem(a);
                ui->tableWidget->setItem(i,3,c);
                aux++;
                i++;
            }
        }
    }
}

void MainWindow::on_pushButton_6_clicked(){
    //BUSCAR
    bool bandera = false;
    QString line_text=ui->lineEdit->text();
    list<Neurona>::iterator aux = lista.begin();
    while(aux!=lista.end()){
        if(line_text==QString::number(aux->getId())){
            ui->tableWidget->clear();
            ui->tableWidget->setColumnCount(4);
            ui->tableWidget->setRowCount(1);
            QStringList nom_colum={"ID","VOLTAJE","POS_X","POS_Y"};
            QString a = QString::number(aux->getId());
            QTableWidgetItem *c= new QTableWidgetItem(a);
            ui->tableWidget->setItem(0,0,c);
            a = QString::number(aux->getVoltaje());
            c= new QTableWidgetItem(a);
            ui->tableWidget->setItem(0,1,c);
            a = QString::number(aux->getPosX());
            c= new QTableWidgetItem(a);
            ui->tableWidget->setItem(0,2,c);
            a = QString::number(aux->getPosY());
            c= new QTableWidgetItem(a);
            ui->tableWidget->setItem(0,3,c);
            bandera=true;
        }
        aux++;
    }
    if(!bandera){
        QMessageBox::information(this,"Buscar","Id no encontrado...");
    }
}

void MainWindow::on_pushButton_7_clicked(){
    //MOSTRAR EN TABLA
    ui->tableWidget->clear();
    int tamano = lista.size();
    int i=0;
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(tamano);
    QStringList nom_colum={"ID","VOLTAJE","POS_X","POS_Y"};
    ui->tableWidget->setHorizontalHeaderLabels(nom_colum);
    if(!lista.empty()){
        list<Neurona>::iterator aux = lista.begin();
        while(aux!=lista.end()){
            QString a = QString::number(aux->getId());
            QTableWidgetItem *c= new QTableWidgetItem(a);
            ui->tableWidget->setItem(i,0,c);
            a = QString::number(aux->getVoltaje());
            c= new QTableWidgetItem(a);
            ui->tableWidget->setItem(i,1,c);
            a = QString::number(aux->getPosX());
            c= new QTableWidgetItem(a);
            ui->tableWidget->setItem(i,2,c);
            a = QString::number(aux->getPosY());
            c= new QTableWidgetItem(a);
            ui->tableWidget->setItem(i,3,c);
            aux++;
            i++;
        }
    }
}

void MainWindow::on_pushButton_8_clicked(){
    //GRAFICAR
    if(!lista.empty()){
        for(list<Neurona>::iterator aux = lista.begin();aux!=lista.end();aux++){
            QPen pen;
            pen.setWidth(2);
            QColor color(aux->getRed(),aux->getGreen(),aux->getBlue());
            pen.setColor(color);
            grafica.addEllipse(aux->getPosX(),aux->getPosY(),aux->getVoltaje(),aux->getVoltaje(),pen);
            ui->graphicsView->setScene(&grafica);
        }
    }
}

void MainWindow::on_pushButton_9_clicked(){
    //LIMPIAR GRÁFICA
    ui->plainTextEdit_2->clear();
    grafica.clear();
}

void MainWindow::on_pushButton_10_clicked(){
    //ORDENAR
    ordenamiento_burbuja_mejorada(lista);
}

void MainWindow::on_pushButton_11_clicked(){
    //GRAFICAR (FUERZABRUTA)
    ui->plainTextEdit_2->clear();
    list<pair<int, list<int>>> lista_adyacencia;
    list<pair<Point, Point>> conexiones;
    vector<Point> points;
    if(!lista.empty()){
        for(list<Neurona>::iterator aux = lista.begin();aux!=lista.end();aux++){
            Point nuevo = {aux->getPosX(), aux->getPosY(), aux->getId()};
            points.push_back(nuevo);
        }
    }
    int tam = points.size();
    for(int i=0;i<tam;i++){
        Point p = points[i];
        pair<Point, int> aux = bruteForce(p, points);
        Point closestPoint = aux.first;
        int x1 = static_cast<int>(p.x);
        int y1 = static_cast<int>(p.y);
        int x2 = static_cast<int>(aux.first.x);
        int y2 = static_cast<int>(aux.first.y);
        QGraphicsTextItem *labelItem = new QGraphicsTextItem(QString::number(p.id));
        labelItem->setPos(p.x, p.y);
        QPointF punto1(x1,y1);
        QPointF punto2(x2,y2);
        QLineF linea(punto1, punto2);
        pair<Point, Point> ejemplo = make_pair(p,closestPoint);
        conexiones.push_back(ejemplo);
        QGraphicsTextItem *label = new QGraphicsTextItem(QString::number(aux.second));
        QColor color(Qt::red);
        label->setDefaultTextColor(color);
        label->setPos((linea.p1() + linea.p2()) / 2);
        grafica.addItem(label);
        grafica.addLine(linea);
        grafica.addItem(labelItem);
    }
    for (auto it = conexiones.begin(); it != conexiones.end(); ++it) {
        for (auto it2 = conexiones.begin(); it2 != conexiones.end(); ++it2) {
            if (it->first.id == it2->second.id && it->second.id == it2->first.id){
                it = conexiones.erase(it);
            }
        }
    }
    for(list<pair<Point, Point>>::iterator i = conexiones.begin();i!=conexiones.end();i++){
        list<int> sublista1;
        for(list<pair<Point, Point>>::iterator j = conexiones.begin();j!=conexiones.end();j++){
            if(i->first.id==j->second.id){
                sublista1.push_back(j->first.id);
            }
        }
        std::list<int>::iterator it = std::find(sublista1.begin(), sublista1.end(), i->second.id);
        if(it != sublista1.end()){
            continue;
        }else{
            sublista1.push_back(i->second.id);
        }
        pair<int, list<int>> ejemplo = make_pair(i->first.id, sublista1);
        lista_adyacencia.push_back(ejemplo);
    }
    for (auto& par : lista_adyacencia) {
        ui->plainTextEdit_2->insertPlainText("Nodo "+QString::number(par.first)+" conectado a:");
        for (auto& entero : par.second) {
            ui->plainTextEdit_2->insertPlainText(QString::number(entero)+" ");
        }
        ui->plainTextEdit_2->insertPlainText("\n");
    }
    for (auto it = conexiones.begin(); it != conexiones.end(); ++it){
        int x_1=it->first.x,y_1=it->first.y,x_2=it->second.x,y_2=it->second.y;
        QPainterPath path;
        path.moveTo(x_1, y_1);
        path.lineTo(x_2, y_2);
        double angle = atan2(y_2 - y_1, x_2 - x_1);

        // Calcular las coordenadas de la punta de la flecha
        double arrowSize = 10; // Tamaño de la punta de la flecha
        double x3 = x_2 - arrowSize * cos(angle + M_PI / 6);
        double y3 = y_2 - arrowSize * sin(angle + M_PI / 6);
        double x4 = x_2 - arrowSize * cos(angle - M_PI / 6);
        double y4 = y_2 - arrowSize * sin(angle - M_PI / 6);

        // Añadir la punta de la flecha al QPainterPath
        path.moveTo(x3, y3);
        path.lineTo(x_2, y_2);
        path.lineTo(x4, y4);
        QGraphicsPathItem *arrowItem = new QGraphicsPathItem(path);
        grafica.addItem(arrowItem);
    }
    ui->graphicsView->setScene(&grafica);
}
