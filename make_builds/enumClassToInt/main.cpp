#include <iostream>
#include <string>
#include "./MibVariables.hpp"

int main() {
    //test of int casting
    for (auto&& i : OID::oidToEnumVal) {
        int asInt = static_cast<int>(i.second);
        std::cout << asInt << std::endl;
        std::cout << "translated = " << OID::enumToName(i.second) << std::endl;
    }

    std::string trapOid = OID_v(redReleasedNotif);

    OID::Name test = OID::OID_enum(trapOid);
    std::cout << "test= " << static_cast<int>(test) << std::endl;
    switch (test) {
        case OID::Name::redReleasedNotif:
            // Notification of a red service being released
            std::cout << "Red Service Released." << std::endl;
            break;
        default:
            std::cout << "not found" << std::endl;
            // Take no action unless explicitly defined
    }
}
