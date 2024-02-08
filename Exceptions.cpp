#include "Exceptions.hpp"

const char* Not_Found::what() const noexcept {
    return "Not Found";
}

const char* Bad_request::what() const noexcept {
    return "Bad Request";
}
const char* Permission_denied::what() const noexcept {
    return "Permission Denied";
}