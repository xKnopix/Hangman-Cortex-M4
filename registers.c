#include "registers.h"

void writeToRegister(uint32_t address, uint32_t value){
    
    uint32_t *pointer_to_address;
    
    //pointer wird auf Addresse gesetzt
    pointer_to_address = (uint32_t *)address;
    
    //addresse bekommt wert
    *pointer_to_address = value;
}

uint32_t readFromRegister(uint32_t address){
    uint32_t *pointer; //"pointer variable"
    uint32_t value; //Wert
    
    pointer = (uint32_t *)address; //Setzte pointer zu addesse

    value = *pointer; //dereferneziere Pointer und weise den Wert value zu 

    return value;
    
}