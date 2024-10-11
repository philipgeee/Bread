#ifndef _READER_H_
#define _READER_H_


#include <stdio.h>


// cursor
/*
13.2.3.5 Preprocessing the input stream § p12
68
The input stream consists of the characters pushed into it as the input byte stream is decoded or from the various APIs that
directly manipulate the input stream.
Any occurrences of surrogates are surrogate-in-input-stream p1260 parse errors p1257 . Any occurrences of noncharacters are noncharacter-
in-input-stream p1259 parse errors p1257 and any occurrences of controls other than ASCII whitespace and U+0000 NULL characters are
control-character-in-input-stream p1257 parse errors p1257 .
*/

/*
Before the tokenization p1274 stage, the input stream must be preprocessed by normalizing newlines. Thus, newlines in HTML DOMs are
represented by U+000A LF characters, and there are never any U+000D CR characters in the input to the tokenization p1274 stage.
The next input character is the first character in the input stream p1268 that has not yet been consumed or explicitly ignored by the
requirements in this section. Initially, the next input character p1269 is the first character in the input. The current input character is
the last character to have been consumed.

The insertion point is the position (just before a character or just before the end of the input stream) where content inserted using
document.write() p1137 is actually inserted. The insertion point is relative to the position of the character immediately after it, it is not
an absolute offset into the input stream. Initially, the insertion point is undefined.

The "EOF" character in the tables below is a conceptual character representing the end of the input stream p1268 . If the parser is a
script-created parser p1135 , then the end of the input stream p1268 is reached when an explicit "EOF" character (inserted by the
document.close() p1136 method) is consumed. Otherwise, the "EOF" character is not a real character in the stream, but rather the lack
of any further characters.
*/

/* Consume character -
Implementations must act as if they used the following state machine 
to tokenize HTML. The state machine must start in the data
state . Most states consume a single character, which 
may have various side-effects, and either switches the state 
machine to a new state to reconsume the current input 
character, or switches it to a new state to consume 
the next character , or stays in the same state to 
consume the next character. Some states have more complicated 
behavior and can consume several characters before switching 
to another state. In some cases, the tokenizer state is 
also changed by the tree construction stage.
*/

/*
reconsume char - When a state says to reconsume a 
matched character in a specified state, that means 
to switch to that state, but when it attempts to
consume the next input character p1269 , provide 
it with the current input character p1269 instead.
*/ 




#endif