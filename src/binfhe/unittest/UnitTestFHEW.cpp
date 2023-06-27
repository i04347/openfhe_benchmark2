//==================================================================================
// BSD 2-Clause License
//
// Copyright (c) 2014-2022, NJIT, Duality Technologies Inc. and other contributors
//
// All rights reserved.
//
// Author TPOC: contact@openfhe.org
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//==================================================================================

/*
  This code runs unit tests for the FHEW methods of the OpenFHE lattice encryption library
 */

#include "binfhecontext.h"
#include "utils/demangle.h"

#include "gtest/gtest.h"
#include <sstream>

using namespace lbcrypto;

//===========================================================================================================
enum TEST_CASE_TYPE {
    FHEW_AND = 0,
    FHEW_OR,
    FHEW_NAND,
    FHEW_NOR,
    FHEW_XOR,
    FHEW_XNOR,
    FHEW_XOR_FAST,
    FHEW_XNOR_FAST,
    FHEW_SIGNED_MODE,
    FHEW_KEY_SWITCH,
    FHEW_MOD_SWITCH,
    FHEW_NOT,
};

static std::ostream& operator<<(std::ostream& os, const TEST_CASE_TYPE& type) {
    std::string typeName;
    switch (type) {
        case FHEW_AND:
            typeName = "FHEW_AND";
            break;
        case FHEW_OR:
            typeName = "FHEW_OR";
            break;
        case FHEW_NAND:
            typeName = "FHEW_NAND";
            break;
        case FHEW_NOR:
            typeName = "FHEW_NOR";
            break;
        case FHEW_XOR:
            typeName = "FHEW_XOR";
            break;
        case FHEW_XNOR:
            typeName = "FHEW_XNOR";
            break;
        case FHEW_XOR_FAST:
            typeName = "FHEW_XOR_FAST";
            break;
        case FHEW_XNOR_FAST:
            typeName = "FHEW_XNOR_FAST";
            break;
        case FHEW_SIGNED_MODE:
            typeName = "FHEW_SIGNED_MODE";
            break;
        case FHEW_KEY_SWITCH:
            typeName = "FHEW_KEY_SWITCH";
            break;
        case FHEW_MOD_SWITCH:
            typeName = "FHEW_MOD_SWITCH";
            break;
        case FHEW_NOT:
            typeName = "FHEW_NOT";
            break;
        default:
            typeName = "UNKNOWN_TESTTYPE";
            break;
    }
    return os << typeName;
}
//===========================================================================================================
struct TEST_CASE_UTGENERAL_FHEW {
    TEST_CASE_TYPE testCaseType;
    // test case description - MUST BE UNIQUE
    std::string description;

    BINFHE_PARAMSET securityLevel;
    BINFHE_METHOD   method;

    BINGATE gate;

    std::vector<LWEPlaintext> results;


    // additional test case data
    // ........

    std::string buildTestName() const {
        std::stringstream ss;
        ss << testCaseType << "_" << description;
        return ss.str();
    }
    std::string toString() const {
        std::stringstream ss;
        ss << "testCaseType [" << testCaseType
           << "], BINFHE_PARAMSET: " << securityLevel
           << "BINFHE_METHOD: " << method
           << "BINGATE: " << gate;
        return ss.str();
    }
};

// this lambda provides a name to be printed for every test run by INSTANTIATE_TEST_SUITE_P.
// the name MUST be constructed from digits, letters and '_' only
static auto testName = [](const testing::TestParamInfo<TEST_CASE_UTGENERAL_FHEW>& test) {
    return test.param.buildTestName();
};

static std::ostream& operator<<(std::ostream& os, const TEST_CASE_UTGENERAL_FHEW& test) {
    return os << test.toString();
}
//===========================================================================================================
// clang-format off
static std::vector<TEST_CASE_UTGENERAL_FHEW> testCasesUTGENERAL_FHEW = {
    // TestType, Descr,  ParamSet, Method,  Gate, Results
    { FHEW_AND,  "01",   TOY,      GINX,    AND,   {1, 0, 0, 0} },
    { FHEW_AND,  "02",   TOY,      AP,      AND,   {1, 0, 0, 0} },
    { FHEW_AND,  "03",   TOY,      LMKCDEY, AND,   {1, 0, 0, 0} },
    // ==========================================
    { FHEW_NAND, "01",   TOY,      GINX,    NAND,  {0, 1, 1, 1} },
    { FHEW_NAND, "02",   TOY,      AP,      NAND,  {0, 1, 1, 1} },
    { FHEW_NAND, "03",   TOY,      LMKCDEY, NAND,  {0, 1, 1, 1} },
    // ==========================================
    { FHEW_OR,   "01",   TOY,      GINX,    OR,    {1, 1, 1, 0} },
    { FHEW_OR,   "02",   TOY,      AP,      OR,    {1, 1, 1, 0} },
    { FHEW_OR,   "03",   TOY,      LMKCDEY, OR,    {1, 1, 1, 0} },
    // ==========================================
    { FHEW_NOR,  "01",   TOY,      GINX,    NOR,   {0, 0, 0, 1} },
    { FHEW_NOR,  "02",   TOY,      AP,      NOR,   {0, 0, 0, 1} },
    { FHEW_NOR,  "03",   TOY,      LMKCDEY, NOR,   {0, 0, 0, 1} },
    // ==========================================
    { FHEW_XOR,  "01",   TOY,      GINX,    XOR,   {0, 1, 1, 0} },
    { FHEW_XOR,  "02",   TOY,      AP,      XOR,   {0, 1, 1, 0} },
    { FHEW_XOR,  "03",   TOY,      LMKCDEY, XOR,   {0, 1, 1, 0} },
    // ==========================================

    { FHEW_XNOR,  "01",  TOY,      GINX,    XNOR,  {1, 0, 0, 1} },
    { FHEW_XNOR,  "02",  TOY,      AP,      XNOR,  {1, 0, 0, 1} },
    { FHEW_XNOR,  "03",  TOY,      LMKCDEY, XNOR,  {1, 0, 0, 1} },
    // ==========================================
    // TestType,     Descr, ParamSet, Method,  Gate,      Results
    { FHEW_XOR_FAST,  "01", TOY,      GINX,    XOR_FAST,  {0, 1, 1, 0} },
    { FHEW_XOR_FAST,  "02", TOY,      AP,      XOR_FAST,  {0, 1, 1, 0} },
    { FHEW_XOR_FAST,  "03", TOY,      LMKCDEY, XOR_FAST,  {0, 1, 1, 0} },
    // ==========================================
    { FHEW_XNOR_FAST, "01", TOY,      GINX,    XNOR_FAST, {1, 0, 0, 1} },
    { FHEW_XNOR_FAST, "02", TOY,      AP,      XNOR_FAST, {1, 0, 0, 1} },
    { FHEW_XNOR_FAST, "03", TOY,      LMKCDEY, XNOR_FAST, {1, 0, 0, 1} },
    // ==========================================
    { FHEW_SIGNED_MODE, "01", SIGNED_MOD_TEST, GINX, AND, {1, 0, 0, 0} },
    // ==========================================
    { FHEW_KEY_SWITCH, "01", TOY,      GINX,    OR, {1, 0} }, // OR is not needed; added as a random value
    { FHEW_KEY_SWITCH, "02", TOY,      AP,      OR, {1, 0} }, // OR is not needed; added as a random value
    { FHEW_KEY_SWITCH, "03", TOY,      LMKCDEY, OR, {1, 0} }, // OR is not needed; added as a random value
    // ==========================================
    { FHEW_MOD_SWITCH, "01", TOY,      GINX,    OR, {1, 0} }, // OR is not needed; added as a random value
    { FHEW_MOD_SWITCH, "02", TOY,      AP,      OR, {1, 0} }, // OR is not needed; added as a random value
    { FHEW_MOD_SWITCH, "03", TOY,      LMKCDEY, OR, {1, 0} }, // OR is not needed; added as a random value
    // ==========================================
    { FHEW_NOT, "01", TOY,      GINX,    OR, {0, 1} }, // OR is not needed; added as a random value
    { FHEW_NOT, "02", TOY,      AP,      OR, {0, 1} }, // OR is not needed; added as a random value
    { FHEW_NOT, "03", TOY,      LMKCDEY, OR, {0, 1} }, // OR is not needed; added as a random value
};
// clang-format on
//===========================================================================================================
class UTGENERAL_FHEW : public ::testing::TestWithParam<TEST_CASE_UTGENERAL_FHEW> {

protected:
    void SetUp() {}
    void TearDown() {}

    // ---------------  TESTING METHODS OF FANDHEW ---------------
    void UnitTest_FHEW_KeySwitch(const TEST_CASE_UTGENERAL_FHEW& testData, const std::string& failmsg = std::string()) {
        try {
            auto cc = BinFHEContext();
            cc.GenerateBinFHEContext(testData.securityLevel, testData.method);

            NativeInteger Q = cc.GetParams()->GetLWEParams()->GetQ();

            auto sk  = cc.KeyGen();
            auto skN = cc.KeyGenN();

            auto ctQN1 = cc.Encrypt(skN, 1, FRESH, 4, Q);
            auto ctQN0 = cc.Encrypt(skN, 0, FRESH, 4, Q);

            NativeVector newSK = sk->GetElement();
            newSK.SwitchModulus(Q);
            auto skQ = std::make_shared<LWEPrivateKeyImpl>(newSK);

            auto keySwitchHint = cc.KeySwitchGen(sk, skN);

            LWECiphertext eQ1 = cc.GetLWEScheme()->KeySwitch(cc.GetParams()->GetLWEParams(), keySwitchHint, ctQN1);
            LWECiphertext eQ0 = cc.GetLWEScheme()->KeySwitch(cc.GetParams()->GetLWEParams(), keySwitchHint, ctQN0);

            LWEPlaintext resultAfterKeySwitch1;
            cc.Decrypt(skQ, eQ1, &resultAfterKeySwitch1);

            LWEPlaintext resultAfterKeySwitch0;
            cc.Decrypt(skQ, eQ0, &resultAfterKeySwitch0);

            std::string failed = testData.toString() + " failed";

            EXPECT_EQ(testData.results[0], resultAfterKeySwitch1) << failed;
            EXPECT_EQ(testData.results[1], resultAfterKeySwitch0) << failed;
        }
        catch (std::exception& e) {
            std::cerr << "Exception thrown from " << __func__ << "(): " << e.what() << std::endl;
            // make it fail
            EXPECT_TRUE(0 == 1) << failmsg;
        }
        catch (...) {
#if defined EMSCRIPTEN
            std::string name("EMSCRIPTEN_UNKNOWN");
#else
            std::string name(demangle(__cxxabiv1::__cxa_current_exception_type()->name()));
#endif
            std::cerr << "Unknown exception of type \"" << name << "\" thrown from " << __func__ << "()" << std::endl;
            // make it fail
            EXPECT_TRUE(0 == 1) << failmsg;
        }
    }

    void UnitTest_FHEW_ModSwitch(const TEST_CASE_UTGENERAL_FHEW& testData, const std::string& failmsg = std::string()) {
        try {
            auto cc = BinFHEContext();
            cc.GenerateBinFHEContext(testData.securityLevel, testData.method);

            NativeInteger Q = cc.GetParams()->GetLWEParams()->GetQ();

            auto sk = cc.KeyGen();

            // switch secret key to Q
            NativeVector newSK = sk->GetElement();
            newSK.SwitchModulus(Q);
            auto skQ = std::make_shared<LWEPrivateKeyImpl>(newSK);

            auto ctQ1 = cc.Encrypt(skQ, 1, FRESH, 4, Q);
            auto ctQ0 = cc.Encrypt(skQ, 0, FRESH, 4, Q);

            // switches the modulus from Q to q
            auto ct1 = cc.GetLWEScheme()->ModSwitch(cc.GetParams()->GetLWEParams()->Getq(), ctQ1);
            auto ct0 = cc.GetLWEScheme()->ModSwitch(cc.GetParams()->GetLWEParams()->Getq(), ctQ0);

            LWEPlaintext resultAfterModSwitch1;
            cc.Decrypt(sk, ct1, &resultAfterModSwitch1);

            LWEPlaintext resultAfterModSwitch0;
            cc.Decrypt(sk, ct0, &resultAfterModSwitch0);

            std::string failed = testData.toString() + " failed";

            EXPECT_EQ(1, resultAfterModSwitch1) << failed;
            EXPECT_EQ(0, resultAfterModSwitch0) << failed;
        }
        catch (std::exception& e) {
            std::cerr << "Exception thrown from " << __func__ << "(): " << e.what() << std::endl;
            // make it fail
            EXPECT_TRUE(0 == 1) << failmsg;
        }
        catch (...) {
#if defined EMSCRIPTEN
            std::string name("EMSCRIPTEN_UNKNOWN");
#else
            std::string name(demangle(__cxxabiv1::__cxa_current_exception_type()->name()));
#endif
            std::cerr << "Unknown exception of type \"" << name << "\" thrown from " << __func__ << "()" << std::endl;
            // make it fail
            EXPECT_TRUE(0 == 1) << failmsg;
        }
    }

    void UnitTest_FHEW_NOT(const TEST_CASE_UTGENERAL_FHEW& testData, const std::string& failmsg = std::string()) {
        try {
            auto cc = BinFHEContext();
            cc.GenerateBinFHEContext(testData.securityLevel, testData.method);

            auto sk = cc.KeyGen();

            auto ct1 = cc.Encrypt(sk, 1, FRESH);
            auto ct0 = cc.Encrypt(sk, 0, FRESH);

            auto ct1Not = cc.EvalNOT(ct1);
            auto ct0Not = cc.EvalNOT(ct0);

            LWEPlaintext result1;
            cc.Decrypt(sk, ct1Not, &result1);

            LWEPlaintext result0;
            cc.Decrypt(sk, ct0Not, &result0);

            std::string failed = testData.toString() + " failed";

            EXPECT_EQ(testData.results[0], result1) << failed;
            EXPECT_EQ(testData.results[1], result0) << failed;
        }
        catch (std::exception& e) {
            std::cerr << "Exception thrown from " << __func__ << "(): " << e.what() << std::endl;
            // make it fail
            EXPECT_TRUE(0 == 1) << failmsg;
        }
        catch (...) {
#if defined EMSCRIPTEN
            std::string name("EMSCRIPTEN_UNKNOWN");
#else
            std::string name(demangle(__cxxabiv1::__cxa_current_exception_type()->name()));
#endif
            std::cerr << "Unknown exception of type \"" << name << "\" thrown from " << __func__ << "()" << std::endl;
            // make it fail
            EXPECT_TRUE(0 == 1) << failmsg;
        }
    }

    void UnitTest_FHEW(const TEST_CASE_UTGENERAL_FHEW& testData, const std::string& failmsg = std::string()) {
        try {
            auto cc = BinFHEContext();
            cc.GenerateBinFHEContext(testData.securityLevel, testData.method);

            auto sk = cc.KeyGen();

            cc.BTKeyGen(sk);

            auto ct1    = cc.Encrypt(sk, 1);
            auto ct0    = cc.Encrypt(sk, 0);
            auto ct1Alt = cc.Encrypt(sk, 1);
            auto ct0Alt = cc.Encrypt(sk, 0);

            auto ct11 = cc.EvalBinGate(testData.gate, ct1, ct1Alt);
            auto ct01 = cc.EvalBinGate(testData.gate, ct0, ct1);
            auto ct10 = cc.EvalBinGate(testData.gate, ct1, ct0);
            auto ct00 = cc.EvalBinGate(testData.gate, ct0, ct0Alt);

            LWEPlaintext result11;
            cc.Decrypt(sk, ct11, &result11);
            LWEPlaintext result01;
            cc.Decrypt(sk, ct01, &result01);
            LWEPlaintext result10;
            cc.Decrypt(sk, ct10, &result10);
            LWEPlaintext result00;
            cc.Decrypt(sk, ct00, &result00);

            std::string failed = testData.toString() + " failed";

            EXPECT_EQ(testData.results[0], result11) << failed;
            EXPECT_EQ(testData.results[1], result01) << failed;
            EXPECT_EQ(testData.results[2], result10) << failed;
            EXPECT_EQ(testData.results[3], result00) << failed;
        }
        catch (std::exception& e) {
            std::cerr << "Exception thrown from " << __func__ << "(): " << e.what() << std::endl;
            // make it fail
            EXPECT_TRUE(0 == 1) << failmsg;
        }
        catch (...) {
#if defined EMSCRIPTEN
            std::string name("EMSCRIPTEN_UNKNOWN");
#else
            std::string name(demangle(__cxxabiv1::__cxa_current_exception_type()->name()));
#endif
            std::cerr << "Unknown exception of type \"" << name << "\" thrown from " << __func__ << "()" << std::endl;
            // make it fail
            EXPECT_TRUE(0 == 1) << failmsg;
        }
    }
};
//===========================================================================================================
TEST_P(UTGENERAL_FHEW, BINFHE) {
    // setupSignals();
    auto test = GetParam();

    switch (test.testCaseType) {
        case FHEW_AND:
        case FHEW_NAND:
        case FHEW_OR:
        case FHEW_NOR:
        case FHEW_XOR:
        case FHEW_XNOR:
        case FHEW_XOR_FAST:
        case FHEW_XNOR_FAST:
        case FHEW_SIGNED_MODE:
            UnitTest_FHEW(test, test.buildTestName());
            break;
        case FHEW_KEY_SWITCH:
            UnitTest_FHEW_KeySwitch(test, test.buildTestName());
            break;
        case FHEW_MOD_SWITCH:
            UnitTest_FHEW_ModSwitch(test, test.buildTestName());
            break;
        case FHEW_NOT:
            UnitTest_FHEW_NOT(test, test.buildTestName());
            break;
        default:
            break;
    }
}

INSTANTIATE_TEST_SUITE_P(UnitTests, UTGENERAL_FHEW, ::testing::ValuesIn(testCasesUTGENERAL_FHEW), testName);
