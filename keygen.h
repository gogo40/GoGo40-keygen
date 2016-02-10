/// @file: keygen.h
/*
 Copyright 2016 Péricles Lopes Machado

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef __KEYGEN_H__
#define __KEYGEN_H__

#include <cryptopp/dll.h>
#include <string>
#include <cryptopp/cryptlib.h>
#include <cryptopp/osrng.h>
#include <iostream>
#include <fstream>
#include <cryptopp/queue.h>
#include <cryptopp/rsa.h>

namespace gogo40_keygen {

class KeyGen {
public:
    KeyGen();
    virtual ~KeyGen();

    static void load(std::istream& in, CryptoPP::BufferedTransformation& bt);
    static void save(std::ostream& out, const CryptoPP::BufferedTransformation& bt);

    static void load_public_key(std::istream& in, CryptoPP::PublicKey& pub_key);
    static void save_public_key(std::ostream& out, const CryptoPP::PublicKey& pub_key);

    static void load_private_key(std::istream& in, CryptoPP::PrivateKey& pri_key);
    static void save_private_key(std::ostream& out, const CryptoPP::PrivateKey& pri_key);

    void generate_keys(std::ostream& pub_out, std::ostream& pri_out, int key_size);

    void encrypt(const CryptoPP::PublicKey& pub_key, const std::string& message, std::string& cipher);
    void decrypt(const CryptoPP::PrivateKey& pri_key, const std::string& cipher, std::string& message);
private:
    CryptoPP::AutoSeededRandomPool rng;
};


void save_message(std::ostream& out, const std::string& message);
void load_message(std::istream& in, std::string& message);


} // namespace gogo40_keygen

#endif // __KEYGEN_H__

