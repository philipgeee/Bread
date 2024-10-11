#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <stdbool.h>
#include <stdio.h>


// Token Types
typedef enum 
{
    DOCTYPE,
    StartTag, 
    EndTag, 
    Comment,
    Character, 
    EndOfFile
} TokenType;

// Doctype
typedef struct 
{
    char *name;
    char *public_id;
    char *system_id;
    bool forceQuirks;
} DOCTYPE;

// Attribute Token
typedef struct 
{
    char *name;
    char *value;
} Attribute;

// Tag token 
typedef struct
{
    // start-tag or end-tag;
    union TagType
    {
        TokenType StartTag;
        TokenType EndTag;
    };
    char *TagName;
    bool selfClosing;
    Attribute *attributes;
} Tag;

//Comment or Character Token
typedef struct
{
    char *data;
} CommentorCharacter;


// function protoypes for token creation
void create_doctype_token();
void create_attribute();
void create_tag_token();
void create_comment_or_character();


#endif