/*
 * Copyright 2018 Darik Harter
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Parsing.h"
using namespace Parsing;

#include <exception>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    // examples
    try {
        std::vector<std::string> strings;
        strings.push_back("COMMAND\r\n");
        strings.push_back("PASS password\r\n");
        strings.push_back(":old NICK new\r\n");
        strings.push_back("USER one two three :Four Five\r\n");
        strings.push_back(":nickname!username@host PRIVMSG recipient :Hello, world!\r\n");

        for (const auto& string : strings) {
            IRC_message irc_message{string};
            std::cout << string;
            std::cout << "name: " << irc_message.name << '\n';
            std::cout << "user: " << irc_message.user << '\n';
            std::cout << "host: " << irc_message.host << '\n';
            std::cout << "command: " << irc_message.command << '\n';
            std::cout << "params:\n";
            for (const auto& param : irc_message.params) {
                std::cout << "  " << param << '\n';
            }
            std::cout << '\n';
        }
    }
    catch (const std::exception& exception) {
        std::cerr << exception.what() << '\n';
        return 1;
    }

    return 0;
}
