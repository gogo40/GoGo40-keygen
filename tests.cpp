/// @file: tests.cpp
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

#include "keygen.h"


int run_test1()
{
    std::ios_base::sync_with_stdio(false);
    try {

        //Testing key generation...
        {
            gogo40_keygen::KeyGen key_gen;

            std::ofstream pub_out("key_test1.pub");
            std::ofstream pri_out("key_test1.pri");

            key_gen.generate_keys(pub_out, pri_out);
        }

        CryptoPP::RSA::PublicKey pub_key;
        CryptoPP::RSA::PrivateKey pri_key;

        //Testing load keys...
        {
            std::ifstream pub_in("key_test1.pub");
            std::ifstream pri_in("key_test1.pri");

            gogo40_keygen::KeyGen::load_public_key(pub_in, pub_key);
            gogo40_keygen::KeyGen::load_private_key(pri_in, pri_key);
        }

        std::string message = "run_test1()";

        //Testing encryptation...
        {
            std::string cipher;
            gogo40_keygen::KeyGen key_gen;

            key_gen.encrypt(pub_key, message, cipher);

            std::ofstream out("message.crt");
            gogo40_keygen::save_message(out, cipher);

        }

        std::string recovered;

        //Testing decryptation...
        {
            std::string cipher;
            gogo40_keygen::KeyGen key_gen;

            std::ifstream in("message.crt");
            gogo40_keygen::load_message(in, cipher);
            key_gen.decrypt(pri_key, cipher, recovered);
        }

        std::cout << "message: <" << message << ">\n";
        std::cout << "message recovered: <" << recovered << ">\n";
    } catch( CryptoPP::Exception& e ) {
        std::cerr << "Caught Exception..." << std::endl;
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

