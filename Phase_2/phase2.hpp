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
        char MM[300][4];    //main memory
        char IR[4];         // instruction register
        char R[40];         //general purpose register
        int Ic;             // instruction counter
        int si;             // system interuppt
        int ti;             // timer inpeterupt
        int pi;             //process interuppt 
        bool C;             // toggle 
        string buffer;      // buffer
        int EM;             //error meassage
        int ptr;           // page table pointer
        int rd;
        string function;
        int opAdd;
        
        class processCB{

            public:
                int pid;    //process id
                int ttl;    // total time limit
                int tll;    //total line limit
                int ttc;    //total time counter
                int llc;    //line limit counter
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