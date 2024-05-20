#include <iostream>
#include <fstream>
#include <string>
#include<string.h>
#include <stdlib.h>
#include <time.h> 
#ifndef _PHASETW0_HPP
#define _PHASETW0_HPP

using namespace std;


class opsys{

    private:
        char MM[300][4];    
        char IR[4];         
        char R[40];         
        int Ic;             
        int si;             
        int ti;             
        int pi;             
        bool C;             
        string buffer;      
        int EM;             
        int ptr;           
        int rd;
        string function;
        int opAdd;
        
        class processCB{

            public:
                int pid;    
                int ttl;    
                int tll;    
                int ttc;    
                int llc;   
        }pcb;

    
    public:
        void init();
        void Load();
        void startexecution(string data[]);
        void executeuserprogram(string data[]);
        void MOS(string data[]);
        void displayMemory();
        void Write(char IR[],char MM[][4]);
        void simulation();
        bool isFree(int fream_no);
        void Allocatefream();
        int addressMap(int vr);
        void Read(string data[],char IR[],char MM[][4]);
        void errmsg(int EM);
        bool error;
        fstream fin;
        fstream fout;

};



#endif /* _PHASETW0_HPP */