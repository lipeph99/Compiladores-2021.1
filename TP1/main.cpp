#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct label{
    string lbl;
    int pos;
    struct label *prox;
};

int label(fstream& my_file, fstream& myfile,string lbl){
    int cont = 0;
    string r1 = "";
    if(lbl=="WORD"){
        my_file >> r1;
        myfile << r1 <<" ";
        cont+=2;
    }
    return cont;
}

int instruct(fstream& my_file, fstream& myfile, string ins){
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
        myfile << cod <<" ";
    int cont=1;
    if (cod>0 && cod<20){
        my_file >> r1;
        cont++;
    }
    if (cod==1 || cod==2 || cod==5 || (cod >=8 && cod<=14)){
        my_file >> r2;
        cont++;
    }
    if(r1=="R0" || r1=="R1" || r1=="R2" || r1=="R3"){
        myfile << r1[1] << " ";
        if(r2=="R0" || r2=="R1" || r2=="R2" || r2=="R3"){
            myfile << r2[1] << " ";
        }else if(r2!=""){
            myfile << "y ";
        }
    }else if(r1!=""){
        myfile << "x ";
    }
    if(cod==0 || cod==-1){
        cont--;
    }
    return cont;
}

int main() {
	fstream my_file("MV.txt", ios::in);
    fstream myfile("ex.mv", ios::out);
    int w=0;
	if (!my_file||!myfile) {
		cout << "File not found";
	}
	else {
		string word;
        myfile << "MV-EXE\n\n";
        myfile << "    www 999 xxx\n\n";
		while (1) {
			my_file >> word;
            if(word[word.length()-1]==':'){
                my_file >> word;
                w += label(my_file, myfile, word);
            }else{
                w += instruct(my_file, myfile, word);
            }
            if (my_file.eof())
				break;
		}
	}
	my_file.close();
    myfile << "\n";
    myfile.seekp(10);
    myfile << setfill('0') << setw(3) << w;
    myfile.close();
	return 0;
}