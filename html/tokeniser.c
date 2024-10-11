#include <stdint.h>
#include <stdio.h>

#include "tokeniser.h"

#define SWITCH_TO(new_state)                    \
    {                                           \
        state = new_state;                      \
        current_input = (char)next_codepoint(); \
        goto new_state;                         \
    }

#define EMIT_CURRENT_INPUT_AS_CHAR_TOKEN(input)     \
    {                                               \             
        printf("Emmiting a character token");       \
    }                                               \

#define EMIT_EOF_TOKEN 

#define RECONSUME(state)

#define EMIT_REPLACEMENT_CHARACTER_TOKEN(character)

char current_input = 0;
char next_input = 0;
State state = Data;
State r_state = Data;

char buff[1024] = {0};

char next_codepoint()
{
}

void state_machine()
{
    while (1)
    {
        next_input = next_copepoint();
        switch (state)
        {
        Data:
        case Data:
            if (current_input == '&')
            {
                r_state = Data;
                SWITCH_TO(CharacterReference);
            }
            else if (current_input == '<')
            {
                SWITCH_TO(TagOpen);
            }
            else if (current_input == '\0')
            {
                EMIT_CURRENT_INPUT_AS_CHAR_TOKEN(current_input);
            }
            else if (current_input == -1)
            {
                EMIT_EOF_TOKEN;
            }
            else 
            {
                EMIT_CURRENT_INPUT_AS_CHAR_TOKEN(current_input);
            }
            break;

        RCDATA:
        case RCDATA:
            if (current_input == '&')
            {
                r_state = RCDATA;
                SWITCH_TO(CharacterReference);
            }
            else if (current_input == '<')
            {
                SWITCH_TO(RCDATALessThanSign);
            }
            else if (current_input == '\0')
            {
                EMIT_REPLACEMENT_CHARACTER_TOKEN("U+FFFD");
            }
            else if (current_input == -1)
            {
                EMIT_EOF_TOKEN;
            }
            else 
            {
                EMIT_CURRENT_INPUT_AS_CHAR_TOKEN(current_input);
            }
            break;
        
        RAWTEXT:
        case RAWTEXT:
            if (current_input == '<')
            {
                SWITCH_TO(RAWTEXTLessThanSign)
            }
            else if (current_input == '\0')
            {
                EMIT_REPLACEMENT_CHARACTER_TOKEN("U+FFFD");
            }
             else if (current_input == -1)
            {
                EMIT_EOF_TOKEN;
            }
            else 
            {
                EMIT_CURRENT_INPUT_AS_CHAR_TOKEN(current_input);
            }
            break;
            


        RAWTEXTLessThanSign:
        case RAWTEXTLessThanSign:
        
        RCDATALessThanSign:
        case RCDATALessThanSign:    
            
        TagOpen:
        case TagOpen:

        CharacterReference:
        case CharacterReference:
            if (isalnum(current_input))
            {
                RECONSUME(NamedCharacterReference);
            }
            else if (current_input == '#')
            {
                
                SWITCH_TO(NumericCharacterReference)
            }
            
        NumericCharacterReference:
        case NumericCharacterReference:

        NamedCharacterReference:
        case NamedCharacterReference:    
        }
    }
}
