#pragma once

#include <map>
#include <tuple>

extern const std::map<std::string, int> commands;

std::tuple<std::string, std::string> pars_input(std::string &input);
