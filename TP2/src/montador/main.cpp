#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct label{
    string lbl;
    int pos = -1;
    struct label *prox = nullptr;
    label(int type){
        if (type == 0){
            lbl="UseHead";
        }
        else if(type==1){
            lbl="DefHead";
        }
        else{
            throw invalid_argument("Tentando definir tipo de label inexistente");
        }
    }
    label(string lbl, int pos){
        this->lbl = lbl;
        this->pos = pos;
    }
};

struct labelLists{
    label *use = new label(0);
    label *def = new label(1);
    void add(int type, string lbl, int pos){
        label *aux;
        if (type==0){
            aux = use;
        }
        else if(type==1){
            aux = def;
        }
        else{
            throw invalid_argument("Tentando definir tipo de label inexistente");
            return;
        }
        while (aux->prox!=nullptr){
            aux = aux->prox;
        }
        aux->prox = new label(lbl,pos);
    }
};

int checkInst(string word){
    if (word=="HALT"||word=="R0") return 0;
    else if(word=="LOAD"||word=="R1") return 1;
    else if(word=="STORE"||word=="R2") return 2;
    else if(word=="READ"||word=="R3") return 3;
    else if(word=="WRITE") return 4;
    else if(word=="COPY") return 5;
    else if(word=="PUSH") return 6;
    else if(word=="POP") return 7;
    else if(word=="ADD") return 8;
    else if(word=="SUB") return 9;
    else if(word=="MUL") return 10;
    else if(word=="DIV") return 11;
    else if(word=="MOD") return 12;
    else if(word=="AND") return 13;
    else if(word=="OR") return 14;
    else if(word=="NOT") return 15;
    else if(word=="JUMP") return 16;
    else if(word=="JZ") return 17;
    else if(word=="JN") return 18;
    else if(word=="CALL") return 19;
    else if(word=="RET") return 20;
    else if(word=="WORD") return 21;
    else if(word=="END") return 22;
    else return -1;
}

bool is_number(string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int checkLabel(labelLists labels, string word, int count){
    label *aux = labels.def;
    while(aux->prox!=nullptr){
        aux=aux->prox;
        if(aux->lbl==(word+':')){
            return (aux->pos-count-1);
        }
    }
    return -1;
}

int main(int argc, char **argv){
    if (argc!=2){
        throw invalid_argument("Numero de parametros incorretos na chamada do montador");
    }
    labelLists labels;
    ifstream in;
    std::stringstream fileDir;
    fileDir << "../tst/" << argv[1];
    in.open(fileDir.str().c_str(), ios::in);
    if (!in){
        throw runtime_error("Arquivo a ser aberto nao encontrado!");
    }

    string line;
    stringstream fullFile;
    int count = 0;
    while(getline(in, line)) {
        stringstream lineIn(line);
        string word;
        while (lineIn >> word){
            if (word[0]==';'){
                break;
            }
            else if(word[word.length()-1]==':'){
                labels.add(1,word,count);
                fullFile << word << " ";
            }
            else{
                int ins = checkInst(word);
                if (ins == -1){
                    labels.add(0,word,count);
                    count++;
                    fullFile << word << " ";
                }
                else if (ins<=20){
                    fullFile << ins << " ";
                    count++;
                }
                else if(ins==21){
                    lineIn >> word;
                    count++;
                    fullFile << word << " ";
                }
            }
        }
    }
    in.close();
    std::stringstream fileDirOut;
    fileDirOut << "../tst/" << argv[1] << "_out";
    ofstream out;
    string name = argv[1]; 
    out.open(fileDirOut.str().c_str(), ios::out);
    out << count;

    string word;
    count = 0;
    while (fullFile >> word){
        if (word[word.length()-1]==':'||is_number(word)){
            out << " " << word;
            if (is_number(word)){
                count++;
            }
            continue;
        }else{
            int chk = checkLabel(labels,word,count);
            if(chk!=-1){
                out << " " << chk;
            }
            else{
                out << " " << word;
            }
            count++;
        }
    }
    

    return 0;
}

