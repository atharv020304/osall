#include <iostream>
#include <fstream>
#include <string>
#include<string.h>
#include <stdlib.h>
#include <time.h> 
#include "phase2.hpp"


void opsys::init(){                     

    for(int i =0;i<300;i++){
        for(int j=0;j<4;j++){
            MM[i][j] = '-';
        }
    }

    si = 0;
    ti = 0;
    pi = 0;
    IR[0] = ' ';
    R[0] = ' ';
    error = false;

}

void opsys::errmsg(int EM){

    ofstream outputFile("output.txt",ios::app);
    string error;

    switch(EM){

        case 0:
            error = "NO Error";
            outputFile<<error<<endl;
            break;
        case 1:
            error = "Out Of Data";
            outputFile<<error<<endl;
            break;
        case 2:
            error = "Line Limit Exceeded";
            outputFile<<error<<endl;
            break;
        case 3:
            error = "Time Limit Exceeded";
            outputFile<<error<<endl;
            break;
        case 4:
            error = "Opration Code Error";
            outputFile<<error<<endl;
            break;
        case 5:
            error = "Oprand Error";
            outputFile<<error<<endl;
            break;
        case 6:
            error = "Invalid Page Fault";
            outputFile<<error<<endl;
            break;
    }
     
    
        outputFile <<"si -> "<< si << endl;
        outputFile <<"ti -> "<< ti << endl;
        outputFile <<"pi -> "<< pi << endl;
        outputFile <<"ttl -> "<< pcb.ttl << endl;
        outputFile <<"tll -> "<< pcb.tll << endl;
        outputFile <<"ttc -> "<< pcb.ttc << endl;
        outputFile <<"Ic -> "<< Ic << endl;
        
       

}

void Terminate(){                              

    ofstream outputFile("output.txt",ios::app);
    outputFile<<"\n"<<endl;
    outputFile.close();

}

int find(char ch1,char ch2){     
    
    if(isdigit(ch1) && isdigit(ch2)){
        int tempop = ch1 - 48;
        tempop = tempop*10;
        return tempop;
    }
    else{
       
        return -1;
    }
}

void opsys::Write(char IR[],char MM[][4]){         

    pcb.llc++;                                     
    if(pcb.llc > pcb.tll){                         
        errmsg(2);
        Terminate();

        error=true;
        return;
    }
    
    int sadd = rd;
    int eadd = sadd+9;
    ofstream outputFile("output.txt",ios::app); 

    for(int i =sadd;i<eadd;i++){
        for(int j=0;j<4;j++){
            if(MM[i][j] != '-'){
            outputFile<<MM[i][j];
            }
        }
    }
    outputFile.close();
}


int di = 0;

void opsys::Read(string data[],char IR[],char MM[][4]){        

    
    string dataline = data[di++];

    if(dataline.at(0) == '$'){ 
        errmsg(1);
        error = true;
    }

    IR[3] = '0';  
     
    int row = rd;
    int col =0;
    for(int i =0;i<dataline.length();i++){
        if(col == 4){
            row++;
            col = 0;
        }
        MM[row][col] = dataline.at(i);
        col++;
    }
}


void opsys::MOS(string data[]){

    if(ti == 0 && si ==1 ){
        Read(data,IR,MM);
    }
    else if(ti ==0 && si==2){
        Write(IR,MM); 
    }
    else if(ti ==0 && si== 3 && pi ==0){
        errmsg(0);
        Terminate(); 
    }
    else if(ti ==2 && si== 1){
        errmsg(3);
        Terminate();
        error =  true;
    }
    else if(ti == 2 && si== 2){
        Write(IR,MM); 
        errmsg(3);
        Terminate(); 
        error =  true;
    }
    else if(ti == 2 && si== 3 && pi == 0){
        errmsg(0);
        Terminate();   
        error = true; 
    }
    else if(ti == 0 && pi == 1){
        errmsg(4);
        Terminate(); 
        error = true;
    }
    else if(ti ==0 && pi== 2){
        errmsg(5);
        Terminate(); 
        error = true;
    }
    else if(ti ==0 && pi== 3){
       
        if(function == "GD" || function =="SR"){       
            string progce;
            while(true){
        
            srand(time(0)); 
            int fream_no = rand()%30; 

            if(isFree(fream_no)){
                progce = to_string(fream_no);
                break;
            }else{
                continue;
            }
            }
             
            int k =3;
            for(int i=progce.length()-1;i>=0;i--){
                MM[ptr+(opAdd/10)][k] = progce.at(i);
                k--;
            }
            for(int i=k;i>=0;i--){
                MM[ptr+(opAdd/10)][i] = '0';
            }
           
            Ic--;
        }
        else if(function == "PD")                   
        {    
            errmsg(6);
            Terminate();
            error = true;
        }
        else{
            errmsg(4);
            Terminate(); 
            error = true;
        }
    }
    else if(ti ==2 && pi== 1){
        errmsg(3);
        errmsg(4);
        Terminate(); 
        error = true;
    }
    else if(ti ==2 && pi== 2){
        errmsg(3);
        errmsg(5);
        Terminate(); 
        error = true;
    }
    else if(ti ==2 && pi== 3){
        errmsg(3);
        Terminate(); 
        error = true;
    }
}

void opsys::simulation(){
    if(pcb.ttc > pcb.ttl){
        ti = 2;
    }
}

int opsys::addressMap(int vr){
    int pte ;
    int rd ;
    if(vr >= 0 && vr <= 99){
        pte = ptr + vr/10;
        if(MM[pte][0] == '*'){
            pi = 3;
            return -1;
        }
        else{
            string sfno ="";
            for(int i=0;i<4;i++){
                sfno = sfno + MM[pte][i];
            }
            int fno = stoi(sfno);
            rd = fno*10 + vr%10;
            return rd;
        }
    }
    else{
        pi = 2;
        string data[30] = {};
        MOS(data);
    }
}

void opsys::executeuserprogram(string data[]){
  
    while(true){

        if(error){

            return;

        }

    si = 3; 
    pi = 0;
    ti = 0;                        

    int ra = addressMap(Ic);
    if(ra == -1){                   
        Terminate();
        break;
    }

    for (int j = 0; j < 4; j++) {       
        IR[j] = MM[ra][j];
    }
  
    Ic++;
    
    function = "";
    function = function + IR[0];
    function = function + IR[1];
    int operandAdd ;

    if(IR[0] != 'H'){
        opAdd = find(IR[2],IR[3]);
        operandAdd = addressMap(opAdd);
        if(error){
            return;
        }
    }

    if(operandAdd == -1 && IR[0] != 'H'){
        pi = 3;
        simulation();
        MOS(data);
        continue;
    }

    
    if(function == "LR"){               
        int r_count =0;
        for(int i =operandAdd;i<=(operandAdd+9);i++){
            for(int j = 0;j<4;j++){
                R[r_count++] = MM[i][j];
            }
        }
       si = 0;
    }

    else if(function == "SR"){          

        int r_count = 0;
        for(int i = operandAdd;i<(operandAdd+9);i++){
            for(int j=0;j<4;j++){
                MM[i][j] = R[r_count++];
            }
        }  
        si =0;
    }

    else if(function == "CR"){          
        int r_count = 0;
        int flag = 0;
        for(int i=operandAdd;i<(operandAdd+9);i++){
            for(int j=0;j<4;j++){
                if(MM[i][j] != R[r_count++]){
                    flag = 1;
                    break;
                }
            }
        }
        if(flag == 0){
            C = true;
        }
        else{
            C = false;
        }
        si = 0;
    }

    else if(function == "BT"){              
        if(C == true){
            Ic = operandAdd + (IR[3] - 48);
            C = false;
        }
        else{
            continue;
        }
        si = 0;
    }

    else if(function == "GD"){          
        si = 1;
        rd = operandAdd;
        pcb.ttc = pcb.ttc+2;
    }
    else if(function == "PD"){          
        si = 2;
        pcb.ttc++;
        rd = operandAdd;
    }
    else if(IR[0] == 'H'){              
        si = 3;
        pcb.ttc++;
        simulation();
        MOS(data);
        break;
    }
    else{ 
        si = 0;
        pi = 1;
    }

    simulation();
    MOS(data);                         
    }
}

void opsys::startexecution(string data[]){
    Ic = 0;
    executeuserprogram(data);               
}

bool opsys::isFree(int fream_no){
    int esf = 0;
    for(int i=fream_no*10;i<fream_no*10+9;i++){
        for(int j=0;j<4;j++){
            if(MM[i][j] != '-'){
                esf = 1;
                break;
            }
        }
        if(esf == 0){
            return true;
       }
       else{
        return false;
       }
    }
}

void opsys::Allocatefream(){
    int ptsi ;              
    while (true)
    {
        srand(time(0)); 
        int fream_no = rand()%30; 
        
        if(isFree(fream_no)){
            ptsi = fream_no*10;
            for(int i=ptsi;i<=ptsi+9;i++){
                for(int j=0;j<4;j++){
                    MM[i][j] = '*';
                }
            }
            break;
        }
        else{
            continue;
        }
    }

    ptr = ptsi;
}

void opsys::Load(){
 
    
    if(buffer.length() > 40){
        printf("index out of bound!");
        return;
    } 

    string databuffer[4]; 
    int data_count =0;

    
    fin.open("inputx.txt");  
 
    while (getline(fin, buffer)) {      

        string opcode = buffer;
        string op = opcode.substr(0,4);
        
        if(op == "$AMJ"){   
            init();             
            Allocatefream();
            string pid = opcode.substr(4,4);
            string timelimit = opcode.substr(8,4);
            string linelimit = opcode.substr(12,4);
            pcb.pid = stoi(pid);
            pcb.ttl = stoi(timelimit);
            pcb.tll = stoi(linelimit);
            pcb.llc = 0;
            pcb.ttc = 0;
            continue;
        }
        
        else if(op == "$DTA"){
            while(getline(fin, buffer)){
                if(buffer.substr(0,1) == "$"){
                    break;
                }
                if (buffer.substr(0,1) != "$"){
                    databuffer[data_count++] = buffer;
                }
                else{
                   continue;
                }
            }
            startexecution(databuffer);         
        }

        else if(op == "$END"){
           break;
        }

         
        else{     
            string inst = buffer;
            int progei;
            while(true){

                srand(time(0)); 
                int fream_no = rand()%30; 

                if(isFree(fream_no)){
                    progei = fream_no;
                    break;
                }
                else{
                   continue;
                }
            }

            int row = progei*10;
            int col =0;
            for(int i =0;i<buffer.length();i++){
                if(col == 4){
                    row++;
                    col = 0;
                }
                MM[row][col] = buffer.at(i);
                if(buffer.at(i) == 'H'){
                    row++;
                    col = 0;
                }
                else{
                    col++;
                }
            }
            
            
            string progce = to_string(progei);
            int k =3;
            for(int i=progce.length()-1;i>=0;i--){
                MM[ptr][k] = progce.at(i);
                k--;
            }
            for(int i=k;i>=0;i--){
                MM[ptr][i] = '0';
            } 
        }
    }
    fin.close();    
}

void opsys::displayMemory(){        

    printf("\n Main Memory Simulation\n\n");
    for(int i =0;i<300;i++){
        printf("%2d     ",i);
        for(int j=0;j<4;j++){
            printf("%5c ",MM[i][j]);
        }
        printf("\n");
    }
}
