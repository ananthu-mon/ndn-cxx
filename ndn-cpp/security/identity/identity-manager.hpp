/**
 * Copyright (C) 2013 Regents of the University of California.
 * @author: Yingdi Yu <yingdi@cs.ucla.edu>
 * @author: Jeff Thompson <jefft0@remap.ucla.edu>
 * See COPYING for copyright and distribution information.
 */

#ifndef NDN_IDENTITY_MANAGER_HPP
#define	NDN_IDENTITY_MANAGER_HPP

#include "../../data.hpp"
#include "identity-storage.hpp"
#include "private-key-storage.hpp"

namespace ndn {

/**
 * An IdentityManager is the interface of operations related to identity, keys, and certificates.
 */
class IdentityManager {
public:
  IdentityManager(const ptr_lib::shared_ptr<IdentityStorage>& identityStorage, const ptr_lib::shared_ptr<PrivateKeyStorage>& privateKeyStorage)
  : identityStorage_(identityStorage), privateKeyStorage_(privateKeyStorage)
  {
  }
  
#if 0
  /**
   * Create identity, by default it will create a pair of Key-Signing-Key(KSK) for this identity and a self-signed certificate of the KSK
   * @param identityName the name of the identity
   * @return the key name of the auto-generated KSK of the identity 
   */
  Name
  createIdentity(const Name& identityName);
#endif
    
  /**
   * Get the default identity.
   * @return The default identity name.
   */
  Name
  getDefaultIdentity()
  {
    return identityStorage_->getDefaultIdentity();
  }

#if 0
  /**
   * Generate a pair of RSA keys for the specified identity
   * @param identityName the name of the identity
   * @param ksk create a KSK or not, true for KSK, false for DSK 
   * @param keySize the size of the key
   * @return the generated key name 
   */
  Name
  generateRSAKeyPair(const Name& identityName, bool ksk = false, int keySize = 2048);

  /**
   * Set a key as the default key of an identity
   * @param keyName the name of the key
   * @param identityName the name of the identity, if not specified the identity name can be inferred from the keyName
   */
  void
  setDefaultKeyForIdentity(const Name& keyName, const Name& identityName = Name());

  /**
   * Generate a pair of RSA keys for the specified identity and set it as default key of the identity
   * @param identityName the name of the identity
   * @param ksk create a KSK or not, true for KSK, false for DSK 
   * @param keySize the size of the key
   * @return the generated key name
   */
  Name
  generateRSAKeyPairAsDefault(const Name& identityName, bool ksk = false, int keySize = 2048);

  /**
   * Get public key with the specified name
   * @param keyName name of the key
   * @return the public key
   */
  Ptr<Publickey>
  getPublickey(const Name& keyName);

  /**
   * Add a certificate into the public storage
   * @param certificate the certificate to to added
   */
  void
  addCertificate(Ptr<Certificate> certificate);

  /**
   * Set the certificate as the default of its corresponding key
   * @param certificateName name of the certificate
   */
  void
  setDefaultCertificateForKey(const Name& certificateName);

  /**
   * Add a certificate into the public storage and set the certificate as the default of its corresponding identity
   * @param certificate the certificate to be added
   */
  void
  addCertificateAsIdentityDefault(const Certificate& certificate);

  /**
   * Add a certificate into the public storage and set the certificate as the default of its corresponding key
   * certificate the certificate to be added
   */
  void
  addCertificateAsDefault(const Certificate& certificate);

  /**
   * Get a certificate with the specified name
   * @param certificateName name of the requested certificate
   * @return the requested certificate
   */
  Ptr<Certificate>
  getCertificate(const Name& certificateName);
    
  /**
   * Get a certificate even if the certificate is not valid anymore
   * @param certificateName name of the requested certificate
   * @return the requested certificate
   */
  Ptr<Certificate>
  getAnyCertificate(const Name& certificateName);
#endif
    
  /**
   * Get the default certificate name for the specified identity, which will be used when signing is performed based on identity.
   * @param identityName The name of the specified identity.
   * @return The requested certificate name.
   */
  Name
  getDefaultCertificateNameForIdentity(const Name& identityName)
  {
    return identityStorage_->getDefaultCertificateNameForIdentity(identityName);
  }
    
  /**
   * Get the default certificate name of the default identity, which will be used when signing is based on identity and 
   * the identity is not specified.
   * @return The requested certificate name.
   */
  Name
  getDefaultCertificateName()
  {
    return identityStorage_->getDefaultCertificateNameForIdentity(getDefaultIdentity());
  }
        
#if 0
  /**
   * Sign blob based on identity
   * @param blob the blob to be signed
   * @param identityName the signing identity name
   * @return the generated signature
   */
  Ptr<Signature>
  signByIdentity(const Blob& blob, const Name& identityName);

  /**
   * Sign data based on identity
   * @param data the data packet to be signed, on return the Signature inside the data packet will be set
   * @param identityName the signing identity name
   */
  void
  signByIdentity(Data& data, const Name& identityName);

  /**
   * sign blob based on certificate name
   * @param blob the blob to be signed
   * @param certificateName the signing certificate name
   * @return the generated signature
   */
  Ptr<Signature>
  signByCertificate(const Blob& blob, const Name& certificateName);
#endif
    
  /**
   * Sign data packet based on the certificate name.
   * Note: the caller must make sure the timestamp in data is correct, for example with 
   * data.getMetaInfo().setTimestampMilliseconds(time(NULL) * 1000.0).
   * @param data The Data object to sign and update its signature.
   * @param certificateName The Name identifying the certificate which identifies the signing key.
   * @param wireFormat The WireFormat for calling encodeData, or WireFormat::getDefaultWireFormat() if omitted.
   */
  void 
  signByCertificate(Data& data, const Name& certificateName, WireFormat& wireFormat = *WireFormat::getDefaultWireFormat());
  
private:
  ptr_lib::shared_ptr<IdentityStorage> identityStorage_;
  ptr_lib::shared_ptr<PrivateKeyStorage> privateKeyStorage_;
};

}

#endif