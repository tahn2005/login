#ifndef CRYPT_H
#define CRYPT_H

//function signatures for encrypting and decrypting passwords
std::uint32_t mod_exp(std::uint32_t base, std::uint32_t exponent, std::uint32_t mod);
std::string encrypt(std::string password);
std::string decrypt(std::string encrypt);

#endif