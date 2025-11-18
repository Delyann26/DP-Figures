#include "Exceptions.h"

invalid_triangle_error::invalid_triangle_error(const std::string& what_arg)
	: std::logic_error(what_arg) {
}

invalid_triangle_error::invalid_triangle_error(const char* what_arg) 
	: std::logic_error(what_arg) {

}
invalid_rectangle_error::invalid_rectangle_error(const std::string& what_arg) 
	: std::logic_error(what_arg) {
}

invalid_rectangle_error::invalid_rectangle_error(const char* what_arg) 
	: std::logic_error(what_arg) {
}

invalid_circle_error::invalid_circle_error(const std::string& what_arg) 
	: std::logic_error(what_arg) {
}

invalid_circle_error::invalid_circle_error(const char* what_arg) 
	: std::logic_error(what_arg) {
}
