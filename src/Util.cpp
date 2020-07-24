#include "Util.h"

boolean Util::isValidNumber(String str) {
    boolean isNum=false;
    for(byte i=0; i<str.length(); i++)
    {
        isNum = isDigit(str.charAt(i)) || (i == 0 && (str.charAt(i) == '+' || str.charAt(i) == '.' || str.charAt(i) == '-'));
        if(!isNum) {
            return false;
        }
    }
    return isNum;
}