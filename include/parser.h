/*
 *  <Short Description>
 *  Copyright (C) 2024  Brett Terpstra
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MDMPD_VRP_PARSER_H
#define MDMPD_VRP_PARSER_H

#include <string>
#include <string_view>
#include <variant>
#include <blt/std/types.h>
#include <vector>

namespace ga
{
    
    using word_t = std::string;
    using number_t = blt::i64;
    using floating_t = float;
    
    using token_t = std::variant<word_t, number_t, floating_t>;
    
    class problem_parser
    {
        private:
            std::string file;
            std::vector<token_t> tokens;
        public:
            explicit problem_parser(std::string_view path);
    };
    
}

#endif //MDMPD_VRP_PARSER_H
