/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2013-2016 Regents of the University of California.
 *
 * This file is part of ndn-cxx library (NDN C++ library with eXperimental eXtensions).
 *
 * ndn-cxx library is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * ndn-cxx library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 *
 * You should have received copies of the GNU General Public License and GNU Lesser
 * General Public License along with ndn-cxx, e.g., in COPYING.md file.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * See AUTHORS.md for complete list of ndn-cxx authors and contributors.
 */

#ifndef NDN_TESTS_MANAGEMENT_NFD_CONTROLLER_FIXTURE_HPP
#define NDN_TESTS_MANAGEMENT_NFD_CONTROLLER_FIXTURE_HPP

#include "boost-test.hpp"
#include "util/dummy-client-face.hpp"
#include "../identity-management-time-fixture.hpp"

namespace ndn {
namespace nfd {
namespace tests {

using namespace ndn::tests;

class ControllerFixture : public IdentityManagementTimeFixture
{
protected:
  ControllerFixture()
    : face(io, m_keyChain)
    , controller(face, m_keyChain)
    , failCallback(bind(&ControllerFixture::fail, this, _1, _2))
  {
    Name identityName("/localhost/ControllerFixture");
    if (this->addIdentity(identityName)) {
      m_keyChain.setDefaultIdentity(identityName);
    }
    else {
      BOOST_FAIL("cannot create identity");
    }
  }

private:
  void
  fail(uint32_t code, const std::string& reason)
  {
    failCodes.push_back(code);
  }

protected:
  ndn::util::DummyClientFace face;
  Controller controller;
  Controller::CommandFailCallback failCallback;
  std::vector<uint32_t> failCodes;
};

} // namespace tests
} // namespace nfd
} // namespace ndn

#endif // NDN_TESTS_MANAGEMENT_NFD_CONTROLLER_FIXTURE_HPP
