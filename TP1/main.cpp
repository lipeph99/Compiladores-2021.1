#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct list{
    string lbl;
    int pos;
    struct list *prox;
};

int label(fstream& input_file, fstream& out_file,string lbl){
    int cont = 0;
    string r1 = "";
    if(lbl=="WORD"){
        input_file >> r1;
        out_file << setfill('0') << setw(3) << r1 <<" ";
        cont+=2;
    }
    return cont;
}

void labelInsert(list* l, string lbl, int count){
    while (l->prox!=nullptr){
        l=l->prox;
    }
    l->prox = new list();
    l = l->prox;
    l->pos=count;
    l->lbl=lbl;
    l->prox=nullptr;
}

int instruct(fstream& input_file, fstream& out_file, string ins, list* lblUse, int count){
    int cod = -1;
    string r1 = "",r2="";
    if (ins=="HALT") cod=0;
    else if(ins=="LOAD") cod=1;
    else if(ins=="STORE") cod=2;
    else if(ins=="READ") cod=3;
    else if(ins=="WRITE") cod=4;
    else if(ins=="COPY") cod=5;
    else if(ins=="PUSH") cod=6;
    else if(ins=="POP") cod=7;
    else if(ins=="ADD") cod=8;
    else if(ins=="SUB") cod=9;
    else if(ins=="MUL") cod=10;
    else if(ins=="DIV") cod=11;
    else if(ins=="MOD") cod=12;
    else if(ins=="AND") cod=13;
    else if(ins=="OR") cod=14;
    else if(ins=="NOT") cod=15;
    else if(ins=="JUMP") cod=16;
    else if(ins=="JZ") cod=17;
    else if(ins=="JN") cod=18;
    else if(ins=="CALL") cod=19;
    else if(ins=="RET") cod=20;
    if(cod > -1)
        out_file << setfill('0') << setw(3) << cod <<" ";
    int cont=1;
    if (cod>0 && cod<20){
        input_file >> r1;
        cont++;
    }
    if (cod==1 || cod==2 || cod==5 || (cod >=8 && cod<=14)){
        input_file >> r2;
        cont++;
    }
    if(r1=="R0" || r1=="R1" || r1=="R2" || r1=="R3"){
        out_file << setfill('0') << setw(3) << r1[1] << " ";
        if(r2=="R0" || r2=="R1" || r2=="R2" || r2=="R3"){
            out_file << setfill('0') << setw(3) << r2[1] << " ";
        }else if(r2!=""){
            labelInsert(lblUse,r2,count+2);
            out_file << "yyy ";
        }
    }else if(r1!=""){
        out_file << "xxx ";
    }
    if(cod==0 || cod==-1){
        cont--;
    }
    return cont;
}

int main() {
	fstream input_file("MV.txt", ios::in);
    fstream out_file("ex.mv", ios::out);
    int countInst=0;
	if (!input_file||!out_file) {
		cout << "File not found";
	}
	else {
		string word;
        list* lblDef = new list();
        lblDef->lbl="head";
        lblDef->pos=-1;
        lblDef->prox=nullptr;
        list* lblUse = new list();
        lblUse->lbl="head";
        lblUse->pos=-1;
        lblUse->prox=nullptr;
        out_file << "MV-EXE\n\n";
        out_file << "    www 999 www\n\n";
		while (1) {
			input_file >> word;
            if(word[word.length()-1]==':'){
                labelInsert(lblDef,word,countInst);
                input_file >> word;
                countInst += label(input_file, out_file, word);
            }else{
                countInst += instruct(input_file, out_file, word, lblUse, countInst);
            }
            if (input_file.eof()){
                out_file << "\n";
                list* lUseAux = lblUse;
                while(lUseAux->prox!=nullptr){
                    lUseAux = lUseAux->prox;
                    list* lDefAux = lblDef;
                    while(lDefAux->prox!=nullptr){
                        lDefAux = lDefAux->prox;
                        if (lDefAux->lbl.compare(lDefAux->lbl)==0){
                            out_file.seekp((29 + 4*(lUseAux->pos)));
                            out_file << setfill('0') << setw(3) << (lDefAux->pos - lUseAux->pos);
                            break;
                        }
                    }
                }
                break;
            }
		}
	}
	input_file.close();
    out_file.seekp(10);
    out_file << setfill('0') << setw(3) << countInst;
    out_file.close();
	return 0;
}