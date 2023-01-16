// Copyright 2010-2021, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef MOZC_BASE_PASSWORD_MANAGER_H_
#define MOZC_BASE_PASSWORD_MANAGER_H_

#include <string>

#include "base/port.h"

namespace mozc {

class PasswordManagerInterface;

// PasswordManager is a class for managing
// a password(passphrase) used for user-data encryption.
// It doesn't save user password, but save a session
// password automatically generated by mozc.
// PasswordManager uses an OS-provided mechanism
// to safely save password/passphrase into local disk.
//
// Currently, Linux password manager just stores password in plain text.
// you might want to write your own password manager.
// See password_manager.cc file for the details.

class PasswordManager {
 public:
  PasswordManager() = delete;
  PasswordManager(const PasswordManager &) = delete;
  PasswordManager &operator=(const PasswordManager &) = delete;

  // Initialize password.
  // If password is not found, make a random password internally.
  // return false if initialization failed.
  // Do nothing and return true if password is found.
  static bool InitPassword();

  // get current password
  // Call InitPassword() if need be
  static bool GetPassword(std::string *password);

  // remove current password
  static bool RemovePassword();

  // set internal interface for unittesting
  static void SetPasswordManagerHandler(PasswordManagerInterface *handler);
};

// Implements PasswordManager implementation.
class PasswordManagerInterface {
 public:
  virtual bool SetPassword(const std::string &password) const = 0;
  virtual bool GetPassword(std::string *password) const = 0;
  virtual bool RemovePassword() const = 0;

  PasswordManagerInterface() {}
  virtual ~PasswordManagerInterface() {}
};
}  // namespace mozc

#endif  // MOZC_BASE_PASSWORD_MANAGER_H_
