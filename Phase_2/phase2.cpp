#include <iostream>
#include <fstream>
#include <string>
#include<string.h>
#include <stdlib.h>
#include <time.h> 
#include "phase2.hpp"


void opsys::init(){                     //init function

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
     
    //  outputFile << error << endl;
     outputFile <<"si -> " << si << "\t ti-> " << ti << "\t pi-> " << pi << endl;
     outputFile << "ttl -> " << pcb.ttl << "\ttll -> " << pcb.tll <<"\tttc -> " << pcb.ttc << endl;
     outputFile << "Ic -> "<< Ic;

}

void Terminate(){                               //function for adding two blank line after execution of one job

    ofstream outputFile("output.txt",ios::app);
    outputFile<<"\n"<<endl;
    outputFile.close();

}

int find(char ch1,char ch2){      //function for return oprand Address
    
    if(isdigit(ch1) && isdigit(ch2)){
        int tempop = ch1 - 48;
        tempop = tempop*10;
        return tempop;
    }
    else{
       
        return -1;
    }
}

void opsys::Write(char IR[],char MM[][4]){         //write function

    pcb.llc++;                                     // llc increment
    if(pcb.llc > pcb.tll){                         // check tll range 
        errmsg(2);
        Terminate();
        // exit(0);
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

void opsys::Read(string data[],char IR[],char MM[][4]){         //read data from input file and store into memory

     //datacard missing condition (out of data)
    // if(data->empty()){
    //     errmsg(1);
    //     Terminate();
    //     // exit(0);
    // }
    string dataline = data[di++];

    if(dataline.at(0) == '$'){
        errmsg(1);
        // terminate();
        error = true;
    }

    IR[3] = '0';  //error handling
     
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
        // exit(0); 
        error =  true;
    }
    else if(ti == 2 && si== 2){
        Write(IR,MM); 
        errmsg(3);
        Terminate();
        // exit(0); 
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
        // exit(0);
        error = true;
    }
    else if(ti ==0 && pi== 2){
        errmsg(5);
        Terminate(); 
        // exit(0);
        error = true;
    }
    else if(ti ==0 && pi== 3){
        //page fault eror
        //valid --> allocate memmory and execute user program -->> ic--;
        //invalid --> terminate and EM = 6 
        if(function == "GD" || function =="SR"){       //valid page fault
            string progce;
            while(true){
        //random page assigning
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
        else if(function == "PD")                   // invalid page fault
        {    
            errmsg(6);
            Terminate();
            // exit(0);
            error = true;
        }
        else{
            errmsg(4);
            Terminate(); 
            // exit(0);
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
        // exit(0);
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
    ti = 0;                        //default si set to 3

    int ra = addressMap(Ic);
    if(ra == -1){                   //Invalid page fault
        Terminate();
        break;
    }

    for (int j = 0; j < 4; j++) {       // load instruction from memory to Instruction Register
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

    
    if(function == "LR"){               //load data from memory to register
        int r_count =0;
        for(int i =operandAdd;i<=(operandAdd+9);i++){
            for(int j = 0;j<4;j++){
                R[r_count++] = MM[i][j];
            }
        }
       si = 0;
    }

    else if(function == "SR"){          //store data into memory from register

        int r_count = 0;
        for(int i = operandAdd;i<(operandAdd+9);i++){
            for(int j=0;j<4;j++){
                MM[i][j] = R[r_count++];
            }
        }  
        si =0;
    }

    else if(function == "CR"){          //compare data of register and perticular memory location
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

    else if(function == "BT"){              //branch on true it is like jump instrction
        if(C == true){
            Ic = operandAdd + (IR[3] - 48);
            C = false;
        }
        else{
            continue;
        }
        si = 0;
    }

    else if(function == "GD"){          //get data
        si = 1;
        rd = operandAdd;
        pcb.ttc = pcb.ttc+2;
    }
    else if(function == "PD"){          //put data
        si = 2;
        pcb.ttc++;
        rd = operandAdd;
    }
    else if(IR[0] == 'H'){              //halt
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
    MOS(data);                         //  User Mode ---> kernal Mode
    }
}

void opsys::startexecution(string data[]){
    Ic = 0;
    executeuserprogram(data);               //function call for executeuserprogram() function
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
    int ptsi ;              //page table starting index
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
 
    //Max buffer size 40
    if(buffer.length() > 40){
        printf("index out of bound!");
        return;
    } 

    string databuffer[4]; //data buffer for storing data
    int data_count =0;

    
    fin.open("inputx.txt");  //input file open
 
    while (getline(fin, buffer)) {      //while loop for reading input file line by line

        string opcode = buffer;
        string op = opcode.substr(0,4);
        
        if(op == "$AMJ"){   
            init();             //memory reset / memory reallocation
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
        //data card
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
            startexecution(databuffer);         //call for startexecution
        }

        else if(op == "$END"){
           break;
        }

         // program card control
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
            
            //pagetable update
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
    fin.close();    //after reading all file closing the file
}

void opsys::displayMemory(){        //function for display memory

    printf("\n Main Memory Simulation\n\n");
    for(int i =0;i<300;i++){
        printf("%2d     ",i);
        for(int j=0;j<4;j++){
            printf("%5c ",MM[i][j]);
        }
        printf("\n");
    }
}
