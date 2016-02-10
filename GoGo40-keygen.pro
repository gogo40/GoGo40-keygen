#-------------------------------------------------
#
# Project created by QtCreator 2016-02-09T17:31:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG   += c++11

TARGET = GoGo40-keygen
TEMPLATE = app


SOURCES += main.cpp\
        keygen_widget.cpp \
    keygen.cpp \
    tests.cpp


HEADERS  += keygen_widget.h \
    keygen.h \
    tests.h


FORMS    += keygen_widget.ui

win32 {
    INCLUDEPATH += "$${PWD}"

    HEADERS += cryptopp/3way.h \
    cryptopp/adhoc.cpp.proto \
    cryptopp/adler32.h \
    cryptopp/aes.h \
    cryptopp/algebra.h \
    cryptopp/algparam.h \
    cryptopp/arc4.h \
    cryptopp/argnames.h \
    cryptopp/asn.h \
    cryptopp/base32.h \
    cryptopp/base64.h \
    cryptopp/basecode.h \
    cryptopp/bench.h \
    cryptopp/blowfish.h \
    cryptopp/blumshub.h \
    cryptopp/camellia.h \
    cryptopp/cast.h \
    cryptopp/cbcmac.h \
    cryptopp/channels.h \
    cryptopp/config.h \
    cryptopp/crc.h \
    cryptopp/cryptlib.h \
    cryptopp/cryptopp.rc \
    cryptopp/default.h \
    cryptopp/des.h \
    cryptopp/dh.h \
    cryptopp/dh2.h \
    cryptopp/dll.h \
    cryptopp/dmac.h \
    cryptopp/dsa.h \
    cryptopp/ec2n.h \
    cryptopp/eccrypto.h \
    cryptopp/ecp.h \
    cryptopp/elgamal.h \
    cryptopp/emsa2.h \
    cryptopp/eprecomp.h \
    cryptopp/esign.h \
    cryptopp/factory.h \
    cryptopp/files.h \
    cryptopp/filters.h \
    cryptopp/fips140.h \
    cryptopp/fltrimpl.h \
    cryptopp/gf2_32.h \
    cryptopp/gf2n.h \
    cryptopp/gf256.h \
    cryptopp/gfpcrypt.h \
    cryptopp/gost.h \
    cryptopp/gzip.h \
    cryptopp/hex.h \
    cryptopp/hmac.h \
    cryptopp/hrtimer.h \
    cryptopp/ida.h \
    cryptopp/idea.h \
    cryptopp/integer.h \
    cryptopp/iterhash.h \
    cryptopp/lubyrack.h \
    cryptopp/luc.h \
    cryptopp/mars.h \
    cryptopp/md2.h \
    cryptopp/md4.h \
    cryptopp/md5.h \
    cryptopp/mdc.h \
    cryptopp/misc.h \
    cryptopp/modarith.h \
    cryptopp/modes.h \
    cryptopp/modexppc.h \
    cryptopp/mqueue.h \
    cryptopp/mqv.h \
    cryptopp/nbtheory.h \
    cryptopp/network.h \
    cryptopp/nr.h \
    cryptopp/oaep.h \
    cryptopp/oids.h \
    cryptopp/osrng.h \
    cryptopp/panama.h \
    cryptopp/pch.h \
    cryptopp/pkcspad.h \
    cryptopp/polynomi.h \
    cryptopp/pssr.h \
    cryptopp/pubkey.h \
    cryptopp/pwdbased.h \
    cryptopp/queue.h \
    cryptopp/rabin.h \
    cryptopp/randpool.h \
    cryptopp/rc2.h \
    cryptopp/rc5.h \
    cryptopp/rc6.h \
    cryptopp/resource.h \
    cryptopp/rijndael.h \
    cryptopp/ripemd.h \
    cryptopp/rng.h \
    cryptopp/rsa.h \
    cryptopp/rw.h \
    cryptopp/safer.h \
    cryptopp/seal.h \
    cryptopp/secblock.h \
    cryptopp/seckey.h \
    cryptopp/serpent.h \
    cryptopp/sha.h \
    cryptopp/shacal2.h \
    cryptopp/shark.h \
    cryptopp/simple.h \
    cryptopp/skipjack.h \
    cryptopp/smartptr.h \
    cryptopp/socketft.h \
    cryptopp/square.h \
    cryptopp/stdcpp.h \
    cryptopp/strciphr.h \
    cryptopp/tea.h \
    cryptopp/tiger.h \
    cryptopp/trdlocal.h \
    cryptopp/trunhash.h \
    cryptopp/ttmac.h \
    cryptopp/twofish.h \
    cryptopp/validate.h \
    cryptopp/wait.h \
    cryptopp/wake.h \
    cryptopp/whrlpool.h \
    cryptopp/winpipes.h \
    cryptopp/words.h \
    cryptopp/xormac.h \
    cryptopp/xtr.h \
    cryptopp/xtrcrypt.h \
    cryptopp/zdeflate.h \
    cryptopp/zinflate.h \
    cryptopp/zlib.h\
    cryptopp/authenc.h \
    cryptopp/ccm.h \
    cryptopp/cmac.h \
    cryptopp/cpu.h \
    cryptopp/eax.h \
    cryptopp/gcm.h \
    cryptopp/hkdf.h \
    cryptopp/mersenne.h \
    cryptopp/rdrand.h \
    cryptopp/salsa.h \
    cryptopp/seed.h \
    cryptopp/serpentp.h \
    cryptopp/sha3.h \
    cryptopp/sosemanuk.h \
    cryptopp/trap.h \
    cryptopp/vmac.h

    SOURCES += cryptopp/3way.cpp \
    cryptopp/adler32.cpp \
    cryptopp/algebra.cpp \
    cryptopp/algparam.cpp \
    cryptopp/arc4.cpp \
    cryptopp/asn.cpp \
    cryptopp/base32.cpp \
    cryptopp/base64.cpp \
    cryptopp/basecode.cpp \
    cryptopp/bench.cpp \
    cryptopp/bench2.cpp \
    cryptopp/bfinit.cpp \
    cryptopp/blowfish.cpp \
    cryptopp/blumshub.cpp \
    cryptopp/camellia.cpp \
    cryptopp/cast.cpp \
    cryptopp/casts.cpp \
    cryptopp/cbcmac.cpp \
    cryptopp/channels.cpp \
    cryptopp/crc.cpp \
    cryptopp/cryptlib.cpp \
    cryptopp/datatest.cpp \
    cryptopp/default.cpp \
    cryptopp/des.cpp \
    cryptopp/dessp.cpp \
    cryptopp/dh.cpp \
    cryptopp/dh2.cpp \
    cryptopp/dll.cpp \
    cryptopp/dsa.cpp \
    cryptopp/ec2n.cpp \
    cryptopp/eccrypto.cpp \
    cryptopp/ecp.cpp \
    cryptopp/elgamal.cpp \
    cryptopp/emsa2.cpp \
    cryptopp/eprecomp.cpp \
    cryptopp/esign.cpp \
    cryptopp/files.cpp \
    cryptopp/filters.cpp \
    cryptopp/fips140.cpp \
    cryptopp/fipsalgt.cpp \
    cryptopp/gf2_32.cpp \
    cryptopp/gf2n.cpp \
    cryptopp/gf256.cpp \
    cryptopp/gfpcrypt.cpp \
    cryptopp/gost.cpp \
    cryptopp/gzip.cpp \
    cryptopp/hex.cpp \
    cryptopp/hmac.cpp \
    cryptopp/hrtimer.cpp \
    cryptopp/ida.cpp \
    cryptopp/idea.cpp \
    cryptopp/integer.cpp \
    cryptopp/iterhash.cpp \
    cryptopp/luc.cpp \
    cryptopp/mars.cpp \
    cryptopp/marss.cpp \
    cryptopp/md2.cpp \
    cryptopp/md4.cpp \
    cryptopp/md5.cpp \
    cryptopp/misc.cpp \
    cryptopp/modes.cpp \
    cryptopp/mqueue.cpp \
    cryptopp/mqv.cpp \
    cryptopp/nbtheory.cpp \
    cryptopp/network.cpp \
    cryptopp/oaep.cpp \
    cryptopp/osrng.cpp \
    cryptopp/panama.cpp \
    cryptopp/pch.cpp \
    cryptopp/pkcspad.cpp \
    cryptopp/polynomi.cpp \
    cryptopp/pssr.cpp \
    cryptopp/pubkey.cpp \
    cryptopp/queue.cpp \
    cryptopp/rabin.cpp \
    cryptopp/randpool.cpp \
    cryptopp/rc2.cpp \
    cryptopp/rc5.cpp \
    cryptopp/rc6.cpp \
    cryptopp/rdtables.cpp \
    cryptopp/regtest.cpp \
    cryptopp/rijndael.cpp \
    cryptopp/ripemd.cpp \
    cryptopp/rng.cpp \
    cryptopp/rsa.cpp \
    cryptopp/rw.cpp \
    cryptopp/safer.cpp \
    cryptopp/seal.cpp \
    cryptopp/serpent.cpp \
    cryptopp/sha.cpp \
    cryptopp/shacal2.cpp \
    cryptopp/shark.cpp \
    cryptopp/sharkbox.cpp \
    cryptopp/simple.cpp \
    cryptopp/skipjack.cpp \
    cryptopp/socketft.cpp \
    cryptopp/square.cpp \
    cryptopp/squaretb.cpp \
    cryptopp/strciphr.cpp \
    cryptopp/tea.cpp \
    cryptopp/test.cpp \
    cryptopp/tftables.cpp \
    cryptopp/tiger.cpp \
    cryptopp/tigertab.cpp \
    cryptopp/trdlocal.cpp \
    cryptopp/ttmac.cpp \
    cryptopp/twofish.cpp \
    cryptopp/wait.cpp \
    cryptopp/wake.cpp \
    cryptopp/whrlpool.cpp \
    cryptopp/winpipes.cpp \
    cryptopp/xtr.cpp \
    cryptopp/xtrcrypt.cpp \
    cryptopp/zdeflate.cpp \
    cryptopp/zinflate.cpp \
    cryptopp/zlib.cpp\
    cryptopp/authenc.cpp \
    cryptopp/ccm.cpp \
    cryptopp/cmac.cpp \
    cryptopp/cpu.cpp \
    cryptopp/cryptlib_bds.cpp \
    cryptopp/dlltest.cpp \
    cryptopp/eax.cpp \
    cryptopp/gcm.cpp \
    cryptopp/rdrand.cpp \
    cryptopp/salsa.cpp \
    cryptopp/seed.cpp \
    cryptopp/sha3.cpp \
    cryptopp/sosemanuk.cpp \
    cryptopp/validat1.cpp \
    cryptopp/validat2.cpp \
    cryptopp/validat3.cpp \
    cryptopp/vmac.cpp
}

win32-g++ {
    #LIBS += "$${PWD}/win_deps/win32/cryptopp.lib"

    #dynamiclibrary.files = "cryptopp.dll"
    #dynamiclibrary.path = "$${PWD}/win_deps/win32"

    #DEPLOYMENT += dynamicfiles
}

win32-msvc2013 {
    #LIBS += "$${PWD}/win_deps/win64/cryptopp.lib"
    #DEFINES += -DCRYPTOPP_IMPORTS

    DEFINES += CRYPTOPP_MSC_VERSION
}
linux:!android: LIBS += -ldl -lcrypto++

