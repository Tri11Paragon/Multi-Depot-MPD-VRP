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
#include <parser.h>
#include <blt/std/string.h>
#include <blt/std/loader.h>
#include <blt/std/utility.h>
#include "blt/std/assert.h"

namespace ga
{
    
    enum class state_t
    {
        EMPTY, WORD, NUMBER, FLOAT
    };
    
    class file_tokenizer
    {
        private:
            blt::size_t index = 0;
            std::string file;
            
            char current()
            {
                return file[index];
            }
            
            char advance()
            {
                return file[index++];
            }
        
        public:
            explicit file_tokenizer(std::string_view file): file(file)
            {}
            
            void skipWS()
            {
                while (hasNext() && std::isspace(current()))
                    advance();
            }
            
            token_t process()
            {
                std::string token_buffer;
                state_t current_state = state_t::EMPTY;
                while (hasNext())
                {
                    char c = advance();
                    
                    if (std::isspace(c))
                    {
                        skipWS();
                        continue;
                    }
                    
                    token_buffer += c;
                    
                    switch (current_state)
                    {
                        case state_t::EMPTY:
                            if (std::isdigit(c))
                                current_state = state_t::NUMBER;
                            else
                                current_state = state_t::WORD;
                            break;
                        case state_t::WORD:
                            break;
                        case state_t::NUMBER:
                            if (c == '.')
                                current_state = state_t::FLOAT;
                            break;
                        case state_t::FLOAT:
                            break;
                    }
                }
                BLT_ASSERT(current_state != state_t::EMPTY && "Failed to parse any word! Parser finished in an empty state!");
                switch (current_state)
                {
                    case state_t::EMPTY:
                    case state_t::WORD:
                        break;
                    case state_t::NUMBER:
                        return std::stol(token_buffer);
                        break;
                    case state_t::FLOAT:
                        return std::stof(token_buffer);
                        break;
                }
                return word_t{token_buffer};
            }
            
            bool hasNext()
            {
                return index < file.size();
            }
    };
    
    ga::problem_parser::problem_parser(std::string_view path)
    {
        file = blt::fs::getFile(path);
        file_tokenizer tokenizer(file);
        
        while (tokenizer.hasNext())
            tokens.push_back(tokenizer.process());
    }
}
