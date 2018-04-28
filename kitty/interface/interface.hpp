#pragma once

#include <kitty/stl_impl.hpp>
#include <string>

#include <kitty/interpreter/interpreter.hpp>
#include <kitty/parser/parser.hpp>
#include <kitty/tokenizer/tokenizer.hpp>

namespace kitty {

namespace interface {

/*!
    @brief  Class that handles interactions between the user(programmer) 
            and the rest of the program.
*/
class Interface {

public:
    /*!
        @brief  Prints the welcome screen for the Kitty interpreter,
                as well as other information.
    */
    void print_welcome() {
        Serial.begin(115200);
        Serial.println(F(R"(
            _                        
            \`*-.                    
             )  _`-.                 
            .  : \  .                
            : ^   '  \               
            ; *  _.   `*-._          
            `-.-'          `-.       
              ;       `       `.     
              :.       .        \    
             ,  \   ;  :   .-'   .   
            .  , `..;  ;  '      :   _.--.
           '  .     |  , ;       ;.-'_.-'`
        .*' `      : :`-:     _.`-'`
        `*-*      .*' ; .*`- +' 
     (bug)        `*-*  `*-*'        
        )"));
        Serial.println(F("Kitty 0.2.0 for Arduino (2017, 2018)"));
        Serial.println(F("Mattheus Lee, mattheus.lee@gmail.com"));
        Serial.println(F(""));
    }

    /*!
        @brief  Prints the basic prompt for the user to enter a command.
    */
    void print_prompt() {
        Serial.print(F(">>> "));        
    }

    /*!
        @brief  Prints the basic prompt for the user to enter a command,
                with a prefix string to be printed before the prompt.
        
        @param  prefix
                An additional string to be printed before the rest of the prompt.
    */
    void print_prompt(std::string const & prefix) {
        if (prefix.size() > 0) {
            Serial.print(prefix.c_str());
        }
        print_prompt();
    }

    /*!
        @brief  Reads in a command string from the Serial interface until the
                newline character is read.
                Blocks until a complete command string is read.
        
        @return The command string read from the Serial interface.
    */
    std::string get_next_command() {
        std::string line;
        while (true) {
            if (Serial.available()) {
                char c = Serial.read();
                if (c == '\n') { // Finished reading one complete line of input
                    break;
                }
                line += c;
            }
        }
        if (line[line.size() - 1] == ' ') {
            line.erase(line.size() - 1);
        }
        return line;
    }

    /*!
        @brief  Echoes a command back to the user through the Serial interface.
        
        @param  command
                The command string to be echoed to the user.
    */
    void echo_command(std::string const & command) {
        Serial.println(command.c_str());
    }

private:

};

} // namespace interface

} // namespace kitty
