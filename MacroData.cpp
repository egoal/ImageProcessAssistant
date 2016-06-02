#include "MacroData.h"
#include <fstream>
#include <cassert>

using namespace std;

GD* GD::getInstance(){
    static GD* gd   =   new GD();

    return gd;
}

GD::GD(){
    initFromFile();
}

void GD::initFromFile(){
    ifstream fin(initfile, ios::in);
    if(fin.is_open()){
        string valname, equal, value;
        fin>>valname>>equal>>lastOpenFolder;
        fin>>valname>>equal>>lastSaveFolder;
    }else{
        lastOpenFolder  =   "";
        lastSaveFolder  =   "";
    }

    fin.close();
}
void GD::updateToFile(){
    ofstream fout(initfile, ios::out);
    assert(fout.is_open());

    fout<<"lastOpenFolder = "<<lastOpenFolder<<"\n";
    fout<<"lastSaveFolder = "<<lastSaveFolder<<"\n";
    fout.close();
}
