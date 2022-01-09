#ifndef SNMP_TYPES_HPP
#define SNMP_TYPES_HPP


namespace SnmpTypes {
enum class SecLevel : int {
    NoAuthNoPriv,
    AuthNoPriv,
    AuthAndPriv
};

enum class AuthProtocol : int { NONE, MD5, SHA };

enum class PrivProtocol : int { NONE, AES, DES };

enum class PduType : int { SET, GET };

enum class OidDataType : char {
    INTEGER = 'i',
    OCTET_STR = 's',
    OID = 'o',
    IP_ADD = 'a',
    COUNTER32 = 'c',
    COUNTER64 = 'C',
    GAUGE = 'u',
    UNSIGNED = 'u',
    TIMETICKS = 't'
};
}  // namespace SnmpTypes

#endif
