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

win32-g++ {
    INCLUDEPATH += "$${PWD}" \
    "$${PWD}/win_deps/include/"

    LIBS += "$${PWD}/win_deps/win32/libcryptopp.dll.a"

    dynamiclibrary.files = "libcryptopp.dll"
    dynamiclibrary.path = "$${PWD}/win_deps/win32"

    DEPLOYMENT += dynamiclibrary
    DEFINES += NO_OS_DEPENDENCE OS_RNG_AVAILABLE NDEBUG
}

win32-msvc2015 | win32-msvc2013 {
    INCLUDEPATH += "$${PWD}" \
    "$${PWD}/win_deps/fips140/" \
    "$${PWD}/win_deps/fips140/cryptopp"

    DEFINES +=  OS_RNG_AVAILABLE NDEBUG  CRYPTOPP_DEFAULT_NO_DLL

    SOURCES += \
    win_deps/fips140/dll.cpp \
    win_deps/fips140/3way.cpp \
    win_deps/fips140/adler32.cpp \
    win_deps/fips140/algebra.cpp \
    win_deps/fips140/algparam.cpp \
    win_deps/fips140/arc4.cpp \
    win_deps/fips140/asn.cpp \
    win_deps/fips140/base32.cpp \
    win_deps/fips140/base64.cpp \
    win_deps/fips140/basecode.cpp \
    win_deps/fips140/bfinit.cpp \
    win_deps/fips140/blowfish.cpp \
    win_deps/fips140/blumshub.cpp \
    win_deps/fips140/camellia.cpp \
    win_deps/fips140/cast.cpp \
    win_deps/fips140/casts.cpp \
    win_deps/fips140/cbcmac.cpp \
    win_deps/fips140/channels.cpp \
    win_deps/fips140/crc.cpp \
    win_deps/fips140/cryptlib.cpp \
    win_deps/fips140/default.cpp \
    win_deps/fips140/des.cpp \
    win_deps/fips140/dessp.cpp \
    win_deps/fips140/dh.cpp \
    win_deps/fips140/dh2.cpp \
    win_deps/fips140/dsa.cpp \
    win_deps/fips140/ec2n.cpp \
    win_deps/fips140/eccrypto.cpp \
    win_deps/fips140/ecp.cpp \
    win_deps/fips140/elgamal.cpp \
    win_deps/fips140/emsa2.cpp \
    win_deps/fips140/eprecomp.cpp \
    win_deps/fips140/esign.cpp \
    win_deps/fips140/files.cpp \
    win_deps/fips140/filters.cpp \
    win_deps/fips140/fips140.cpp \
    win_deps/fips140/fipsalgt.cpp \
    win_deps/fips140/gf2_32.cpp \
    win_deps/fips140/gf2n.cpp \
    win_deps/fips140/gf256.cpp \
    win_deps/fips140/gfpcrypt.cpp \
    win_deps/fips140/gost.cpp \
    win_deps/fips140/gzip.cpp \
    win_deps/fips140/hex.cpp \
    win_deps/fips140/hmac.cpp \
    win_deps/fips140/hrtimer.cpp \
    win_deps/fips140/ida.cpp \
    win_deps/fips140/idea.cpp \
    win_deps/fips140/integer.cpp \
    win_deps/fips140/iterhash.cpp \
    win_deps/fips140/luc.cpp \
    win_deps/fips140/mars.cpp \
    win_deps/fips140/marss.cpp \
    win_deps/fips140/md2.cpp \
    win_deps/fips140/md4.cpp \
    win_deps/fips140/md5.cpp \
    win_deps/fips140/misc.cpp \
    win_deps/fips140/modes.cpp \
    win_deps/fips140/mqueue.cpp \
    win_deps/fips140/mqv.cpp \
    win_deps/fips140/nbtheory.cpp \
    win_deps/fips140/network.cpp \
    win_deps/fips140/oaep.cpp \
    win_deps/fips140/osrng.cpp \
    win_deps/fips140/panama.cpp \
    win_deps/fips140/pch.cpp \
    win_deps/fips140/pkcspad.cpp \
    win_deps/fips140/polynomi.cpp \
    win_deps/fips140/pssr.cpp \
    win_deps/fips140/pubkey.cpp \
    win_deps/fips140/queue.cpp \
    win_deps/fips140/rabin.cpp \
    win_deps/fips140/randpool.cpp \
    win_deps/fips140/rc2.cpp \
    win_deps/fips140/rc5.cpp \
    win_deps/fips140/rc6.cpp \
    win_deps/fips140/rdtables.cpp \
    win_deps/fips140/rijndael.cpp \
    win_deps/fips140/ripemd.cpp \
    win_deps/fips140/rng.cpp \
    win_deps/fips140/rsa.cpp \
    win_deps/fips140/rw.cpp \
    win_deps/fips140/safer.cpp \
    win_deps/fips140/seal.cpp \
    win_deps/fips140/serpent.cpp \
    win_deps/fips140/sha.cpp \
    win_deps/fips140/shacal2.cpp \
    win_deps/fips140/shark.cpp \
    win_deps/fips140/sharkbox.cpp \
    win_deps/fips140/simple.cpp \
    win_deps/fips140/skipjack.cpp \
    win_deps/fips140/square.cpp \
    win_deps/fips140/squaretb.cpp \
    win_deps/fips140/strciphr.cpp \
    win_deps/fips140/tea.cpp \
    win_deps/fips140/tftables.cpp \
    win_deps/fips140/tiger.cpp \
    win_deps/fips140/tigertab.cpp \
    win_deps/fips140/trdlocal.cpp \
    win_deps/fips140/ttmac.cpp \
    win_deps/fips140/twofish.cpp \
    win_deps/fips140/wait.cpp \
    win_deps/fips140/wake.cpp \
    win_deps/fips140/whrlpool.cpp \
    win_deps/fips140/winpipes.cpp \
    win_deps/fips140/xtr.cpp \
    win_deps/fips140/xtrcrypt.cpp \
    win_deps/fips140/zdeflate.cpp \
    win_deps/fips140/zinflate.cpp \
    win_deps/fips140/zlib.cpp
}

linux:!android: LIBS += -ldl -lcrypto++

DISTFILES += \
    win_deps/fips140/crypto++.mcp

