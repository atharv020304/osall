#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <time.h> 
#include "phase2.hpp"

int main(){

    opsys vos;

    vos.init();                
          
    vos.Load();           

    cout<<"\n\n\n***After Execution of Job***\n"<<endl;
    
    vos.displayMemory();       
   
    return 0;
}
