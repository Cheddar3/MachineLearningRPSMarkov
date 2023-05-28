#pragma once

#ifndef GLOBALHELPER_H
#define GLOBALHELPER_H

#include <string>

void copyStringToOtherString(std::string& stringToCopyTo, std::string extract, int frompos, int topos){
    for(int i = frompos; i < topos; i++){
        stringToCopyTo.push_back(extract.at(i));
    }
}

#endif