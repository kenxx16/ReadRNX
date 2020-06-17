#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <regex>
#include <QMap>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void count_match(QStringList &ret, const std::string& user_string, const std::string& user_pattern, const std::string& flags = "o" ){

const bool flags_has_i = flags.find( "i" ) < flags.size();
const bool flags_has_g = flags.find( "g" ) < flags.size();

std::regex::flag_type regex_flag = flags_has_i ? std::regex_constants::icase : std::regex_constants::ECMAScript;
std::regex rx( user_pattern, regex_flag );
std::match_results< std::string::const_iterator > mr;

unsigned int counter = 0;
std::string temp = user_string;

while( std::regex_search( temp, mr, rx ) ){
    temp = mr.suffix().str();
    ret.push_back(mr[1].str().c_str());
    ++counter;
    }
}

//-------------------------------------------------чтение 2,11
void read_2_11(fstream &rnx){
    cout<<"!!";
    rinex file;
    bool stop = false;
    int num = 1;
    num++;
    cout << num << endl;
    while (!rnx.eof() and stop == false) {

        cout << num << endl;
        num++;

        string s;
        getline(rnx, s);
        smatch m;

        if(regex_search(s, m, regex("\\s{1,}(\\d{1,})\\s.*# / TYPES OF OBSERV"))){
            file.length = stoi(m[1]);
            int snum = stoi(m[1])/9;
            for (int i=0; i<=snum; i++) {
                smatch n;
                count_match(file.ObsType, s, "([A-Z][0-9])", "g");
                getline(rnx, s);
            }
            continue;
        }

//        if(regex_search(s, regex("TIME OF FIRST OBS"))){
//            cout << "!!!";
//            QDate DFirst;
//            QTime TFirst;
//            DFirst.setDate(su(str), stoi(m[2]), stoi(m[3]));
//            TFirst.setHMS(stoi(m[4]), stoi(m[5]), stoi(m[6]));
//            file.begin.setDate(DFirst);
//            file.begin.setTime(TFirst);
//        }
//        if(regex_search(s, m, regex("\\s*(\\d*)\\s*(\\d*)\\s*(\\d*)\\s*(\\d*)\\s*(\\d*)\\s*(\\S*)\\s*(\\w*)\\s*TIME OF LAST OBS"))){
//            QDate DLast;
//            QTime TLast;
//            DLast.setDate(stoi(m[1]), stoi(m[2]), stoi(m[3]));
//            TLast.setHMS(stoi(m[4]), stoi(m[5]), stoi(m[6]));
//            file.end.setDate(DLast);
//            file.end.setTime(TLast);
//            cout << file.end.toString().toStdString() << endl;
//        }

        if(regex_search(s, regex("END OF HEADER"))){
            stop = true;
        }
    }
}
//-------------------------------------------------открытие файлов
void MainWindow::on_pushButton_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.*");
    fstream rnx;
    rnx.open(str.toStdString(), ios::in);
    string ver;
    bool stop = false;

    while (!rnx.eof() and stop == false) {
        string s;
        getline(rnx, s);
        smatch m;
        if(regex_search(s, m, regex("\\s*(\\S*)\\s*.*RINEX VERSION / TYPE"))){
            cout<<m[1]<<endl;
            ver = m[1];
            stop = true;
            continue;
        }
    }
    if(ver == "2.11"){
        read_2_11(rnx);
    }
    else {
        cout<<qPrintable("Неизвестная версия Rinex")<<endl;
    }
}

