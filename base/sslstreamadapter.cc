/*
 *  Copyright 2004 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif  // HAVE_CONFIG_H

#include "base/sslstreamadapter.h"
#include "base/sslconfig.h"

#if SSL_USE_SCHANNEL

// SChannel support for DTLS and peer-to-peer mode are not
// done.
#elif SSL_USE_OPENSSL  // && !SSL_USE_SCHANNEL

#include "base/opensslstreamadapter.h"

#elif SSL_USE_NSS      // && !SSL_USE_SCHANNEL && !SSL_USE_OPENSSL

#include "base/nssstreamadapter.h"

#endif  // !SSL_USE_OPENSSL && !SSL_USE_SCHANNEL && !SSL_USE_NSS

///////////////////////////////////////////////////////////////////////////////

namespace rtc {

SSLStreamAdapter* SSLStreamAdapter::Create(StreamInterface* stream) {

  return NULL;

}

bool SSLStreamAdapter::GetSslCipher(std::string* cipher) {
  return false;
}

bool SSLStreamAdapter::ExportKeyingMaterial(const std::string& label,
                                            const uint8* context,
                                            size_t context_len,
                                            bool use_context,
                                            uint8* result,
                                            size_t result_len) {
  return false;  // Default is unsupported
}

bool SSLStreamAdapter::SetDtlsSrtpCiphers(
    const std::vector<std::string>& ciphers) {
  return false;
}

bool SSLStreamAdapter::GetDtlsSrtpCipher(std::string* cipher) {
  return false;
}

// Note: this matches the logic above with SCHANNEL dominating
#if SSL_USE_SCHANNEL
bool SSLStreamAdapter::HaveDtls() { return false; }
bool SSLStreamAdapter::HaveDtlsSrtp() { return false; }
bool SSLStreamAdapter::HaveExporter() { return false; }
std::string SSLStreamAdapter::GetDefaultSslCipher(SSLProtocolVersion version,
                                                  KeyType key_type) {
  return std::string();
}
#elif SSL_USE_OPENSSL
bool SSLStreamAdapter::HaveDtls() {
  // return OpenSSLStreamAdapter::HaveDtls();
  return false;
}
bool SSLStreamAdapter::HaveDtlsSrtp() {
  // return OpenSSLStreamAdapter::HaveDtlsSrtp();
  return false;
}
bool SSLStreamAdapter::HaveExporter() {
  // return OpenSSLStreamAdapter::HaveExporter();
  return false;
}
std::string SSLStreamAdapter::GetDefaultSslCipher(SSLProtocolVersion version,
                                                  KeyType key_type) {
  // return OpenSSLStreamAdapter::GetDefaultSslCipher(version, key_type);
  return std::string("");
}
#elif SSL_USE_NSS
bool SSLStreamAdapter::HaveDtls() {
  // return NSSStreamAdapter::HaveDtls();
  return false;
}
bool SSLStreamAdapter::HaveDtlsSrtp() {
  return NSSStreamAdapter::HaveDtlsSrtp();
  return false;
}
bool SSLStreamAdapter::HaveExporter() {
  // return NSSStreamAdapter::HaveExporter();
  return false;
}
std::string SSLStreamAdapter::GetDefaultSslCipher(SSLProtocolVersion version,
                                                  KeyType key_type) {
  // return NSSStreamAdapter::GetDefaultSslCipher(version, key_type);
  return std::string("");
}
#endif  // !SSL_USE_SCHANNEL && !SSL_USE_OPENSSL && !SSL_USE_NSS

///////////////////////////////////////////////////////////////////////////////

}  // namespace rtc
