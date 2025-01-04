#include <vector>
#include <cstdint>
#include <iostream>
#include <string>
#include <sstream>
#include "crypt.h"
using namespace std;

//calculates (base ^ exponent) % mod
uint32_t mod_exp(uint32_t base, uint32_t exponent, uint32_t mod){
    if (mod == 1) return 0;  
    if (exponent == 0) return 1;
    base = base % mod; 
    uint32_t result = 1;
    while(exponent > 0){
        if(exponent & 1){
            result = (static_cast<uint64_t>(result) * base) % mod;  
        }
        exponent >>= 1;
        base = (static_cast<uint64_t>(base) * base) % mod;  
    }
    return result;
}

//rsa encrypts a string by letter using e=17, n=3233
string encrypt(string password){
    string passkey;
    for(int i=0; i < password.length(); i++){
        passkey += to_string(mod_exp(static_cast<uint32_t>(password[i]), 17, 3233));
        passkey += '-';
    }
    return passkey;
}

//rsa decrypts a string using d=2753, n=3233
string decrypt(string encrypt){
    string password;
    stringstream ss(encrypt);
    string part;
    while (getline(ss, part, '-')) {
        if (!part.empty()) {  // Avoid empty parts
            password += static_cast<char>(mod_exp(static_cast<uint32_t>(stoi(part)), 2753, 3233));
        }
    }
    return password;
}