#include <iostream>
#include <string>
#include "senha.h"

std::string user = "admin";
std::string senha = "123";

bool verificarLogin(std::string a, std::string b){
    if(a == user && b == senha)
        return true;
    else
        return false;
}
