#ifndef __MYLDAP_HPP__
#define __MYLDAP_HPP__

#include <ldap.h>
#include "common.hpp"

struct BrutException : public std::exception {
    const char * what () const throw () {
        return "LDAP Protocol Error!";
    }
};

class CheckPwd {
    const char * ldapUrl;
    const char * bindDN;
    LDAP * ldap;
    struct berval cred;
#ifdef DEBUG_TO_FILE
    std::ofstream myfile;
#endif
public:
    CheckPwd(const char * aLdapUrl = LDAP_URL, const char * aBindDN = LDAP_BIND_DN){
        ldapUrl = aLdapUrl;
        bindDN = aBindDN;
#ifdef DEBUG_TO_FILE
        myfile.open ("results.txt");
#endif
    }
    ~CheckPwd(){
#ifdef DEBUG_TO_FILE
        myfile.close();
#endif
    }
    bool checkPwdFunc(const std::string &pwd){
        /* while(true){
            ldap_initialize(&ldap, ldapUrl);
            cred.bv_val = const_cast<char*>(pwd.c_str());
            cred.bv_len = pwd.length();

            int err = ldap_sasl_bind_s(ldap, bindDN, NULL, &cred, NULL, NULL, NULL);

            ldap_unbind_ext_s(ldap, NULL, NULL);
            if (err == LDAP_SUCCESS)
                return true;
            else if (err == LDAP_INVALID_CREDENTIALS)
                return false;
        } */
        
#ifdef DEBUG_TO_FILE
        myfile << pwd << std::endl;
#endif
        if (pwd.compare("++++++") == 0) return true;
        //if (pwd.length() == 4) return true;
        return false;
    }
};

/* bool checkPwdFunc1(std::string pwd) {
    //connect
    LDAP * ldap;
    int err = ldap_initialize(&ldap, LDAP_URL);
    //bind    
    //deprecated
//    err = ldap_simple_bind_s(ldap, LDAP_BIND_DN, pwd.c_str());
    //recomended
    struct berval cred;
    cred.bv_val = const_cast<char*>(pwd.c_str());
    cred.bv_len = strlen(cred.bv_val);
    err = ldap_sasl_bind_s(ldap, LDAP_BIND_DN, NULL, &cred, NULL, NULL, NULL);

    //deprecated
    //ldap_unbind(ldap);
    //recomended
    ldap_unbind_ext_s(ldap, NULL, NULL);
    if (err == LDAP_SUCCESS)
        return true;
    else if (err == LDAP_INVALID_CREDENTIALS)
        return false;
    else throw BrutException();
}
 */
#endif