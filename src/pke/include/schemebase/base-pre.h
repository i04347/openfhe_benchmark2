// @file pre-base.h -- Public key type for lattice crypto operations.
// @author TPOC: contact@palisade-crypto.org
//
// @copyright Copyright (c) 2019, New Jersey Institute of Technology (NJIT)
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution. THIS SOFTWARE IS
// PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef LBCRYPTO_CRYPTO_BASE_PRE_H
#define LBCRYPTO_CRYPTO_BASE_PRE_H

#include <vector>
#include <memory>

#include "key/allkey.h"
#include "ciphertext.h"

/**
 * @namespace lbcrypto
 * The namespace of lbcrypto
 */
namespace lbcrypto {

/**
 * @brief Abstract interface class for LBC PRE algorithms
 * @tparam Element a ring element.
 */
template <class Element>
class PREBase {
  using ParmType = typename Element::Params;
  using IntType = typename Element::Integer;
  using DugType = typename Element::DugType;
  using DggType = typename Element::DggType;
  using TugType = typename Element::TugType;

 public:
  virtual ~PREBase() {}

  /**
   * Virtual function to generate 1..log(q) encryptions for each bit of the
   * original private key Variant that uses the public key for the new secret
   * key.
   *
   * @param &newKey public key for the new secret key.
   * @param &origPrivateKey original private key used for decryption.
   * @param *evalKey the evaluation key.
   * @return the re-encryption key.
   */
  virtual EvalKey<Element> ReKeyGen(const PrivateKey<Element> oldPrivateKey,
                                    const PublicKey<Element> newPublicKey) const;

  /**
   * Virtual function to define the interface for re-encypting ciphertext
   * using the array generated by ProxyGen
   *
   * @param &evalKey proxy re-encryption key.
   * @param &ciphertext the input ciphertext.
   * @param publicKey the public key of the recipient of the re-encrypted
   * ciphertext.
   * @param *newCiphertext the new ciphertext.
   */
  virtual Ciphertext<Element> ReEncrypt(
      ConstCiphertext<Element> ciphertext, const EvalKey<Element> evalKey,
      const PublicKey<Element> publicKey = nullptr, usint noiseflooding = 0) const;
};

}  // namespace lbcrypto

#endif