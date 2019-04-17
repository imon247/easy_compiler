typedef enum { typeInt, typeChar, typeStr, typeId, typeOpr } nodeEnum;

/* constants */
typedef struct {
    int value;                  /* value of constant */
} intNodeType;

typedef struct{
    char value;
}charNodeType;

typedef struct{
    int *value;
}strNodeType;

/* identifiers */
typedef struct {
    int i;                      /* subscript to sym array */
} idNodeType;

/* operators */
typedef struct {
    int oper;                   /* operator */
    int nops;                   /* number of operands */
    struct nodeTypeTag *op[1];  /* operands (expandable) */
} oprNodeType;

typedef struct nodeTypeTag {
    nodeEnum type;              /* type of node */

    /* union must be last entry in nodeType */
    /* because operNodeType may dynamically increase */
    union {
        // conNodeType con;        /* constants */
        intNodeType Int;
        charNodeType Char;
        idNodeType id;          /* identifiers */
        oprNodeType opr;        /* operators */
    };
} nodeType;

extern int sym[26];
