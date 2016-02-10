/// @file: keygen.cpp
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

#include <cryptopp/queue.h>
#include <cryptopp/files.h>
#include <cryptopp/rsa.h>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
#include <cryptopp/secblock.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/base64.h>


namespace gogo40_keygen {

void KeyGen::load(std::istream& in, CryptoPP::BufferedTransformation& bt)
{
    CryptoPP::FileSource file(in, true);

    file.TransferTo(bt);
    bt.MessageEnd();
}

void KeyGen::save(std::ostream& out, const CryptoPP::BufferedTransformation& bt)
{
    CryptoPP::FileSink file(out);

    bt.CopyTo(file);
    file.MessageEnd();
}

void KeyGen::load_public_key(std::istream& in, CryptoPP::PublicKey& pub_key)
{
    CryptoPP::ByteQueue queue;

    load(in, queue);
    pub_key.Load(queue);
}

void KeyGen::save_public_key(std::ostream& out, const CryptoPP::PublicKey& pub_key)
{
    CryptoPP::ByteQueue queue;

    pub_key.Save(queue);
    save(out, queue);
}

void KeyGen::load_private_key(std::istream& in, CryptoPP::PrivateKey& pri_key)
{
    CryptoPP::ByteQueue queue;

    load(in, queue);
    pri_key.Load(queue);
}

void KeyGen::save_private_key(std::ostream& out, const CryptoPP::PrivateKey& pri_key)
{
    CryptoPP::ByteQueue queue;

    pri_key.Save(queue);
    save(out, queue);
}

void KeyGen::generate_keys(std::ostream& pub_out, std::ostream& pri_out, int key_size)
{
    CryptoPP::InvertibleRSAFunction parameters;
    parameters.GenerateRandomWithKeySize(rng, key_size);

    CryptoPP::RSA::PrivateKey pri_key(parameters);
    CryptoPP::RSA::PublicKey pub_key(parameters);

    save_private_key(pri_out, pri_key);
    save_public_key(pub_out, pub_key);
}

void KeyGen::encrypt(const CryptoPP::PublicKey& pub_key, const std::string& message, std::string& cipher)
{
    CryptoPP::RSAES_OAEP_SHA_Encryptor e(pub_key);

    CryptoPP::StringSource(message, true,
                           new CryptoPP::PK_EncryptorFilter(rng, e,
                                                            new CryptoPP::StringSink(cipher)
                                                            )
                           );
}

void KeyGen::decrypt(const CryptoPP::PrivateKey& pri_key, const std::string& cipher, std::string& message)
{
    CryptoPP::RSAES_OAEP_SHA_Decryptor d( pri_key );

    CryptoPP::StringSource(cipher, true,
                           new CryptoPP::PK_DecryptorFilter(rng, d,
                                                            new CryptoPP::StringSink(message)
                                                            )
                           );
}

KeyGen::KeyGen() : rng(){}

KeyGen::~KeyGen() {}

void save_message(std::ostream &out, const std::string &message)
{
    std::string encoded;

    CryptoPP::StringSource(message,
                           true,
                           new CryptoPP::Base64Encoder(
                               new CryptoPP::StringSink(encoded)
                               )
                           );

    out << encoded;
}

void load_message(std::istream &in, std::string &message)
{
    std::string input = "";
    std::string line = "";

    while (std::getline(in, line)) {
        input += line;
    }

    CryptoPP::StringSource(input,
                           true,
                           new CryptoPP::Base64Decoder(
                               new CryptoPP::StringSink(message)
                               )
                           );
}

} // namespace gogo40_keygen

