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

bool is_number(string& s)
{
    std::string::const_iterator it = s.begin();
    if (s[0]=='+'||s[0]=='-'){
        it++;
    }
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
    labelLists labels;

    stringstream fullFile;
    int count = 0;
    int size = 0;
    for (int i=1; i<argc; i++){
        fstream in(argv[i], ios::in);
        if (!in){
            throw runtime_error(("Não foi possível abrir o arquivo ",argv[i]));
        }
        string word;
        in >> word;
        if(is_number(word)){
            size += stoi(word);
        }else{
            throw runtime_error(("O arquivo ",argv[i]," não começa com um tamanho"));
        }
        while (!in.eof()){
            in >> word;
            if(word[word.length()-1]==':'){
                labels.add(1,word,count);
            }
            else if (is_number(word)){
                fullFile << word << " ";
                count++;
            }
            else{
                fullFile << word << " ";
                labels.add(0,word,count);
                count++;
            }
        }
    }

    string word;
    fstream out("ex.mv", ios::out);
    out << "EX-MV" << "\n\n" << size << " " << 100 << " " << 999 << " " << 100 << "\n\n";
    count=0;

    while (fullFile >> word){

        if (is_number(word)){
            out << word << " ";
            count++;
        }else{
            int chk = checkLabel(labels,word,count);
            if(chk==-1){
                throw runtime_error("D de Deu ruim");
            }
            else{
                out << chk << " ";
            }
            count++;
        }
    }

    return 0;
}